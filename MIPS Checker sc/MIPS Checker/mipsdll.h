#include <Windows.h>
#include <cstdio>
#include <string>

using namespace std;

#define MYDLL_API __declspec(dllexport)

namespace convert
{
std::wstring str_to_wstr( const std::string& str )
{
  std::wstring wstr( str.length()+1, 0 );
  
  MultiByteToWideChar( CP_ACP,
             0,
             str.c_str(),
             str.length(),
             &wstr[0],
             str.length() );
  return wstr;
}
std::string wstr_to_str( const std::wstring& wstr )
{
  size_t size = wstr.length();
  std::string str( size + 1, 0 );
  
  WideCharToMultiByte( CP_ACP,
             0,
             wstr.c_str(),
             size,
             &str[0],
             size,
             NULL,
             NULL );
  return str;
}
}