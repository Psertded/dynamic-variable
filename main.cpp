#include <iostream>
#include <Windows.h>
#include "variable.h"
#include "help.h"
#include "error.h"
#include "control.h"
#include "docmd.h"
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
	cout << "Dynamic variables runner - v1.1\n\tWritten by Psertded\n\n";
	wcout.imbue(locale("", locale::all | locale::numeric));
	cout << "Use help to show help.\n";
	int result = 0;
	while (true)
	{
		cout << ">";
		getline(wcin, input);
		if (input.empty())
		{
			input.clear();
			continue;
		}
		input = clear(input);
		result = doCommand(input);
		wcout << endl << repError(result) << endl;
	}
}