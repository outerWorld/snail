// -*- encoding=utf-8 -*-
/*
 * Author: huang chunping
 * Date  : 2013-01-25
 * Desc  :
 *		word dict file format:
 *		词表头|词属性列表|词内容块
 *      词表头=词表字节大小(4byte)，词个数(1byte)，词编码方式(1byte)
 *		词属性列表={词ID(4byte)，词偏移(4byte)，内容长度(2byte)}，
 *		词内容块={词字节长(1byte)，词内容(nbyte)，词性(1byte)，情感特征及强度（1byte)，词频(1byte)，
 *				  近似词个数（1byte)，近似词ID列表（4*n)，反义词个数（1byte），
 *				  反义词ID列表（4*n）}，
 *
 *	内存中以hash存储，
 */

#ifndef __SN_WORDICT_H
#define __SN_WORDICT_H

//namespace word_dic {
// word part definition 词性定义
enum {
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
	WD_POL_NEG = -1,	// 情感负极性(negativity)，贬义
	WD_POL_NEU,			// 情感中性(neutrality)，无义
	WD_POL_POS,			// 情感正极性(positivity)，褒义
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
typedef wd_node_p word_dic_p;
struct _wd_node_s {
	unsigned short	wd_code;	// unicode value
	wd_attr_p		p_attr;		// attribute of word
	wd_node_p		p_sib;		// sibling, in the same level
	wd_node_p		p_next;		// the word next to current, for example, "我们", current node is"我"，its next node is "们"
};

word_dic_p word_dic_create();

int word_dic_add_word(word_dic_p p_wdic, char *word, word_attr_p p_attr);

int word_dic_get_word_attr(word_dic_p p_wdic, char *word, word_attr_p p_attr);

int word_dic_destroy(word_dic_p p_wdic);

//}

#endif // __SN_WORDICT_H
