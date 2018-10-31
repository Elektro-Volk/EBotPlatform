#include "strutils.hpp"
#include <codecvt>
#include <iostream>
#include <locale>
#include <string>
#include <sstream>
#include "utf8cases.hpp"
#ifndef __linux__
	#include "windows.h"
#endif

std::wstring to_wstring(std::string const& s)
{
#ifdef __linux__
	std::wstring_convert<std::codecvt_utf8<wchar_t> > conv;
	return conv.from_bytes(s);
#else
	if (s.empty())
	{
		return std::wstring();
	}
	int num_chars = MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, s.c_str(), s.length(), NULL, 0);
	std::wstring wstrTo;
	if (num_chars)
	{
		wstrTo.resize(num_chars);
		if (MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, s.c_str(), s.length(), &wstrTo[0], num_chars))
		{
			return wstrTo;
		}
	}
	return std::wstring();
#endif
}

std::string to_string(std::wstring const& s) {
  std::wstring_convert<std::codecvt_utf8<wchar_t> > conv;
  return conv.to_bytes(s);
}

bool strutils::starts(string str, string token)
{
  return str.rfind(token, 0) == 0;
}

bool strutils::ends(string str, string token)
{
	if (token.size() > str.size()) return false;
    return std::equal(token.rbegin(), token.rend(), str.rbegin());
}

string strutils::toLower(string str)
{
//#ifdef __linux__
	std::wstring ss = to_wstring(str);
	//std::cout << str << '\n';
	//std::wcout << ss << '\n';
	for (wchar_t& c : ss) {
		c = std::tolower(c, std::locale("en_US.UTF8"));
	  
		//for (int j = 0; j < UTF8CASES_SIZE; j++)
		//	if (c == cases[j][0]) { c = cases[j][1]; break; }
	}
	return to_string(ss);
//#else
	//return CharLower(const_cast<char*>(str.c_str()));
//#endif
}

string strutils::toUpper(string str)
{
#ifdef __linux__
	auto ss = to_wstring(str);
  for (wchar_t& c : ss) {
    c = std::toupper(c);
		for (int j = 0; j < UTF8CASES_SIZE; j++)
			if (c == cases[j][1]) { c = cases[j][0]; break; }
  }
  return to_string(ss);
#else
	return CharUpper(const_cast<char*>(str.c_str()));
#endif
}

void strutils::replace(std::string& str, const std::string& old, const std::string& repl) {
size_t pos = 0;
while ((pos = str.find(old, pos)) != std::string::npos) {
str.replace(pos, old.length(), repl);
pos += repl.length();
}
}

std::vector<string> strutils::split(string str, char sep)
{
  std::vector<string> tokens;
	std::istringstream ss(str);

	for (string item; std::getline(ss, item, sep);)
		tokens.push_back(item);

	return tokens;
}
