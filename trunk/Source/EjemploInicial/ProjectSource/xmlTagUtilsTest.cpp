#include "StdAfx.h"
#include "xmlTagUtils.h"
#include "xmlTagUtilsTest.h"

xmlTagUtilsTest::xmlTagUtilsTest(void)
{
}

xmlTagUtilsTest::~xmlTagUtilsTest(void)
{
}

void xmlTagUtilsTest :: run (void)
{
	xmlTagUtils miTag;
	string element="<note day=""10"" month=""01"" year=""2008"" to=""Tove"" from=""Jani"" heading=""Reminder"" body=""Don't forget me this weekend!"">";
	map <string, string>::iterator m1_pIter, m2_pIter;
	map <string, string> mapa;
	miTag.parseElementAttribute(element,mapa);
	cout << "El mapa resultante (clave, valor)"<<endl;
	for ( m1_pIter = mapa.begin( ); m1_pIter != mapa.end( ); m1_pIter++ ){
		cout << "Clave: " << m1_pIter -> first;
		cout << " Valor: " << m1_pIter -> second;
		cout<<endl;
	}
	cout << "FIN MAPA." << endl;

 

}
