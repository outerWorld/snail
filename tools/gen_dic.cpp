
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <errno.h>

#include <iostream>
#include <fstream>

#include <iconv.h>
#include "sn_wordic.h"
#include "word_splitter.h"

typedef std::ifstream std_inf;

#define OUT_BUF_SZ 2048
#define IN_BUF_SZ 1024
static int load_file(wordic_p p_fdic, wordic_p p_bdic, char *file)
{
	wd_attr_t attr;
	std_inf inf;
	word_splitter words("", std_str(" ",2));
	char * line;
	char * in_line;
	char * enc_line;
	char * enc_buf;
	iconv_t convert;
	iconv_t convert2;
	size_t len0, len1;
	size_t len;

	convert = iconv_open("UCS-2LE", "UTF-8");
	if (-1 == (int)convert) return -1;
	
	convert2 = iconv_open("UTF-8", "UCS-2LE");
	if (-1 == (size_t)convert2) return -1;

	//line = new char(1024);
	line = (char*)malloc(IN_BUF_SZ);
	enc_buf = (char*)malloc(OUT_BUF_SZ);
	enc_line = enc_buf;

	inf.open(file, std_inf::in|std_inf::binary);

	words.clear();
	while (inf.good()) {
		inf.getline(line, IN_BUF_SZ);
		if (line[strlen(line)-1] == 0x0a)
			line[strlen(line)-1] = '\0';
		len0 = strlen(line);
		if (len0 <= 0) continue;
		if ('#' == line[0]) continue;
		len1 = OUT_BUF_SZ;
		enc_line = enc_buf;
		in_line = line;
		len = iconv(convert, &in_line, &len0, &enc_line, &len1);
		if (len == (size_t)-1) {
			std::cout << "iconv error" << errno << ":" << strerror(errno) << std::endl;
			break;
		}
		words.work_on(std_str(enc_buf, OUT_BUF_SZ-len1));
		words.debug();
		words.clear();
		in_line = line;
		len0 = OUT_BUF_SZ-len1;
		enc_line = enc_buf;
		len1 = OUT_BUF_SZ;
		len = iconv(convert2, &enc_line, &len0, &in_line, &len1);
		if (len == (size_t)-1) {
			std::cout << "iconv error" << errno << ":" << strerror(errno) << std::endl;
			break;
		}
		words.chg_sep(" ");
		words.work_on(std_str(line, OUT_BUF_SZ-len1));
		words.debug();
		words.clear();
		
	}

	iconv_close(convert);
	iconv_close(convert2);
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

	//load_file(p_fdic, p_bdic, "data/sorted_out/中文主张词语.txt");
	load_file(p_fdic, p_bdic, "data/sorted_out/连词.txt");

	wordic_destroy(p_fdic);
	free(p_fdic);
	p_fdic = NULL;
	wordic_destroy(p_bdic);
	free(p_fdic);
	p_bdic = NULL;

	return 0;
}
