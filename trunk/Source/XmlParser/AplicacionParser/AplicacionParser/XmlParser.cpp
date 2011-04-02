#include "StdAfx.h"
#include "XmlParser.h"
#include "Tokenizer.h"
#include <string.h>
#include <stdio.h>

using namespace std;

XmlParser::XmlParser(void)
{
	this->lineNumber=1; //Las líneas del archivo comienzan en 1.
}

XmlParser::~XmlParser(void)
{
	if (this->xmlFile.is_open())
		this->xmlFile.close();
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

	if (this->xmlFile.is_open() && getline( this->xmlFile, this->lineRead ))
	{
		this->lineNumber++;
		//Ahora removemos el < y > y los espacios al principio y al final
		this->trim(this->lineRead);
		strMine=this->lineRead;
		string::size_type mayor = strMine.find( ">", 0 );
		strMine=strMine.erase(mayor,1);
		string::size_type menor = strMine.find( "<", 0 );
		strMine=strMine.erase(menor,1);
		this->lineRead=strMine;
		this->parseLine();
	}
	else
		return false;
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
	line=this->getLineRead();
	line=this->preParseString(line,' ', '&');
	Tokenizer miTokenizer(line);
	while (miTokenizer.NextToken()){
		token=miTokenizer.GetToken();
		//cout<<"Token: " << token <<endl;
		found = token.find("=");
		if (found!=string::npos)
			this->parseAttribute(token);
		else
			this->tagName=token;
	}
}
void XmlParser::parseAttribute(string myLine){

	Tokenizer miTok(myLine,"=");
	string attName;
	string attValue;

	while (miTok.NextToken()){
		attName=miTok.GetToken();
		//cout<<"attName: " << attName <<endl;
		attValue=miTok.GetToken();
		this->preParseString(attValue,'&',' ');
		//cout<<"attValue: " << attValue <<endl;
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
