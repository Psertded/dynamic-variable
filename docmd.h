#pragma once
#include "control.h"
#include "error.h"
#include "help.h"
#include "variable.h"
#include "cmdlist.h"

#include <iostream>
using namespace std;

std::wstring AutoCheck(std::wstring str)
{
	bool beNum = true;
	int invalidrecord = 0;
	if (str.size() == 1)
	{
		return L"char";
	}
	if (str == L"01" || str == L"1" || tolower(str) == L"true" || tolower(str) == L"false")
	{
		return L"bool";
	}
	for (int i = 0; i < str.size(); i++)
	{
		if (!(str[i] <= '9' && str[i] >= '0'))
		{
			beNum = false;
			invalidrecord++;
		}
	}
	if (invalidrecord == 1 && ((str.find('.') == str.rfind('.') && str.find('.') != string::npos)))
	{
		return L"double";
	}
	if (invalidrecord == 1 && (str.back() == 'f' || str.back() == 'F'))
	{
		return L"double";
	}
	if (invalidrecord == 1 && (str.back() == 'l' || str.back() == 'L'))
	{
		return L"long";
	}
	if (invalidrecord == 1 && (str.back() == 'c' || str.back() == 'C'))
	{
		return L"char";
	}
	if (invalidrecord == 1 && (str.back() == 'i' || str.back() == 'I'))
	{
		return L"int";
	}
	if (invalidrecord == 1 && (str.back() == 's' || str.back() == 'S'))
	{
		return L"string";
	}
	if (beNum)
	{
		if (stoull(str) <= (unsigned long long)INT_MAX)
		{
			return L"int";
		}
		else
			return L"long";
	}
	if (!beNum)
		return L"string";
}

wstring special_check(wstring eptr)
{
	if (eptr.size()<=1)
	{
		return eptr;
	}
	if (eptr[0] == '*')
	{
		eptr.erase(0, 1);
		if (save.find(eptr) == save.end())
		{
			return eptr;
		}
		else
		{
			wstring result = *(wstring*)(save[eptr].value);
			result;
			if (result == L"NULL")
			{
				return eptr;
			}
			else
			{
				return result;
			}
		}
	}
	return eptr;
}

int doCommand(wstring command)
{
	int cmd = -1;
	vector <wstring> buf = wsplitArgs(command);
	if (!buf.size())
	{
		return -1;
	}
	for (int i = 1; i < buf.size(); i++)
	{
		buf[i] = special_check(buf[i]);
	}
	buf[0] = tolower(buf[0]);
	for (int i = 0; i < 100; i++)
	{
		if (commands[i] == buf[0])
		{
			cmd = i;
			break;
		}
	}
	if (cmd == -1)
	{
		return 8;
	}
	if (cmd == 0)
	{
		if (buf.size() <= 3)
		{
			return 11;
		}
		else if(buf.size() == 4)
		{
			if (buf[2] == L"auto")
			{
				buf[2] = AutoCheck(buf[3]);
				wcout << "type : " << buf[2] << endl;
			}
			write(buf[1], _data(buf[2], nullptr), false);//Oh,no!Your code is error!Please write twice :(
			if (buf[2] == L"int")
			{
				int hresult = stoi(buf[3]);
				return write(buf[1], _data(buf[2], &(hresult)));
			}
			if (buf[2] == L"string")
			{
				return write(buf[1], _data(buf[2], &buf[3]));
			}
			if (buf[2] == L"long")
			{
				long long hresult = stoll(buf[3]);
				return write(buf[1], _data(buf[2], &(hresult)));
			}
			if (buf[2] == L"double")
			{
				long double hresult = stod(buf[3]);
				return write(buf[1], _data(buf[2], &(hresult)));
			}
			if (buf[2] == L"bool")
			{
				int hresult;
				if (buf[3] == L"true")
				{
					hresult = 1;
				}
				else if (buf[3] == L"false")
				{
					hresult = 0;
				}
				else
				{
					if (buf[3].size() != 1)
					{
						return 5;
					}
					else
						hresult = stoi(buf[3]);
				}
				bool dresult = (hresult) ? true : false;
				return write(buf[1], _data(buf[2], &(dresult)));
			}
			if (buf[2] == L"char")
			{
				wchar_t hresult = buf[3][0];
				return write(buf[1], _data(buf[2], &(hresult)));
			}
			if (buf[2] == L"ptr")
			{
				variable_pointer pointer = buf[3];
				return write(buf[1], _data(buf[2], &(pointer)));
			}
			else
			{
				return 9;
			}
		}
		else
		{
			return 12;
		}
	}
	else if (cmd == 1)
	{
		if (buf.size() <= 1)
		{
			return 11;
		}
		else if (buf.size() == 2)
		{
			wstring bufx;
			int rvalue = read(buf[1], &bufx);
			if (!rvalue)
			{
				wcout << ((last) ? L"last" : buf[1]) << ((save[buf[1]].type == L"ptr") ? " -> " : " : ") << 
					((save[buf[1]].type != L"ptr") ? bufx : (save.find(bufx) == save.end()) ? L"Unknown" : bufx) << endl;
				return 0;
			}
			else
			{
				return rvalue;
			}
		}
		else
		{
			return 12;
		}
	}
	else if (cmd == 2)
	{
		if (buf.size() <= 1)
		{
			return 11;
		}
		if (buf.size() >= 3)
		{
			return 12;
		}
		return _delete(buf[1]);
	}
	else if (cmd == 3)
	{
		if (buf.size() <= 2)
		{
			return 11;
		}
		if (buf.size() >= 4)
		{
			return 12;
		}
		return add(buf[1], _data(buf[2], nullptr));
	}
	else if (cmd == 4)
	{
		if (buf.size() <= 2)
		{
			return 11;
		}
		if (buf.size() >= 4)
		{
			return 12;
		}
		return swap(buf[1], buf[2]);
	}
	else if (cmd == 5)
	{
		if (buf.size() <= 2)
		{
			return 11;
		}
		if (buf.size() >= 4)
		{
			return 12;
		}
		return copy(buf[1], buf[2]);
	}
	else if (cmd == 6)
	{
		if (save.empty())
		{
			wcout << "No variable exist.";
			return 0;
		}
		wstring value, itv;
		int f_result;
		for (auto it : save)
		{
			itv = it.first;
			f_result = read(itv, &value);
			if (f_result && f_result != 2)
			{
				wcout << repError(f_result);
			}
			else if (f_result == 2)
			{
				value = L"(all)empty";
			}
			else
			{
				value.insert(0, L"(");
				value.insert(1, it.second.type + L")");
			}

			wcout << it.first << " = " << value << endl;
		}
		wcout << L"last -> " << (b_last.empty() ? (wstring)L"empty" : b_last);
		wcout << endl;
		return 0;
	}
	else if (cmd == 7)
	{
		help();
		return 0;
	}
	else if (cmd == 8)
	{
		cls(GetStdHandle(STD_OUTPUT_HANDLE));
		return 0;
	}
	else if (cmd == 9)
	{
		save.clear();
		if (save.size())
		{
			return -1;
		}
		return 0;
	}
	else if (cmd == 10)
	{
		wcout << "Size : " << save.size() << endl;
		return 0;
	}
	else if (cmd == 11)
	{
		if (b_last.empty())
		{
			wcout << L"Last is empty.";
		}
		else
			wcout << L"last -> " << b_last;
		return 0;
	}
	else if (cmd == 12)
	{
		if (buf.size() <= 1)
		{
			return 11;
		}
		else if (buf.size() == 2)
		{
			pointer(buf[1], L"");
			return pointer(buf[1], L"");
		}
		else if (buf.size() == 3)
		{
			pointer(buf[1], buf[2]);
			return pointer(buf[1], buf[2]);
		}
		else
		{
			return 12;
		}
	}
	else if (cmd == 13)
	{
		if (buf.size() <= 1)
		{
			return 11;
		}
		else if (buf.size() == 2)
		{
			return free(buf[1]);
		}
		else
		{
			return 12;
		}
	}
}