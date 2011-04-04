#include "stdafx.h"
#include "XMLParser.h"


/* 
 * Defino los metodos de la clase 
 */
string XMLParser::parsear(string tag)
{
	// valor a retornar
	string valor = "";

	// abro el archivo
	pFile = fopen ("mapa.xml" , "r");

	if (pFile == NULL) perror ("Error en la apertura");
	else
	{
		size_t posIni, posFin;
		string tagApertura = "<" + tag + ">";
		string tagCierre = "</" + tag + ">";

		while( fgets (buffer , 100 , pFile) )
		{
			string sbuffer = string(buffer);
			posIni=sbuffer.find( tagApertura );
			if(posIni != string::npos)
			{
				posFin=sbuffer.find(tagCierre, posIni+1);
				if(posFin != string::npos)
				{
					valor = sbuffer.substr(posIni+tagApertura.length(), posFin-1-tagCierre.length());
				}
			}
		}
		fclose (pFile);
	}

	return valor;
}