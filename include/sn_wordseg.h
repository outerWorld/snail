// -*- encoding=utf-8 -*-
/*
 * Author: huang chunping
 * Date  : 2013-01-25
 *
 */

#ifndef __SN_WORDSEG_H
#define __SN_WORDSEG_H

class std::deque;
struct wd_attr_t;

// max word num 最大中文字个数
#define WORD_SIZE	16
typedef struct _word_info_s {
	unsigned short 	code[WORD_SIZE];	
	wd_attr_t 		attr;	
}word_info_t, *word_info_p;

/*
 * attention: sentence must have been unicode data
 */
int wd_seg_sentence(unsigned short *sentence, int sentence_len, std::deque<word_info_t> & words);

#endif // __SN_WORDSEG_H
