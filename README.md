# train
A small assembly compiler
just study progream.

可以编译20多条16位指令（包括伪代码），写的很冗长。
使用c++，但没有按照面向对象的方式编写。
特点，结合intel语法和AT&T汇编的语法，操作数位置取了AT&T的语法方式，例如：mov ax,bx ;将ax存入bx
同时没有使用AT&T中的前缀，如“&””$“等。
详情见CSDN博客：https://blog.csdn.net/lindorx/article/details/80084111