
#include <stdio.h>
#include "ictclas50.h"
#include "text_ws.h"


text_ws::text_ws(int init_ws_sys, char *ws_dir)
{
	ws_inited = 0;
	st = 0;

	if (init_ws_sys) {
		ws_inited = 1;
		if (true != ICTCLAS_Init(ws_dir)) {
			st = -1;
		}
	}

	paragraphs.clear();
}

text_ws::~text_ws()
{
	if (ws_inited) ICTCLAS_Exit();
}

int text_ws::parse_file(char *file, unsigned int code_type)
{
	int fd = 0;
	int len = 0;
	char *buf = NULL;
	struct stat fst;

	fd = open(file, O_RDONLY);
	if (fd < 0) return -1;

	memset(&fs, 0x00, sizeof(struct stat));


	return 0;
}


int text_ws::parse_string(char *data, int data_len, unsigned int code_type)
{
	int i = 0;
	int res_count = 0;
	LPICTCLAS_RESULT res;

	res = ICTCLAS_ParagraphProcessA(data, data_len, res_count, code_type, true);
	
	for (i=0; i<res_count; i++) {
	}

	ICTCLAS_ResultFree(res);
}


int text_ws::show_paragraph()
{
}
