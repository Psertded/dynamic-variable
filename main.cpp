#include <iostream>
#include <Windows.h>
#include "variable.h"
#include "help.h"
#include "error.h"
#include "control.h"
void cls(HANDLE hConsole)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	SMALL_RECT scrollRect;
	COORD scrollTarget;
	CHAR_INFO fill;

	if (!GetConsoleScreenBufferInfo(hConsole, &csbi))
	{
		return;
	}

	scrollRect.Left = 0;
	scrollRect.Top = 0;
	scrollRect.Right = csbi.dwSize.X;
	scrollRect.Bottom = csbi.dwSize.Y;

	scrollTarget.X = 0;

	scrollTarget.Y = (SHORT)(0 - csbi.dwSize.Y);
	fill.Char.UnicodeChar = TEXT(' ');
	fill.Attributes = csbi.wAttributes;

	ScrollConsoleScreenBuffer(hConsole, &scrollRect, NULL, scrollTarget, &fill);

	csbi.dwCursorPosition.X = 0;
	csbi.dwCursorPosition.Y = 0;

	SetConsoleCursorPosition(hConsole, csbi.dwCursorPosition);
}
wstring tolower(wstring _Str)
{
	for (int i = 0; i < _Str.size(); i++)
	{
		if (_Str[i] >= L'A' && _Str[i] <= L'Z')
		{
			_Str[i] += 32;
		}
	}
	return _Str;
}

wstring clear(wstring in)
{
	for (int i = 0; i < in.size(); i++)
	{
		if (in.empty())
			return in;
		else if (in[0] == L' ')
		{
			in.erase(0, 1);
		}
	}
	for (int tmp = 0; tmp < ULLONG_MAX; tmp++)
	{
		if (in.back() == L' ')
		{
			in.pop_back();
		}
		else break;
	}
	return in;
}

int main()
{
	cout << "Dynamic variables runner - v1.0\n\tWritten by Psertded\n\n";
	wcout.imbue(locale("", locale::all | locale::numeric));
	wstring input, b_last = L"";
	vector <wstring> buf;
	bool last;
	cout << "Use help to show help.\n";
	while (true)
	{
		cout << ">";
		getline(wcin, input);
		if (input.empty())
		{
			buf.clear();
			input.clear();
			continue;
		}
		input = clear(input);
		buf = wsplitArgs(input);
		buf[0] = tolower(buf[0]);
		
		if (buf[0] == L"help")
		{
			help();
			continue;
		}
		if (buf[0] == L"cls")
		{
			cls(GetStdHandle(STD_OUTPUT_HANDLE));
			continue;
		}
		if (buf[0] == L"clear")
		{
			save.clear();
			if (save.size())
			{
				wcout << repError(-1) << endl;
			}
			else
			{
				wcout << repError(0) << endl;
			}
			continue;
		}
		if (buf[0] == L"size")
		{
			wcout << "save.size() = " << save.size() << endl;
			wcout << repError(0) << endl;
			continue;
		}
		if (buf[0] == L"last")
		{
			if (b_last.empty())
			{
				wcout << L"Last is empty.";
			}
			else
				wcout << L"last -> " << b_last;
			wcout << endl;
			continue;
		}
		if (buf.size() >= 2)
		{
			if (tolower(buf[1]) == L"last")
			{
				if (b_last.empty())
				{
					wcout << repError(14) << endl;
				}
				else if (save.find(b_last) == save.end())
				{
					wcout << repError(15) << endl;
				}
				else
				{
					last = true;
					buf[1] = b_last;
				}
			}
			else
			{
				last = false;
				if (!(b_last == buf[1]) && !(buf[0] == L"s" || buf[0] == L"d"))
				{
					b_last = buf[1];
					wcout << L"Last successfully updated.\n";
				}
				if (buf[0] == L"s" || buf[0] == L"d")
				{
					b_last.clear();
					wcout << L"Last successfully cleared.";
				}
			}
		}
		if (buf.size() == 1)
		{
			if (buf[0] == L"list")
			{
				wstring value, itv;
				int f_result;
				for (auto it : save)
				{
					itv = it.first;
					f_result=read(itv, &value);
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
				if (save.empty())
				{
					wcout << "No variable exist.";
				}
				else
				{
					wcout << L"last -> " << (b_last.empty() ? (wstring)L"empty" : b_last);
				}
				wcout << endl;
				continue;
			}
			if (buf[0].size() == 1)
			{
				if (buf[0] == L"w" || buf[0] == L"r" || buf[0] == L"d" || buf[0] == L"a" || buf[0] == L"s")
				{
					wcout << repError(11) << endl;
					continue;
				}
			}
			wcout << repError(8) << endl;
		}
		if (buf.size() == 2)
		{
			if (buf[0] == L"list")
			{
				wcout << repError(12);
			}
			else if (buf[0].size() == 1)
			{
				if (buf[0][0] == 'r')
				{
					if (buf.size() != 2)
					{
						wcout << repError(10) << endl;
					}
					else
					{
						wstring bufx;
						int rvalue = read(buf[1], &bufx);
						if (!rvalue)
						{
							wcout << ((last) ? L"last" : buf[1]) << ":" << bufx << endl;
							wcout << repError(0);
						}
						else
							wcout << endl << repError(rvalue);
						wcout << endl;
						continue;
					}
				}
				if (buf[0][0] == 'd')
				{
					wcout << endl;
					wcout << repError(_delete(buf[1])) << endl;
					wcout << endl;
					continue;
				}
				if (buf[0] == L"w" || buf[0] == L"a" || buf[0] == L"s")
				{
					wcout << repError(11) << endl;
					continue;
				}
			}
			wcout << repError(8) << endl;
			continue;
		}
		if (buf.size() == 3)
		{
			if (buf[0] == L"list")
			{
				wcout << repError(12) << endl;
			}
			else if (buf[0].size() == 1)
			{
				if (buf[0] == L"r" || buf[0] == L"d")
				{
					wcout << repError(12) << endl;
				}
				if (buf[0] == L"w")
				{
					wcout << repError(11) << endl;
				}
				if (buf[0] == L"a")
				{
					wcout << repError(add(buf[1], _data(buf[2], nullptr))) << endl;
				}
				if (buf[0] == L"s")
				{
					wcout << repError(swap(buf[1], buf[2])) << endl;
				}
				continue;
			}
			wcout << repError(8) << endl;
		}
		if (buf.size() == 4)
		{
			if (buf[0] == L"list")
			{
				wcout << repError(12) << endl;
				continue;
			}
			if (buf[0] == L"w")
			{
				write(buf[1], _data(buf[2], nullptr), false);//Oh,no!Your code is error!Please write twice :(
				if (buf[2]==L"int")
				{
					int hresult = stoi(buf[3]);
					wcout << repError(write(buf[1], _data(buf[2], &(hresult)))) << endl;
				}
				if (buf[2] == L"string")
				{
					wcout << repError(write(buf[1], _data(buf[2], &buf[3]))) << endl;
				}
				if (buf[2] == L"long")
				{
					long long hresult = stoll(buf[3]);
					wcout << repError(write(buf[1], _data(buf[2], &(hresult)))) << endl;
				}
				if (buf[2] == L"double")
				{
					double hresult = stod(buf[3]);
					wcout << repError(write(buf[1], _data(buf[2], &(hresult)))) << endl;
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
							wcout << repError(5) << endl;
							continue;
						}
						else
							hresult = stoi(buf[3]);
					}
					bool dresult = (hresult) ? true : false;
					wcout << repError(write(buf[1], _data(buf[2], &(dresult)))) << endl;
				}
				if (buf[2] == L"char")
				{
					wchar_t hresult = buf[3][0];
					wcout << repError(write(buf[1], _data(buf[2], &(hresult)))) << endl;
				}
				continue;
			}
			if (buf[0] == L"r" || buf[0] == L"d" || buf[0] == L"a" || buf[0] == L"s")
			{
				wcout << repError(12) << endl;
				continue;
			}
			wcout << repError(8) << endl;
		}
		if (buf.size() > 4)
		{
			wcout << repError(12) << endl;
			continue;
		}
	}
}