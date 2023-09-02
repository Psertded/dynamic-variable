#pragma once
#include <string>
#include <map>

using namespace std;
pair <int/*error code*/, wstring/*error format message*/> errorCode[] =
{
	{-1,L"Unknown error."},
	{0,L"Success."/*Success*/ },
	{1,L"Variable is not exist."},
	{2,L"Variable is empty."},
	{3,L"Write error."},
	{4,L"Variable is exist."},//when add
	{5,L"Invalid value."},
	{6,L"Invalid type."},
	{7,L"Make error."},
	{8,L"Unknown command.Check help to write command!"},
	{9,L"Unknown Argument.Check help to write command!"},
	{10,L"Invalid Argument.Check help to write command!"},
	{11,L"Lack Argument.Check help to write command!"},
	{12,L"Too many Argument.Check help to write command!"},
	{13,L"Read Error"},
	{14,L"No last control."},
	{15,L"Last is invalid, is last correct?"},
	{16,L"This name cannot be used as a variable name"}
};

wstring __repError__(int code)
{
	for (int i = 0; i < 18; i++)
	{
		if (code == (errorCode[i].first))
		{
			return errorCode[i].second;
		}
	}
	return L"NOT DEFINED Error code";
}

wstring repError(int code)
{
	wstring basic = __repError__(code);
	if (basic==L"Success.")
		return basic;
	return wstring(L"An error has occurred!\nError:") + basic;
}