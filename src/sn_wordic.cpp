// -*- encoding=utf-8 -*-
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "common.h"
#include "sn_wordic.h"

#define L0_SIZE 0xffff
#define INIT_CODE_VAL 0xffff
#define INVAILD_CODE_VAL 0xffff

word_dic_p word_dic_create()
{
	word_dic_p p_wdic = NULL;

	MEM_ALLOC(p_wdic, wd_node_p, sizeof(wd_node_t)*L0_SIZE, NULL);
	for (unsigned short i=0; i<L0_SIZE; i++) {
		p_wdic[i].wd_code = i; //
	}

	return p_wdic;
}

static int word_node_add_attr(wd_node_p p_node, const wd_attr_p p_attr)
{
	if (!p_node->p_attr) {
		MEM_ALLOC(p_node->p_attr, wd_attr_p, sizeof(wd_attr_t), -1);
	}

	p_node->p_attr->word_part |= p_attr->word_part;
	p_node->p_attr->senti |= p_attr->senti;
	// as one word may have more than one sentiment, so here only
	// one variable can't store information for each part of this 
	// word, that is it will be improved later!!!!!
	p_node->p_attr->senti_strength = p_attr->senti_strength;

	return 0;
}

int word_dic_add_word(word_dic_p p_wdic, unsigned short*word, int word_len, wd_attr_p p_attr)
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

		if (i >= word_len) {
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
		if (i >= word_len) {
			if (0 != word_node_add_attr(p_cur, p_attr)) return -1;
			break;
		}
	}

	return 0;
}

