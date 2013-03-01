/*
 * Author: huang chunping
 * Date  : 2013-02-21
 * Desc  :
 */

#ifndef __TEXT_WS_H
#define __TEXT_WS_H

#include "common.h"
typedef std::vector<cn_word> sentence;
typedef std::vector<sentence> paragraph;

class text_ws {
public:
	text_ws(int init_ws_sys = 0, char *ws_dir = NULL);
	~text_ws();

	int parse_file(char *file, unsigned int code_type);
	int parse_string(char *data, int data_len, unsigned int code_type);

	int show_paragraph();

private:
	int						ws_inited;
	int						st;
	std::vector<paragraph> 	paragraphs;
};

#endif // __TEXT_WS_H
