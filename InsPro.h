/*InsPro.h用来声明InsPro.cpp文件*/
#pragma once
#include<string>
#include<vector>

#include"Struct_self.h"

//定义数组

//函数定义

std::vector<unsigned char>MOVE(const std::string& str, int k, int num);

std::vector<unsigned char>Move1(const std::string& str,int n,int num);

std::vector<unsigned char>Move2(const std::string& str, STRINF *m1, STRINF *m2, int num);

long Organ(const std::string& str, int n, int num);

//Data函数，用于处理DB,DW,DD指令,str:该行指令字符串；num：指令字符之后的一字节位置；fix：本指令占用的字节数
std::vector<unsigned char>DataBWD(const std::string& str, int n, int fix, int num);

int ReserveByte(const std::string& str, int num, int all);

//加法指令
std::vector<unsigned char>Additive(const std::string& str, int n, int num);
//减法指令
std::vector<unsigned char>Subtraction(const std::string& str, int n, int num);

//处理jmp语句。
std::vector<unsigned char>Jemp();

std::vector<unsigned char>Push(const std::string& str, int n, int num);

std::vector<unsigned char>Pop(const std::string& str, int n);

//INT指令为显卡调用指令
std::vector<unsigned char>Int(std::string& str, int n, int num);

//处理je语句。str:字符串；n：起始字符串截取位置；m：main.cpp中的jp
std::vector<unsigned char>Je();
//cmp指令，比较指令
std::vector<unsigned char>Cmp(const std::string& str, int n, int num);
//移位指令,cmd_ch告诉程序是shr右移，还是shl左移，这两个的区别是翻译后的第二个机器码，shr：0xe8~0xef；shl:0xe0~0xe7
std::vector<unsigned char>Shl_Shr(const std::string& str, int n, int num, unsigned char cmd_ch);

//处理jbe语句。
std::vector<unsigned char>Jbe();

//处理jb语句。
std::vector<unsigned char>Jb();

//用于in，out指令，w用来判断是in还是out，如果w=i，为in，如果是w=o，那么是out指令；
std::vector<unsigned char>In_Out(const std::string& str, int n, int num, char w);

std::vector<unsigned char>Logic(const std::string& str, int n, int num, char w);

//not取反指令
std::vector<unsigned char>Not(const std::string& str, int n);
//mul乘法指令
std::vector<unsigned char>Mul(const std::string& str, int n);