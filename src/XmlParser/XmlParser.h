/*********************************************************
*
*	��xmlֻ�������洢���ݣ���������ȫ��xml��ʽ�����ʽҪ�����£�
*	1. ��ǩ����������ֻ������ĸ���»������
*	2. ����ֵ������˫����������
*	3. <��</���ǩ��֮�䲻���пո�, <��/֮��Ҳ�����пո�
*	4. û�б�ǩ���ı�
*	5. �޷�����ע�ͣ�<!--��, ���<?��, �ı���<![DATA[���ȱ�ǩ
*
*********************************************************/

#ifndef _XMLPARSER_H_
#define _XMLPARSER_H_

#include <string>
#include <vector>
#include <unordered_map>



///////////////////////////////////////////////////////////
//
//	��������
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
//	�궨��
//
///////////////////////////////////////////////////////////
#define SAFEDELETE(p) if(p){ delete p; p = NULL;}

///////////////////////////////////////////////////////////
//
//	���Ͷ���
//
///////////////////////////////////////////////////////////

// ��ǩ
struct XmlElement 
{
	std::string			tag;
	AttribsPtrUMap		attribs;
	ChildrenPtrVec		children;	//ͬ����ǩͨ���䴮������
	XmlElement() :tag(""), attribs(), children(){}
};

///////////////////////////////////////////////////////////
//
//	������
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
		STATE_FINDENDTAGEND,		// ��Ӧ��"</"��">"
		STATE_SUCCESS,
	};
private:
	static PXMLELEMENT			m_pRoot;
	static std::string			m_Content;
	static std::string			m_ErrorMsg;
};

#endif //_XMLPARSER_H_