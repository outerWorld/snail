
#include <stdio.h>

#include "cn_word.h"

cn_word::cn_word(char *wd, int len)
{
	this->wd = std_str(wd, len);
}

cn_word::~cn_word()
{
}

int cn_word::show()
{
	printf("[%.*s] pol=%08x weight=%d type=%d\n",
			wd.length(), wd.c_str(), pol, weight, word_type);

	return 0;
}
