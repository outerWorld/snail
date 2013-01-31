// -*- encoding=utf-8 -*-
/*
 * Author: huang chunping
 * Date  : 2013-01-25
 *
 */

#ifndef __SN_WORDSEG_H
#define __SN_WORDSEG_H

// max word num 最大中文字个数
#define WORD_SIZE	16
typedef struct _word_info_s {
	unsigned short 	code[WORD_SIZE];
	wd_attr_t 		attr;	
}word_info_t, *word_info_p;

typedef std::vector<word_info_t> word_info_list;

class word_segmentor {
public:
	word_segmentor(const char *dict_file);
	~word_segmentor();
	bool ok() { return status==0?true:false; }
	int sentence_ws(const unsigned short *ucs_2le, int len);
	int file_ws(const char *fname, std_str enc_type);
	const word_info_p operator [](int id);

	void debug();
private:
	wordic_p 		p_bdic; // backward dict
	wordic_p 		p_fdic; // forward dict
	word_info_list 	words;
	int				status;
};

#endif // __SN_WORDSEG_H
