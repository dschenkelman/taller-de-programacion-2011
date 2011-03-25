#include "StdAfx.h"
#include "XmlParser.h"

using namespace std;

XmlParser::XmlParser(void)
{
	this->lineNumber=1; //Las líneas del archivo comienzan en 1
	this->lineRead=NULL;
}

XmlParser::~XmlParser(void)
{
	this->file.close();
}
void XmlParser::openFile(char *filename){

	if (!this->file.is_open()){
		this->file.open(filename, ios::in);
	}
}
void XmlParser::closeFile(void){
	if (this->file.is_open()){
		this->file.close();	
	}
}
void  XmlParser::getXmlLine(void){
	if (this->file.is_open()){
		getline(this->file,this->line);
	}
	if (line.size()> 0)
		this->lineRead=(char *)line.c_str();
	return;
}
char * XmlParser::getLineRead(void){
	return this->lineRead;
}
long XmlParser::getLineNumber(void){
	return this->lineNumber;
}
char * XmlParser::getLineTagName(){
	return "NADA";
	}
char * XmlParser::getLineTagAttributes(char * tagName){
	return "NADA";
}