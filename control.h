#pragma once
#include <iomanip>
#include "variable.h"
#include "blacklist.h"

int __add__(wstring name, _data* data)
{
	if (data->type == L"int")
	{
		data->value = new int;
		if (!data->value)
			return 7;
		return 0;
	}
	else if (data->type == L"string")
	{
		data->value = new wstring;
		if (!data->value)
			return 7;
		return 0;
	}
	else if (data->type == L"long")
	{
		data->value = new long long;
		if (!data->value)
			return 7;
		return 0;
	}
	else if (data->type == L"double")
	{
		data->value = new long double;
		if (!data->value)
			return 7;
		return 0;
	}
	else if (data->type == L"bool")
	{
		data->value = new bool;
		if (!data->value)
			return 7;
		return 0;
	}
	else if (data->type == L"char")
	{
		data->value = new wchar_t;
		if (!data->value)
			return 7;
		return 0;
	}
	else if (data->type == L"ptr")
	{
		data->value = new variable_pointer;
		if (!data->value)
			return 7;
		return 0;
	}
	else
	{
		return 6;
	}
	return -1;
}
int _delete(wstring name)
{
	if (save.find(name) != save.end())
	{
		delete save[name].value;
	}
	if (save.erase(name))
	{
		return 0;//success
	}
	else
	{
		return 1;//not exist
	}
	return -1;//unknown error
}
int add(wstring name, _data data)
{
	_data dat;
	dat.type = data.type;
	int a_result = __add__(name, &dat);
	if (a_result)
	{
		delete dat.value;
		return a_result;
	}
	if (save.find(name) != save.end())
	{
		return 4;
	}
	else
	{
		for (int i = 0; i < 100; i++)
		{
			if (name == blacklist[i])
			{
				return 16;
			}
		}
		save[name] = dat;
		return 0;
	}
	return -1;
}

int write(wstring name, _data data, bool dshow = true)
{
	bool createnew = false;
	if (save.find(name) == save.end())
	{
		int a_result = add(name, data);
		createnew = true;
		if (a_result)
			return a_result;
	}
	else
	{
		if ((!createnew) && (save[name].type != data.type) && dshow)
		{
			wcout << "(You shoule use " << save[name].type << " type,not " << data.type << " to assign)" << endl;
			return 6;
		}
		else if (createnew && save[name].type != data.type || !dshow)
		{
			return 6;
		}
		else
		{
			if (!save[name].value)
				return 5;
			if (save[name].type == L"int")
			{
				*(int*)(save[name].value) = *(int*)(data.value);
				if (save[name].value)
					return 0;
			}
			else if (save[name].type == L"string")
			{
				*(wstring*)(save[name].value) = *(wstring*)(data.value);
				if (save[name].value)
					return 0;
			}
			else if (save[name].type == L"long")
			{
				*(long long*)(save[name].value) = *(long long*)(data.value);
				if (save[name].value)
					return 0;
			}
			else if (save[name].type == L"double")
			{
				*(long double*)(save[name].value) = *(long double*)(data.value);
				if (save[name].value)
					return 0;
			}
			else if (save[name].type == L"bool")
			{
				*(bool*)(save[name].value) = *(bool*)(data.value);
				if (save[name].value)
					return 0;
			}
			else if (save[name].type == L"char")
			{
				*(wchar_t*)(save[name].value) = *(wchar_t*)(data.value);
				if (save[name].value)
					return 0;
			}
			else if (save[name].type == L"ptr")
			{
				*(variable_pointer*)(save[name].value) = *(variable_pointer*)(data.value);
				if (save[name].value)
					return 0;
			}
			return 3;
		}
		return -1;
	}
	return -1;
}
int pointer(wstring ptr, wstring source)
{
	if (source.find(L"new.") == 0)
	{
		int a_result = add(source.substr(4), _data(L"ptr", nullptr));
		if (a_result)
		{
			return a_result;
		}
		source = source.substr(4);
		int w_result = write(ptr, _data(L"ptr", &(source)));
		if (w_result)
		{
			return w_result;
		}
	}
	else if (source.find(L"delete.") == 0)
	{
		int d_result = _delete(source.substr(7));
		if(d_result)
		{
			return d_result;
		}
		if (save.find(ptr) != save.end())
		{
			std::wstring nul = L"NULL";
			save[ptr] = _data(L"ptr", &nul);
		}
	}
	else if (source.empty())
	{
		int a_result = add(ptr, _data(L"ptr", nullptr));
		if (a_result)
		{
			return a_result;
		}
	}
	else
	{
		if (save.find(source) == save.end())
		{
			return 1;
		}
		int w_result = write(ptr, _data(L"ptr", &source));
		if (w_result)
		{
			return w_result;
		}
	}
}
int free(wstring pointer)
{
	if (save.find(pointer) == save.end())
	{
		return 1;
	}
	else if (save[pointer].type != L"ptr")
	{
		return 6;
	}
	else
	{
		wstring dst = *(wstring*)(save[pointer].value);
		if (save.find(dst) == save.end())
		{
			return 1;
		}
		else
		{
			int d_result = _delete(dst);
			if (d_result)
			{
				return d_result;
			}
			delete save[pointer].value;
			std::wstring nul = L"NULL";
			save[pointer] = _data(L"ptr", &nul);
		}
	}
	return 0;
}
int read(wstring name,wstring* dst/*empty else your data will go!*/)
{
	if (save.find(name) == save.end())
	{
		return 1;
	}
	else if (save[name].type == L"string")
	{
		if ((*(wstring*)(save[name].value)).empty())
		{
			return 2;
		}
	}
	//Return
	{
		dst->clear();
		if (save[name].type == L"int")
		{
			*dst = to_wstring(*(int*)(save[name].value));
			if (!dst)
				return 3;
		}
		if (save[name].type == L"string")
		{
			*dst = *(wstring*)(save[name].value);
			if (!dst)
				return 3;
		}
		if (save[name].type == L"long")
		{
			*dst = to_wstring(*(long long*)(save[name].value));
			if (!dst)
				return 3;
		}
		if (save[name].type == L"double")
		{
			*dst = to_wstring(*(long double*)(save[name].value));
			if (!dst)
				return 3;
		}
		if (save[name].type == L"bool")
		{
			bool _bd = *(bool*)(save[name].value);
			*dst = (_bd) ? L"true" : L"false";
			if (!dst)
				return 3;
		}
		if (save[name].type == L"char")
		{
			dst->clear();
			wchar_t _bc = *(wchar_t*)(save[name].value);
			if (_bc <= 31)
			{
				dst->append((to_wstring(int(_bc))));
				dst->append(L"(character is not visible)");
			}
			else
				dst->push_back(*(wchar_t*)(save[name].value));
			if (!dst)
				return 3;
		}
		if (save[name].type == L"ptr")
		{
			dst->clear();
			dst->append(*((wstring*)save[name].value));
			if (!dst)
				return 3;
		}
		return 0;
	}
	return -1;
}
#define AUTO_CHECK(resultcode,func,param) int resultcode##_result=func(param);if(resultcode##_result)return resultcode##_result; 
#define AUTO_CHECK_D(resultcode,func,param1,param2) int resultcode##_result=func(param1,param2);if(resultcode##_result)return resultcode##_result; 

int swap(wstring x, wstring y)
{
	if (save.find(x) == save.end() || save.find(y) == save.end())
	{
		return 1;
	}
	swap(save[x], save[y]);
	return 0;
}

int copy(wstring source, wstring dest)
{
	if (save.find(source) == save.end())
	{
		return 1;
	}
	if (save.find(dest) == save.end())
	{
		add(dest, _data(save[source].type, nullptr));
	}
	int w_result = write(dest, _data(save[source].type, save[source].value));
	if (w_result)
		return w_result;
	return 0;
}