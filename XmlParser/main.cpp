#include "../src/XmlParser/XmlParser.h"
#include <string>
int main()
{
	PXMLELEMENT root = XmlParser::ParseFile("../bin/pic/green_tank.xml");

	return 0;
}