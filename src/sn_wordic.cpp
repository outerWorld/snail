// -*- encoding=utf-8 -*-
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

int wordic_load(wordic_p p_dic, char *dicfile)
{
	return 0;
}

int wordic_store(wordic_p p_dic, char *dicfile)
{
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
		free(p_temp);
		p_temp = p_node->p_sib;
	}

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

