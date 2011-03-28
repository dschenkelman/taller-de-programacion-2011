#include "StdAfx.h"
#include "XmlParser.h"
#include <string.h>
#include <stdio.h>

using namespace std;

XmlParser::XmlParser(void)
{
	this->lineNumber=0; //Las líneas del archivo comienzan en 1 pero inicialmente no leyo nada.
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

//Si el archivo no esta abierto o se acabaron las lineas, devuelve false.

bool  XmlParser::getXmlLine(void){
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
			else
				return false;
		}
	    //Ahora removemos el < y >
		this->lineRead[strlen(this->lineRead) -2]=0;//Saco el >
		strcpy_s(this->lineRead,(strstr(this->lineRead,"<")+1)); //Saco el <
	}
	else
		return false;
	return true;
}
char * XmlParser::getLineRead(void){
	return this->lineRead;
}
long XmlParser::getLineNumber(void){
	return this->lineNumber;
}
String XmlParser::getLineTagName(){
	return this->tagName;
	}
List<String> XmlParser::getLineTagAttributes(void){
	return this->tagAtt;
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
		//cout<<"TOKEN LEIDO: "<<token<<endl;
		if (strstr(token,"=") != NULL) //Si tiene "=" debe ser un atributo.
			this->parseAttribute(token);
		else
		{
			String tag(token);
			this->tagName=tag; //Es el nombre del TAG
		}
		token=strtok_s(NULL," \t\n",&nextToken);
	}

}
void XmlParser::parseAttribute(char * token){

	char attributes[LINE_SIZE]={0};
	strcpy_s(attributes,token);
	char *attToken, *attNextToken=NULL;

	String key;
	String value;

	attToken=strtok_s(attributes,"=",&attNextToken);
	while (attToken != NULL){
		//cout<<"KEY LEIDO: "<<attToken<<endl;
		String key(attToken);
		this->tagAtt.add(key);
		attToken=strtok_s(NULL," \t\n",&attNextToken);
		//cout<<"Valor LEIDO: "<<attToken<<endl;
		String value(attToken);
		this->tagAtt.add(value);
		attToken=strtok_s(NULL," \t\n",&attNextToken);

	}



}