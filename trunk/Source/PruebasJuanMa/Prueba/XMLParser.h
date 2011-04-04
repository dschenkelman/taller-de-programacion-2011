#include <string>

using namespace System;
using namespace std;

class XMLParser {

private:
	FILE * pFile;
	char buffer [100];

public:
	string parsear(string tag);

};