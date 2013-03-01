
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iostream>
#include "ictclas50.h"

static void show_result(LPICTCLAS_RESULT result)
{
	fprintf(stdout, "StartPos=%d, len=%d, POS=%s, POSID=%d, WordID=%d, WordType=%d, Weight=%d\n",
			result->iStartPos, result->iLength, result->szPOS, result->iPOS, result->iWordID,
			result->iWordType, result->iWeight);
}

int main(int argc, char *argv[])
{
	int len;
	char *buf;
	int count = 0;
	LPICTCLAS_RESULT result;
	char *data_path = NULL;
	char * test_data = "我认为这件事情的发生，oh my god,对我们所有人来说，都是个灾难！,毛主席也这么认为啊！去那里逛逛？";

	if (argc < 2) return 1;

	data_path = argv[1];

	if (true != ICTCLAS_Init(data_path)) return 1;

	buf = (char*)malloc(strlen(test_data)*6);
	if (!buf) return 1;
	
	len = ICTCLAS_ParagraphProcess(test_data, strlen(test_data), buf, CODE_TYPE_UTF8, 1);
	std::cout<<"result is "<<buf<<std::endl;	

	result = ICTCLAS_ParagraphProcessA(test_data, strlen(test_data), count, CODE_TYPE_UTF8, true);
	for (int i=0; i<count; i++) {
		show_result(&result[i]);
	}

	ICTCLAS_ResultFree(result);

	ICTCLAS_Exit();

	return 0;
}
