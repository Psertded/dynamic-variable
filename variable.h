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