
// stdafx.cpp : 只包括标准包含文件的源文件
// Demo_Basic.pch 将作为预编译头
// stdafx.obj 将包含预编译类型信息

#include "stdafx.h"

// CHAR2WCHAR(szA, szW, sizeof(szW) / sizeof(szW[0]));
bool CHAR2WCHAR(const char* lpcszStr, wchar_t *lpwszStr, unsigned int dwSize)
{
	// Get the required size of the buffer that receives the Unicode   
	// string.   
	unsigned int dwMinSize;
	dwMinSize = MultiByteToWideChar(CP_ACP, 0, lpcszStr, -1, NULL, 0);
	if (dwSize < dwMinSize)
	{
		return false;
	}
	// Convert headers from ASCII to Unicode.  
	MultiByteToWideChar(CP_ACP, 0, lpcszStr, -1, lpwszStr, dwMinSize);

	return true;
}


