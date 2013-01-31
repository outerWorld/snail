// -*- encoding=utf-8 -*-
/*
 * Author: huang chunping
 * Date  : 2013-01-25
 * Desc  :
 *		word dict file format:
 *			{词长度（2bytes）、词内容、词属性长度（2bytes）、属性}
 *
 *	内存中构建两张trie表，一张正向表，一张逆向表，在分词时可正向和逆向
 */

#ifndef __SN_WORDICT_H
#define __SN_WORDICT_H

//namespace wordic {
// word part definition 词性定义
enum {
	WD_PART_UNKNOWN = 0x0000,
	WD_PART_NOUN = 0x0001,			// 名词(noun)
	WD_PART_PRONOUN = 0x0002,		// 代词(pronoun)，如你、我，这个，那个
	WD_PART_ADJ = 0x0004,			// 形容词(adjective)
	WD_PART_ADV = 0x0008,			// 副词(adverb)
	WD_PART_VERB = 0x0010,			// 动词(verb)，如看、评论
	WD_PART_DEGREE_ADV = 0x0020,	// 程度副词(degree adverb)
	WD_PART_NUME = 0x0040, 			// 数词(numeral)，一、第一、一倍...
	WD_PART_MEAS = 0x0080,			// 量词/单位词(measure word)，如个
	WD_PART_PERP = 0x0100,			// 介词(perposition)，如在、向、从
	WD_PART_CONJ = 0x0200,			// 连词(conjunction)，如和、与
	WD_PART_AUX = 0x0400,			// 助词(Auxiliary word)，如的、地、得，着
	WD_PART_INTER = 0x0800,			// 叹词(interjection)，如嗯、唉、喂
	WD_PART_ONOM = 0x1000,			// 拟声词（Onomatopoeic），如嘟嘟、哗哗
	WD_PART_SENTI = 0x2000,			// 情感词（sentiment），如悲哀、悲伤、厌恶、喜欢、愉快
};

// word polarity definition 情感倾向定义
enum {
	WD_POL_NEG = 0x01,	// 情感负极性(negativity)，贬义
	WD_POL_NEU = 0x02,	// 情感中性(neutrality)，无义
	WD_POL_POS = 0x04,	// 情感正极性(positivity)，褒义
};

// senti 情感类型定义
enum {
	SENTI_UNKNOWN = 0x00,
	SENTI_HAPPY,
	SENTI_ANGRY,
	SENTI_HATE,
};

typedef struct _wd_attr_s {
	unsigned char	senti:4;
	unsigned char	senti_strength:4;
	char			word_pol;			// word polarity
	unsigned short	word_part; 			// composition of word part, bit mode used. for example:WD_PART_PRONOUN|WD_PART_ADJ
}wd_attr_t, *wd_attr_p;

/* word node: single word, for example "我", not "我们"
 * and it will be used as the node of tire-tree
 * {a,b,c,d,....}
 */
struct _wd_node_s;
typedef struct _wd_node_s wd_node_t;
typedef struct _wd_node_s *wd_node_p;
typedef wd_node_p wordic_p;
struct _wd_node_s {
	unsigned short	wd_code;	// unicode value
	wd_attr_p		p_attr;		// attribute of word
	wd_node_p		p_sib;		// sibling, in the same level
	wd_node_p		p_next;		// the word next to current, for example, "我们", current node is"我"，its next node is "们"
};

wordic_p wordic_create();

// load dict data from file
int wordic_load(wordic_p p_dic, char *dicfile);

int wordic_add_word(wordic_p p_wdic, unsigned short*word, int word_len, wd_attr_p p_attr);

int wordic_get_word_attr(wordic_p p_wdic, unsigned short *word, int word_len, wd_attr_p p_attr);

// store dict data to file
int wordic_store(wordic_p p_dic, char *dicfile);

int wordic_destroy(wordic_p p_wdic);

//}

#endif // __SN_WORDICT_H
