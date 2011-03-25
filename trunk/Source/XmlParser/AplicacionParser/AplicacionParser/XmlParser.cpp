#include "StdAfx.h"
#include "XmlParser.h"

using namespace std;

XmlParser::XmlParser(void)
{
	this->lineNumber=1; //Las líneas del archivo comienzan en 1
}

XmlParser::~XmlParser(void)
{
	this->file.close();
}
void XmlParser::openFile(char *filename){

	if (!this->file.is_open()){
		this->file.open(filename, ios::in|ios::binary);
	}
}
void XmlParser::closeFile(void){
	if (this->file.is_open()){
		this->file.close();	
	}
}
char * XmlParser::getNextTagName(){
	return "NADA";
	}
char * XmlParser::getTagAttributes(char * tagName){
	return "NADA";
}