#ifndef _XMLPARSER_H_
#define _XMLPARSER_H_

#include <string>
#include <vector>


///////////////////////////////////////////////////////////
//
//	类型声明
//
///////////////////////////////////////////////////////////
struct XmlAttrib;
struct XmlElement;
typedef XmlAttrib*					PXMLATTRIB;
typedef XmlElement*					PXMLELEMENT;
typedef std::vector<PXMLATTRIB>		AttribsPtrVec;
typedef std::vector<PXMLELEMENT>	ChildrenPtrVec;

///////////////////////////////////////////////////////////
//
//	宏定义
//
///////////////////////////////////////////////////////////
#define SAFEDELETE(p) if(p){ delete p; p = NULL;}

///////////////////////////////////////////////////////////
//
//	类型定义
//
///////////////////////////////////////////////////////////
// 标签属性
struct XmlAttrib
{
	std::string		key;
	std::string		value;
	XmlAttrib() :key(""), value(""){}
};

// 标签
struct XmlElement 
{
	std::string			tag;
	AttribsPtrVec		attribs;
	ChildrenPtrVec		children;	//同父标签通过其串联起来
	XmlElement() :tag(""), attribs(), children(){}
};

///////////////////////////////////////////////////////////
//
//	类声明
//
///////////////////////////////////////////////////////////
class XmlParser
{
public:
	static PXMLELEMENT ParseFile(const char* fname);
	static const string& GetLastErrorMsg();
private:
	XmlParser() = delete;
	XmlParser(const XmlParser&) = delete;

	static bool loadFile(const char* fname);
	static PXMLELEMENT parseRecursion(char *&p);
	static bool getTagName(char *&p, std::string& o_tag); 
	static bool getAttribKey(char *&p, std::string& o_key);
	static bool getAttribValue(char *&p, std::string& o_value);
	static bool compareStr(char *&p, std::string& str);

	static bool isTagNameLegalCharactor(char c) { return isalpha(c) || c == '_'; }
	static bool isAttribKeyLegalCharactor(char c) { return isalpha(c) || c == '_'; }
	static bool isSpace(char c) { return (c == ' ' || c == '\r' || c == '\n'); }
	static void skipSpace(char *p){ while (p && *p && isSpace(*p)) ++p; }

	static void release();
	static void setErrorMsg(const std::string& format, ...);

private:
	enum 
	{
		STATE_FINDSTARTTAG = 0,	// <
		STATE_FINDATTRIB,
		STATE_FINDCLOSEEND,		// />
		STATE_FINDCHILD,
		STATE_FINDENDTAGEND,		// 对应于"</"的">"
		STATE_SUCCESS,
	};
private:
	static std::string			m_Content;
	static std::string			m_ErrorMsg;
};

#endif //_XMLPARSER_H_