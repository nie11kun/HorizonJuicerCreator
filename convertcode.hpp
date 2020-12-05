#ifndef ConvertCode_hpp
#define ConvertCode_hpp

#include <stdio.h>
#include <string>

using namespace std;

class ConvertCode
{
public:
    ConvertCode();
    ~ConvertCode();
    string UnicodeToUTF8(const wstring& ws);
    string GBKToUTF8(const string in);
    string UTF8ToGBK(const string in);
private:

};

#endif
