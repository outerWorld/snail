/*
 * Author: huang chunping
 * Date  : 2013-03-01
 * Desc  :
 */

#ifndef __WORD_POLAR_H
#define __WORD_POLAR_H

// 词性从ictclas处获取,高3个字节的每一位表示一级词性，可有24个一级词性，二级词性用低字节的高4位表示（16个二级词性），三级词性用低字节的低4位表示（16个三级词性）
enum {
	WP_UNK 			= 		0x00000000, // 未知
	WP_NOUN 		= 		0x00000100, //一级名词
	WP_TIME 		= 		0x00000200, // 时间词
	WP_POSITION 	= 		0x00000400, // 处所词
	WP_DIRECTION 	= 		0x00000800,// 方位词
	WP_VERB 		= 		0x00001000, // 动词	
	WP_ADJ 			= 		0x00002000, // 形容词
	WP_DIFF 		= 		0x00004000, // 区别词（？）
	WP_STATUS 		= 		0x00008000, // 状态词（？）
	WP_PRONOUN 		= 		0x00010000, // 代词
	WP_NUMERAL 		= 		0x00020000, // 数词
	WP_MEAS 		= 		0x00040000, // 量词
	WP_ADV 			= 		0x00080000, // 副词
	WP_PERP 		= 		0x00100000, // 介词
	WP_CONJ 		= 		0x00200000, // 连词
	WP_AUX 			= 		0x00400000, // 助词	
	WP_INTER 		= 		0x00800000, //叹词
	WP_MODAL 		= 		0x01000000, // 语气词
	WP_ONOM 		= 		0x02000000, // 拟声词
	WP_PUNCTION 	= 		0x04000000, // 标点符号
	WP_STRING 		= 		0x08000000, // 字符串
	WP_PREV 		= 		0x10000000, // 前缀
	WP_POST 		= 		0x20000000, // 后缀
};

// for comforming to ictclas
int get_polar_by_string(char *str_pos, unsigned int & wd_pos);

#endif // __WORD_POLAR_H
