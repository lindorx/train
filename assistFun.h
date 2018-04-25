#include<string>

//截取字符串，str：源字符串；num：开始位置，自动在空格，跳格，换行，‘；’及其他非字符英文和数字字符处结束
std::string CutStr(const std::string& str, int num = 0);

//截取字符串，str：源字符串；num：开始位置，自动在空格，跳格，换行，‘；’及其他非字符英文和数字字符处结束
std::string CutStrDBWD(const std::string& str, int num = 0);

short isReg(unsigned char);//判断寄存器机器码

std::string *CS(const std::string& str, int k);