// -*- encoding=utf-8 -*-
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <fstream>
#include <iostream>
#include "common.h"

#include "lang_conv.h"


static char * test_data = "我们a";
int main(int argc, char *argv[])
{
	std_inf		inf;
	size_t		result = 0;
	lang_conv 	lc1("UTF-8", "UCS-2LE");
	lang_conv 	lc2("UCS-2LE", "UTF-8");

	if (true != lc1.ok()) {
		std::cout << "lc1 create fail" << std::endl;
		return 1;
	}
	if (true != lc2.ok()) {
		std::cout << "lc2 create fail" << std::endl;
		return 1;
	}

	result = lc1.conv(test_data, strlen(test_data));
	if (true != lc1.ok()) {
		std::cout << "lc1 conv fail" << std::endl;
		return 1;
	}
	std::cout << "result = " << result << "data len = " << lc1.len() << std::endl;

	result = lc2.conv(lc1.data(), lc1.len());
	if (true != lc2.ok()) {
		std::cout << "lc2 conv fail" << std::endl;
		return 1;
	}
	std::cout << "result = " << result << "to = " << lc2.data() << std::endl;

	return 0;
}
