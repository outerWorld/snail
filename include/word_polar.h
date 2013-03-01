/*
 * Author: huang chunping
 * Date  : 2013-03-01
 * Desc  :
 */

#ifndef __WORD_POLAR_H
#define __WORD_POLAR_H

// 词性从ictclas处获取
enum {
	WP_NOUN = 0x010000, //一级名词
	WP_TIME = 0x020000, // 时间词
	WP_POSITION = 0x30000, // 处所词
	WP_DIRECTION = 0x40000,// 方位词
	WP_VERB = 0x50000, // 动词	
	WP_ADJ = 0x60000, // 形容词
	WP_DIFF = 0x70000, // 区别词（？）
	WP_STATUS = 0x80000, // 状态词（？）
	WP_PRONOUN = 0x90000, // 代词
	WP_NUMERAL = 0xA0000, // 数词
	WP_MEAS = 0xB0000, // 量词
	WP_ADV = 0xC0000, // 副词
	WP_PERP = 0xD0000, // 介词
	WP_CONJ = 0xE0000, // 连词
	WP_AUX = 0xF0000, // 助词	
	WP_INTER = 0x100000, //叹词
	WP_MODAL = 0x200000, // 语气词
	WP_ONOM = 0x300000, // 拟声词
};

#endif // __WORD_POLAR_H
