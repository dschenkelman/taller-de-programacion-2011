#include "StdAfx.h"
#include "xmlTagUtils.h"
#include "Tokenizer.h"


xmlTagUtils::xmlTagUtils(void)
{
}

xmlTagUtils::~xmlTagUtils(void)
{
}

//Recibe un tag XML (supuestamente bien formado y validado)
//y devuelve un mapa con sus valores y atributos. 
void xmlTagUtils::parseElementAttribute(string element,  std::map<std::string, std::string> &  myMap ){
  
	Tokenizer s(element);
	s.NextToken(); //El nombre del tag se descarta
	string key;
	string value;
	while (s.NextToken())
	{
		key=s.GetToken();
		cout<<"Clave: "+ key;
		s.NextToken();
		value=s.GetToken();
		cout<<" Valor: "+ value;
		cout<<endl;
		myMap.insert(pair <string, string> (key,value));
	}

	return;
}
