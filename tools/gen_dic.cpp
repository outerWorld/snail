// -*- encoding=utf-8 -*-
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <errno.h>

#include <iostream>
#include <fstream>
#include <algorithm>

#include <iconv.h>

#include "common.h"

#include "lang_conv.h"
#include "sn_wordic.h"
#include "word_splitter.h"

#define IN_BUF_SZ 1024
static int load_file(wordic_p p_fdic, wordic_p p_bdic, char *file, wd_attr_p p_attr)
{
	std_inf inf;
	char * line;
	std_str revert_word;
	lang_conv lc("UTF-8", "UCS-2LE");
#if defined(_CONV_TEST_)
	lang_conv lc2("UCS-2LE", "UTF-8");
#endif // _CONV_TEST_
	size_t len0, len1;
	size_t len;
	word_splitter words("", std_str(" ",2));

	line = (char*)malloc(IN_BUF_SZ);

	inf.open(file, std_inf::in|std_inf::binary);

	while (inf.good()) {
		inf.getline(line, IN_BUF_SZ);
		if (line[strlen(line)-1] == 0x0a)
			line[strlen(line)-1] = '\0';
		len0 = strlen(line);
		if (len0 <= 0) continue;
		if ('#' == line[0]) continue;
		len = lc.conv(line, len0);

		words.work_on(std_str(lc.data(), lc.len()));
		int i = 0;
		// each element is 2bytes, so when revert the code, it should go with 2 bytes everytime.
		while (word_splitter::err != words[i]) {
			revert_word.clear();
			//revert_word.resize(words[i].length());
			int k = words[i].length() - sizeof(short);
			int j = 0;
			while (k >= 0) {
				revert_word.insert(j, words[i], k, sizeof(short));
				k -= sizeof(short);
				j += sizeof(short);
			}
			wordic_add_word(p_fdic, (unsigned short*)words[i].data(), words[i].length()/2, p_attr);
			wordic_add_word(p_bdic, (unsigned short*)revert_word.data(), revert_word.length()/2, p_attr);
			i++;
		}
		words.debug();
		words.clear();

#if defined(_CONV_TEST_)
		len = lc2.conv(lc.data(), lc.len());
		if (len != lc.len()+1) {
			std::cout << "error or incomplete input" << std::endl;
		}
		words.chg_sep(" ");
		words.work_on(std_str(lc2.data(), lc2.len()));
		words.debug();
		words.clear();
#endif // _CONV_TEST_
	}

	inf.close();
	free(line);

	std::cout << "end" << std::endl;

	return 0;
}

int main(int argc, char *argv[])
{
	wordic_p p_fdic;
	wordic_p p_bdic;
	wd_attr_t attr;

	p_fdic = wordic_create();
	if (!p_fdic) return 1;

	p_bdic = wordic_create();
	if (!p_bdic) return 1;

	memset(&attr, 0x00, sizeof(attr));

	attr.word_pol = WD_POL_NEU;
	attr.word_part = WD_PART_CONJ;
	load_file(p_fdic, p_bdic, "data/sorted_out/连词.txt", &attr);

#if 0
	//load_file(p_fdic, p_bdic, "data/sorted_out/中文主张词语.txt");
	attr.word_pol = WD_POL_NEU;
	attr.word_part = WD_PART_NUME;
	load_file(p_fdic, p_bdic, "data/sorted_out/数词.txt", &attr);

	attr.word_pol = WD_POL_NEU;
	attr.word_part = WD_PART_ONOM;
	load_file(p_fdic, p_bdic, "data/sorted_out/拟声词.txt", &attr);

	attr.senti = SENTI_UNKNOWN;
	attr.senti_strength = 0;
	attr.word_pol = WD_POL_NEG;
	attr.word_part = WD_PART_ONOM;
	load_file(p_fdic, p_bdic, "data/sorted_out/中文负面情感词语.txt", &attr);

	attr.senti = SENTI_UNKNOWN;
	attr.senti_strength = 0;
	attr.word_pol = WD_POL_NEG;
	attr.word_part = WD_PART_ONOM;
	load_file(p_fdic, p_bdic, "data/sorted_out/中文负面情感词语.txt", &attr);
#endif

	wordic_store(p_fdic, "sn_forward.dict");
	wordic_store(p_bdic, "sn_backward.dict");

	wordic_destroy(p_fdic);
	free(p_fdic);
	p_fdic = NULL;
	wordic_destroy(p_bdic);
	free(p_fdic);
	p_bdic = NULL;

	return 0;
}
