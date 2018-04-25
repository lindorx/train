/*HelpInsPro.cpp用来定义InsPro中会用到的辅助函数*/
//编译系统头文件
#include<string>
#include<iostream>
#include<vector>
#include<ctype.h>
#include<math.h>
//自定义头文件
#include"MyRegister.h"
#include"assistFun.h"
#include"Struct_self.h"

//本函数用来处理mov指令中寄存器之间的赋值
//*ch为输入的字符串数组，a：为需要识别的类型，
//1:寄存器高位低位之间赋值；2:寄存器之间赋值；3:段寄存器赋给寄存器
unsigned char TwoRegBin(std::string *ch, int n)
{
	using namespace std;
	int i, j;
	int num1=16, num2=16;//储存数组大小
	int a, b;
	const string *m1,*m2;
	string ch0 = ch[0];
	string ch1 = ch[1];
	if (n == 1 ){
		m1 = reg_1;
		m2 = reg_1;
	}
	else if (n == 2){
		m1 = reg2;
		m2 = reg2;
	}
	else if (n == 3){
		num2 = 8;
		m1 = reg2;
		m2 = reg3;
	}
	else if (n == 4){
		ch0 = ch[1];
		ch1 = ch[0];
		num2 = 8;
		m1 = reg2;
		m2 = reg3;
	}
	else{
		std::cout << "TwoRegBin函数参数错误！error-002！\n";
		return 0;
	}
	a = num1 / 2 - 1;
	b = num2 / 2 - 1;
	for (i = 0; i<num1; i++)
	for (j = 0; j<num2; j++){
		if (ch0 == m1[i] && ch1 == m2[j]){
			if (i>a && j>b)return 0xc0 + i - a - 1 + (j - b - 1) * 8;
			if (i > a)return 0xc0 + (i - a - 1) + j * 8;
			if (j > b)return 0xc0 + i + (j - b - 1) * 8;
			return 0xc0 + i+j*8;
		}
	}
	return 0;
}

unsigned char RegACDB(const std::string& str, short num)
{
	if (num == 2){
		if (str == "AX")return AX_HEX;
		if (str == "CX")return CX_HEX;
		if (str == "DX")return DX_HEX;
		if (str == "BX")return BX_HEX;
		if (str == "SP")return SP_HEX;
		if (str == "BP")return BP_HEX;
		if (str == "SI")return SI_HEX;
		if (str == "DI")return DI_HEX;
		if (str == "ax")return AX_HEX;
		if (str == "cx")return CX_HEX;
		if (str == "dx")return DX_HEX;
		if (str == "bx")return BX_HEX;
		if (str == "sp")return SP_HEX;
		if (str == "bp")return BP_HEX;
		if (str == "si")return SI_HEX;
		if (str == "di")return DI_HEX;
	}
	else if (num == 1){
		if (str == "AH")return AH_HEX;
		if (str == "AL")return AL_HEX;
		if (str == "CH")return CL_HEX;
		if (str == "CL")return CH_HEX;
		if (str == "DH")return DH_HEX;
		if (str == "DL")return DL_HEX;
		if (str == "BH")return BH_HEX;
		if (str == "BL")return BL_HEX;
		if (str == "ah")return AH_HEX;
		if (str == "al")return AL_HEX;
		if (str == "ch")return CL_HEX;
		if (str == "cl")return CH_HEX;
		if (str == "dh")return DH_HEX;
		if (str == "dl")return DL_HEX;
		if (str == "bh")return BH_HEX;
		if (str == "bl")return BL_HEX;
	}
	return 0;
}

//HexOct输入一个十六进制字符，返回对应的整数
short HexOct(char ch)
{
	using namespace std;
	switch (ch){
	case '0':return 0;
	case '1':return 1;
	case '2':return 2;
	case '3':return 3;
	case '4':return 4;
	case '5':return 5;
	case '6':return 6;
	case '7':return 7;
	case '8':return 8;
	case '9':return 9;
	case 'a':return 10;
	case 'b':return 11;
	case 'c':return 12;
	case 'd':return 13;
	case 'e':return 14;
	case 'f':return 15;
	case 'A':return 10;
	case 'B':return 11;
	case 'C':return 12;
	case 'D':return 13;
	case 'E':return 14;
	case 'F':return 15;
	}
	std::cout << "HexOct参数错误！error-003！\n" ;
	return -1;
}
//IsHexNum输入一个字符，确认是否属于16进制字符
bool IsHexNum(const std::string& str)
{
	for (int i = 0; i < (int)str.size(); i++){
		if (!isxdigit(str[i]))return false;
	}
	return true;
}

//将一个整数转化为 unsigned char 数组，n:整数；num：输出数组元素数量
std::vector<unsigned char>NumToUc(long n,int num)
{
	std::vector<unsigned char>data;
	for (int i = 0; i<num; i++){
		data.push_back((unsigned char)(n >> (8 * i)));
	}
	return data;
}
//查找字符串中是否包含
char FoundMathChar(const std::string& str)
{
	for (int i = 0; i < (int)str.size(); ++i){
		switch (str[i]){
		case '+':return '+';
		case '-':return '-';
		case '*':return '*';
		case '/':return '/';
		}
	}
	return 0;
}

//将16进制或10进制字符串转化为整数。str:字符串;num:主文件中的number
long IntNum(const std::string& str,int num)
{
	using namespace std;
	int i, sum = 0, n = str.size();
	//查看是否有BYTE WORD等标识符
	char c = FoundMathChar(str);//查找运算符号
	if (c>0){
		string ch[2];
		long k[2] = {0};
		ch[0] = str.substr(0,str.find(c));
		ch[1] = str.substr(str.find(c)+1,n - str.find(c)-1);
		//此时，ch分别储存了运算符两边的数字字符串，调用IntNum函数转换为整数
		k[0] = IntNum(ch[0], num);
		k[1] = IntNum(ch[1], num);
		switch (c){
		case '+':return k[0] + k[1];
		case '-':return k[0] - k[1];
		case '*':return k[0] * k[1];
		case '/':return k[0] / k[1];
		case '$':return num;
		}
	}
	if (str[0] == '0' && (str[1] == 'x' || str[1] == 'X')){
		for (i = 2; i<n; ++i){
			sum += (int)pow(16.0, (double)(n - 1 - i))*HexOct(str[i]);
		}
		return sum;
	}
	else if (IsHexNum(str)){
		//将数字字符串转化为可供输出的格式
		for (i = 0; i < n; ++i){
			sum += (int)pow(10.0, (double)(n - i - 1))*HexOct(str[i]);
		}
		return sum;
	}
	else if (str == "$")return num;
	//可能是标号字符串
	return -1;
}
//将16进制或10进制字符串转化为合适写入文件的值。str:字符串；num:输出数组元素数量;a：main.cpp中的Number（即指令中的$），如输入的字符串无法转化为数组，则输出的数组大小为0；
std::vector<unsigned char>Num(const std::string& str, int num, int a)
{
	using namespace std;
	vector<unsigned char>data;
	int i, sum = 0, n = str.size();
	int w = IntNum(str, a);
	if (!(w < 0)){ return NumToUc(w, num); }
	else if (str[0] == '0' && (str[1] == 'x' || str[1] == 'X')){
		for (i = 2; i < n; ++i){
			sum += (int)pow(16.0, (double)(n - 1 - i))*HexOct(str[i]);
		}
		return NumToUc(sum, num);
	}
	else if (IsHexNum(str)){
		//将数字字符串转化为可供输出的格式
		for (i = 0; i < n; ++i){
			sum += (int)pow(10.0, (double)(n - i - 1))*HexOct(str[i]);
		}
		return NumToUc(sum, num);
		//cout << "Num转换错误，请确认为寄存器的赋值正确！error-004!" << endl;
		//可能是标号字符串,返回data的大小为0
	}
	return data;
}

unsigned char regadd(const std::string& str,int num)
{
	if (num == 2){
		if (str == "CX")return CX_ADD;
		if (str == "DX")return DX_ADD;
		if (str == "BX")return BX_ADD;
		if (str == "SP")return SP_ADD;
		if (str == "BP")return BP_ADD;
		if (str == "SI")return SI_ADD;
		if (str == "DI")return DI_ADD;

		if (str == "cx")return CX_ADD;
		if (str == "dx")return DX_ADD;
		if (str == "bx")return BX_ADD;
		if (str == "sp")return SP_ADD;
		if (str == "bp")return BP_ADD;
		if (str == "si")return SI_ADD;
		if (str == "di")return DI_ADD;
	}
	else if (num == 1){
		if (str == "cl")return CL_ADD;
		if (str == "dl")return DL_ADD;
		if (str == "bl")return BL_ADD;
		if (str == "ah")return AH_ADD;
		if (str == "ch")return CH_ADD;
		if (str == "dh")return DH_ADD;
		if (str == "bh")return BH_ADD;

		if (str == "CL")return CL_ADD;
		if (str == "DL")return DL_ADD;
		if (str == "BL")return BL_ADD;
		if (str == "AH")return AH_ADD;
		if (str == "CH")return CH_ADD;
		if (str == "DH")return DH_ADD;
		if (str == "BH")return BH_ADD;
	}
	return 0;
}

unsigned char regsub(const std::string& str, int num)
{
	if (num == 2){
		if (str == "CX")return CX_SUB;
		if (str == "DX")return DX_SUB;
		if (str == "BX")return BX_SUB;
		if (str == "SP")return SP_SUB;
		if (str == "BP")return BP_SUB;
		if (str == "SI")return SI_SUB;
		if (str == "DI")return DI_SUB;

		if (str == "cx")return CX_SUB;
		if (str == "dx")return DX_SUB;
		if (str == "bx")return BX_SUB;
		if (str == "sp")return SP_SUB;
		if (str == "bp")return BP_SUB;
		if (str == "si")return SI_SUB;
		if (str == "di")return DI_SUB;
	}
	else if (num == 1){
		if (str == "cl")return CL_SUB;
		if (str == "dl")return DL_SUB;
		if (str == "bl")return BL_SUB;
		if (str == "ah")return AH_SUB;
		if (str == "ch")return CH_SUB;
		if (str == "dh")return DH_SUB;
		if (str == "bh")return BH_SUB;

		if (str == "CL")return CL_SUB;
		if (str == "DL")return DL_SUB;
		if (str == "BL")return BL_SUB;
		if (str == "AH")return AH_SUB;
		if (str == "CH")return CH_SUB;
		if (str == "DH")return DH_SUB;
		if (str == "BH")return BH_SUB;
	}
	return 0;
}

//专用于mov指令的辅助函数
std::vector<unsigned char>mov_push(const std::string& str, unsigned char b, unsigned char a, int num, STRINF *m1, STRINF *m2)
{
	using namespace std;
	int ch_num;
	vector<unsigned char>d;
	vector<unsigned char>data;
	//本嵌套内的代码是对ch[1]段代码的处理
	if (m2->explain == "byte" || m2->explain == "BYTE"){
		//在这里ch[1]内不能有中括号，只能为数值字符串：
		if (!m2->w){
			d = Num(m2->str, 1, num);
			if (d.size() == 0){
				cout << "错误-008！,请检查本字符串：" << str << endl;
				return data;
			}
			else{
				data.push_back(b);
				if (a != 0x00)data.push_back(a);
				else{
					data.push_back(0x46);
					data.push_back(0x00);
				}
				data.push_back(d[0]);
				return data;
			}
		}
		else{
			cout << "错误-009,请检查本字符串：" << str << endl;
			return data;
		}
	}
	if (m2->explain == "word" || m2->explain == "WORD"){
		//当m1->explain == "byte"，m2->explain不能为"word"
		cout << "错误-010,请检查本字符串（不能为word）：" << str << endl;
		return data;
	}
	//当ch[1]内没有字长说明符时,也不会有中括号
	if (!m2->w){//没有括号时
		//判断是否为数字字符串
		ch_num = IntNum(m2->str, num);
		//if (ch_num<0){//小于0则说明为标号
		//cout << "*******" << m2->str << endl;
		if (ch_num>0xff)cout << "警告,不能大于0xff(编译程序将会丢弃溢出部分):" << str << endl;
		//正常转换为1字节，
		d = NumToUc(ch_num, 1);
		data.push_back(b);
		if (a != 0x00)data.push_back(a);
		else{
			data.push_back(0x46);
			data.push_back(0x00);
		}
		data.push_back(d[0]);
		return data;
	}
	cout << "请检查本行代码：" << str << endl;
	return data;
}

//cmd1:当cmd1=‘b’时，说明m1->explain=="byte",当cmd1=‘w’时，说明m1->explain=="word";
//cmd2:取值从0~15,分别对应 AX~DI,AL~BH。
//cmd1用来决定是否要加0x3e，cmd2决定目标寄存器类型
//explain，str对应m2的值
std::vector<unsigned char>BX_BP_SI_DI(char cmd1, char cmd2, std::string explain,std::string str,int num)
{
	using namespace std;
	bool n=false;
	short a=0, b=0;
	//定义数组
	

	vector<unsigned char>data;
	vector<unsigned char>d;
	if (cmd1 == 'b' && (cmd2 >= 0 && cmd2 < 8))n = true;//0<=cmd2<8说明为16位寄存器，只有16位寄存器前面指定了byte是需要推入0x3e
	if (cmd2 == 0){ a = 1; b = 0; }
	if (cmd2 == 1){ a = 1; b = 1; }
	if (cmd2 == 2){ a = 1; b = 2; }
	if (cmd2 == 3){ a = 1; b = 3; }
	if (cmd2 == 4){ a = 1; b = 4; }
	if (cmd2 == 5){ a = 1; b = 5; }
	if (cmd2 == 6){ a = 1; b = 6; }
	if (cmd2 == 7){ a = 1; b = 7; }
	if (cmd2 == 8){ a = 0; b = 0; }
	if (cmd2 == 9){ a = 0; b = 1; }
	if (cmd2 == 10){ a = 0; b = 2; }
	if (cmd2 == 11){ a = 0; b = 3; }
	if (cmd2 == 12){ a = 0; b = 4; }
	if (cmd2 == 13){ a = 0; b = 5; }
	if (cmd2 == 14){ a = 0; b = 6; }
	if (cmd2 == 15){ a = 0; b = 7; }
//*************************************************************
	if (str == "bx" || str == "BX"){
		if (n)
		data.push_back(0x3e);
		data.push_back(a1[a]);
		data.push_back(b1[b][0]);
		return data;
	}
	if (str == "bp" || str == "BP"){
		if (n)
		data.push_back(0x3e);
		data.push_back(a1[a]);
		data.push_back(b1[b][1]);
		data.push_back(0x00);
		return data;
	}
	if (str == "si" || str == "SI"){
		if (n)
		data.push_back(0x3e);
		data.push_back(a1[a]);
		data.push_back(b1[b][2]);
		
		return data;
	}
	if (str == "di" || str == "DI"){
		if (n)
		data.push_back(0x3e);
		data.push_back(a1[a]);
		data.push_back(b1[b][3]);
		return data;
	}
	//判断一下是否为数字字符串
	int number = IntNum(str, num);
	if (number>-1){//说明number是一个正数，取值有效
		if ((explain == "word" || explain == "WORD" || explain == "n") && cmd1 == 'b'&& cmd2<8){//对应的指令格式：mov byte 16位寄存器，[0x00]
			data.push_back(0x3e);
			data.push_back(0x8b);
			data.push_back(m_unch[cmd2]);
			d = NumToUc(number, 2);
			data.insert(data.end(), d.begin(), d.end());
			return data;
		}
		if (explain == "n" && cmd1 == 'b'&& cmd2 > 7){//对应的指令格式：mov byte 8位寄存器，[0x00]<==>mov 8位寄存器，[0x00]
			data.push_back(0x8a);
			data.push_back(m_unch[cmd2 - 8]);
			d = NumToUc(number, 2);
			data.insert(data.end(), d.begin(), d.end());
			return data;
		}
		if ((explain == "word" || explain == "WORD" || explain == "n") && cmd1 == 'w'&& cmd2<8){//对应的指令格式：mov word 16位寄存器，[0x00]<==>mov 16位寄存器，[0x00]
			if (cmd2 == 0)data.push_back(0xa1);
			else{
				data.push_back(0x8b);
				data.push_back(m_unch[cmd2]);
			}
			d = NumToUc(number, 2);
			data.insert(data.end(), d.begin(), d.end());
			return data;
		}
		if (explain == "n" && cmd1 == 'w'&& cmd2 > 7){//对应的指令格式：mov word 8位寄存器，[0x00];这种格式是错误的
			cout << "错误-012，请检查代码：" << str << endl;
			return data;
		}
		if ((explain == "byte" || explain == "BYTE") && cmd1 == 'b'&& cmd2<8){//对应指令格式 mov	byte 16位寄存器 ,byte [0x23]；错误，目标寄存器只能是8位寄存器
			cout << "错误-013，目标寄存器只能是8位寄存器:" <<str<< endl;
			return data;
		}
		if ((explain == "byte" || explain == "BYTE") && cmd1 == 'b'&& cmd2>7){//对应指令格式 mov	byte 8位寄存器 ,byte [0x23]；
			if (cmd2 == 8)data.push_back(0xa0);
			else{
				data.push_back(0x8a);
				data.push_back(m_unch[cmd2 - 8]);
			}
			d = NumToUc(number, 2);
			data.insert(data.end(), d.begin(), d.end());
			return data;
		}//************************************************
		if ((explain == "byte" || explain == "BYTE") && cmd1 == 'w'){//对应指令格式 mov	byte 16位寄存器 ,byte [0x23]；错误，目标寄存器只能是8位寄存器
			cout << "错误-014，目标寄存器只能是16位寄存器:" << str << endl;
			return data;
		}
		if ((explain == "word" || explain == "WORD") && cmd1 == 'b'){//错误
			cout << "错误-015，目标寄存器应指定为word:" << str << endl;
		}
	}
	cout << "[]内仅允许bx、bp、si、di,请检查代码：" << str << endl;
	return data;
}
//str：寄存器名称,a:0~3
std::vector<unsigned char>acdb(unsigned char n1,unsigned char n2,short a,std::string str)
{
	using namespace std;
	vector<unsigned char>data;
	for (int i = 0; i < 16; ++i){
		//判断是否为16位寄存器
		if (str == reg2[i]){
			data.push_back(n1);
			if (i>7)data.push_back(b1[i-8][a]);
			else data.push_back(b1[i][a]);
			if (a == 1)data.push_back(0x00);
			return data;
		}
		if (str == reg_1[i]){
			data.push_back(n2);
			if (i>7)data.push_back(b1[i - 8][a]);
			else data.push_back(b1[i][a]);
			if (a == 1)data.push_back(0x00);
			return data;
		}
	}
	cout << "请检查代码：" << str << endl;
	return data;
}
//cmd为控制数字，当cmd=1时，指令格式：mov [0x00],ax ；当cmd=2时，mov ax，[0x00]
std::vector<unsigned char>acdb_m1_num(short cmd,std::string str,std::string m1_str,int num)
{
	using namespace std;
	vector<unsigned char>data;
	vector<unsigned char>d = Num(m1_str, 2, num);
	unsigned char n_ax=0xa3,n_al=0xa2, n_16=0x89,n_8=0x88,n_s=0x8c;
	//处理cmd
	if (cmd == 2){
		n_ax = 0xa1;
		n_al = 0xa0;
		n_16 = 0x8b;
		n_8 = 0x8a;
		n_s = 0x8e;
	}
	for (int i = 0; i < 16; ++i){
		//判断是否为16位寄存器
		if (str == reg2[i]){
			if (i == 0 || i == 8)//reg[0]、reg[8]对应的字符串时ax，特殊情况
				data.push_back(n_ax);
			else{
				data.push_back(n_16);
				if (i>7)data.push_back(m_unch[i - 8]);
				else data.push_back(m_unch[i]);
			}
			data.insert(data.end(), d.begin(), d.end());
			return data;
		}
		//判断是否为8位寄存器
		if (str == reg2[i]){
			if (i == 0 || i == 8)//reg[0]、reg[8]对应的字符串时ax，特殊情况
				data.push_back(n_al);
			else{
				data.push_back(n_8);
				if (i>7)data.push_back(m_unch[i - 8]);
				else data.push_back(m_unch[i]);
			}
			data.insert(data.end(), d.begin(), d.end());
			return data;
		}
	}
	if (str == "es" || str == "ES"){
		data.push_back(n_s);
		data.push_back(0x06);
		data.insert(data.end(), d.begin(), d.end());
		return data;
	}
	if (str == "cs" || str == "CS"){
		data.push_back(n_s);
		data.push_back(0x0e);
		data.insert(data.end(), d.begin(), d.end());
		return data;
	}
	if (str == "ss" || str == "SS"){
		data.push_back(n_s);
		data.push_back(0x16);
		data.insert(data.end(), d.begin(), d.end());
		return data;
	}
	if (str == "ds" || str == "DS"){
		data.push_back(n_s);
		data.push_back(0x1e);
		data.insert(data.end(), d.begin(), d.end());
		return data;
	}
	cout << "错误--017,请检查：" << str<<endl;
	return data;
}
//专用于mov指令的辅助函数
STRINF *hep(const std::string& str)
{
	using namespace std;
	int str_size = str.size();
	int lk, rk, k;
	STRINF *m = new STRINF;
	//去除尾部的空格
	while (str_size>0 && (str[str_size - 1] == 0x20 || str[str_size - 1] == '\t'))str_size--;
	k = str.find(0x20);
	if (k >= str_size)k = str.find('\t');
	//k储存了空格的位置，如果有的话，否则k将是一个远大于字符串长度的值,或小于0的值
	if (k < str_size && k >= 0){
		m->explain = str.substr(0, k);
		lk = str.find('[');
		rk = str.find(']');
	
		if (lk < str_size && rk < str_size && lk >= 0 && rk >= 0){//判断中括号
			m->str = str.substr(lk + 1, rk - lk - 1);
			m->lk = lk;
			m->rk = rk;
			m->w = true;
			return m;
		}
		else{
			//跳过空格或者跳格
			while (k < str_size && (str[k] == 0x20 || str[k] == '\t'))k++;
			m->str = str.substr(k, str_size - k);
			m->lk = 0;
			m->rk = 0;
			m->w = false;
			return m;
		}
	}
	else{//没有空格
		m->explain = "n";//说明符设为n
		//查找中括号
		lk = str.find('[');
		rk = str.find(']');
		
		if (lk < str_size && rk < str_size && lk >= 0 && rk >= 0){
			m->str = str.substr(lk + 1, rk - lk - 1);
			m->lk = lk;
			m->rk = rk;
			m->w = true;
			return m;
		}
		else{
			m->str = str.substr(0,str_size);
			m->lk = 0; m->rk = 0;
			m->w = false;
			return m;
		}
	}
	return m;
}