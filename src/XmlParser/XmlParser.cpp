#include "global_def.h"
#include "XmlParser.h"
#include <fstream>
#include <sstream>
#include <queue>
#include <iostream>

using namespace std;

#define ZeroStructByPtr(p) memset(p, 0, sizeof(*p))

#define FALSE_ASSERT_RETURN(express) if(!(express)) {ASSERT(false); return false;}

PXMLELEMENT			XmlParser::m_pRoot		= NULL;
std::string			XmlParser::m_Content	= "";
std::string			XmlParser::m_ErrorMsg	= "";

PXMLELEMENT XmlParser::ParseFile(const char* fname)
{
	release();
	
	if(!loadFile(fname)) return NULL;

	char *p = &m_Content[0];
	m_pRoot = parseRecursion(p);
	skipSpace(p);
	FALSE_ASSERT_RETURN(p && !*p);
	return m_pRoot;
}

bool XmlParser::loadFile(const char* fname)
{
	ifstream xmlfile(fname);
	if (!fname)
	{
		ASSERT(false);
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
	FALSE_ASSERT_RETURN(m_ErrorMsg.empty());

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
				ASSERT(false);
				setErrorMsg("û���ҵ�\"<\", ���: %d", static_cast<int>(p - &m_Content[0]));
				return NULL;
			}

			FALSE_ASSERT_RETURN (getTagName(++p, elm.tag));
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
			FALSE_ASSERT_RETURN(getAttribKey(p, key));

			skipSpace(p);
			if (*p != '=')
			{
				ASSERT(false);
				setErrorMsg("���Ժ�����ֵδ�á�=������, ���: %d", p - &m_Content[0]);
				return NULL;
			}
			++p;
			skipSpace(p);

			FALSE_ASSERT_RETURN(getAttribValue(p, value));
			
			elm.attribs.insert(make_pair(key, value));

		}break;
		case STATE_FINDCLOSEEND:		// />
		{
			if (*p != '>')
			{
				ASSERT(false);
				setErrorMsg("\"/\"����û���ҵ�\">\", ���: %d", p - &m_Content[0]);
				return NULL;
			}
			state = STATE_SUCCESS;
		}break;
		case STATE_FINDCHILD:
		{
			// �ж��Ƿ���</ + <tagname>
			if (compareStr(p, endtag))
			{
				state = STATE_FINDENDTAGEND;
				break;
			}

			// ��ȡ�ӱ�ǩ
			PXMLELEMENT pChild = parseRecursion(p);
			FALSE_ASSERT_RETURN(m_ErrorMsg.empty());
			elm.children.push_back(pChild);

		}break;
		case STATE_FINDENDTAGEND:	// ��'</'��Ե�'>'
		{
			if (*p != '>')
			{
				ASSERT(false);
				setErrorMsg("���Ժ�����ֵδ�á�=������, ���: %d", p - &m_Content[0]);
				return NULL;
			}
			state = STATE_SUCCESS;
		}break;
		case STATE_SUCCESS:
		{
			PXMLELEMENT pe = new XmlElement;
			pe->tag = elm.tag;
			pe->attribs.swap(elm.attribs);
			pe->children.swap(elm.children);
			++p;
			return pe;
		}break;
		}
	}
	ASSERT(false);
	return NULL;
}


bool XmlParser::compareStr(char *&p, std::string& str)
{
	char *ps = p;
	int i = 0,
		size = str.size();
	while (p && *p && i < size && *p == str[i++]) ++p;
	if (i < size)
		p = ps;
	return i == size;
}

bool XmlParser::getTagName(char *&p, std::string& o_tag)
{
	char *ps = p;
	while (p && *p && isTagNameLegalCharactor(*p))++p;
	o_tag.assign(ps, p);
	return true;
}


bool XmlParser::getAttribKey(char *&p, std::string& o_key)
{
	char *ps = p;
	while (p && *p && isAttribKeyLegalCharactor(*p))++p;
	if (p - ps == 0)
	{
		setErrorMsg("��������ȡ����..");
		return false;
	}

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
	++p;

	return true;
}

void XmlParser::release()
{
	queue<PXMLELEMENT> qu;
	if (m_pRoot) qu.push(m_pRoot);
	while (!qu.empty())
	{
		PXMLELEMENT p = qu.front();

		for (ChildrenPtrVec::iterator it = p->children.begin(); it != p->children.end(); ++it)
		{
			qu.push(*it);
		}
		delete p;
		qu.pop();
	}

	m_Content.clear();
	m_ErrorMsg.clear();
}

void  XmlParser::setErrorMsg(const char* format, ...)
{
	cout << format << endl;
}