## Dynamic Variable Runner - DVR

| English | [中文](README_zh-cn.md) |

A simple dynamic variable modifier.  
Here you can modify variables, create variables, delete variables, swap variables, read variables, etc...

**IMPORTANT**:Not all types are the same as in C++, here is a special note:
|  DVR Type  |  C++ Type  |
|   :----:   |   :----:   |
|long        |long long   |
|char        |wchar_t     |
|string      |wstring     |

---
### Usage:
> ### Add
> Command : __a__  
> Useful: Add an empty variable  
> 
> __Note__: Except for string, other types do not detect null
>
> Example
> ~~~
> > a first int
> ~~~
> This command creates **an integer variable** named **first**  
> **Note** : In **Write**, if there is no target variable, **Add** is automatically called to create a rewrite

> ### Write
> Command : __w__  
> Useful: Write a variable  
>
> Example 1
> ~~~
> > w first int 123
> ~~~
> This command creates an integer variable named first and specifies its value as 123
>
> Example 2
> ~~~
> > w second string "second string"
> ~~~
> This command creates a string variable named second and specifies its value as "second string"

> ### Delete
> Command : __d__  
> Useful: Delete a variable  
>
> Example 1
> ~~~
> > d first
> ~~~
> This command deletes first.
>

> ### Read
> Command : __r__  
> Useful: Read a variable  
>
> Example 1
> ~~~
> > r first
> ~~~
> This command reads first's value.

> ### Swap
> Command : __r__  
> Useful: Swap the values of two variables
>
> Example 1
> ~~~
> > s first second
> ~~~
> This command swaps the values of first and second.

## Have Fun !

Translator : [Bing Microsoft Translator](https://www.bing.com/translator)
