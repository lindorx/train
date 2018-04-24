/*HelpInsPro.h头文件用来声明HelpInsPro.cpp*/
#pragma once
#include<string>
#include<vector>

#include"Struct_self.h"

//定义辅助函数

unsigned char RegACDB(const std::string& str, short num);

//返回两个寄存器赋值对应的操作码，1:8位寄存器；2:16位寄存器；3:（16位，段寄存器）；4：（段寄存器，16位）
unsigned char TwoRegBin(std::string *ch, int n);

//将16进制或10进制字符串转化为合适写入文件的值。str:字符串；num:输出数组元素数量;a:number
std::vector<unsigned char>Num(const std::string& str, int num,int a);

//将一个整数转化为 unsigned char 数组，n:整数；num：输出数组元素数量
std::vector<unsigned char>NumToUc(long n, int num);

//将16进制或10进制字符串转化为整数。str:字符串
long IntNum(const std::string& str,int num);

unsigned char regadd(const std::string& str, int num);

unsigned char regsub(const std::string& str, int num);
//处理含有空格或tab的字符串
std::vector<unsigned char>Num_cut(const std::string& str, int num);


//专用于mov指令的辅助函数
std::vector<unsigned char>mov_push(const std::string& str, unsigned char b, unsigned char a, int num, STRINF *m1, STRINF *m2);

//cmd1:当cmd1=‘b’时，说明m1->explain=="byte",当cmd1=‘w’时，说明m1->explain=="word";
//cmd2:取值从0~15,分别对应 AX~DI,AL~BH。
//cmd1用来决定是否要加0x3e，cmd2决定目标寄存器类型
//explain，str对应m2的值
std::vector<unsigned char>BX_BP_SI_DI(char cmd1, char cmd2, std::string explain, std::string str, int num);

//str：寄存器名称,a:0~3;n1/n2，分别是16位与8位寄存器的机器码
std::vector<unsigned char>acdb(unsigned char n1, unsigned char n2, short a, std::string str);

std::vector<unsigned char>acdb_m1_num(short cmd, std::string str, std::string m1_str, int num);

STRINF *hep(const std::string& str);