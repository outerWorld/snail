/*
 * Author: huang chunping
 * Date  : 2013-03-01
 * Desc  :
 */

#ifndef __WORD_POLAR_H
#define __WORD_POLAR_H

// 标点符号定义
// 左括号
#define LEFT_PBRACKET_MARK 	0x10
// 右括号
#define RIGHT_PBRACKET_MARK 0x20
// 左引号
#define LEFT_QUTA_MARK 		0x30
// 右引号
#define RIGHT_QUTA_MARK 	0x40
// 句号
#define PERIOD_MARK 		0x50
// 问号
#define QUESTION_MARK 		0x60
// 感叹号
#define EXCLAM_MARK 		0x70
// 逗号
#define COMMA_MARK 			0x80
// 分号
#define SEMICOLON_MARK 		0x90
// 顿号
#define BACKSLOP_MARK 		0xA0
// 冒号
#define COLON_MARK 			0xB0
// 省略号
#define ELLIPSIS_MARK 		0xC0
// 破折号
#define DASH_MARK 			0xD0
// 百分号
#define PERCENT_MARK 		0xE0
// 单位符号
#define UNIT_MARK 			0xF0

// 词性从ictclas处获取,高3个字节的每一位表示一级词性，可有24个一级词性，二级词性用低字节的高4位表示（16个二级词性），三级词性用低字节的低4位表示（16个三级词性）
enum {
	WP_UNK 			= 		0x00000000, // 未知
	WP_NOUN 		= 		0x00000100, //一级名词
	WP_NOUN_P		= 		0x00000110, // 二级名词 人名
	WP_NOUN_P_CN1	=		0x00000111, // 三级名词 人名 汉语姓氏
	WP_NOUN_P_CN2	=		0x00000112, // 三级名词 人名 汉语名字
	WP_NOUN_P_JP	=		0x00000113, // 三级名词 人名 日语人名
	WP_NOUN_P_YY	=		0x00000114, // 三级名词 人名 音译人名
	WP_NOUN_L		= 		0x00000120, // 二级名词 地名 (Location)
	WP_NOUN_L_YY	= 		0x00000121, // 三级名词 地名 音译地名 (yinyi)
	WP_NOUN_O		= 		0x00000130, // 二级名词 机构团体名(organization)
	WP_NOUN_S		= 		0x00000140, // 二级名词 专有名(special)
	WP_NOUN_I		= 		0x00000150, // 二级名词 惯用语(idiom)
	WP_NOUN_E		= 		0x00000160, // 二级名词 词素(element)

	WP_TIME 		= 		0x00000200, // 一级时间词
	WP_TIME_E 		= 		0x00000210, // 二级时间词 词素(element)

	WP_POSITION 	= 		0x00000400, // 一级处所词

	WP_DIRECTION 	= 		0x00000800, // 一级方位词

	WP_VERB 		= 		0x00001000, // 一级动词	
	WP_VERB_ADV 	= 		0x00001010, // 二级动词	副动词(adv)
	WP_VERB_NOUN 	= 		0x00001020, // 二级动词	名动词(noun)
	WP_VERB_SHI 	= 		0x00001030, // 二级动词	是(shi)
	WP_VERB_YOU 	= 		0x00001040, // 二级动词	有(you)
	WP_VERB_DIR 	= 		0x00001050, // 二级动词	趋向动词(directional)
	WP_VERB_FORM 	= 		0x00001060, // 二级动词	形式动词(formal)
	WP_VERB_INTRA 	= 		0x00001070, // 二级动词	不及物动词(intransitive)
	WP_VERB_I 		= 		0x00001080, // 二级动词	惯用语(idiom)
	WP_VERB_E		= 		0x00001090, // 二级动词	词素(element)

	WP_ADJ 			= 		0x00002000, // 一级形容词
	WP_ADJ_ADV 		= 		0x00002010, // 二级形容词 副形词(adv)
	WP_ADJ_NOUN 	= 		0x00002020, // 二级形容词 名形词(adv)
	WP_ADJ_E 		= 		0x00002030, // 二级形容词 词素(element)
	WP_ADJ_I 		= 		0x00002040, // 二级形容词 惯用语(idiom)

	WP_DIFF 		= 		0x00004000, // 一级区别词（？）
	WP_DIFF_I 		= 		0x00004010, // 二级区别词 惯用语（idiom）

	WP_STATUS 		= 		0x00008000, // 状态词（？）

	WP_PRONOUN 		= 		0x00010000, // 一级代词
	WP_PRONOUN_P 	= 		0x00010010, // 二级代词 人称代词(personal)
	WP_PRONOUN_D 	= 		0x00010020, // 二级代词 指示代词 (demonstrative)
	WP_PRONOUN_D_T 	= 		0x00010021, // 三级代词 指示代词 时间指示(Time)
	WP_PRONOUN_D_PO = 		0x00010022, // 三级代词 指示代词 处所指示(Position)
	WP_PRONOUN_D_PR = 		0x00010023, // 三级代词 指示代词 谓词性指示(predicate)
	WP_PRONOUN_IR 	= 		0x00010030, // 二级代词 疑问代词(interrogative)
	WP_PRONOUN_IR_T = 		0x00010031, // 三级代词 疑问代词 时间疑问(Time)
	WP_PRONOUN_IR_PO= 		0x00010032, // 三级代词 疑问代词 处所疑问(Position)
	WP_PRONOUN_IR_PR= 		0x00010033, // 三级代词 疑问代词 谓词疑问(predicate)
	WP_PRONOUN_E 	= 		0x00010040, // 二级代词 词素(element)

	WP_NUMERAL 		= 		0x00020000, // 一级数词
	WP_NUMERAL_M 	= 		0x00020010, // 二级数词 数量词(measure)

	WP_MEAS 		= 		0x00040000, // 一级量词
	WP_MEAS_V 		= 		0x00040010, // 二级量词 动量词(Verb)
	WP_MEAS_T 		= 		0x00040020, // 二级量词 时量词(Time)

	WP_ADV 			= 		0x00080000, // 一级副词

	WP_PERP 		= 		0x00100000, // 一级介词
	WP_PERP_BA 		= 		0x00100010, // 二级介词 把(ba)
	WP_PERP_BEI 	= 		0x00100020, // 二级介词 被(bei)

	WP_CONJ 		= 		0x00200000, // 一级连词
	WP_CONJ_C 		= 		0x00200010, // 二级连词 并列(coordinating)

	WP_AUX 			= 		0x00400000, // 一级助词	
	WP_AUX_ZHE 		= 		0x00400010, // 二级助词	着(zhe)
	WP_AUX_LE 		= 		0x00400020, // 二级助词	了、喽(le)
	WP_AUX_GUO 		= 		0x00400030, // 二级助词	过(guo)
	WP_AUX_DE1 		= 		0x00400040, // 二级助词	的、底(de)
	WP_AUX_DE2 		= 		0x00400050, // 二级助词	地(de)
	WP_AUX_DE3 		= 		0x00400060, // 二级助词 得(de)
	WP_AUX_SUO 		= 		0x00400070, // 二级助词 所(suo)
	WP_AUX_DENG 	= 		0x00400080, // 二级助词 等等 等(deng)
	WP_AUX_YB 		= 		0x00400090, // 二级助词 一般 一样 似的(yiban)
	WP_AUX_DH 		= 		0x004000A0, // 二级助词 的话(de hua)
	WP_AUX_LS 		= 		0x004000B0, // 二级助词 来说(lai shuo)
	WP_AUX_ZHI 		= 		0x004000C0, // 二级助词 之(zhi)
	WP_AUX_LIAN 	= 		0x004000D0, // 二级助词 连(lian)

	WP_INTER 		= 		0x00800000, //一级叹词

	WP_MODAL 		= 		0x01000000, // 一级语气词

	WP_ONOM 		= 		0x02000000, // 一级拟声词

	WP_PUNCTION 	= 		0x04000000, // 一级标点符号
	WP_PUNCTION_LP 	= 		WP_PUNCTION|LEFT_PBRACKET_MARK, // 二级标点符号 左括号(left parenthesesbrackets)
	WP_PUNCTION_RP 	= 		WP_PUNCTION|RIGHT_PBRACKET_MARK, // 二级标点符号 右括号(right parenthesesbrackets)
	WP_PUNCTION_LQM = 		WP_PUNCTION|LEFT_QUTA_MARK, // 二级标点符号 左引号(left quotation mark)
	WP_PUNCTION_RQM = 		WP_PUNCTION|RIGHT_QUTA_MARK, // 二级标点符号 右引号(right quotation mark)
	WP_PUNCTION_PER = 		WP_PUNCTION|PERIOD_MARK, // 二级标点符号 句号(period)
	WP_PUNCTION_QUM = 		WP_PUNCTION|QUESTION_MARK, // 二级标点符号 问号(question mark)
	WP_PUNCTION_EXM = 		WP_PUNCTION|EXCLAM_MARK, // 二级标点符号 叹号(exclamation mark)
	WP_PUNCTION_COMMA = 	WP_PUNCTION|COMMA_MARK, // 二级标点符号 逗号(comma)
	WP_PUNCTION_SEMI = 		WP_PUNCTION|SEMICOLON_MARK, // 二级标点符号 分号(semicolon)
	WP_PUNCTION_BSL = 		WP_PUNCTION|BACKSLOP_MARK, // 二级标点符号 顿号(Chinese back-sloping comma)
	WP_PUNCTION_COLON = 	WP_PUNCTION|COLON_MARK, // 二级标点符号 冒号(colon)
	WP_PUNCTION_ELLIP = 	WP_PUNCTION|ELLIPSIS_MARK, // 二级标点符号 省略号(ellipsis)
	WP_PUNCTION_DASH = 		WP_PUNCTION|DASH_MARK, // 二级标点符号 破折号(dashChinese dash)
	WP_PUNCTION_PERS = 		WP_PUNCTION|PERCENT_MARK, // 二级标点符号 百分号(percent sign)
	WP_PUNCTION_UNIT = 		WP_PUNCTION|UNIT_MARK, // 二级标点符号 单位符号(unit sign)

	WP_STRING 		= 		0x08000000, // 一级字符串
	WP_STRING_NE 	= 		0x08000010, // 一级字符串 非语素字(not element)
	WP_STRING_URL 	= 		0x08000020, // 一级字符串 网址URL(url)

	WP_PREV 		= 		0x10000000, // 前缀
	WP_POST 		= 		0x20000000, // 后缀
};


#define IS_PUNCTION(polar) (polar&WP_PUNCTION != 0x00)
#define IS_SENT_MARK(polar) (polar&WP_PUNCTION && \
((polar&0xF0==PERIOD_MARK)||(polar&0xF0==QUESTION_MARK)|| (polar&0xF0==EXCLAM_MARK)))

// for comforming to ictclas
int get_polar_by_string(char *str_pos, unsigned int & wd_pos);

#endif // __WORD_POLAR_H
