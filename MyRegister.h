/*本头文件定义了常用的一些二进制码*/
#pragma once
#include<string>
#include<vector>
//为寄存器赋值的机器码
// 例：MOV AX,0X1234		=>0XB8 0X34 0X12
//     MOV AH,0X12			=>0XB4 0X12

//以下是mov指令中各个寄存器对应的值
const unsigned char AL_HEX = 0XB0;
const unsigned char CL_HEX = 0XB1;
const unsigned char DL_HEX = 0XB2;
const unsigned char BL_HEX = 0XB3;
const unsigned char AH_HEX = 0XB4;
const unsigned char CH_HEX = 0XB5;
const unsigned char DH_HEX = 0XB6;
const unsigned char BH_HEX = 0XB7;

const unsigned char AX_HEX = 0XB8;
const unsigned char CX_HEX = 0XB9;
const unsigned char DX_HEX = 0XBA;
const unsigned char BX_HEX = 0XBB;
const unsigned char SP_HEX = 0XBC;
const unsigned char BP_HEX = 0XBD;
const unsigned char SI_HEX = 0XBE;
const unsigned char DI_HEX = 0XBF;

//以下是add指令中各个寄存器对应的机器码
const unsigned char AL_ADD = 0XC0;
const unsigned char CL_ADD = 0XC1;
const unsigned char DL_ADD = 0XC2;
const unsigned char BL_ADD = 0XC3;
const unsigned char AH_ADD = 0XC4;
const unsigned char CH_ADD = 0XC5;
const unsigned char DH_ADD = 0XC6;
const unsigned char BH_ADD = 0XC7;

const unsigned char AX_ADD = 0XC0;
const unsigned char CX_ADD = 0XC1;
const unsigned char DX_ADD = 0XC2;
const unsigned char BX_ADD = 0XC3;
const unsigned char SP_ADD = 0XC4;
const unsigned char BP_ADD = 0XC5;
const unsigned char SI_ADD = 0XC6;
const unsigned char DI_ADD = 0XC7;

//以下是sub指令
const unsigned char AL_SUB = 0XE8;
const unsigned char CL_SUB = 0XE9;
const unsigned char DL_SUB = 0XEA;
const unsigned char BL_SUB = 0XEB;
const unsigned char AH_SUB = 0XEC;
const unsigned char CH_SUB = 0XED;
const unsigned char DH_SUB = 0XEE;
const unsigned char BH_SUB = 0XEF;

const unsigned char AX_SUB = 0XE8;
const unsigned char CX_SUB = 0XE9;
const unsigned char DX_SUB = 0XEA;
const unsigned char BX_SUB = 0XEB;
const unsigned char SP_SUB = 0XEC;
const unsigned char BP_SUB = 0XED;
const unsigned char SI_SUB = 0XEE;
const unsigned char DI_SUB = 0XEF;

//32位寄存器名称为：
//EAX,ECX,EDX,EBX,ESP,EBP,ESI,EDI;
//AX,CX,DX・・・・・・分别是对应的32位寄存器的低位
//使用时可以先把低位（AX,CX,DX・・・・・・）赋值，再用位转移指令移动到高位

//以下为寄存器储存代码
//例：MOV AX,CX  => 0X89,0XC8
//   MOV AX,DX  =>0X89,0XD0
//・・・・・・・・・・・・・・・・・・・・・・・・・・・・・
//AX,CX,DX,BX,SP,BP,SI,DI
//以下寄存器AX赋值机器码；
const unsigned char AX_AX = 0XC0;
const unsigned char CX_AX = 0XC1;
const unsigned char DX_AX = 0XC2;
const unsigned char BX_AX = 0XC3;
const unsigned char SP_AX = 0XC4;
const unsigned char BP_AX = 0XC5;
const unsigned char SI_AX = 0XC6;
const unsigned char DI_AX = 0XC7;
//以下寄存器CX赋值机器码；
const unsigned char AX_CX = 0XC8;
const unsigned char CX_CX = 0XC9;
const unsigned char DX_CX = 0XCA;
const unsigned char BX_CX = 0XCB;
const unsigned char SP_CX = 0XCC;
const unsigned char BP_CX = 0XCD;
const unsigned char SI_CX = 0XCE;
const unsigned char DI_CX = 0XCF;
//以下寄存器DX赋值机器码；
const unsigned char AX_DX = 0XD0;
const unsigned char CX_DX = 0XD1;
const unsigned char DX_DX = 0XD2;
const unsigned char BX_DX = 0XD3;
const unsigned char SP_DX = 0XD4;
const unsigned char BP_DX = 0XD5;
const unsigned char SI_DX = 0XD6;
const unsigned char DI_DX = 0XD7;
//以下寄存器BX赋值机器码；
const unsigned char AX_BX = 0XD8;
const unsigned char CX_BX = 0XD9;
const unsigned char DX_BX = 0XDA;
const unsigned char BX_BX = 0XDB;
const unsigned char SP_BX = 0XDC;
const unsigned char BP_BX = 0XDD;
const unsigned char SI_BX = 0XDE;
const unsigned char DI_BX = 0XDF;
//以下寄存器SP赋值机器码；
const unsigned char AX_SP = 0XE0;
const unsigned char CX_SP = 0XE1;
const unsigned char DX_SP = 0XE2;
const unsigned char BX_SP = 0XE3;
const unsigned char SP_SP = 0XE4;
const unsigned char BP_SP = 0XE5;
const unsigned char SI_SP = 0XE6;
const unsigned char DI_SP = 0XE7;
//以下寄存器BP赋值机器码；
const unsigned char AX_BP = 0XE8;
const unsigned char CX_BP = 0XE9;
const unsigned char DX_BP = 0XEA;
const unsigned char BX_BP = 0XEB;
const unsigned char SP_BP = 0XEC;
const unsigned char BP_BP = 0XED;
const unsigned char SI_BP = 0XEE;
const unsigned char DI_BP = 0XEF;
//以下寄存器SI赋值机器码；
const unsigned char AX_SI = 0XF0;
const unsigned char CX_SI = 0XF1;
const unsigned char DX_SI = 0XF2;
const unsigned char BX_SI = 0XF3;
const unsigned char SP_SI = 0XF4;
const unsigned char BP_SI = 0XF5;
const unsigned char SI_SI = 0XF6;
const unsigned char DI_SI = 0XF7;
//以下寄存器DI赋值机器码；
const unsigned char AX_DI = 0XF8;
const unsigned char CX_DI = 0XF9;
const unsigned char DX_DI = 0XFA;
const unsigned char BX_DI = 0XFB;
const unsigned char SP_DI = 0XFC;
const unsigned char BP_DI = 0XFD;
const unsigned char SI_DI = 0XFE;
const unsigned char DI_DI = 0XFF;

//***********************************************
//寄存器高低位机器码
//AL,CL,DL,BL,AH,CH,DH,BH
//AX低位AL:
const unsigned char AL_AL = 0XC0;
const unsigned char CL_AL = 0XC1;
const unsigned char DL_AL = 0XC2;
const unsigned char BL_AL = 0XC3;
const unsigned char AH_AL = 0XC4;
const unsigned char CH_AL = 0XC5;
const unsigned char DH_AL = 0XC6;
const unsigned char BH_AL = 0XC7;
//CX低位CL:
const unsigned char AL_CL = 0XC8;
const unsigned char CL_CL = 0XC9;
const unsigned char DL_CL = 0XCA;
const unsigned char BL_CL = 0XCB;
const unsigned char AH_CL = 0XCC;
const unsigned char CH_CL = 0XCD;
const unsigned char DH_CL = 0XCE;
const unsigned char BH_CL = 0XCF;
//DX低位DL
const unsigned char AL_DL = 0XD0;
const unsigned char CL_DL = 0XD1;
const unsigned char DL_DL = 0XD2;
const unsigned char BL_DL = 0XD3;
const unsigned char AH_DL = 0XD4;
const unsigned char CH_DL = 0XD5;
const unsigned char DH_DL = 0XD6;
const unsigned char BH_DL = 0XD7;
//BX低位BL
const unsigned char AL_BL = 0XD8;
const unsigned char CL_BL = 0XD9;
const unsigned char DL_BL = 0XDA;
const unsigned char BL_BL = 0XDB;
const unsigned char AH_BL = 0XDC;
const unsigned char CH_BL = 0XDD;
const unsigned char DH_BL = 0XDE;
const unsigned char BH_BL = 0XDF;
//AX高位AH
const unsigned char AL_AH = 0XE0;
const unsigned char CL_AH = 0XE1;
const unsigned char DL_AH = 0XE2;
const unsigned char BL_AH = 0XE3;
const unsigned char AH_AH = 0XE4;
const unsigned char CH_AH = 0XE5;
const unsigned char DH_AH = 0XE6;
const unsigned char BH_AH = 0XE7;
//CX高位CH
const unsigned char AL_CH = 0XE8;
const unsigned char CL_CH = 0XE9;
const unsigned char DL_CH = 0XEA;
const unsigned char BL_CH = 0XEB;
const unsigned char AH_CH = 0XEC;
const unsigned char CH_CH = 0XED;
const unsigned char DH_CH = 0XEE;
const unsigned char BH_CH = 0XEF;
//以下寄存器SI赋值机器码；
const unsigned char AL_DH = 0XF0;
const unsigned char CL_DH = 0XF1;
const unsigned char DL_DH = 0XF2;
const unsigned char BL_DH = 0XF3;
const unsigned char AH_DH = 0XF4;
const unsigned char CH_DH = 0XF5;
const unsigned char DH_DH = 0XF6;
const unsigned char BH_DH = 0XF7;
//以下寄存器DI赋值机器码；
const unsigned char AL_BH = 0XF8;
const unsigned char CL_BH = 0XF9;
const unsigned char DL_BH = 0XFA;
const unsigned char BL_BH = 0XFB;
const unsigned char AH_BH = 0XFC;
const unsigned char CH_BH = 0XFD;
const unsigned char DH_BH = 0XFE;
const unsigned char BH_BH = 0XFF;

//其他寄存器
//ES,CS,SS,DS,FS,GS
//寄存器ES
const unsigned char AX_ES = 0XC0;
const unsigned char CX_ES = 0XC1;
const unsigned char DX_ES = 0XC2;
const unsigned char BX_ES = 0XC3;
const unsigned char SP_ES = 0XC4;
const unsigned char BP_ES = 0XC5;
const unsigned char SI_ES = 0XC6;
const unsigned char DI_ES = 0XC7;
//寄存器CS
const unsigned char AX_CS = 0XC8;
const unsigned char CX_CS = 0XC9;
const unsigned char DX_CS = 0XCA;
const unsigned char BX_CS = 0XCB;
const unsigned char SP_CS = 0XCC;
const unsigned char BP_CS = 0XCD;
const unsigned char SI_CS = 0XCE;
const unsigned char DI_CS = 0XCF;
//寄存器SS
const unsigned char AX_SS = 0XD0;
const unsigned char CX_SS = 0XD1;
const unsigned char DX_SS = 0XD2;
const unsigned char BX_SS = 0XD3;
const unsigned char SP_SS = 0XD4;
const unsigned char BP_SS = 0XD5;
const unsigned char SI_SS = 0XD6;
const unsigned char DI_SS = 0XD7;
//寄存器DS
const unsigned char AX_DS = 0XD8;
const unsigned char CX_DS = 0XD9;
const unsigned char DX_DS = 0XDA;
const unsigned char BX_DS = 0XDB;
const unsigned char SP_DS = 0XDC;
const unsigned char BP_DS = 0XDD;
const unsigned char SI_DS = 0XDE;
const unsigned char DI_DS = 0XDF;


const std::string reg1[16] = { "AH", "AL", "CH", "CL", "DH", "DL", "BH", "BL", "ah", "al", "ch", "cl", "dh", "dl", "bh", "bl" };

const std::string reg_1[16] = { "AL", "CL", "DL", "BL", "AH", "CH", "DH", "BH", "al", "cl", "dl", "bl", "ah", "ch", "dh", "bh" };

const std::string reg2[16] = { "AX", "CX", "DX", "BX", "SP", "BP", "SI", "DI", "ax", "cx", "dx", "bx", "sp", "bp", "si", "di" };

const std::string reg3[8] = { "ES", "CS", "SS", "DS", "es", "cs", "ss", "ds" };


const unsigned char a1[2] = { 0x8a, 0x8b };//0x8a是8位寄存器的，0x8b是16位寄存器的
const unsigned char b1[8][4] = {
	{ 0x07, 0x46, 0x04, 0x05 },
	{ 0x0f, 0x4e, 0x0c, 0x0d },
	{ 0x17, 0x56, 0x14, 0x15 },
	{ 0x1f, 0x5e, 0x1c, 0x1d },
	{ 0x27, 0x66, 0x24, 0x25 },
	{ 0x2f, 0x6e, 0x2c, 0x2d },
	{ 0x37, 0x76, 0x34, 0x35 },
	{ 0x3f, 0x7e, 0x3c, 0x3d } };
const unsigned char m_unch[8] = { 0x06, 0x0e, 0x16, 0x1e, 0x26, 0x2e, 0x36, 0x3e };
const unsigned char logic_and[8] = { 0xe0, 0xe1, 0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7 };
const unsigned char logic_or[8] = { 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf };
const unsigned char logic_xor[8] = { 0xf0, 0xf1, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7 };
const unsigned char logic_not[8] = { 0xd0, 0xd1, 0xd2, 0xd3, 0xd4, 0xd5, 0xd6, 0xd7 };