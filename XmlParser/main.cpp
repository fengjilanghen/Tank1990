#include "../src/XmlParser/XmlParser.h"
#include <string>
int main()
{
	PXMLELEMENT root = XmlParser::ParseFile("../bin/pic/collection.xml");

	return 0;
}