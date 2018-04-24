//本头文件包含对指令字符判断的宏定义
#ifndef DB
#define DB CodeStr=="DB" || CodeStr=="db" || CodeStr=="Db" || CodeStr=="dB"
#endif

#ifndef DW
#define DW CodeStr=="DW" || CodeStr=="dw" || CodeStr=="Dw" || CodeStr=="dW"
#endif

#ifndef DD
#define DD CodeStr=="DD" || CodeStr=="dd" || CodeStr=="Dd" || CodeStr=="dD"
#endif

#ifndef RESB
#define RESB CodeStr=="RESB"|| CodeStr=="resb" || CodeStr=="RESb" || CodeStr=="REsB" || CodeStr=="ReSB"  || CodeStr=="RESb" || CodeStr=="rESB" || CodeStr=="REsb" || CodeStr=="ResB" || CodeStr=="reSB" || CodeStr=="rESb" || CodeStr=="ReSb" || CodeStr=="rEsB" || CodeStr=="Resb" || CodeStr=="rEsb" || CodeStr=="reSb" || CodeStr=="resB"
#endif

#ifndef JMP
#define JMP CodeStr=="JMP" || CodeStr=="jmp" || CodeStr=="Jmp" || CodeStr=="jMp" || CodeStr=="jmP" || CodeStr=="JMp" || CodeStr=="jMP" || CodeStr=="JmP"
#endif

#ifndef MOV
#define MOV CodeStr=="MOV" || CodeStr=="mov"
#endif

#ifndef ORG
#define ORG CodeStr=="ORG" || CodeStr=="org"
#endif

#ifndef ADD
#define ADD CodeStr=="ADD" || CodeStr=="add"
#endif

#ifndef SUB
#define SUB CodeStr=="SUB" || CodeStr=="sub"
#endif

#ifndef PUSH
#define PUSH CodeStr=="PUSH" || CodeStr=="push"
#endif

#ifndef POP
#define POP CodeStr=="POP" || CodeStr=="pop"
#endif

#ifndef INT
#define INT CodeStr=="INT" || CodeStr=="int"
#endif

#ifndef HLT
#define HLT CodeStr=="HLT" || CodeStr=="hlt"
#endif

#ifndef JE
#define JE CodeStr=="JE" || CodeStr=="je" 
#endif

#ifndef CMP
#define CMP CodeStr=="CMP" || CodeStr=="cmp" 
#endif

#ifndef SHR
#define SHR CodeStr=="SHR" || CodeStr=="shr" 
#endif

#ifndef SHL
#define SHl CodeStr=="SHL" || CodeStr=="shl" 
#endif

#ifndef JBE
#define JBE CodeStr=="JBE" || CodeStr=="jbe" 
#endif

#ifndef JZ
#define JZ CodeStr=="JZ" || CodeStr=="jz" 
#endif

#ifndef JB
#define JB CodeStr=="JB" || CodeStr=="jb" 
#endif

#ifndef IN
#define IN CodeStr=="IN" || CodeStr=="in" 
#endif

#ifndef OUT
#define OUT CodeStr=="OUT" || CodeStr=="out" 
#endif

#ifndef AND
#define AND CodeStr=="AND" || CodeStr=="and" 
#endif

#ifndef OR
#define OR CodeStr=="OR" || CodeStr=="or" 
#endif

#ifndef XOR
#define XOR CodeStr=="XOR" || CodeStr=="xor" 
#endif

#ifndef NOT
#define NOT CodeStr=="NOT" || CodeStr=="not" 
#endif

#ifndef MUL
#define MUL CodeStr=="MUL" || CodeStr=="mul" 
#endif