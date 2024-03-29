#include "StdAfx.h"
//#include "CaminoTests.h"
//using namespace std;
//
////useful to detect memory leaks
//#define _CRTDBG_MAP_ALLOC
//#include <stdlib.h>
//#include <crtdbg.h>
//
//CaminoTests::CaminoTests(void)
//{
//}
//
//CaminoTests::~CaminoTests(void)
//{
//}
//
//void CaminoTests::printLeaks(int leaks)
//{
//	std::cout << "Camino Tests: Hubo " << leaks << " memory leaks." << endl << endl;
//}
//
//void CaminoTests::run(void)
//{
//	printResult("testAtributoFilaConValorNegativoLoggeaError", testAtributoFilaConValorNegativoLoggeaError());
//	printResult("testAtributoColumnaConValorNegativoLoggeaError", testAtributoColumnaConValorNegativoLoggeaError());
//	printResult("testAtributoFilaCorrectoGuardaCorrectamente", testAtributoFilaCorrectoGuardaCorrectamente());
//	printResult("testAtributoColumnaCorrectoGuardaCorrectamente",testAtributoColumnaCorrectoGuardaCorrectamente());
//	printResult("testCaminoConBonusCreaCorrectamente", testCaminoConBonusCreaCorrectamente());
//	printResult("testCaminoConDosBonusTiraExcepcion", testCaminoConDosBonusTiraExcepcion());
//	printResult("testNonValidAttributeMakesHasErrorTrue", testNonValidAttributeMakesHasErrorTrue());
//
//	int leaks = _CrtDumpMemoryLeaks();
//	printLeaks(leaks);
//}
//
//void CaminoTests::printResult(std::string testName, bool result)
//{
//	std::cout << (testName.append(result ? ": Passed\n" : ": Failed!!!\n"));
//}
//
//bool CaminoTests::testAtributoFilaConValorNegativoLoggeaError()
//{
//	XmlElement elemento("Nombre", 1, 100);
//	XmlAttribute atributo("fila", "-5");
//	elemento.addAttribute(atributo);
//
//	// tamanio del archivo antes
//	size_t tamanioAntes = Logger::getInstance()->obtenerTamanioArchivo();
//	
//	Camino camino(elemento);	
//
//	// tamanio despues
//	size_t tamanioDespues = Logger::getInstance()->obtenerTamanioArchivo();
//
//	Logger::getInstance()->closeLog();
//	return (tamanioAntes<tamanioDespues)?true:false;
//}
//
//bool CaminoTests::testAtributoColumnaConValorNegativoLoggeaError()
//{
//	XmlElement elemento("Nombre", 1, 100);
//	XmlAttribute atributo("columna", "-9");
//	elemento.addAttribute(atributo);
//
//	// tamanio del archivo antes
//	size_t tamanioAntes = Logger::getInstance()->obtenerTamanioArchivo();
//	
//	// creo al camino
//	Camino camino(elemento);	
//
//	// tamanio despues
//	size_t tamanioDespues = Logger::getInstance()->obtenerTamanioArchivo();
//
//	// finalizo al logger
//	Logger::getInstance()->closeLog();
//
//	return (tamanioAntes<tamanioDespues)?true:false;
//}
//
//bool CaminoTests::testAtributoFilaCorrectoGuardaCorrectamente()
//{
//	XmlElement elemento("Nombre", 1, 100);
//	XmlAttribute atributo("fila", "9");
//	elemento.addAttribute(atributo);
//
//	Camino camino(elemento);
//
//	int fila = camino.getFila();
//	
//	Logger::getInstance()->closeLog();
//	if (fila != 9)
//	{
//		return false;
//	}
//
//	return true;
//}
//
//bool CaminoTests::testAtributoColumnaCorrectoGuardaCorrectamente()
//{
//	XmlElement elemento("Nombre", 1, 100);
//	XmlAttribute atributo("columna", "13");
//	elemento.addAttribute(atributo);
//
//	Camino camino(elemento);
//
//	int columna = camino.getColumna();
//	
//	Logger::getInstance()->closeLog();
//	if (columna != 13)
//	{
//		return false;
//	}
//
//	return true;
//}
//
//bool CaminoTests::testCaminoConBonusCreaCorrectamente()
//{
//	XmlElement xmlElement("camino", 1, 100);
//	XmlAttribute atributoFila("fila", "4");
//	XmlAttribute atributoColumna("columna", "8");
//	xmlElement.addAttribute(atributoFila);
//	xmlElement.addAttribute(atributoColumna);
//
//	XmlElement xmlElementBonus("bonus", 1, 20);
//	XmlAttribute atributoTipo("tipo", "uva");
//	xmlElementBonus.addAttribute(atributoTipo);
//
//	xmlElement.addChild(xmlElementBonus);
//
//	Camino camino(xmlElement);
//	
//	bool eval = true;
//	if(camino.getFila() != 4)
//	{
//		eval = false;
//	}
//
//	if(camino.getColumna() != 8)
//	{
//		eval = false;
//	}
//
//	if(camino.getBonus().getTipo() != "uva")
//	{
//		eval = false;
//	}
//	
//	Logger::getInstance()->closeLog();	
//	return eval;
//}
//
//bool CaminoTests::testCaminoConDosBonusTiraExcepcion()
//{
//	XmlElement xmlElement("camino", 1, 100);
//	XmlAttribute atributoFila("fila", "4");
//	XmlAttribute atributoColumna("columna", "8");
//	xmlElement.addAttribute(atributoFila);
//	xmlElement.addAttribute(atributoColumna);
//
//	XmlElement xmlElementBonusUno("bonus", 1, 20);
//	XmlAttribute atributoTipoB1("tipo", "uva");
//	xmlElementBonusUno.addAttribute(atributoTipoB1);
//
//	XmlElement xmlElementBonusDos("bonus", 1, 20);
//	XmlAttribute atributoTipoB2("tipo", "sandia");
//	xmlElementBonusDos.addAttribute(atributoTipoB2);
//
//	xmlElement.addChild(xmlElementBonusUno);
//	xmlElement.addChild(xmlElementBonusDos);
//	
//	size_t tamanioAntes = Logger::getInstance()->obtenerTamanioArchivo();
//
//	// agrego el elemento
//	Camino camino(xmlElement);
//
//	// Se tuvo que haber generado un linea en el log, entonces el archivo de log aumento su tama�o
//	size_t tamanioDespues = Logger::getInstance()->obtenerTamanioArchivo();
//
//	// Cierro el log
//	Logger::getInstance()->closeLog();
//
//	return (tamanioAntes<tamanioDespues)?true:false;
//}
//
//bool CaminoTests::testNonValidAttributeMakesHasErrorTrue(void)
//{
//	XmlElement element("Camino", 1, 2);
//	XmlAttribute att1("fila", "1");
//	XmlAttribute att2("columna", "1");
//	XmlAttribute att3("invalido", "invalido");
//
//	element.addAttribute(att1);
//	element.addAttribute(att2);
//	element.addAttribute(att3);
//
//	Camino camino(element);
//
//	bool successCondition = camino.hasError();
//
//	Logger::closeLog();
//
//	return successCondition;
//}