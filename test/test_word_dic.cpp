#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <string>
#include <iostream>
//#include "sn_wordic.h"

int main(int argc, char *argv[])
{
	std::string temp_str;
	char code[16];

	for (int i=0; i<16; i++) code[i] = i;

	temp_str = std::string(code, 16);
	temp_str += "abc";
	std::cout<<temp_str<<std::endl;
	fprintf(stdout, "|%.*s|", temp_str.c_str(), temp_str.length());

	return 0;
}

