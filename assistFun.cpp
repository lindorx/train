#include<string>
#include<iostream>

std::string CutStr(const std::string& str, int num = 0)
{
	std::string m;
	bool w = false;
	if (num < 2)w = true;
	//丢去开头部分可能存在的无关字符，0x20为空格
	while(num<(int)str.size()){
		if (str[num] != 0x20 
			&& str[num]!='\t' 
			&& str[num]!=','
			&& str[num]!='"')break;
		num++;
	}
	//截取字符串
	while (num<(int)str.size() && (isalnum(str[num]) || str[num] == '$' || str[num] == '+' || str[num] == '-' || str[num] == '*' || str[num] == '/')){
		m.push_back(str[num]);num++;
	}
	return m;
}

short isReg(unsigned char ch)
{
	if (ch >= 0xb0 && ch <= 0xb7)return 1;
	else if (ch>0xb7 && ch <= 0xbf)return 2;
	return 0;
}

//导入指令行字符串地址，k:起始查找位置
std::string *CS(const std::string& str, int k)
{
	using namespace std;
	string *ch=new string[2];
	bool w=false;
	int str_size = str.size(),i=0,j=0;
	while (k < str_size && (str[k] == 0x20 || str[k] == '\t'))k++;
	ch[0] = str.substr(k, str.find(',') - k); 
	for (i = ch[0].size() - 1; i >= 0; --i){
		if (ch[0][i] == 0x20 || ch[0][i] == '\t'){ 
			ch[0].pop_back();
			continue;
		}
		break;
	}
	k = str.find(',')+1;
	while (k < str_size && str[k] != '\n' && str[k] != 0x00 && str[k] != ';'){
		if (!w && (str[k] == 0x20 || str[k] == '\t')){k++; continue; }
		if (!w){
			w = true;
		}
		if (str[k] == 0x20 || str[k] == '\t'){ i = k; j++; }
		if(w){
			ch[1].push_back(str[k]); k++;
		}
	}
	if (k - i == j){
		for (j; j>0;j--)ch[1].pop_back();
	}
	return ch;
}