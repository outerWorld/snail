// -*- encoding=utf-8 -*-
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

#include <iostream>

#include "common.h"
#include "sn_wordic.h"

#define L0_SIZE 0x10000
#define INIT_CODE_VAL 0x10000
#define INVAILD_CODE_VAL 0x10000

wordic_p wordic_create()
{
	wordic_p p_wdic = NULL;

	MEM_ALLOC(p_wdic, wd_node_p, sizeof(wd_node_t)*L0_SIZE, NULL);
	for (unsigned int i=0; i<L0_SIZE; i++) {
		p_wdic[i].wd_code = i; //
	}

	return p_wdic;
}

static int short_swap(unsigned short *data, int data_len)
{
	int i = 0;
	int mid = 0;
	unsigned short temp;
	mid = data_len / 2;
	for (i=0; i<mid; i++) {
		temp = data[i];
		data[i] = data[data_len-1-i];
		data[data_len-1-i] = temp;
	}

	return 0;
}

typedef struct _code_buf_s {
	unsigned short size;
	unsigned short len;
	unsigned short *buf;
}code_buf_t, *code_buf_p;
int wordic_load(wordic_p p_fdic, char *dicfile, wordic_p p_bdic = NULL)
{
	int fd;
	code_buf_t cb;
	wd_attr_t attr;
	unsigned short code_len; // unit with sizeof(short)
	unsigned short attr_len;

	fd = open(dicfile, O_RDONLY);
	if (fd < 0) return -1;

	cb.size = 1024;
	cb.len = 0;
	cb.buf = NULL;
	MEM_ALLOC(cb.buf, unsigned short*, cb.size*sizeof(short), -1);

	read(fd, (char*)&code_len, sizeof(short));
	while (code_len != 0) {
		if (code_len >= cb.size) { /*enlarge the size*/ }
		read(fd, (char*)cb.buf, code_len*sizeof(short));
		read(fd, (char*)&attr_len, sizeof(short));
		read(fd, (char*)&attr, sizeof(wd_attr_t));
		//
		wordic_add_word(p_fdic, cb.buf, code_len, &attr);
		//
		if (p_bdic) {
			short_swap(cb.buf, code_len);
			wordic_add_word(p_bdic, cb.buf, code_len, &attr);
		}
		read(fd, (char*)&code_len, sizeof(short));
	}

	close(fd);

	return 0;
}

// attention: the question of byte order must be thought!!!
static int write_to_file(wd_node_p p_node, int fd, code_buf_p p_cb)
{
	unsigned short i = 0;
	const unsigned short attr_size = sizeof(wd_attr_t);
	wd_node_p p_temp = NULL;

	if (!p_node) return 0;

	i = p_cb->len;

	// check p_cb->size
	if (i >= p_cb->size) {
		// enlarge
	}

	// store itself.
	if (p_node->p_attr) {
		p_cb->buf[i] = p_node->wd_code;
		i++;
		write(fd, (char*)&i, sizeof(short));
		write(fd, (char*)p_cb->buf, sizeof(short)*i);
		write(fd, (char*)&attr_size, sizeof(attr_size)); 
		write(fd, p_node->p_attr, sizeof(wd_attr_t));
		i--; // note: the use of this decrease matches the increase 6 lines ahead !!!
	}

	// store its siblings.
	p_temp = p_node->p_sib;
	while (p_temp) {
		p_cb->buf[i] = p_temp->wd_code;
		i++;
		if (p_temp->p_attr) {
			write(fd, (char*)&i, sizeof(short));
			write(fd, (char*)p_cb->buf, sizeof(short)*i);
			write(fd, (char*)&attr_size, sizeof(attr_size)); 
			write(fd, p_temp->p_attr, sizeof(wd_attr_t));
		}
		p_cb->len += 1;
		write_to_file(p_temp->p_next, fd, p_cb);
		p_cb->len -= 1;
		p_temp = p_temp->p_sib;
		i--;
	}

	// store its followings
	p_cb->buf[i] = p_node->wd_code;
	p_cb->len += 1;
	write_to_file(p_node->p_next, fd, p_cb);

	return 0;
}

int wordic_store(wordic_p p_dic, char *dicfile)
{
	int fd;
	code_buf_t cb;
	unsigned int i = 0;

	fd = open(dicfile, O_CREAT|O_WRONLY, S_IRWXU);
	if (fd < 0) {
		std::cout << "open " << dicfile << " failed [" << errno << "," << strerror(errno) << std::endl;
		return -1;
	}

	cb.size = 1024;
	cb.len = 0;
	cb.buf = NULL;
	MEM_ALLOC(cb.buf, unsigned short *, cb.size*sizeof(short), -1);

	for (i=0; i<L0_SIZE; i++) {
		cb.buf[0] = i;
		cb.len = 0;
		write_to_file(&p_dic[i], fd, &cb);
	}
	i = 0;
	write(fd, (char*)&i, sizeof(short)); // end flag for dict.

	MEM_FREE(cb.buf);
	close(fd);

	return 0;
}

static int word_node_add_attr(wd_node_p p_node, const wd_attr_p p_attr)
{
	if (!p_node->p_attr) {
		MEM_ALLOC(p_node->p_attr, wd_attr_p, sizeof(wd_attr_t), -1);
	}

	p_node->p_attr->word_part |= p_attr->word_part;
	p_node->p_attr->word_pol |= p_attr->word_pol;
	p_node->p_attr->senti |= p_attr->senti;
	// as one word may have more than one sentiment, so here only
	// one variable can't store information for each part of this 
	// word, that is it will be improved later!!!!!
	p_node->p_attr->senti_strength = p_attr->senti_strength;

	return 0;
}

int wordic_add_word(wordic_p p_wdic, unsigned short*word, int word_len, wd_attr_p p_attr)
{
	int i = 0;
	int need_new = 0;
	wd_node_p p_new, p_cur;

	p_cur = &p_wdic[word[i]];

	while (i < word_len) {
		// horizontally check
		while (word[i] != p_cur->wd_code) {
			if (!p_cur->p_sib) {
				// not found the word code, so add one, after that,
				// the code is found and then quit this loop
				MEM_ALLOC(p_new, wd_node_p, sizeof(wd_node_t), -1);
				p_new->wd_code = word[i];
				p_cur->p_sib = p_new;
				p_cur = p_cur->p_sib;
				i++;
				break;
			}
			p_cur = p_cur->p_sib;
		}

		if (i >= word_len-1) {
			// add attribute
			if (0 != word_node_add_attr(p_cur, p_attr)) return -1;
			break;
		}

		// move vertically, to check the next word
		if (!p_cur->p_next) {
			MEM_ALLOC(p_new, wd_node_p, sizeof(wd_node_t), -1);
			p_new->wd_code = word[i+1];
			p_cur->p_next = p_new;
		}
		p_cur = p_cur->p_next;
		i++;
		if (i >= word_len-1) {
			if (0 != word_node_add_attr(p_cur, p_attr)) return -1;
			break;
		}
	}

	return 0;
}

int wordic_get_word_attr(wordic_p p_wdic, unsigned short *word, int word_len, wd_attr_p p_attr)
{
	int i = 0;
	int max_pos = 0; // the max-matching position in dic for word.
	wd_attr_p p_matched_attr = NULL;
	wd_node_p p_cur, p_temp;

	// the first word must be matched.
	p_cur = &p_wdic[word[0]];
	
	while (i < word_len) {
		p_temp = p_cur;
		while (p_temp && word[i] != p_temp->wd_code) {
			p_temp = p_temp->p_sib;
		}
		// the word code hasn't been found
		if (!p_temp) {
			break;
		}

		if (p_temp->p_attr) p_matched_attr = p_temp->p_attr;

		p_cur = p_temp->p_next;
		i++;
	}

	if (p_matched_attr && p_attr) memcpy(p_attr, p_matched_attr, sizeof(wd_attr_t));

	return 0;
}

static int wordic_free(wd_node_p p_node)
{
	wd_node_p p_temp = NULL;

	if (!p_node) return 0;

	if (p_node->p_next) wordic_free(p_node->p_next);

	p_temp = p_node->p_sib;
	while (p_temp) {
		p_node->p_sib = p_temp->p_sib;
		wordic_free(p_temp->p_next);
		if (p_temp->p_attr) free(p_temp->p_attr);
		free(p_temp);
		p_temp = p_node->p_sib;
	}

	if (p_node->p_attr) free(p_node->p_attr);
	free(p_node);

	return 0;
}

int wordic_destroy(wordic_p p_wdic)
{
	int i = 0;
	for (i=0; i<L0_SIZE; i++) {
		wordic_free(p_wdic[i].p_next);
	}

	return 0;
}

