#include "XmlParser.h"
#include <fstream>
#include <sstream>

using namespace std;

#define ZeroStructByPtr(p) memset(p, 0, sizeof(*p))

PXMLELEMENT XmlParser::ParseFile(const char* fname)
{
	m_ErrorMsg = "";
	release();
	
	if(!loadFile(fname)) return NULL;

	char *p = &m_Content[0];
	PXMLELEMENT root = parseRecursion(p);
	skipSpace(p);
	if (!p || *p)
	{
		release();
		return NULL;
	}
	return root;
}

bool XmlParser::loadFile(const char* fname)
{
	ifstream xmlfile(fname);
	if (fname)
	{
		//ASSERT(fname);
		return false;
	}

	xmlfile.seekg(0, xmlfile.end);
	int length = xmlfile.tellg();
	xmlfile.seekg(0, xmlfile.beg);
	m_Content.resize(length);

	xmlfile.read(&m_Content[0], length);
	xmlfile.close();
	return true;
}

PXMLELEMENT XmlParser::parseRecursion(char *&p)
{
	if (!m_ErrorMsg.empty()) return NULL;

	XmlElement elm;
	string endtag = "</";


	int state = STATE_FINDSTARTTAG;
	while (p && *p)
	{
		skipSpace(p);
		switch (state)
		{
		case STATE_FINDSTARTTAG:
		{
			if (*p != '<')
			{
				setErrorMsg("没有找到"<", 序号: %d", p - &m_Content[0]);
				return NULL;
			}

			if (!getTagName(++p, elm.tag)) return NULL;
			state = STATE_FINDATTRIB;
		}break;
		case STATE_FINDATTRIB:
		{
			if (*p == '/' || *p == '>')
			{
				state = (*p == '/' ? STATE_FINDCLOSEEND : STATE_FINDCHILD);
				endtag.append(elm.tag.begin(), elm.tag.end());
				++p;
				break;
			}

			string key, value;
			if (!getAttribKey(p, key)) return NULL;

			skipSpace(p);
			if (*p != '=')
			{
				setErrorMsg("属性和属性值未用“=”连接, 序号: %d", p - &m_Content[0]);
				return NULL;
			}

			skipSpace(p);

			if (!getAttribValue(p, value)) return NULL;

			PXMLATTRIB attrib = new XmlAttrib;
			attrib->key = key;
			attrib->value = value;
			elm.attribs.push_back(attrib);

		}break;
		case STATE_FINDCLOSEEND:		// />
		{
			if (*p != '>')
			{
				setErrorMsg("\"/\"后面没有找到\">\", 序号: %d", p - &m_Content[0]);
				return NULL;
			}
			++p;
			state = STATE_SUCCESS;
		}break;
		case STATE_FINDCHILD:
		{
			// 判断是否是</ + <tagname>
			char *ps = p;
			if (compareStr(ps, endtag))
			{
				state = STATE_FINDENDTAGEND;
				++p;
				break;
			}
			p = ps;

			// 读取子标签
			PXMLELEMENT pChild = parseRecursion(p);
			if (!m_ErrorMsg.empty())
			{
				return NULL;
			}
			elm.children.push_back(pChild);

		}break;
		case STATE_FINDENDTAGEND:	// 与'</'配对的'>'
		{
			if (*p != '>')
			{
				setErrorMsg("属性和属性值未用“=”连接, 序号: %d", p - &m_Content[0]);
				return NULL;
			}
			state = STATE_SUCCESS;
			++p;
		}break;
		case STATE_SUCCESS:
		{
			PXMLELEMENT pe = new XmlElement;
			pe->tag = elm.tag;
			pe->attribs.swap(elm.attribs);
			pe->children.swap(elm.children);
			return pe;
		}break;
		}
	}
	return NULL;
}


bool XmlParser::compareStr(char *&p, std::string& str)
{
	char *ps = p;
	int i = 0,
		size = str.size();
	while (p && *p && i < size && *p == str[i++]) ++p;
	p = ps;
	return i == size;
}

bool XmlParser::getTagName(char *&p, std::string& o_tag)
{
	char *ps = p;
	while (p && *p && isTagNameLegalCharactor(*p))++p;
	o_tag.assign(ps, p);
}


bool XmlParser::getAttribKey(char *&p, std::string& o_key)
{
	char *ps = p;
	while (p && *p && isAttribKeyLegalCharactor(*p))++p;
	o_key.assign(ps, p);
	return true;
}

bool XmlParser::getAttribValue(char *&p, std::string& o_value)
{
	if (!p || !*p || *p != '\"')
	{
		setErrorMsg("value is not begin with '\"', index: %d", p - &m_Content[0]);
		return false;
	}

	char *ps = ++p;
	while (p && *p && *p != '\"') ++p;
	o_value.assign(ps, p);

	if (!p || !*p || *p != '\"')
	{
		setErrorMsg("value is not end with '\"', index: %d", p - &m_Content[0]);
		return false;
	}
}