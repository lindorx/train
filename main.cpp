#include<iostream>
#include<string>
#include<fstream>
#include<stdio.h>
#include<ctype.h>
#include<vector>
//�Զ���ͷ�ļ�
#include"assistFun.h"
#include"InsPro.h"
#include"HelpInsPro.h"
#include"Struct_self.h"
#include"def_cc.h"

#define REG_16 data[0]==AX_HEX || data[0]==CX_HEX || data[0]==DX_HEX || data[0]==BX_HEX || data[0]==SP_HEX || data[0]==BP_HEX || data[0]==SI_HEX || data[0]==DI_HEX
#define REG_8 data[0]==AL_HEX || data[0]==CL_HEX || data[0]==DL_HEX || data[0]==BL_HEX || data[0]==AH_HEX || data[0]==CH_HEX || data[0]==DH_HEX || data[0]==BH_HEX

int FileSize;//�������ɵ��ļ���С
int Number;//����ƫ�Ƶ�ַ
int Line_num;//�к�
std::vector<unsigned char>Data;//�������������

std::string fin_src;//Դ�ļ�·��
std::string fout_src;//���ɵ��ļ�·��

std::vector<ReTitle>Title;//���������飬�������������ҵ��ı��
ReTitle t;//��Ϊ�м����

std::vector<ReTitle>Mov_place;//����Movָ�������ı��
std::vector<ReTitle>jp_p;//����jmpָ�������ı��
std::vector<ReTitle>push_p;//����jmpָ�������ı��
std::vector<ReTitle>je_p;//����jeָ�������ı��
std::vector<ReTitle>jbe_p;//����jeָ�������ı��
std::vector<ReTitle>jb_p;//����jeָ�������ı��

bool is_Title;//��־λ������ֵΪtrue˵��CutStrCode()�����ڴ��������ҵ��ˡ�:��
//�����ʽΪ�棬�жϺ�Ӧ���¸�ֵΪfalse

//�˴�������õ��ĺ���******************************************************************
void CompileCode(void);//����Դ�ļ����ı����룬���ɶ�Ӧ�Ķ������ļ�
void Data_put(std::vector<unsigned char>m);//��data��������������
void EndCode(void);
std::string CutStrCode(const std::string& str, int num);//�ж��Ƿ���ð�ţ������ؽ�ȡ��ָ���ַ���
void FileOut(void);//��Data����д���ļ�
void DataChar(int n, unsigned char ch);//������д��ָ���ֽ�
void jmpch(void);//��jmpָ��ĺ�������
//END************************************************************************************
//������
int main(int argc, char* argv[])
{
	using namespace std;
	int i, n = 0;
	if (argc == 1)return 0;
	for (i = 1; i < argc; ++i) {
		FileSize = 0;//�������ɵ��ļ���С
	Number = 0;//����ƫ�Ƶ�ַ
	Line_num = 1;//�к�
	is_Title = false;//��־λ������ֵΪtrue˵��CutStrCode()�����ڴ��������ҵ��ˡ�:��,�����ʽΪ�棬�жϺ�Ӧ���¸�ֵΪfalse
		fin_src = argv[i];
		cout<<"code file="<<fin_src<<endl;
		if (fin_src.rfind(".asm") == 0) {//.asmΪ�������ļ���������ǣ��������룬����ʾ��׺������
			cout << "The suffix name is not \".asm\"" << endl;//��ʾ��׺�������⣬��������
		}
		n = fin_src.rfind(".");
		if (n == 0)return 0;
		fout_src = fin_src.substr(0, n)+".bin";
		CompileCode();//����Դ�ļ����ı����룬���ɶ�Ӧ�Ķ������ļ�
		EndCode();//�����ļ��в�������ȷ��������ֵ��λ�ã�������β����
		FileOut();
		cout << "file size=\t" << FileSize << "\tbyte" << endl<<endl;
	}
	cout << endl<<"compile done." << endl;
	return 0;
}
//CompileCode()ʶ��ʶ��ָ���ַ�������������Ӧ�Ĵ���
void CompileCode(void)
{
	using namespace std;
	ifstream fin(fin_src);
	if (!fin.is_open()){
		cout << "Դ�ļ���ʧ��!" << endl;
		return;
	}
	string Line;//����һ���ı�
	string CodeStr;//����ָ���ַ���
	vector<unsigned char>d;
	int i = 0;//line���ַ���λ��
	while (getline(fin, Line)) {
		cout << Line_num << "\t" << Line << endl;//������ڴ�����ı���
		//��2��while�����ã����˵��ı��п�ͷ�Ŀո�����ע�ͣ����е��޹��ַ�����֤������
		//�������ı���֮���Բ�ʹ��while(?)i++;��Ϊ�˱�֤��ȡ�����֮���ָ�����������
		while (i < (int)Line.size() && Line[i] != '\n' && Line[i] != '\0' && Line[i] != ';') {
			//�����ո�TAB
			if (Line[i] == 0x20 || Line[i] == '\t' || Line[i] == ':' || Line[i] == ',') {
				i++; continue;
			}
			//�ж��Ƿ������ţ���������û��ð�š�������
			CodeStr = CutStrCode(Line, i);
			i += CodeStr.size();
			if (is_Title) {
				t.str = CodeStr;
				t.num = Number;
				t.s = FileSize;
				Title.push_back(t);
				is_Title = false;
			}
			else {//����ָ���ж�
				if (MOV) {
					d = MOVE(Line, i, Number);
					if (d.size() > 1 && d.size() < 4) {
						Data_put(d);
					}
					else if (d.size() > 3) {
						//�ж�Ϊ���,�������ַ���
						t.str = CutStr(Line, Line.find(',') + 1);
						t.s = FileSize;
						t.num = Number;
						Mov_place.push_back(t);
						//��������
						Data.insert(Data.end(), d.begin(), d.end() - (int)d[3]);
						FileSize += (d.size() - (int)d[3]);
						Number += (d.size() - (int)d[3]);
					}
				}
				else if (DB) {
					Data_put(DataBWD(Line, i, 1, Number));

				}
				else if (DW) {
					Data_put(DataBWD(Line, i, 2, Number));
				}
				else if (DD) {
					Data_put(DataBWD(Line, i, 4, Number));
				}
				else if (ADD) {
					Data_put(Additive(Line, i, Number));
				}
				else if (SUB) {
					Data_put(Subtraction(Line, i, Number));
				}
				else if (JMP) {
					d = Jemp();
					//���������jp����
					t.str = CutStr(Line, i);
					t.s = FileSize;
					t.num = Number;
					Data_put(d);
					jp_p.push_back(t);
				}
				else if (JE || JZ) {
					d = Je();
					//���������jp����
					t.str = CutStr(Line, i);
					t.s = FileSize;
					t.num = Number;
					Data_put(d);
					je_p.push_back(t);
				}
				else if (JB) {
					d = Jb();
					//���������jp����
					t.str = CutStr(Line, i);
					t.s = FileSize;
					t.num = Number;
					Data_put(d);
					jb_p.push_back(t);
				}
				else if (JBE) {
					d = Jbe();
					//���������jp����
					t.str = CutStr(Line, i);
					t.s = FileSize;
					t.num = Number;
					Data_put(d);
					jbe_p.push_back(t);
				}
				else if (SHR) {
					Data_put(Shl_Shr(Line, i, Number, 0xe8));
				}
				else if (SHR) {
					Data_put(Shl_Shr(Line, i, Number, 0xe0));
				}
				else if (PUSH) {
					d = Push(Line, i, Number);
					if ((int)d.size() > 0) {
						Data_put(d);
					}
					else {
						//˵��Ϊ��ţ������ֵ����push_p����
						t.str = CutStr(Line, i);
						t.num = Number;
						t.s = FileSize;
						push_p.push_back(t);
						//д�������ֽ�0x6a��0x00
						Data.push_back(0x6a);
						Data.push_back(0x00);
						Number += 2;
						FileSize += 2;
					}
				}
				else if (POP) {
					Data_put(Pop(Line, i));
				}
				else if (CMP) {
					Data_put(Cmp(Line, i, Number));
				}//�˷�ָ��
				else if (MUL) {
					Data_put(Mul(Line, i));
				}
				else if (OR) {
					Data_put(Logic(Line, i, Number, 'o'));
				}
				else if (XOR) {
					Data_put(Logic(Line, i, Number, 'x'));
				}
				else if (AND) {
					Data_put(Logic(Line, i, Number, 'a'));
				}
				else if (NOT) {
					Data_put(Not(Line, i));
				}
				else if (RESB) {
					DataChar(ReserveByte(Line, i, FileSize), '\0');
				}
				else if (INT) {
					Data_put(Int(Line, i, Number));
				}
				else if (ORG) {
					Number = Organ(Line, i, Number);
				}
				else if (HLT) {
					Data.push_back(0xf4);
					FileSize++;
					Number++;
				}
				else if (IN) {
					Data_put(In_Out(Line, i, Number, 'i'));
				}
				else if (OUT) {
					Data_put(In_Out(Line, i, Number, 'o'));
				}
				else {
					cout << "����ָ���޷�ʶ���������룡error-" << Line_num << endl << endl;
				}
			}
			break;
		}
		i = 0;
		Line_num++;
	}
	//ѭ���������ر��ļ�
	fin.close();
}
//EndCode()�����β����������������ת������jmpch
void EndCode(void)
{
	using namespace std;
	int i, j;
	std::vector<unsigned char>data;
	short d;
	for (i = 0; i < (int)Title.size(); ++i)
		for (j = 0; j < (int)Mov_place.size(); ++j) {
			if (Title[i].str == Mov_place[j].str) {
				d = isReg(Data[Mov_place[j].s]);
				//������������data
				if (d == 1) {
					data = NumToUc(Title[i].num, 1);
					Data[Mov_place[j].s + 1] = data[0];
				}
				else if (d == 2) {
					data = NumToUc(Title[i].num, 2);
					Data[Mov_place[j].s + 1] = data[0];
					Data[Mov_place[j].s + 2] = data[1];
				}
				else {
					std::cout << "����Χ��error-006!\n";
				}
			}
		}
	//����jmpָ��
	jmpch();
}
//ר����CompileCode()�������ַ�����ȡ������������ȡָ���ַ���
std::string CutStrCode(const std::string& str, int num = 0)//�ж��Ƿ��б�ţ�û���򷵻�ָ���ַ���
{
	using namespace std;
	std::string m;
	//��ȥ��ͷ���ֿ��ܴ��ڵ��޹��ַ���0x20Ϊ�ո�
	while (num < (int)str.size()) {
		if (str[num] != 0x20 && str[num] != '\t' && str[num] != ',')break;
		num++;
	}
	//��ȡ�ַ���
	while (num < (int)str.size() && (isalnum(str[num]) || str[num] == '$' || str[num] == ':' || str[num] == '_')) {
		if (str[num] == ':') {
			is_Title = true;
			break;
		}
		m.push_back(str[num]); num++;
	}
	return m;
}

void Data_put(std::vector<unsigned char>m)
{
	Data.insert(Data.end(), m.begin(), m.end());
	FileSize += m.size();
	Number += m.size();
}
//���ɱ����ļ���������д���ļ�
void FileOut(void)
{
	using namespace std;
	std::ofstream fout(fout_src, std::ios::binary);
	if (!fout.is_open())cout << endl << "�ļ�д��ʧ��!" << endl;
	for (int i = 0; i < (int)Data.size(); i++) {
		fout.put(Data[i]);
	}
	fout.close();
}
//��������д���ƶ������ض�ֵ���ڳ���������resbָ�д��NULL
void DataChar(int n, unsigned char ch)
{
	using namespace std;
	if (n > 0) {
		Data.insert(Data.end(), n, ch);
		FileSize += n;
		Number += n;
	}
	else if (n < 0) {
		cout << "����-027��������resbָ�������������������С��0" << endl;
	}
}
//jmpch������Ŀ���ļ���������תָ�ѹջָ����д���
void jmpch(void)
{
	using namespace std;
	int i, j, n, k = 50;//k���ѭ������
	vector<unsigned char>d;
	//ע��������ʹ�ö��if��Ƕ
	for (i = 0; i < (int)Title.size(); i++)
		for (j = k - 1; j >= 0; j--) {
			//------------------------����ָ���-----------------------------//
			if (j < (int)jp_p.size()) {//��������������ó���Χ
				if (Title[i].str == jp_p[j].str) {
					//jp���鴦��
					n = Title[i].num - jp_p[j].num - 2;
					if (n > 0x7f) {//���n=0x80��˵����jmpָ��ռ3�ַ��������������Ϊ0xe9,0xxx,0xxx
						Data[jp_p[j].s] = 0xe9;
						//��nת��Ϊ��Ӧ�Ŀ����������
						d = NumToUc(n - 1, 2);
						Data[jp_p[j].s + 1] = d[0];
						Data.insert(Data.begin() + jp_p[j].s + 2, 1, d[1]);
					}
					else {
						d = NumToUc(n, 1);
						Data[jp_p[j].s + 1] = d[0];
					}
				}
			}
			//------------------------����ָ���-----------------------------//
			if (j < (int)je_p.size()) {
				if (Title[i].str == je_p[j].str) {
					n = Title[i].num - je_p[j].num - 2;
					if (n > 0x7f) {
						Data[je_p[j].s] = 0x0f;
						Data[je_p[j].s + 1] = 0x84;
						d = NumToUc(n, 2);
						Data.insert(Data.begin() + je_p[j].s + 2, d.begin(), d.end());
					}
					else {
						d = NumToUc(n, 1);
						Data[je_p[j].s + 1] = d[0];
					}
				}
			}
			//------------------------����ָ���-----------------------------//
			//JB���
			if (j < (int)jb_p.size()) {
				if (Title[i].str == jb_p[j].str) {
					n = Title[i].num - jb_p[j].num - 2;
					if (n > 0x7f) {
						Data[jb_p[j].s] = 0x0f;
						Data[jb_p[j].s + 1] = 0x82;
						d = NumToUc(n, 2);
						Data.insert(Data.begin() + jb_p[j].s + 2, d.begin(), d.end());
					}
					else {
						d = NumToUc(n, 1);
						Data[jb_p[j].s + 1] = d[0];
					}
				}
			}
			//------------------------����ָ���-----------------------------//
			if (j < (int)jbe_p.size()) {
				if (Title[i].str == jbe_p[j].str) {
					n = Title[i].num - jbe_p[j].num - 2;
					if (n > 0x7f) {
						Data[jbe_p[j].s] = 0x0f;
						Data[jbe_p[j].s + 1] = 0x86;
						d = NumToUc(n, 2);
						Data.insert(Data.begin() + jbe_p[j].s + 2, d.begin(), d.end());
					}
					else {
						d = NumToUc(n, 1);
						Data[jbe_p[j].s + 1] = d[0];
					}
				}
			}
			//------------------------����ָ���-----------------------------//
			if (j < (int)push_p.size()) {
				//push_p���鴦��
				if (Title[i].str == push_p[j].str) {
					//jp���鴦��
					n = Title[i].num;
					if (n > 0x7f) {//���n=0x80��˵����jmpָ��ռ3�ַ��������������Ϊ0xe9,0xxx,0xxx
						Data[push_p[j].s] = 0x68;
						//��nת��Ϊ��Ӧ�Ŀ����������
						d = NumToUc(n, 2);
						Data[push_p[j].s + 1] = d[0];
						Data.insert(Data.begin() + push_p[j].s + 2, 1, d[1]);
					}
					else {
						d = NumToUc(n, 1);
						Data[push_p[j].s + 1] = d[0];
					}
				}
			}
			//------------------------����ָ���-----------------------------//
		}
}