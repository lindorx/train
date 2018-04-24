#include<string>

#ifndef RET_H
#define RET_H
typedef struct ReT{
	std::string str;
	int num;//储存写入的值number
	int s;//储存位置AllNum
}ReTitle;
#endif

#ifndef STRUCT_H
#define STRUCT_H 
typedef struct STRINF{
	std::string explain;//将说明储存在这里（byte，word等）
	std::string str;//将字符串中括号内的字符保存在这里
	bool w;//字符串中是否有中括号
	int lk;//如果w=true，字符串中左中括号的位置
	int rk;//如果w=true，字符串中右中括号的位置
}STRINF;
#endif