text2048.exe: text2048.cpp
	g++ -o text2048.exe -Wall -g -std=c++11 text2048.cpp

run:
	text2048.exe
