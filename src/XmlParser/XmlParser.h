/*********************************************************
*
*	此xml只是用来存储数据，并不是完全的xml格式，其格式要求如下：
*	1. 标签名和属性名只能以字母和下划线组成
*	2. 属性值必须用双引号括起来
*	3. <，</与标签名之间不能有空格, <与/之间也不能有空格
*	4. 没有标签内文本
*	5. 无法解析注释（<!--）, 命令（<?）, 文本（<![DATA[）等标签
*
*********************************************************/

#ifndef _XMLPARSER_H_
#define _XMLPARSER_H_

#include <string>
#include <vector>
#include <unordered_map>



///////////////////////////////////////////////////////////
//
//	类型声明
//
///////////////////////////////////////////////////////////
struct XmlAttrib;
struct XmlElement;
typedef XmlAttrib*										PXMLATTRIB;
typedef XmlElement*										PXMLELEMENT;
typedef std::unordered_map<std::string, std::string>	AttribsPtrUMap;
typedef std::vector<PXMLELEMENT>						ChildrenPtrVec;

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

// 标签
struct XmlElement 
{
	std::string			tag;
	AttribsPtrUMap		attribs;
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
	static const std::string& GetLastErrorMsg();
	static PXMLELEMENT GetRoot(){ return m_pRoot; }
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
	static bool isSpace(char c) { return (c == ' ' || c == '\t' || c == '\r' || c == '\n'); }
	static void skipSpace(char *&p){ while (p && *p && isSpace(*p)) ++p; }

	static void release();
	static void setErrorMsg(const char* format, ...);


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
	static PXMLELEMENT			m_pRoot;
	static std::string			m_Content;
	static std::string			m_ErrorMsg;
};

#endif //_XMLPARSER_H_