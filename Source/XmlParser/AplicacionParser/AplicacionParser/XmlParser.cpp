#include "StdAfx.h"
#include "XmlParser.h"
#include <string.h>
#include <stdio.h>

using namespace std;

XmlParser::XmlParser(void)
{
	this->lineNumber=0; //Las líneas del archivo comienzan en 1 pero inicialmente no leí nada.
	memset(this->lineRead,0, (sizeof(this->lineRead))/(sizeof(this->lineRead[0])) ); //Inicializo el string
	this->xmlFile=NULL;
}

XmlParser::~XmlParser(void)
{
	if (this->xmlFile != NULL)
		fclose(this->xmlFile);
}
void XmlParser::openFile(char *filename){

	if (this->xmlFile == NULL){
		fopen_s(&(this->xmlFile), filename, "rb");
	}
}
void XmlParser::closeFile(void){
	fclose(this->xmlFile);
	memset(this->lineRead,0, (sizeof(this->lineRead))/(sizeof(this->lineRead[0]) ) );
	this->lineNumber=0;
}
void  XmlParser::getXmlLine(void){
	if (this->isFileOpen() && (fgets(this->lineRead,LINE_SIZE,this->xmlFile) != NULL))
	{
		this->lineRead[strlen(this->lineRead)-1]=0; //Saco el \n por el 0.
		this->lineNumber++;
		if (strstr(this->lineRead,"<?") != NULL)
		{ //Es la primer linea del xml, la obviamos y leemos la siguiente.
			if (fgets(this->lineRead,LINE_SIZE,this->xmlFile) != NULL)
			{
				this->lineRead[strlen(this->lineRead)-1]=0;
				this->lineNumber++;
			}
		}
	    //Ahora removemos el < y >
		this->lineRead[strlen(this->lineRead) -2]=0;//Saco el >
		strcpy_s(this->lineRead,(strstr(this->lineRead,"<")+1)); //Saco el <
	}	
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
bool XmlParser::isFileOpen(void){
	return (this->xmlFile != NULL);
}
void XmlParser::parseLine(void){

	char *token, *nextToken;
	char test[LINE_SIZE]={0};

	strcpy_s(test,this->lineRead);

	token=strtok_s(test," \t\n",&nextToken);
	while (token != NULL){
		cout<<"TOKEN LEIDO: "<<token<<endl;
		if (strstr(token,"=") != NULL) //Si tiene "=" debe ser un atributo.
			this->parseAttribute(token);
		token=strtok_s(NULL," \t\n",&nextToken);
	}

}
void XmlParser::parseAttribute(char * token){

	char attributes[LINE_SIZE]={0};
	strcpy_s(attributes,token);
	char *attToken, *attNextToken=NULL;

	attToken=strtok_s(attributes,"=",&attNextToken);
	while (attToken != NULL){
		cout<<"ATTTOKEN LEIDO: "<<attToken<<endl;
		attToken=strtok_s(NULL," \t\n",&attNextToken);
	}



}