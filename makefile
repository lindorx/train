CC=g++
train.exe:assistFun.cpp HelpInsPro.cpp InsPro.cpp main.cpp
	$(CC) assistFun.cpp HelpInsPro.cpp InsPro.cpp main.cpp -o train.exe
