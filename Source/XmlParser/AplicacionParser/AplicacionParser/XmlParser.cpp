#include "StdAfx.h"
#include "Stack.h"
#include "XmlParser.h"
#include "XmlAttribute.h"
#include "Tokenizer.h"
#include "Logger.h"
#include <string>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <fstream>

using namespace std;

XmlParser::XmlParser(void) : lastIndex(0), lastJumpAmount(0)
{
	this->validTags[0] = "escenario";
	this->validTags[1] = "grilla";
	this->validTags[2] = "obstaculo";
	this->validTags[3] = "camino";
	this->validTags[4] = "bonus";
	this->validTags[5] = "tiposbonus";
	this->validTags[6] = "tipobonus";
	this->validTags[7] = "tiposobstaculos";
	this->validTags[8] = "tipoobstaculo";

	this->lineNumber=1; //Las líneas del archivo comienzan en 1.
	this->log=Logger::getInstance();
	this->noChildren=false;
	this->hasErrors=false;
	this->hasAttributeErrors = false;
	this->isOpeningLine = true;
	this->fileOrig=" ";
	this->lastPos=0;
}

XmlParser::~XmlParser(void)
{
	if (this->xmlFile.is_open())
		this->xmlFile.close();
	this->log->closeLog();
	/*remove(AUX);
	remove(PARSING);*/
}
void XmlParser::openFile(std::string filename){

	
	//if (!this->xmlFile.is_open()){
	//	this->xmlFile.open(filename.c_str(), ios::in | ios::binary);
	//	this->lineNumber=1;
	//}

	if (!this->xmlFile.is_open() && this->preParseFile(filename)){
		this->xmlFile.open(PARSING, ios::in | ios::binary);
		this->lineNumber=1;
	}
	//remove(AUX);
	this->parsingFileName=filename;

	
}

bool XmlParser::preParseFile(std::string filename){
	
	std::string lineToRead;
	std::string workLine;
	std::string workAux;
	std::ifstream xmlAuxFile;
	std::ifstream xmlAux;

	if (filename.compare(this->parsingFileName) == 0) //Si ya lo indente como quería no hago más nada.
		return true;
	
	if (!xmlAuxFile.is_open()){
		xmlAuxFile.open(filename.c_str(), ios::in | ios::binary);
		if (xmlAuxFile.is_open() == false)
			return false;
	}
	while (getline( xmlAuxFile, lineToRead )){
		workLine+=lineToRead;
		lineToRead.erase(std::remove(lineToRead.begin(), lineToRead.end(), '\n'), lineToRead.end());
	    lineToRead.erase(std::remove(lineToRead.begin(), lineToRead.end(), '\r'), lineToRead.end());
		lineToRead.append("&");
		this->fileOrig+=lineToRead;

	}

	this->fileOrig.append("\n");
	xmlAuxFile.close();

	workLine.erase(std::remove(workLine.begin(), workLine.end(), '\n'), workLine.end());
	workLine.erase(std::remove(workLine.begin(), workLine.end(), '\r'), workLine.end());
	replaceAll(workLine, "<", "\n<");
	replaceAll(workLine, ">", ">\n");
	
	ofstream file;
	file.open(AUX, ios::binary|ios::out);
	file<<workLine;
	file.close();
	return removeBlankLines();

}

bool XmlParser::removeBlankLines(void){
	ifstream initialFile(AUX, ios::in|ios::binary);	
	ofstream outputFile(PARSING, ios::out|ios::binary);	
	string lineToRead;
	string test;

	if ( !outputFile.is_open() || !initialFile.is_open() ) {
		return false;
	}

	while (getline( initialFile, lineToRead )){
		trim(lineToRead,' ');
		trim(lineToRead,'\n');
		trim(lineToRead,'\t');
		if (lineToRead.length() > 0){
			outputFile<<lineToRead<<"\n";
		}
	}

	initialFile.close();	
	outputFile.close();	
	return true;

}

void XmlParser::closeFile(void){
	if (this->xmlFile.is_open()){
		this->xmlFile.close();
		remove( AUX );
	}
	this->lineNumber=0;

}


//Dada un string a buscar, devuelve en que linea esta del archivo original.
long XmlParser::getOrigLineNumber(string search){

	string stringAux;
	int longitud=search.find_first_of(' ');
	int len=(longitud > 10)? 10 : longitud;
	string pattern=search.substr(0,len );
	size_t pos=this->fileOrig.find(pattern, this->lastIndex + 1);
	
	long saltosDeLinea=1;
	if (pos != string::npos){
		for (int i=this->lastIndex; i < pos; i++){
			if (this->fileOrig[i] == '&')
				saltosDeLinea++;
		}
		this->lastIndex = pos;	
	}

	this->lastJumpAmount += saltosDeLinea;
	return this->lastJumpAmount--;
}


//Si el archivo no esta abierto o se acabaron las lineas, devuelve false.

bool  XmlParser::getXmlLine(void){
	
	string strMine;
	string logMessage;
	//Para encontrar < > y /> en el string
	size_t foundLT,foundGT,closeGT;
	std::stringstream out;
	this->tagAtt.clear();
	this->hasErrors = false;
	this->hasAttributeErrors = false;
	bool resp;

	if ( (resp= this->xmlFile.is_open()) && getline( this->xmlFile, this->lineRead ))
	{
		//this->lineNumber++;
		this->lineNumber=this->getOrigLineNumber(this->lineRead);
		this->trim(this->lineRead, ' ');
		strMine=this->lineRead;
	
		closeGT=strMine.find("/>");
		//Para ver si es tag de cierre en la misma linea.
		this->noChildren=(closeGT != string::npos);
		
		//Si tuviesen,removemos el < y > (el primero y el ultimo, el resto que pueda aparecer no me interesa). 
		//Si no tienen muestro advertencia.
		foundLT=strMine.find_first_of("<");
		foundGT=strMine.find_last_of(">");
		
		if ( (foundGT == string::npos)){

			logMessage= "Falta caracter > en linea: ";
			out << logMessage;
			out << this->lineNumber;
			out << endl;
			this->log->logWarning(out.str().c_str());
			this->hasErrors=true;
		}
		else{
			strMine=strMine.erase(foundGT,1);
		}

		if ( (foundLT == string::npos)){
			this->lineNumber=this->getOrigLineNumber(strMine.substr(1,strMine.length()));
			logMessage="Falta caracter < en linea: ";
			out << logMessage;
			out << this->lineNumber;
			out << endl;
			this->log->logWarning(out.str().c_str());
			this->hasErrors=true;
		}else{
			strMine=strMine.erase(foundLT,1);
		}
		this->lineRead=strMine;
		this->parseLine();
	}
	else
		return false;
	out.flush();
	return true;
}
string XmlParser::getLineRead(void){
	return this->lineRead;
}
long XmlParser::getLineNumber(void){
	return this->lineNumber;
}
string XmlParser::getLineTagName(){
	return this->tagName;
	}
List<string> XmlParser::getLineTagAttributes(void){
	return this->tagAtt;
}

void XmlParser::parseLine(void)
{
	string line;
	line = this->getLineRead();
	if (line[0] == '/')
	{
		this->isOpeningLine = false;
		this->parseClosingLine(line);
	}
	else
	{
		this->isOpeningLine = true;
		this->parseOpeningLine(line);
	}
}
void XmlParser::parseAttribute(string myLine){

	size_t foundOpeningQuotes;
	size_t foundClosingQuotes;
	stringstream out;
	string logMessage;

	Tokenizer miTok(myLine,"=/");
	string attName;
	string attValue;

	while (miTok.NextToken()){
		attName=miTok.GetToken();
		//cout<<"attName: " << attName <<endl;
		miTok.NextToken();
		attValue=miTok.GetToken();
		this->preParseString(attValue,'&',' ');
		//cout<<"attValue: " << attValue <<endl;
		
		//Valido que tenga comillas los atributos, sino hago log de warning y sigo.
		foundOpeningQuotes=attValue.find_first_of('"');
		foundClosingQuotes=attValue.find_last_of('"');

		if (   (foundOpeningQuotes== string::npos) 
			|| (foundClosingQuotes== string::npos) 
			|| (foundOpeningQuotes == foundClosingQuotes) )
		{
			logMessage= "Faltan comillas del atributo en linea: ";
			out << logMessage;
			out << this->lineNumber;
			out << endl;
			this->log->logWarning(out.str().c_str());
			out.flush();
			this->hasErrors=true;
			this->hasAttributeErrors = true;
		}

		this->tagAtt.add(attName);
		this->tagAtt.add(attValue);

	}
		
}

//Reemplazo dentro de las comillas, los char1 por char2.
string& XmlParser::preParseString(string& context, char char1, char char2 )
{
	string::iterator It = context.begin();
	bool insideQuotes=false;

    while ( It != context.end() )
    {
		if ( *It == '"'){
			if (insideQuotes == false)
				insideQuotes=true;
			else
				insideQuotes=false;
		}
		if (*It == char1 && insideQuotes == true){
			*It = char2;
		}
    	*It++;
    }
	//cout << "Context: "<<context<< endl;
    return context;
}

//Remuevo espacios antes del comienzo del string y luego del comienzo del string
void XmlParser::trim(string& str, char c)
{
  string::size_type pos = str.find_last_not_of(c);
  if(pos != string::npos) {
    str.erase(pos + 1);
    pos = str.find_first_not_of(c);
    if(pos != string::npos) str.erase(0, pos);
  }
  else str.erase(str.begin(), str.end());
}

bool XmlParser::isFileOpen(void){
	return this->xmlFile.is_open();
}

bool  XmlParser::tagHasNoChildren(void){
	return this->noChildren;
}

bool XmlParser::lineHasErrors(void){
	return this->hasErrors;
}

XmlElement XmlParser::parse()
{
	Stack<XmlElement> previousParents;
	XmlElement currentParent;
	XmlElement currentElement;
	bool parentSet = false;

	while (this->getXmlLine())
	{
		string name = this->getLineTagName();
		
		//to lower
		std::transform(name.begin(), name.end(), name.begin(), ::tolower);

		if (this->isOpeningLine)
		{
			XmlElement currentElement = XmlElement(name, this->lineNumber, 0);
			if (!this->hasAttributeErrors)
			{
				List<string> attributes = this->getLineTagAttributes();

				for (size_t i = 0; i < attributes.length(); i = i + 2)
				{
					string key = attributes.at(i);
					
					//to lower
					std::transform(key.begin(), key.end(), key.begin(), ::tolower);
					
					string value = attributes.at(i+1);
				
					//remove ""
					trim(value, '"');
				
					XmlAttribute att(key, value);
					currentElement.addAttribute(att);
				}
			}
			// si el tag no cierra en la misma linea apilo al padre anterior y currentParent = currentElement
			if (this->tagHasNoChildren())
			{
				currentElement.setEndLine(this->lineNumber);				
				if (parentSet)
				{
					if (this->isValidTagName(name))
					{
						currentParent.addChild(currentElement);
					}
					else
					{
						stringstream msg;
						msg << "Nombre de tag: " << name << " no reconocido. Linea: " << currentParent.getStartLine();
						this->log->logWarning(msg.str());
					}
				}
			}
			else
			{
				if (parentSet)
				{
					previousParents.push(currentParent);
				}
				currentParent = currentElement;
				parentSet = true;
			}
		}
		else
		{
			//loop in case there are incorrect elements closing
			while (name != currentParent.getName() && previousParents.count() != 0)
			{
				//TODO: loggear que no se cerro bien el tag
				stringstream msg;
				msg << "El tag: " << currentParent.getName() << " no se cerro correctamente. Linea apertura: " << currentParent.getStartLine() << ". Linea error: " << this->lineNumber;
				this->log->logWarning(msg.str());
				
				XmlElement previousParent = previousParents.pop();
				previousParent.addChild(currentParent);
				currentParent = previousParent;
			}

			if (name == currentParent.getName())
			{
				if (previousParents.count() != 0)
				{
					XmlElement previousParent = previousParents.pop();
					currentParent.setEndLine(this->lineNumber);
					if (this->isValidTagName(name))
					{
						previousParent.addChild(currentParent);
					}
					else
					{
						stringstream msg;
						msg << "Nombre de tag: " << name << " no reconocido. Linea: " << currentParent.getStartLine();
						this->log->logWarning(msg.str());
					}
					currentParent = previousParent;
				}
				else
				{
					currentParent.setEndLine(lineNumber);
				}
			}
		}
	}
	return currentParent;
}

void XmlParser::parseOpeningLine(string line)
{
	string token;
	size_t found;
	stringstream out;
	string logMessage;
	string invalidTag="InvalidTagName_";

	
	line=this->preParseString(line,' ', '&');
	Tokenizer miTokenizer(line);
	while (miTokenizer.NextToken()){
		token=miTokenizer.GetToken();
		//cout<<"Token: " << token <<endl;
		found = token.find("=");
		if (found!=string::npos){
			
			if (this->tagName.length() > 0) //Si ya levante el nombre entonces sigo con los atributos.
				this->parseAttribute(token);
			else
			{ //si no le doy un nombre y hago el log del warning
				logMessage= "Falta nombre del tag (por defecto: InvalidTagName) en linea: ";
				out << logMessage;
				out << this->lineNumber;
				out << endl;
				this->log->logWarning(out.str().c_str());
				out.flush();
				out << invalidTag;
				out << this->lineNumber;
				this->tagName=out.str();
				this->hasErrors=true;
			}
		}
		else
			this->tagName=token;
	}
}

void XmlParser::parseClosingLine(std::string line)
{
	trim(line,'\n');
	size_t len = line.length();
	size_t nameInitialPos = line.find_first_of("/");
	if (line.at(len - 1) == '>')
	{
		this->tagName = line.substr(nameInitialPos + 1, len - (nameInitialPos + 1));
	}
	else
	{
		this->tagName = line.substr(nameInitialPos + 1, len - (nameInitialPos));
	}
}

bool XmlParser::getIsOpeningLine() const
{
	return this->isOpeningLine;
}

bool XmlParser::isValidTagName(std::string n)
{
	//string to lower
	std::transform(n.begin(), n.end(), n.begin(), ::tolower);

	size_t len = sizeof(this->validTags) / sizeof(*this->validTags);
	for (size_t i = 0; i < len; i++)
	{
		if (n == this->validTags[i])
		{
			return true;
		}
	}

	return false;
}

string& XmlParser::replaceAll(string& context, const string& from,const string& to) {
	size_t lookHere = 0;
	size_t foundHere;
	while((foundHere = context.find(from, lookHere)) != string::npos) {
		context.replace(foundHere, from.size(), to);
		lookHere = foundHere + to.size();
	}
	return context;
} 



