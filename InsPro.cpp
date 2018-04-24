/*InsPro.cpp用来定义指令编译函数*/
#include<string>
#include<iostream>
#include<vector>
#include<ctype.h>
//*自定义头文件
//#include"MyRegister.h"
#include"assistFun.h"
#include"HelpInsPro.h"
#include"MyRegister.h"
#include"Struct_self.h"

//str：字符串；n：起始位置；num：主文件（main.cpp）的Number
std::vector<unsigned char>Move1( STRINF *m1, STRINF *m2,int num)
{
	using namespace std;
	vector<unsigned char>data;
	vector<unsigned char>w;
	unsigned char a,b,c,c_s,d,f;
	string ch[2];
	ch[0] = m1->str;
	ch[1] = m2->str;
	//ch[0] = CutStr(str,n);
	//ch[1] = CutStr(str, str.find(',')+1);
	//cout << ch[0] << '\t' << ch[1] << endl;
	a=TwoRegBin(ch,1);
	b=TwoRegBin(ch,2);
	c=TwoRegBin(ch,3);
	c_s = TwoRegBin(ch, 4);
	//检查是否为寄存器之间赋值
	if (a){
		data.push_back(0x88);
		data.push_back(a);
		return data;
	}
	else if (b){
		data.push_back(0x89);
		data.push_back(b);
		//cout << "**************" << endl;
		return data;
	}
	else if (c){
		data.push_back(0x8c);
		data.push_back(c);
		return data;
	}
	else if (c_s){
		data.push_back(0x8e);
		data.push_back(c_s);
		return data;
	}
	else{
		d = RegACDB(ch[0], 1);//判断8位寄存器
		f = RegACDB(ch[0], 2);//判断16位寄存器
		if(d){//若d判真，说明符合高低位寄存器
			data.push_back(d);
			//首先判断是否为字符‘$’，如果是，写入3个空元素，是data的大小大于等于4,否则返回将寄存器后面的值转化后的结果
			if (ch[1] != "$"){
				//写入寄存器机器码后面的数值，其后可能是16进制或十进制字符串
				w = Num(ch[1], 1,num);
				if (w.size() > 0){
					data.insert(data.end(), w.begin(), w.end());
					return data;
				}
				else{
					//此时data的大小为4，便可确定此为标号
					data.insert(data.end(), 2, 0x00);
					data.push_back(2);
					return data;
				}
			}
			else {
				w = NumToUc(num, 1);
				data.insert(data.end(), w.begin(), w.end());
				return data;
			}
		}
		else if(f){
			data.push_back(f);//写入寄存器
			//同上
			if (ch[1] != "$"){
				//写入寄存器机器码后面的数值，其后可能是16进制或十进制字符串
				w = Num(ch[1], 2,num);
				//判断是否是标号字符串
				if (w.size() > 0){
					data.insert(data.end(), w.begin(), w.end());
					return data;
				}
				else{
					//此时data的大小为4，便可确定此为标号
					data.insert(data.end(), 2, 0x00);
					data.push_back(1);
					return data;
				}
			}
			else {
				w = NumToUc(num, 2);
				data.insert(data.end(), w.begin(), w.end());
				return data;
			}
		}
		else{
			cout << "参数MOV指令错误！error-005!" << endl;
			return data;
		}
		cout << "参数MOV指令错误！error-019!" << endl;
		return data;
	}
	//补充，之前没有发现段寄存器的赋值
	
	return data;
}

std::vector<unsigned char>Move2(const std::string& str,STRINF *m1, STRINF *m2, int num)
{
	using namespace std;
	vector<unsigned char>data;
	vector<unsigned char>d;
	//判断说明符为byte时
	if (m1->explain == "byte" || m1->explain == "BYTE"){
		//再判断是否有中括号
		if (m1->w){
			//有括号的话：
			if (m1->str == "bx" || m1->str == "BX"){
				return mov_push(str, 0xc6, 0x07, num, m1, m2);
			}
			//有括号的话：
			if (m1->str == "si" || m1->str == "SI"){
				return mov_push(str, 0xc6, 0x04, num, m1, m2);
			}
			if (m1->str == "di" || m1->str == "DI"){
				return mov_push(str, 0xc6, 0x05, num, m1, m2);
			}
			if (m1->str == "bp" || m1->str == "BP"){
				return mov_push(str, 0xc6, 0x00, num, m1, m2);
			}//可能是数值字符串的情况
			d = Num(m1->str, 2, num);
			if ((int)d.size() > 0){
				data = mov_push(str, 0xc6, 0x06, num, m1, m2);
				data.insert(data.end() - 1, d.begin(), d.end());
				return data;
			}
			//说明[]内既不是sp，bp，si，di，也不是数值字符串,不允许存在这种情况
			cout << "请检查本代码：" << str << endl;
			return data;
		}
		//当m1没有括号，然后判断m2是否有括号
		if (m2->w){//m2有括号时
			if (m2->explain == "word"){ cout << "警告-001，请勿指定为word：" << str << endl; }
			if (m1->str == "ax" || m1->str == "AX"){
				return BX_BP_SI_DI('b', 0,m2->explain, m2->str,num);
			}
			if (m1->str == "cx" || m1->str == "CX"){
				return BX_BP_SI_DI('b', 1, m2->explain, m2->str, num);
			}
			if (m1->str == "dx" || m1->str == "DX"){
				return BX_BP_SI_DI('b', 2, m2->explain, m2->str, num);
			}
			if (m1->str == "bx" || m1->str == "BX"){
				return BX_BP_SI_DI('b', 3, m2->explain, m2->str, num);
			}
			if (m1->str == "sp" || m1->str == "SP"){
				return BX_BP_SI_DI('b', 4, m2->explain, m2->str, num);
			}
			if (m1->str == "bp" || m1->str == "BP"){
				return BX_BP_SI_DI('b', 5, m2->explain, m2->str, num);
			}
			if (m1->str == "si" || m1->str == "SI"){
				return BX_BP_SI_DI('b', 6, m2->explain, m2->str, num);
			}
			if (m1->str == "di" || m1->str == "DI"){
				return BX_BP_SI_DI('b', 7, m2->explain, m2->str, num);
			}
			//64465465456****8位寄存器***********************
			if (m1->str == "al" || m1->str == "AL"){
				return BX_BP_SI_DI('b', 8, m2->explain, m2->str, num);
			}
			if (m1->str == "cl" || m1->str == "CL"){
				return BX_BP_SI_DI('b', 9, m2->explain, m2->str, num);
			}
			if (m1->str == "dl" || m1->str == "DL"){
				return BX_BP_SI_DI('b', 10, m2->explain, m2->str, num);
			}
			if (m1->str == "bl" || m1->str == "BL"){
				return BX_BP_SI_DI('b', 11, m2->explain, m2->str, num);
			}
			if (m1->str == "ah" || m1->str == "AH"){
				return BX_BP_SI_DI('b', 12, m2->explain, m2->str, num);
			}
			if (m1->str == "ch" || m1->str == "CH"){
				return BX_BP_SI_DI('b', 13, m2->explain, m2->str, num);
			}
			if (m1->str == "dh" || m1->str == "DH"){
				return BX_BP_SI_DI('b', 14, m2->explain, m2->str, num);
			}
			if (m1->str == "bh" || m1->str == "BH"){
				return BX_BP_SI_DI('b', 15, m2->explain, m2->str, num);
			}
			cout << "错误-011,请检查代码：" << str << endl;
			return data;
		}
	}
	//******************************************************************
	if (m1->explain == "word" || m1->explain == "WORD"){
		//再判断M1是否有中括号
		if (m1->w){
			//有括号的话：
			if (m1->str == "bx" || m1->str == "BX"){
				return mov_push(str, 0xc7, 0x07, num, m1, m2);
			}
			//有括号的话：
			if (m1->str == "si" || m1->str == "SI"){
				return mov_push(str, 0xc7, 0x04, num, m1, m2);
			}
			if (m1->str == "di" || m1->str == "DI"){
				return mov_push(str, 0xc7, 0x05, num, m1, m2);
			}
			if (m1->str == "bp" || m1->str == "BP"){
				return mov_push(str, 0xc7, 0x00, num, m1, m2);
			}//可能是数值字符串的情况
			d = Num(m1->str, 2, num);
			if ((int)d.size() > 0){
				data = mov_push(str, 0xc7, 0x06, num, m1, m2);
				data.insert(data.end() - 1, d.begin(), d.end());
				return data;
			}
			//说明[]内既不是sp，bp，si，di，也不是数值字符串,不允许存在这种情况
			cout << "请检查本代码：" << str << endl;
			return data;
		}
		//当m1没有括号，然后判断m2是否有括号
		if (m2->w){//m2有括号时
			if (m2->explain == "word"){ cout << "警告-001，请勿指定为word：" << str << endl; }
			if (m1->str == "ax" || m1->str == "AX"){
				return BX_BP_SI_DI('w', 0, m2->explain, m2->str, num);
			}
			if (m1->str == "cx" || m1->str == "CX"){
				return BX_BP_SI_DI('w', 1, m2->explain, m2->str, num);
			}
			if (m1->str == "dx" || m1->str == "DX"){
				return BX_BP_SI_DI('w', 2, m2->explain, m2->str, num);
			}
			if (m1->str == "bx" || m1->str == "BX"){
				return BX_BP_SI_DI('w', 3, m2->explain, m2->str, num);
			}
			if (m1->str == "sp" || m1->str == "SP"){
				return BX_BP_SI_DI('w', 4, m2->explain, m2->str, num);
			}
			if (m1->str == "bp" || m1->str == "BP"){
				return BX_BP_SI_DI('w', 5, m2->explain, m2->str, num);
			}
			if (m1->str == "si" || m1->str == "SI"){
				return BX_BP_SI_DI('w', 6, m2->explain, m2->str, num);
			}
			if (m1->str == "di" || m1->str == "DI"){
				return BX_BP_SI_DI('w', 7, m2->explain, m2->str, num);
			}
			//64465465456****8位寄存器***********************
			if (m1->str == "al" || m1->str == "AL"){
				return BX_BP_SI_DI('w', 8, m2->explain, m2->str, num);
			}
			if (m1->str == "cl" || m1->str == "CL"){
				return BX_BP_SI_DI('w', 9, m2->explain, m2->str, num);
			}
			if (m1->str == "dl" || m1->str == "DL"){
				return BX_BP_SI_DI('w', 10, m2->explain, m2->str, num);
			}
			if (m1->str == "bl" || m1->str == "BL"){
				return BX_BP_SI_DI('w', 11, m2->explain, m2->str, num);
			}
			if (m1->str == "ah" || m1->str == "AH"){
				return BX_BP_SI_DI('w', 12, m2->explain, m2->str, num);
			}
			if (m1->str == "ch" || m1->str == "CH"){
				return BX_BP_SI_DI('w', 13, m2->explain, m2->str, num);
			}
			if (m1->str == "dh" || m1->str == "DH"){
				return BX_BP_SI_DI('w', 14, m2->explain, m2->str, num);
			}
			if (m1->str == "bh" || m1->str == "BH"){
				return BX_BP_SI_DI('w', 15, m2->explain, m2->str, num);
			}
			cout << "错误-011,请检查代码：" << str << endl;
			return data;
		}
		cout << "错误--016，请检查代码：" << str << endl;
		return data;
	}
	//******************分割线****检查m1的中括号***********************
	if (m1->w){
		if (m1->str == "bx" || m1->str == "BX"){
			return acdb(0x89, 0x88, 0, m2->str);
		}
		if (m1->str == "bp" || m1->str == "BP"){
			return acdb(0x89, 0x88, 1, m2->str);
		}
		if (m1->str == "si" || m1->str == "SI"){
			return acdb(0x89, 0x88, 2, m2->str);
		}
		if (m1->str == "di" || m1->str == "DI"){
			return acdb(0x89, 0x88, 3, m2->str);
		}
		//当为数值字符串时
		num = IntNum(m1->str, num);
		if (num > -1){
			return acdb_m1_num(1,m2->str, m1->str, num);
		}
		cout << "错误--018，请检查代码：" << str << endl;
		return data;
	}
	//******************分割线****检查m2的中括号***********************
	if (m2->w){
		if (m2->str == "bx" || m2->str == "BX"){
			return acdb(0x8b,0x8a,0, m1->str);
		}
		if (m2->str == "bp" || m2->str == "BP"){
			return acdb(0x8b, 0x8a, 1, m1->str);
		}
		if (m2->str == "si" || m2->str == "SI"){
			return acdb(0x8b, 0x8a, 2, m1->str);
		}
		if (m2->str == "di" || m2->str == "DI"){
			return acdb(0x8b, 0x8a, 3, m1->str);
		}
		//当为数值字符串时
		num = IntNum(m2->str, num);
		if (num > -1){
			return acdb_m1_num(2,m1->str, m2->str, num);
		}
		cout << "错误--019，请检查代码：" << str << endl;
		return data;
	}
	return data;
}

std::vector<unsigned char>MOVE(const std::string& str, int k, int num)
{
	using namespace std;
	int str_size = str.size();
	//vector<unsigned char>data;
	//vector<unsigned char>d;
	string *ch;//ch1，ch2分别用来储存逗号前后的字符串（DEST 和 SRC）
	//跳过空格
	while (k < str_size && (str[k] == 0x20 || str[k] == '\t'))k++;
	ch = CS(str, k);//储存逗号前后两个字符串
	STRINF *m1 = hep(ch[0]);
	STRINF *m2 = hep(ch[1]);
	
	if (!m1->w && !m2->w){
		//没有括号时调用Move1，但要对一些情况作出警告
		if ((m1->explain == "byte" || m1->explain == "BYTE") && (m2->explain == "word" || m2->explain == "WORD"))cout << "警告，请勿使用word，程序将丢弃溢出部分,请检查代码：" << str << endl;
		return Move1(m1, m2, num);
	}//有括号时调用Move2
	//cout << "调用move2" << endl;
	return Move2(str, m1, m2, num);
}
//Data函数，用于处理DB,DW,DD指令,str:该行指令字符串；num：指令字符之后的一字节位置；fix：本指令占用的字节数
std::vector<unsigned char>DataBWD(const std::string& str, int k, int fix,int num)
{
	using namespace std;
	string ch;
	vector<unsigned char>data;
	vector<unsigned char>d;
	bool w = false;
	while (k < (int)str.size() && (str[k] == 0x20 || str[k] == '\t'))k++;
	while (k<(int)str.size() && str[k] != '\n' && str[k] != '\0'){
		if (!w&&str[k] == '"'){ w = true; k++; }
		if (w){
			if (str[k] == '"')break;
			data.push_back(str[k]);
			k++;
		}
		else{
			ch = CutStrDBWD(str, k);
			if ((int)ch.size() > 0)k = ch.size() + k + 1;
			else k++;
			d = Num(ch, fix, num);
			data.insert(data.end(), d.begin(), d.end());
		}
	}
	return data;
}

long Organ(const std::string& str, int n,int num)
{
	std::string m = CutStr(str, n);
	return IntNum(m,num);
}

int ReserveByte(const std::string& str, int n, int num)
{
	using namespace std;
	string ch = CutStr(str, n);
	return IntNum(ch,num);
}

std::vector<unsigned char>Additive(const std::string& str,int n,int num)
{
	using namespace std;

	vector<unsigned char>data;
	vector<unsigned char>w;
	unsigned char a, b, c, d, f;
	string ch[2];
	ch[0] = CutStr(str, n);
	ch[1] = CutStr(str, str.find(',') + 1);
	//cout << ch[0] << '\t' << ch[1] << endl;
	a = TwoRegBin(ch, 1);
	b = TwoRegBin(ch, 2);
	c = TwoRegBin(ch, 3);
	//检查是否为寄存器之间赋值
	if (a){
		//cout << "aaaaaaaaaaaaaaaa"<<endl;
		data.push_back(0x00);
		data.push_back(a);
		return data;
	}
	else if (b){
		//cout << "bbbbbbbbbbbbbbbbb" << endl;
		data.push_back(0x01);
		data.push_back(b);
		//cout << "**************" << endl;
		return data;
	}
	else if (c){
		cout << "段寄存器不能直接参与计算!-error-007!" << endl;
	}
	//说明ch[1]是一段数字字符串或标号
	//检查是否是ax寄存器
	else if (ch[0] == "ax" || ch[0] == "AX"){
		data.push_back(0x05);
		w = Num(ch[1], 2, num);
		data.insert(data.end(), w.begin(), w.end());
		return data;
	}
	else if (ch[0] == "al" || ch[0] == "AL"){
		data.push_back(0x04);
		w = Num(ch[1], 1, num);
		data.insert(data.end(), w.begin(), w.end());
		return data;
	}
	else{
		//判断寄存器位数
		d = regadd(ch[0], 1);//若返回值不为0，则说明ch[0]是8位寄存器名称
		f = regadd(ch[0], 2);//若返回值不为0，则说明ch[1]是16位寄存器名称
		if (d){
			//判断为8位寄存器
			data.push_back(0x80);
			data.push_back(d);
			w = Num(ch[1], 1, num);
			data.insert(data.end(), w.begin(), w.end());
			return data;
		}
		else if (f){
			//判断为16位寄存器
			if (IntNum(ch[1], num) > 0x7f){
				//数值应转换为2字节
				w = Num(ch[1], 2, num);
				data.push_back(0x81);
				data.push_back(f);
				data.insert(data.end(), w.begin(), w.end());
				return data;
			}
			else{
				w = Num(ch[1], 1, num);
				data.push_back(0x83);
				data.push_back(f);
				data.insert(data.end(), w.begin(), w.end());
				return data;
			}
		}
	}
	return data;
}

std::vector<unsigned char>Subtraction(const std::string& str, int n, int num)
{
	using namespace std;
	vector<unsigned char>data;
	vector<unsigned char>w;
	unsigned char a, b, c, d, f;
	string ch[2];
	ch[0] = CutStr(str, n);
	ch[1] = CutStr(str, str.find(',') + 1);
	//cout << ch[0] << '\t' << ch[1] << endl;
	a = TwoRegBin(ch, 1);
	b = TwoRegBin(ch, 2);
	c = TwoRegBin(ch, 3);
	//检查是否为寄存器之间赋值
	if (a){
		//cout << "aaaaaaaaaaaaaaaa"<<endl;
		data.push_back(0x28);
		data.push_back(a);
		return data;
	}
	else if (b){
		//cout << "bbbbbbbbbbbbbbbbb" << endl;
		data.push_back(0x29);
		data.push_back(b);
		//cout << "**************" << endl;
		return data;
	}
	else if (c){
		cout << "段寄存器不能直接参与计算!-error-007!" << endl;
	}
	//说明ch[1]是一段数字字符串或标号
	//检查是否是ax寄存器
	else if (ch[0] == "ax" || ch[0] == "AX"){
		data.push_back(0x2d);
		w = Num(ch[1], 2, num);
		data.insert(data.end(), w.begin(), w.end());
		return data;
	}
	else if (ch[0] == "al" || ch[0] == "AL"){
		data.push_back(0x2c);
		w = Num(ch[1], 1, num);
		data.insert(data.end(), w.begin(), w.end());
		return data;
	}
	else{
		//判断寄存器位数
		d = regsub(ch[0], 1);//若返回值不为0，则说明ch[0]是8位寄存器名称
		f = regsub(ch[0], 2);//若返回值不为0，则说明ch[1]是16位寄存器名称
		if (d){
			//判断为8位寄存器
			data.push_back(0x80);
			data.push_back(d);
			w = Num(ch[1], 1, num);
			data.insert(data.end(), w.begin(), w.end());
			return data;
		}
		else if (f){
			//判断为16位寄存器
			if (IntNum(ch[1], num) > 0x7f){
				//数值应转换为2字节
				w = Num(ch[1], 2, num);
				data.push_back(0x81);
				data.push_back(f);
				data.insert(data.end(), w.begin(), w.end());
				return data;
			}
			else{
				w = Num(ch[1], 1, num);
				data.push_back(0x83);
				data.push_back(f);
				data.insert(data.end(), w.begin(), w.end());
				return data;
			}
		}
	}
	return data;
}
//处理jmp语句。str:字符串；n：起始字符串截取位置；m：main.cpp中的jp
std::vector<unsigned char>Jemp()
{
	//直接返回0xeb，0x00
	std::vector<unsigned char>data{ 0xeb, 0x00 };
	return data;
}

//处理je语句。
std::vector<unsigned char>Je()
{
	//直接返回0x74，0x00
	std::vector<unsigned char>data{ 0x74, 0x00 };
	return data;
}

//处理jbe语句。
std::vector<unsigned char>Jbe()
{
	//直接返回0x76，0x00
	std::vector<unsigned char>data{ 0x76, 0x00 };
	return data;
}

//处理jbe语句。
std::vector<unsigned char>Jb()
{
	//直接返回0x72，0x00
	std::vector<unsigned char>data{ 0x72, 0x00 };
	return data;
}

std::vector<unsigned char>Push(const std::string& str, int n,int num)
{
	using namespace std;
	vector<unsigned char>data;
	vector<unsigned char>d;
	string ch;
	ch = CutStr(str,n);
	if (ch == "AX" || ch == "ax"){
		data.push_back(0x50);
		return data;
	}
	else if (ch == "CX" || ch == "cx"){
		data.push_back(0x51);
		return data;
	}
	else if (ch == "DX" || ch == "dx"){
		data.push_back(0x52);
		return data;
	}
	else if (ch == "BX" || ch == "bx"){
		data.push_back(0x53);
		return data;
	}
	else if (ch == "SP" || ch == "sp"){
		data.push_back(0x54);
		return data;
	}
	else if (ch == "BP" || ch == "bp"){
		data.push_back(0x55);
		return data;
	}
	else if (ch == "SI" || ch == "si"){
		data.push_back(0x56);
		return data;
	}
	else if (ch == "DI" || ch == "di"){
		data.push_back(0x57);
		return data;
	}
	else if (ch == "ES" || ch == "es"){
		data.push_back(0x6);
		return data;
	}
	else if (ch == "CS" || ch == "cs"){
		data.push_back(0xe);
		return data;
	}
	else if (ch == "SS" || ch == "ss"){
		data.push_back(0x16);
		return data;
	}
	else if (ch == "DS" || ch == "ds"){
		data.push_back(0x1e);
		return data;
	}
	else {
		int k = IntNum(ch, num);
		if (k > 0x7f){
			data.push_back(0x68);
			d = Num(ch, 2, num);
			data.insert(data.end(), d.begin(), d.end());
			return data;
		}
		else if(k>=0&&k<0x80){
			data.push_back(0x6a);
			d = Num(ch, 1, num);
			data.insert(data.end(), d.begin(), d.end());
			return data;
		}
		else{
			return data;
			//如果返回data大小为0，说明为标号
		}
	}
}

std::vector<unsigned char>Pop(const std::string& str, int n)
{
	using namespace std;
	vector<unsigned char>data;
	vector<unsigned char>d;
	string ch;
	ch = CutStr(str, n);
	if (ch == "AX" || ch == "ax"){
		data.push_back(0x58);
		return data;
	}
	else if (ch == "CX" || ch == "cx"){
		data.push_back(0x59);
		return data;
	}
	else if (ch == "DX" || ch == "dx"){
		data.push_back(0x5a);
		return data;
	}
	else if (ch == "BX" || ch == "bx"){
		data.push_back(0x5b);
		return data;
	}
	else if (ch == "SP" || ch == "sp"){
		data.push_back(0x5c);
		return data;
	}
	else if (ch == "BP" || ch == "bp"){
		data.push_back(0x5d);
		return data;
	}
	else if (ch == "SI" || ch == "si"){
		data.push_back(0x5e);
		return data;
	}
	else if (ch == "DI" || ch == "di"){
		data.push_back(0x5f);
		return data;
	}
	else if (ch == "ES" || ch == "es"){
		data.push_back(0x7);
		return data;
	}
	else if (ch == "CS" || ch == "cs"){
		data.push_back(0xf);
		return data;
	}
	else if (ch == "SS" || ch == "ss"){
		data.push_back(0x17);
		return data;
	}
	else if (ch == "DS" || ch == "ds"){
		data.push_back(0x1f);
		return data;
	}
	else {
		cout << "请检查pop指令:" << str << endl;
	}
	return data;
}
//INT指令为显卡调用指令,是一种中断指令
std::vector<unsigned char>Int(std::string& str,int n,int num)
{
	using namespace std;
	vector<unsigned char>data;
	vector<unsigned char>d;
	data.push_back(0xcd);
	str = CutStr(str, n);
	d = Num(str, 1, num);
	data.push_back(d[0]);
	return data;
}

//cmp指令，比较指令
std::vector<unsigned char>Cmp(const std::string& str,int n,int num)
{
	using namespace std;
	vector<unsigned char>data;
	vector<unsigned char>d;
	long str_size = str.size();
	short a;//用来储存说明字符串类型，byte为1，word为2
	string *ch;
	unsigned char w[] = {0xf8,0xf9,0xfa,0xfb,0xfc,0xfd,0xfe,0xff};
	unsigned char a1, a2;
	while (n<str_size && (str[n] == 0x20 || str[n] == '\t'))n++;
	ch = CS(str,n);
	STRINF *cm0 = hep(ch[0]);
	STRINF *cm1 = hep(ch[1]);
	ch[0] = cm0->str;
	ch[1] = cm1->str;
	a1 = TwoRegBin(ch, 1);//8位寄存器之间
	a2 = TwoRegBin(ch, 2);//16位寄存器之间
	if (a1){
		data.push_back(0x38);
		data.push_back(a1);
		return data;
	}
	if (a2){
		data.push_back(0x39);
		data.push_back(a2);
		return data;
	}
	if (cm1->explain == "byte" || cm1->explain == "BYTE")a = 1;
	if (cm1->explain == "word" || cm1->explain == "WORD")a = 2;
	for (int i = 0; i < 16; ++i){
		if (reg2[i] == cm0->str){
			if (i==0 ||i==8){
				data.push_back(0x3d);
				d = Num(cm1->str, 2, num);
				data.insert(data.end(), d.begin(), d.end());
				return data;
			}
			str_size = IntNum(cm1->str,num);
			if (str_size>0x7f)a = 2;
			else a = 1;
			d = NumToUc(str_size, a);
			data.push_back(0x85 - 2 * a);
			if (i>8)data.push_back(w[i-8]);
			else data.push_back(w[i]);
			data.insert(data.end(), d.begin(), d.end());
			return data;

		}
		if (reg_1[i] == cm0->str){
			if (i == 0 || i == 8){
				data.push_back(0x3c);
				d = Num(cm1->str, 1, num);
				data.push_back(d[0]);
				return data;
			}
			data.push_back(0x80);
			if (i>8)data.push_back(w[i - 8]);
			else data.push_back(w[i]);
			d = Num(cm1->str, 1, num);
			data.push_back(d[0]);
			return data;

		}
	}
	cout << "错误，请检查代码：" << str << endl;
	return data;
}

//移位指令,cmd_ch告诉程序是shr右移，还是shl左移，这两个的区别是翻译后的第二个机器码，shr：0xe8~0xef；shl:0xe0~0xe7
std::vector<unsigned char>Shl_Shr(const std::string& str, int n, int num,unsigned char cmd_ch)
{
	using namespace std;
	string *ch;
	ch = CS(str, n);//CS函数用来截取‘，’两边的目标寄存器，和源操作数，自动去除空格
	unsigned char m[2] = {0};
	vector<unsigned char>data;
	vector<unsigned char>d;
	for (int i = 0; i < 16; ++i){
		if (ch[0] == reg_1[i]){
			m[0] = 0xc0;
			if (i>7)m[1] = cmd_ch + i - 8;
			else m[1] = cmd_ch + i;

		}
		if (ch[0] == reg2[i]){
			m[0] = 0xc1;
			if (i>7)m[1] = cmd_ch + i - 8;
			else m[1] = cmd_ch + i;
		}
	}
	d = Num(ch[1], 1, num);
	if ((int)d.size() > 0 && m[0] != 0 && m[1] != 0){
		data.push_back(m[0]);
		data.push_back(m[1]);
		data.push_back(d[0]);
		return data;
	}
	cout << "错误-021，请检查指令：" << str << endl;
	return data;
}
//用于in，out指令，w用来判断是in还是out，如果w=i，为in，如果是w=o，那么是out指令；
std::vector<unsigned char>In_Out(const std::string& str, int n, int num,char w)
{
	using namespace std;
	string *ch = CS(str, n);
	vector<unsigned char>d=Num(ch[1],1,num);
	vector<unsigned char>data;
	unsigned char ax_ch=0xe5, al_ch=0xe4,ax_dx=0xed,al_dx=0xec;
	if (w = 'o'){
		ax_ch = 0xe7; al_ch = 0xe6; ax_dx = 0xef; al_dx = 0xee;
	}
	else if (w != 'i'){
		cout << "请检查判断" << endl; return data;
	}
	if ((ch[0] == "ax" || ch[0] == "AX") && (int)d.size() > 0){
		data.push_back(ax_ch);
		data.push_back(d[0]);
		return data;
	}
	if ((ch[0] == "al" || ch[0] == "AL") && (int)d.size() > 0){
		data.push_back(al_ch);
		data.push_back(d[0]);
		return data;
	}
	if ((ch[0] == "ax" || ch[0] == "AX") && (ch[0] == "dx" || ch[0] == "DX")){
		data.push_back(ax_dx);
		return data;
	}
	if ((ch[0] == "al" || ch[0] == "AL") && (ch[0] == "dx" || ch[0] == "DX")){
		data.push_back(al_dx);
		return data;
	}
	cout << "错误-022，请检查代码：" << str << endl;
	return data;
}
//用于and、or、xor指令，w取值为‘a’‘o’‘x’,分别对应
std::vector<unsigned char>Logic(const std::string& str, int n, int num, char w_n)
{
	using namespace std;
	vector<unsigned char>data;
	string *ch = CS(str, n);
	unsigned char dt8 = 0, dt16 = 0, dt_ax = 0, dt_al = 0, dt8_num = 0, dt16_num[2] = {0};

	unsigned char a, b;
	const unsigned char *mm;
	if (w_n == 'a'){
		//寄存器之间
		dt8 = 0x20;
		dt16 = 0x21;
		//寄存器，数值
		dt_al = 0x24;
		dt_ax = 0x25;
		dt8_num = 0x80;
		dt16_num[0] = 0x81;//当操作数大于0x80时
		dt16_num[1] = 0x83;//当操作数小于0x80时
		mm = logic_and;
	}
	else if (w_n == 'o'){
		//寄存器之间
		dt8 = 0x08;
		dt16 = 0x09;
		//寄存器，数值
		dt_al = 0x0c;
		dt_ax = 0x0d;
		dt8_num = 0x80;
		dt16_num[0] = 0x81;//当操作数大于0x80时
		dt16_num[1] = 0x83;//当操作数小于0x80时
		mm = logic_or;
	}
	else if (w_n == 'x'){
		//寄存器之间
		dt8 = 0x30;
		dt16 = 0x31;
		//寄存器，数值
		dt_al = 0x34;
		dt_ax = 0x35;
		dt8_num = 0x80;
		dt16_num[0] = 0x81;//当操作数大于0x80时
		dt16_num[1] = 0x83;//当操作数小于0x80时
		mm = logic_xor;
	}
	else{
		cout << "错误-025，请检查login（）参数：" << w_n << endl;
		return data;
	}
	a = TwoRegBin(ch, 1);//检查是否是8位寄存器
	b = TwoRegBin(ch, 2);//检查是否是16位寄存器
	if (a){
		data.push_back(dt8);
		data.push_back(a);
		return data;
	}
	if (b){
		data.push_back(dt16);
		data.push_back(b);
		return data;
	}
	vector<unsigned char>d;
	int k = IntNum(ch[1], num);
	cout << "k=" << k << endl;
	d = NumToUc(k, 2);
	cout << "d=" << hex<< (int)d[0] << endl;
	if (d.size() <= 0){
		cout << "错误-023，请检查指令:" << str << endl;
		return data;
	}
	for (int i = 0; i < 16; ++i){
		if (ch[0] == reg_1[i]){
			if (i == 0 || i == 8){//判断为al寄存器
				data.push_back(dt_al);
				data.push_back(d[0]);
				return data;
			}
			data.push_back(dt8_num);
			if (i>7)data.push_back(mm[i - 8]);
			else data.push_back(mm[i]);
			data.push_back(d[0]);
			return data;
		}
		if (ch[0] == reg2[i]){
			if (i == 0 || i == 8){
				data.push_back(dt_ax);
				data.push_back(d[0]);
				data.push_back(d[1]);
				return data;
			}
			if (k > 0x7f) data.push_back(dt16_num[0]);
			else data.push_back(dt16_num[1]);
			if (i > 7)data.push_back(mm[i - 8]);
			else data.push_back(mm[i]);
			data.push_back(d[0]);
			if (k >0x7b)data.push_back(d[1]);
			return data;
		}
	}
	cout << "错误-024，请检查指令:" << str << endl;
	return data;
}
//not取反指令
std::vector<unsigned char>Not(const std::string& str, int n)
{
	using namespace std;
	string ch = CutStr(str, n);
	vector<unsigned char>data;
	for (int i = 0; i < 16; ++i){
		if (ch == reg_1[i]){
			data.push_back(0xf6);
			if (i>7)data.push_back(logic_not[i - 8]);
			else data.push_back(logic_not[8]);
			return data;
		}
		if (ch == reg2[i]){
			data.push_back(0xf7);
			if (i>7)data.push_back(logic_not[i - 8]);
			else data.push_back(logic_not[8]);
			return data;
		}
	}
	cout << "错误-026，请检查代码:" << str << endl;
	return data;
}

//mul乘法指令
std::vector<unsigned char>Mul(const std::string& str, int n)
{
	using namespace std;
	string ch = CutStr(str, n);
	vector<unsigned char>data;
	for (int i = 0; i < 16; ++i){
		if (ch == reg_1[i]){
			data.push_back(0xf6);
			if (i>7)data.push_back(logic_and[i - 8]);
			else data.push_back(logic_and[8]);
			return data;
		}
		if (ch == reg2[i]){
			data.push_back(0xf7);
			if (i>7)data.push_back(logic_and[i - 8]);
			else data.push_back(logic_and[8]);
			return data;
		}
	}
	//判断是否有括号
	int lk, rk, str_size = str.size();
	lk=str.find('[');
	rk = str.find(']');
	if (lk < str_size && rk < str_size && !(rk < 0) && !(lk < 0)){
		ch.clear();
		while (n <str_size && (str[n] == 0x20 || str[n] == '\t'))n++;
		while (n < str_size && (str[n] != '\n' || str[n] == '\0')){
			if (str[n] == 0x20 || str[n] == '\t')break;
			if (isalnum(str[n]))ch.push_back(str[n]);
			n++;
		}
		if (ch == "word" || ch == "WORD")data.push_back(0xf7);
		else if (ch == "byte" || ch == "BYTE")data.push_back(0xf6);
		else {
			cout << "错误-027，请检查代码:" << str << endl; return data;
		}
		ch.clear(); ch = str.substr(lk+1, rk - lk-1);
		cout << "**************" << ch << endl;
		if (ch == "bx" || ch == "BX"){
			data.push_back(0x27); return data;
		}
		else if (ch == "bp" || ch == "BP"){
			data.push_back(0x66); data.push_back(0x00);
			return data;
		}
		else if (ch == "si" || ch == "SI"){
			data.push_back(0x24); return data;
		}
		else if (ch == "di" || ch == "DI"){
			data.push_back(0x25); return data;
		}
		else {
			data.clear();
			cout << "错误-028，请检查代码:" << str << endl; return data;
		}
	}
	cout << "错误-029，请检查代码:" << str << endl; return data;
	return data;
}