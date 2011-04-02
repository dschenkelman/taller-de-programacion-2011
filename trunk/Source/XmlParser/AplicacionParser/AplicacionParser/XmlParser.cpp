#include "StdAfx.h"
#include "XmlParser.h"
#include "Tokenizer.h"
#include "Logger.h"
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

XmlParser::XmlParser(void)
{
	this->lineNumber=1; //Las líneas del archivo comienzan en 1.
	this->log=Logger::getInstance();
	this->noChildren=false;
	this->hasErrors=false;
}

XmlParser::~XmlParser(void)
{
	if (this->xmlFile.is_open())
		this->xmlFile.close();
	this->log->closeLog();
}
void XmlParser::openFile(std::string filename){

	if (!this->xmlFile.is_open()){
		this->xmlFile.open(filename.c_str(), ios::in | ios::binary);
	}
}
void XmlParser::closeFile(void){
	if (this->xmlFile.is_open())
		this->xmlFile.close();
	this->lineNumber=0;
}

//Si el archivo no esta abierto o se acabaron las lineas, devuelve false.

bool  XmlParser::getXmlLine(void){
	
	string strMine;
	string logMessage;
	//Para encontrar < > y /> en el string
	size_t foundLT,foundGT,closeGT;
	std::stringstream out;
		
	if (this->xmlFile.is_open() && getline( this->xmlFile, this->lineRead ))
	{
		this->lineNumber++;
		this->trim(this->lineRead);
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

void XmlParser::parseLine(void){

	string token;
	string line;
	size_t found;
	stringstream out;
	string logMessage;
	string invalidTag="InvalidTagName_";
	
	line=this->getLineRead();
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
void XmlParser::parseAttribute(string myLine){

	size_t foundOpeningQuotes;
	size_t foundClosingQuotes;
	stringstream out;
	string logMessage;

	Tokenizer miTok(myLine,"=");
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
		}

		this->getLineTagAttributes().add(attName);
		this->getLineTagAttributes().add(attValue);

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
void XmlParser::trim(string& str)
{
  string::size_type pos = str.find_last_not_of(' ');
  if(pos != string::npos) {
    str.erase(pos + 1);
    pos = str.find_first_not_of(' ');
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
