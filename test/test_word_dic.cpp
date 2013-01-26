#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "sn_wordic.h"

static unsigned short test_word[] = {0xA1A0, 0xA2A3, 0xA3A4};
static unsigned short test_word2[] = {0xA1A0, 0xA2A3, 0xA3A4, 0xA4A5};

static void show_attr(wd_attr_p p_attr)
{
	fprintf(stdout, "senti=%02x, strength=%02x, polarity=%02x, part=%04x\n",
			p_attr->senti, p_attr->senti_strength, p_attr->word_pol, p_attr->word_part);

}

int main(int argc, char *argv[])
{
	char code[16];
	wordic_p p_dic;
	wd_attr_t in_attr;
	wd_attr_t out_attr;

	p_dic = wordic_create();
	if (!p_dic) return 1;

	in_attr.senti = 0x01;
	in_attr.senti_strength = 0x02;
	in_attr.word_pol = WD_POL_NEG;
	in_attr.word_part = WD_PART_SENTI|WD_PART_NOUN;
	wordic_add_word(p_dic, test_word, 3, &in_attr);
	show_attr(&in_attr);

	memset(&out_attr, 0x00, sizeof(wd_attr_t));
	wordic_get_word_attr(p_dic, test_word, 3, &out_attr);
	show_attr(&out_attr);

	in_attr.senti = 0x02;
	in_attr.senti_strength = 0x04;
	in_attr.word_pol = WD_POL_NEG;
	in_attr.word_part = WD_PART_ADJ;
	wordic_add_word(p_dic, test_word2, 4, &in_attr);
	show_attr(&in_attr);

	memset(&out_attr, 0x00, sizeof(wd_attr_t));
	wordic_get_word_attr(p_dic, test_word2, 4, &out_attr);
	show_attr(&out_attr);

	wordic_destroy(p_dic);
	free(p_dic);

	return 0;
}

