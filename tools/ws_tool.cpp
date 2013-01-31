// -*- encoding=utf-8 -*-

#include <iostream>

#include "common.h"
#include "lang_conv.h"
#include "sn_wordic.h"

int main(int argc, char *argv[])
{
	wordic_p p_fdic;  // forward dict
	wordic_p p_bdic;  // backward dict
	lang_conv lc("UTF-8", "UCS-2LE");
	char *sentence = NULL;

	if (true != lc.ok()) {
		std::cout << "init lang_conv failed!" << std::endl;
		return 1;
	}

	return 0;
}
