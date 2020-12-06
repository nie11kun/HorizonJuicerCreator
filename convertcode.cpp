
#include <iostream>       // std::cout, std::hex
#include <string>         // std::string, std::u32string
#include "convertcode.hpp"

#ifdef _WIN32
    #include <Windows.h>
#endif

using namespace std;

ConvertCode::ConvertCode()
{
}

ConvertCode::~ConvertCode()
{
}

string ConvertCode::UnicodeToUTF8(const wstring& ws)
{
    string s;
    for (int i = 0; i < ws.size(); ++i)
    {
        wchar_t wc = ws[i];
        if (0 <= wc && wc <= 0x7f)
        {
            s += (char)wc;
        }
        else if (0x80 <= wc && wc <= 0x7ff)
        {
            s += (0xc0 | (wc >> 6));
            s += (0x80 | (wc & 0x3f));
        }
        else if (0x800 <= wc && wc <= 0xffff)
        {
            s += (0xe0 | (wc >> 12));
            s += (0x80 | ((wc >> 6) & 0x3f));
            s += (0x80 | (wc & 0x3f));
}
        else if (0x10000 <= wc && wc <= 0x1fffff)
        {
            s += (0xf0 | (wc >> 18));
            s += (0x80 | ((wc >> 12) & 0x3f));
            s += (0x80 | ((wc >> 6) & 0x3f));
            s += (0x80 | (wc & 0x3f));
        }
        else if (0x200000 <= wc && wc <= 0x3ffffff)
        {
            s += (0xf8 | (wc >> 24));
            s += (0x80 | ((wc >> 18) & 0x3f));
            s += (0x80 | ((wc >> 12) & 0x3f));
            s += (0x80 | ((wc >> 6) & 0x3f));
            s += (0x80 | (wc & 0x3f));
        }
        else if (0x4000000 <= wc && wc <= 0x7fffffff)
        {
            s += (0xfc | (wc >> 30));
            s += (0x80 | ((wc >> 24) & 0x3f));
            s += (0x80 | ((wc >> 18) & 0x3f));
            s += (0x80 | ((wc >> 12) & 0x3f));
            s += (0x80 | ((wc >> 6) & 0x3f));
            s += (0x80 | (wc & 0x3f));
        }
    }
    return s;
}

string ConvertCode::GBKToUTF8(const string in)
{
    #ifdef _WIN32
        const char* strGBK = in.c_str();
        int len = MultiByteToWideChar(CP_ACP, 0, strGBK, -1, NULL, 0);
        wchar_t* wstr = new wchar_t[len + 1];
        memset(wstr, 0, len + 1);
        MultiByteToWideChar(CP_ACP, 0, strGBK, -1, wstr, len);
        len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
        char* str = new char[len + 1];
        memset(str, 0, len + 1);
        WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, len, NULL, NULL);
        string strTemp = str;
        if (wstr) delete[] wstr;
        if (str) delete[] str;
        return strTemp;
    #else
        return in;
    #endif
}

string ConvertCode::UTF8ToGBK(const string in)
{
    #ifdef _WIN32
        const char* strUTF8 = in.c_str();
        int len = MultiByteToWideChar(CP_UTF8, 0, strUTF8, -1, NULL, 0);
        wchar_t* wszGBK = new wchar_t[len + 1];
        memset(wszGBK, 0, len * 2 + 2);
        MultiByteToWideChar(CP_UTF8, 0, strUTF8, -1, wszGBK, len);
        len = WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, NULL, 0, NULL, NULL);
        char* szGBK = new char[len + 1];
        memset(szGBK, 0, len + 1);
        WideCharToMultiByte(CP_ACP, 0, wszGBK, -1, szGBK, len, NULL, NULL);
        string strTemp(szGBK);
        if (wszGBK) delete[] wszGBK;
        if (szGBK) delete[] szGBK;
        return strTemp;
    #else
        return in;
    #endif
}
