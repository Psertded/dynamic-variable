#pragma once
#include <stdio.h>

using namespace std;

void help()
{
	printf("Help for Dynamic variables runner\nCommand: control name/size [type] [value]\n");
	printf("\tcontrol\tTell how to control variables\n");
	printf("\t\tw     Write variable\n");
	printf("\t\tr     Read variable\n");
	printf("\t\td     Delete variable\n");
	printf("\t\ta     Add empty variable\n");
	printf("\t\ts     Swap the values of two variables\n");
	printf("\t\tNote: There is a special variable called last.\n\t\t Pointing to the last controlled (swap and delete invalid) variable. \n\t\tName can be replaced by last\n");
	printf("\ttype\tVariable type\n");
	printf("\t\tint\tAn integer variable");
	printf("\n\t\tstring\tA String variable");
	printf("\n\t\tlong\tA long integer variable");
	printf("\n\t\tdouble\tA decimal fraction variable");
	printf("\n\t\tbool\tWhat?True or False?");
	printf("\n\t\tchar\tA character variable");
	printf("\n\tname\tVariable name\n\tvalue\tUse when write.Represents the value to be written");
	printf("\n\nCommand: control\n\t\tlist    List all variables\n");
	printf("\t\thelp  Show help\n");
	printf("\t\tcls   Clear screen\n");
	printf("\t\tclear Clear List\n");
	printf("\t\tsize  Show list size\n");
	printf("\t\tlast  Show last controlled variable.\n");
	printf("\nEnjoy it!\n");
}