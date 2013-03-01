/*
 * Author: huang chunping
 * Date  : 2013-02-21
 * Desc  :
 */

#ifndef __CN_WORD_H
#define __CN_WORD_H

#include "common.h"

class cn_word {
public:
	cn_word(char *wd, int len);
	~cn_word();
	int set_pol(int pol) {this->pol = pol; }
	int set_weight(int weight) {this->weight = weight; }
	int set_word_type(int wt) { this->word_type = wt; }

	int show();
private:
	std_str wd;
	int pol;	// 词性
	int weight;
	int word_type;
};

#endif // __CN_WORD_H
