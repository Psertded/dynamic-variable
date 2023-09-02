#pragma once
#include <map>
#include <vector>
#include <string>

using namespace std;

vector<string> splitArgs(string& input)
{
    vector<string> result;
    string current_arg;
    bool in_quotes = false;

    for (size_t i = 0; i < input.length(); ++i)
    {
        char c = input[i];

        if (c == '"')
        {
            in_quotes = !in_quotes;
        }
        else if (c == ' ' && !in_quotes)
        {
            if (!current_arg.empty())
            {
                result.push_back(current_arg);
                current_arg.clear();
            }
        }
        else
        {
            current_arg.push_back(c);
        }
    }
    if (!current_arg.empty())
    {
        result.push_back(current_arg);
    }
    return result;
}

vector<wstring> wsplitArgs(wstring& input)
{
    vector<wstring> result;
    wstring current_arg;
    bool in_quotes = false;

    for (size_t i = 0; i < input.length(); ++i)
    {
        wchar_t c = input[i];

        if (c == '"')
        {
            in_quotes = !in_quotes;
        }
        else if (c == ' ' && !in_quotes)
        {
            if (!current_arg.empty())
            {
                result.push_back(current_arg);
                current_arg.clear();
            }
        }
        else
        {
            current_arg.push_back(c);
        }
    }
    if (!current_arg.empty())
    {
        result.push_back(current_arg);
    }
    return result;
}
struct _data
{
    void* value = nullptr;
	wstring type;
    /*
    * These type can use:
    * int
    * string
    * long
    * double
    * bool
    * char
    */

	_data() = default;
    _data(wstring type2, void* val) : type(type2), value(val) {};
};

map <wstring, _data> save;

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

wstring input, b_last = L"";
bool last;

using variable_pointer = std::wstring;

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
