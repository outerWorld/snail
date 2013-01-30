
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <iostream>
#include <fstream>

#include <iconv.h>
#include "sn_wordic.h"
#include "word_splitter.h"

typedef std::ifstream std_inf;

static int load_file(wordic_p p_fdic, wordic_p p_bdic, char *file)
{
	wd_attr_t attr;
	std_inf inf;
	word_splitter words("");
	char * line;
	char * enc_line;
	char * enc_buf;
	iconv_t convert;
	size_t len0, len1;
	size_t len;

	convert = iconv_open("UTF-8", "UCS-2-INTERNAL");
	if (-1 == (int)convert) return -1;

	//line = new char(1024);
	line = (char*)malloc(1024);
	enc_buf = (char*)malloc(2048);
	enc_line = enc_buf;

	inf.open(file, std_inf::in|std_inf::binary);

	words.clear();
	while (inf.good()) {
		inf.getline(line, 1024);
		line[strlen(line)-1] = '\0';
		len0 = strlen(line);
		if (len0 <= 0) continue;
		if ('#' == line[0]) continue;
		len1 = 2048;
		enc_line = enc_buf;
		len = iconv(convert, &line, &len0, &enc_line, &len1);
		if (len == (size_t)-1) {
			std::cout << "iconv error" << std::endl;
			break;
		}
		words.work_on(std_str(enc_buf, len));
		words.debug();
		words.clear();
	}

	iconv_close(convert);
	inf.close();
	free(line);
	free(enc_buf);
	//delete line;
	std::cout << "end" << std::endl;

	return 0;
}

int main(int argc, char *argv[])
{
	wordic_p p_fdic;
	wordic_p p_bdic;

	p_fdic = wordic_create();
	if (!p_fdic) return 1;

	p_bdic = wordic_create();
	if (!p_bdic) return 1;

	load_file(p_fdic, p_bdic, "data/sorted_out/中文主张词语.txt");

	wordic_destroy(p_fdic);
	free(p_fdic);
	p_fdic = NULL;
	wordic_destroy(p_bdic);
	free(p_fdic);
	p_bdic = NULL;

	return 0;
}
