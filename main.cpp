#include<iostream>
#include<string>
#include<fstream>
#include<stdio.h>
#include<ctype.h>
#include<vector>
//自定义头文件
#include"assistFun.h"
#include"InsPro.h"
#include"HelpInsPro.h"
#include"Struct_self.h"
#include"def_cc.h"

#define REG_16 data[0]==AX_HEX || data[0]==CX_HEX || data[0]==DX_HEX || data[0]==BX_HEX || data[0]==SP_HEX || data[0]==BP_HEX || data[0]==SI_HEX || data[0]==DI_HEX
#define REG_8 data[0]==AL_HEX || data[0]==CL_HEX || data[0]==DL_HEX || data[0]==BL_HEX || data[0]==AH_HEX || data[0]==CH_HEX || data[0]==DH_HEX || data[0]==BH_HEX

int FileSize=0;//储存生成的文件大小
int Number=0;//储存偏移地址
int Line_num = 0;//行号
std::vector<unsigned char>Data;//储存输出数据流

std::string fin_src="d:\\123.txt";//源文件路径
std::string fout_src="d:\\1.bin";//生成的文件路径

std::ofstream fout(fout_src, std::ios::binary);
//std::ifstream fin(fin_src);//定义输入文件流对象
//std::ofstream fout(fout_src,std::ios::binary);//定义输出文件流对象

std::vector<ReTitle>Title;//定义标号数组，储存编译过程中找到的标号
ReTitle t;//作为中间变量

std::vector<ReTitle>Mov_place;//储存Mov指令遇到的标号
std::vector<ReTitle>jp_p;//储存jmp指令遇到的标号
std::vector<ReTitle>push_p;//储存jmp指令遇到的标号
std::vector<ReTitle>je_p;//储存je指令遇到的标号
std::vector<ReTitle>jbe_p;//储存je指令遇到的标号
std::vector<ReTitle>jb_p;//储存je指令遇到的标号


bool is_Title=false;//标志位，若此值为true说明CutStrCode()函数在代码行中找到了‘:’
//若表达式为真，判断后应重新赋值为false

//此处定义会用到的函数******************************************************************
void CompileCode();//处理源文件流文本代码，生成对应的二进制文件
void Data_put(std::vector<unsigned char>m);//像data数组推入数据流
void EndCode();
std::string CutStrCode(const std::string& str,int num);//判断是否含有冒号，并返回截取的指令字符串
void FileOut(std::vector<unsigned char>d);//将Data数组写入文件
void DataChar(int n, unsigned char ch);//向数组写入指定字节
void jmpch();//对jmp指令的后续处理
void f();
void f123(void);
//END************************************************************************************
//STRINF *hep(const std::string& str);
//主函数
int main()
{
	using namespace std;
	f123();
	/*string ch[2] = {"CX","DX"};
	cout << hex << (int)TwoRegBin(ch, 2);
	cin.get();*/
	return 0;
}

void f123(void)
{
	using namespace std;
	CompileCode();//处理源文件流文本代码，生成对应的二进制文件
	EndCode();//处理文件中不能马上确定二进制值的位置，进行收尾工作
	FileOut(Data);
	fout.close();
	cout << "编译完成" << endl;
	cout << "写入字节数：" << FileSize + 1 << 0x20 << "byte" << endl;
	//f();//f()检测与目标文件的不同
	std::cin.get();
}

void CompileCode()
{
	using namespace std;
	ifstream fin(fin_src);
	int i=0;//line中字符的位置
	string Line;//储存一行文本
	string CodeStr;//储存指令字符串
	vector<unsigned char>d;
	while(getline(fin,Line)){
		//处理本行文本
		while(i<(int)Line.size() && Line[i] !='\n' &&Line[i]!='\0' &&Line[i]!=';'){
			//跳过空格，TAB
			if(Line[i]==0x20 || Line[i]=='\t' || Line[i]==':' || Line[i]==','){
				i++;continue;
			}
			cout << Line << endl;//输出正在处理的文本行
			//判断是否包含标号（代码中有没有冒号‘：’）
			CodeStr=CutStrCode(Line,i);
			//cout <<"CodeStr:"<< CodeStr << endl;
			i+=CodeStr.size();
			if(is_Title){
				//cout << "///" << endl;
				t.str=CodeStr;
				t.num=Number;
				t.s=FileSize;
				Title.push_back(t);
				is_Title=false;
			}
			else{//进入指令判断
				if(MOV){
					d = MOVE(Line, i, Number);
					if (d.size() >1 && d.size()<4){
						Data_put(d);
					}
					else if (d.size()>3){
						//判断为标号,保存标号字符串
						t.str = CutStr(Line, Line.find(',') + 1);
						t.s = FileSize;
						t.num = Number;
						Mov_place.push_back(t);
						//存入数组
						Data.insert(Data.end(), d.begin(), d.end() - (int)d[3]);
						FileSize += (d.size() - (int)d[3]);
						Number += (d.size() - (int)d[3]);
					}
				}
				else if(DB){
					Data_put(DataBWD(Line, i, 1, Number));
				}
				else if(DW){
					Data_put(DataBWD(Line, i, 2, Number));
				}
				else if(DD){
					Data_put(DataBWD(Line, i, 4, Number));
				}
				else if(ADD){
					Data_put(Additive(Line, i, Number));
				}
				else if(SUB){
					Data_put(Subtraction(Line, i, Number));
				}
				else if (JMP){
					d = Jemp();
					//将标号推入jp数组
					t.str = CutStr(Line, i);
					t.s = FileSize;
					t.num = Number;
					Data_put(d);
					//cout << "t.str="<<t.str<<endl;
					jp_p.push_back(t);
				}
				else if (JE || JZ){
					d = Je();
					//将标号推入jp数组
					t.str = CutStr(Line, i);
					t.s = FileSize;
					t.num = Number;
					Data_put(d);
					//cout << "t.str="<<t.str<<endl;
					je_p.push_back(t);
				}
				else if (JB){
					d = Jb();
					//将标号推入jp数组
					t.str = CutStr(Line, i);
					t.s = FileSize;
					t.num = Number;
					Data_put(d);
					//cout << "t.str="<<t.str<<endl;
					jb_p.push_back(t);
				}
				else if (JBE){
					d = Jbe();
					//将标号推入jp数组
					t.str = CutStr(Line, i);
					t.s = FileSize;
					t.num = Number;
					Data_put(d);
					//cout << "t.str="<<t.str<<endl;
					jbe_p.push_back(t);
					
				}
				else if (SHR){
					Data_put(Shl_Shr(Line, i, Number,0xe8));
				}
				else if (SHR){
					Data_put(Shl_Shr(Line, i, Number, 0xe0));
				}
				else if(PUSH){
					d = Push(Line, i, Number);
					if ((int)d.size() > 0){
						Data_put(d);
					}
					else{
						//说明为标号，将标号值推入push_p数组
						t.str = CutStr(Line, i);
						t.num = Number;
						t.s = FileSize;
						push_p.push_back(t);
						//写入两个字节0x6a，0x00
						Data.push_back(0x6a);
						Data.push_back(0x00);
						Number += 2;
						FileSize += 2;
					}
				}
				else if(POP){
					Data_put(Pop(Line, i));
				}
				else if (CMP){
					Data_put(Cmp(Line, i,Number));
				}//乘法指令
				else if (MUL){
					cout << "*" << endl;
					Data_put(Mul(Line, i));
				}
				else if (OR){
					Data_put(Logic(Line, i, Number, 'o'));
				}
				else if (XOR){
					Data_put(Logic(Line, i, Number, 'x'));
				}
				else if (AND){
					Data_put(Logic(Line, i ,Number, 'a'));
				}
				else if (NOT){
					Data_put(Not(Line, i));
				}
				else if(RESB){
					DataChar(ReserveByte(Line, i, Number), NULL);
				}
				else if (INT){
					Data_put(Int(Line, i, Number));
				}
				else if (ORG){
					Number = Organ(Line, i,Number);
				}
				else if (HLT){
					Data.push_back(0xf4);
					FileSize++;
					Number++;
				}
				else if (IN){
					Data_put(In_Out(Line,i,Number,'i'));
				}
				else if (OUT){
					Data_put(In_Out(Line, i, Number, 'o'));
				}
				else {
					cout<<"该行指令无法识别，请检查输入！error-"<<Line_num<<endl<<endl;
				}
			}
			break;
		}
		//i=Line.size();//使i等于字符串最大长度，结束本行文本处理的循环
		///*第2个while的作用，过滤掉文本行开头的空格，跳格，注释，换行等无关字符
		i = 0;
		Line_num++;
	}
	//循环结束，开始将Data中的内容写入文件
	fin.close();
}

void EndCode()
{
	using namespace std;
	int i, j;
	std::vector<unsigned char>data;
	short d;
	for (i = 0; i < (int)Title.size(); ++i)
		for(j = 0; j < (int)Mov_place.size(); ++j){
			if (Title[i].str == Mov_place[j].str){
				d = isReg(Data[Mov_place[j].s]);
				//将计算结果代入data
				if (d == 1){
					data = NumToUc(Title[i].num, 1);
					Data[Mov_place[j].s + 1] = data[0];
				}
				else if (d == 2){
					data = NumToUc(Title[i].num, 2);
					//cout << "///////////" << Title[i].num << endl;
					Data[Mov_place[j].s + 1] = data[0];
					Data[Mov_place[j].s + 2] = data[1];
				}
				else{
					std::cout << "超范围！error-006!\n";
				}
			}
		}
		//处理jmp指令
		jmpch();
}

std::string CutStrCode(const std::string& str,int num=0)//判断是否含有标号，没有则返回指令字符串
{
	using namespace std;
	std::string m;
	//丢去开头部分可能存在的无关字符，0x20为空格
	while(num<(int)str.size()){
		if (str[num] != 0x20 && str[num]!='\t' &&str[num]!=',')break;
		num++;
	}
	//截取字符串
	while (num<(int)str.size()&&(isalnum(str[num]) || str[num] == '$' || str[num] == ':' || str[num] == '_')){
		if(str[num]==':'){
			//cout << "找到冒号" << endl;
			is_Title=true;
			break;
		}
		m.push_back(str[num]);num++;
	}
	return m;
}

void Data_put(std::vector<unsigned char>m)
{
	Data.insert(Data.end(),m.begin(),m.end());
	FileSize+=m.size();
	Number+=m.size();
}

void FileOut(std::vector<unsigned char>d = Data)
{
	using namespace std;
	for(int i=0;i<(int)d.size();i++){
		//cout<<(int)d[i]<<"*"<<endl;
		fout.put(d[i]);
		//FileSize++;
		//Number++;
	}

}

void DataChar(int n, unsigned char ch)
{
	Data.insert(Data.end(), n, ch);
	FileSize += n;
	Number += n;
}

void jmpch()
{
	using namespace std;
	int i, j,n, k=50;//k最高循环次数
	vector<unsigned char>d;
	for (i = 0; i<(int)Title.size(); i++)
	for (j = k - 1; j >= 0; j--){
		//------------------------语句块分割线-----------------------------//
		if (j<(int)jp_p.size()){//本语句避免数组调用超范围
			if (Title[i].str == jp_p[j].str){
				//jp数组处理
				n = Title[i].num - jp_p[j].num - 2;
				if (n>0x7f){//如果n=0x80，说明本jmp指令占3字符，将机器码更新为0xe9,0xxx,0xxx
					Data[jp_p[j].s] = 0xe9;
					//将n转换为对应的可输出机器码
					//cout << "n=" << n << endl;
					d = NumToUc(n-1, 2);
					Data[jp_p[j].s + 1] = d[0];
					Data.insert(Data.begin() + jp_p[j].s + 2, 1, d[1]);
				}
				else{
					d = NumToUc(n, 1);
					Data[jp_p[j].s + 1] = d[0];
					//cout << jp[j].s << endl;
					//cout << (int)Data[jp[j].s + 1] << endl;
				}
			}
		}
		//------------------------语句块分割线-----------------------------//
		if (j < (int)je_p.size()){
			if (Title[i].str == je_p[j].str){
				n = Title[i].num - je_p[j].num - 2;
				if (n>0x7f){
					Data[je_p[j].s] = 0x0f;
					Data[je_p[j].s + 1] = 0x84;
					d = NumToUc(n, 2);
					Data.insert(Data.begin() + je_p[j].s + 2, d.begin(), d.end());
				}
				else{
					d = NumToUc(n, 1);
					Data[je_p[j].s + 1] = d[0];
				}
			}
		}
		//------------------------语句块分割线-----------------------------//
		//JB语句
		if (j < (int)jb_p.size()){
			if (Title[i].str == jb_p[j].str){
				n = Title[i].num - jb_p[j].num - 2;
				if (n>0x7f){
					Data[jb_p[j].s] = 0x0f;
					Data[jb_p[j].s + 1] = 0x82;
					d = NumToUc(n , 2);
					Data.insert(Data.begin() + jb_p[j].s + 2, d.begin(), d.end());
				}
				else{
					d = NumToUc(n, 1);
					Data[jb_p[j].s + 1] = d[0];
				}
			}
		}
		//------------------------语句块分割线-----------------------------//
		if (j < (int)jbe_p.size()){
			if (Title[i].str == jbe_p[j].str){
				n = Title[i].num - jbe_p[j].num - 2;
				if (n>0x7f){
					Data[jbe_p[j].s] = 0x0f;
					Data[jbe_p[j].s + 1] = 0x86;
					d = NumToUc(n , 2);
					Data.insert(Data.begin() + jbe_p[j].s + 2, d.begin(), d.end());
				}
				else{
					d = NumToUc(n, 1);
					Data[jbe_p[j].s + 1] = d[0];
				}
			}
		}
		//------------------------语句块分割线-----------------------------//
		if (j<(int)push_p.size()){
			//push_p数组处理
			if (Title[i].str == push_p[j].str){
				//jp数组处理
				n = Title[i].num;
				if (n>0x7f){//如果n=0x80，说明本jmp指令占3字符，将机器码更新为0xe9,0xxx,0xxx
					Data[push_p[j].s] = 0x68;
					//将n转换为对应的可输出机器码
					d = NumToUc(n, 2);
					Data[push_p[j].s + 1] = d[0];
					Data.insert(Data.begin() + push_p[j].s + 2, 1, d[1]);
				}
				else{
					d = NumToUc(n, 1);
					Data[push_p[j].s + 1] = d[0];
				}
			}
		}
		//------------------------语句块分割线-----------------------------//
	}
}

//测试代码，比较nask输出值与本程序输出值的不同
void f()
{
	using namespace std;
	int w=0,m=0;
	unsigned char ch[2];
	//system("d:\\nask.exe d:\\123.txt d:\\nask123.bin");//执行bat，刷新nask输出文件

	ifstream filein1("d:\\nask123.bin", ios::binary);
	ifstream filein2(fout_src, ios::binary);
	while (!filein1.eof() && !filein2.eof()){
		w++;
		ch[0] = filein1.get();
		ch[1] = filein2.get();
		cout << w << "\t" << hex<<(short)ch[0] << "\t" <<hex<<(short)ch[1]<<"\t";
		if (ch[0]!=ch[1] ){
			m++;
			cout << m << ":" << w<<"\t";
		}
		cout << endl;
	}
	cout << endl << "循环次数:" << w << endl;
	cout << endl << "不同:" << m << endl;
	filein1.close();
	filein2.close();
}