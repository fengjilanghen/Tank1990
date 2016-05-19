#ifndef _CONVERT_H_
#define _CONVERT_H_

#include <windows.h>
#include <string>
#include <cstdlib>

/*****************************
*
*	定义在main.cpp中
*
***********************************/

// Convert a wide Unicode string to an UTF8 string
std::string utf8_encode(const std::wstring &wstr);

// Convert an UTF8 string to a wide Unicode String
std::wstring utf8_decode(const std::string &str);

// Convert a wide Unicode string to an UTF8 string
/*std::string wcs2mbs(const std::wstring &wstr)
{
	std::string ret(wstr.length() + 1, '\0');
	wcstombs(&ret[0], wstr.c_str(), wstr.length());
	return ret;
}

// Convert an UTF8 string to a wide Unicode String
std::wstring mbs2wcs(const std::string &str)
{
	std::wstring ret(str.length() + 1, '\0');
	mbstowcs(&ret[0], str.c_str(), str.length());
	return ret;
}
*/

#endif //_CONVERT_H_