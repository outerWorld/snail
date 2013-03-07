
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "word_polar.h"

// 方案：1）case比较字符法 2）小hash法，将预定义的词性串生成8字节的整形数据，每个字节即为字串的每个字符,如ab -> 0x8182
int get_polar_by_string(char *str_pos, unsigned int & wd_pos)
{
	int len = strlen(str_pos);

	wd_pos = 0x00;
	if (len < 1) return 0;

	switch (str_pos[0]) {
		// 名词, 一级
		case 'n': case 'N':
			wd_pos |= WP_NOUN;
			if (len < 2) break;
			switch (str_pos[1]) {
				// 人名
				wd_pos |= WP_NOUN_P;
				case 'r':
					if (len < 3) break;
					switch (str_pos[2]) {
						// 汉语姓氏
						case '1':
							wd_pos |= WP_NOUN_P_CN1;
							break;
						// 汉语名字
						case '2':
							wd_pos |= WP_NOUN_P_CN2;
							break;
						// 日语人名
						case 'j': case 'J':
							wd_pos |= WP_NOUN_P_JP;
							break;
						// 音译人名
						case 'f': case 'F':
							wd_pos |= WP_NOUN_P_YY;
							break;
					}
					break;
				// 地名
				case 's': case 'S':
					wd_pos |= WP_NOUN_L;
					if (len < 3) break;
					switch (str_pos[2]) {
						// 音译地名
						case 'f':
							wd_pos |= WP_NOUN_L_YY;
							break;
						default:
							break;
					}
					break;
				// 机构团体名
				case 't': case 'T':
					wd_pos |= WP_NOUN_O;
					break;
				// 其它专名
				case 'z': case 'Z':
					wd_pos |= WP_NOUN_S;
					break;
				// 名词性惯用语
				case 'l': case 'L':
					wd_pos |= WP_NOUN_I;
					break;
				// 名词性词素
				case 'g': case 'G':
					wd_pos |= WP_NOUN_E;
					break;
				default:
					break;
			}
			break;
		// 时间词
		case 't': case 'T':
			wd_pos |= WP_TIME;
			if (len < 2) break;
			switch (str_pos[1]) {
				// 时间词性语素
				case 'g': case 'G':
					wd_pos |= WP_TIME_E;
					break;
				default:
					break;
			}
			break;
		// 处所词
		case 's': case 'S':
			wd_pos |= WP_POSITION;
			break;
		// 方位词
		case 'f': case 'F':
			wd_pos |= WP_DIRECTION;
			break;
		// 动词
		case 'v': case 'V':
			wd_pos |= WP_VERB;
			if (len < 2) break;
			switch (str_pos[1]) {
				// 副动词
				case 'd': case 'D':
					wd_pos |= WP_VERB_ADV;
					break;
				// 名动词
				case 'n': case 'N':
					wd_pos |= WP_VERB_NOUN;
					break;
				// 动词“是”
				case 's': case 'S':
					if (len == sizeof("vshi")-1 && strcasecmp(str_pos, "vshi") == 0) {
						wd_pos |= WP_VERB_SHI;
					}
					break;
				// 动词“有”
				case 'y': case 'Y':
					if (len == sizeof("vyou")-1 && strcasecmp(str_pos, "vyou")) {
						wd_pos |= WP_VERB_YOU;
					}
					break;
				// 趋向动词
				case 'f': case 'F':
					wd_pos |= WP_VERB_DIR;
					break;
				// 形式动词
				case 'x': case 'X':
					wd_pos |= WP_VERB_FORM;
					break;
				// 不及物动词	
				case 'i': case 'I':
					wd_pos |= WP_VERB_INTRA;
					break;
				// 动词性惯用语
				case 'l': case 'L':
					wd_pos |= WP_VERB_I;
					break;
				// 动词性语素
				case 'g': case 'G':
					wd_pos |= WP_VERB_E;
					break;
				default:
					break;
			}
			break;
		// 形容词
		case 'a': case 'A':
			wd_pos |= WP_ADJ;
			if (len < 2) break;
			switch (str_pos[1]) {
				// 副形词
				case 'd': case 'D':
					wd_pos |= WP_ADJ_ADV;
					break;
				// 名形词
				case 'n': case 'N':
					wd_pos |= WP_ADJ_NOUN;
					break;
				// 形容词性语素
				case 'g': case 'G':
					wd_pos |= WP_ADJ_E;
					break;
				// 形容词性惯用语
				case 'l': case 'L':
					wd_pos |= WP_ADJ_I;
					break;
				default:
					break;
			}
			break;
		// 区别词
		case 'b': case 'B':
			wd_pos |= WP_DIFF;
			if (len < 2) break;
			switch (str_pos[1]) {
				// 区别词性惯用语
				case 'l': case 'L':
					wd_pos |= WP_DIFF_I;
					break;
				default:
					break;
			}
			break;
		// 状态词
		case 'z': case 'Z':
			wd_pos |= WP_STATUS;
			break;
		// 代词
		case 'r': case 'R':
			wd_pos |= WP_PRONOUN;
			if (len < 2) break;
			switch (str_pos[1]) {
				// 人称代词
				case 'r': case 'R':
					wd_pos |= WP_PRONOUN_P;
					break;
				// 指示代词
				case 'z': case 'Z':
					wd_pos |= WP_PRONOUN_D;
					if (len < 3) break;
					switch (str_pos[2]) {
						// 时间指示代词
						case 't': case 'T':
							wd_pos |= WP_PRONOUN_D_T;
							break;
						// 处所指示代词
						case 's': case 'S':
							wd_pos |= WP_PRONOUN_D_PO;
							break;
						// 谓词性指示代词
						case 'v': case 'V':
							wd_pos |= WP_PRONOUN_D_PR;
							break;
						default:
							break;
					}
					break;
				// 疑问代词
				case 'y': case 'Y':
					wd_pos |= WP_PRONOUN_IR;
					if (len < 3) break;
					switch (str_pos[2]) {
						// 时间疑问代词
						case 't': case 'T':
							wd_pos |= WP_PRONOUN_IR_T;
							break;
						// 处所疑问代词
						case 's': case 'S':
							wd_pos |= WP_PRONOUN_IR_PO;
							break;
						// 谓词性疑问代词
						case 'v': case 'V':
							wd_pos |= WP_PRONOUN_IR_PR;
							break;
						default:
							break;
					}
					break;
				// 代词性语素
				case 'g': case 'G':
					wd_pos |= WP_PRONOUN_E;
					break;
				default:
					break;
			}
			break;
		// 数词
		case 'm': case 'M':
			wd_pos |= WP_NUMERAL;
			if (len < 2) break;
			switch (str_pos[1]) {
				// 数量词
				case 'q': case 'Q':
					wd_pos |= WP_NUMERAL_M;
					break;
				default:
					break;
			}
			break;
		// 量词
		case 'q': case 'Q':
			wd_pos |= WP_MEAS;
			if (len < 2) break;
			switch (str_pos[1]) {
				// 动量词
				case 'v': case 'V':
					wd_pos |= WP_MEAS_V;
					break;
				// 时量词
				case 't': case 'T':
					wd_pos |= WP_MEAS_T;
					break;
				default:
					break;
			}
			break;
		// 副词
		case 'd': case 'D':
			wd_pos |= WP_ADV;
			break;
		// 介词
		case 'p': case 'P':
			wd_pos |= WP_PERP;
			if (len < 2) break;
			switch (str_pos[1]) {
				case 'b': case 'B':
					// 介词“把”
					if (len==sizeof("pba")-1 && strcasecmp(str_pos, "pba") == 0) {
						wd_pos |= WP_PERP_BA;
					} else if (len == sizeof("pbei")-1 && strcasecmp(str_pos, "pbei") == 0) {
						wd_pos |= WP_PERP_BEI;
					// 介词“被”
					} else {
					}
					break;
				default:
					break;
			}
			break;
		// 连词
		case 'c': case 'C':
			wd_pos |= WP_CONJ;
			if (len < 2) break;
			switch (str_pos[1]) {
				// 并列连词
				case 'c': case 'C':
					wd_pos |= WP_CONJ_C;
					break;
				default:
					break;
			}
			break;
		// 助词
		case 'u': case 'U':
			wd_pos |= WP_AUX;
			// 着
			if (len==sizeof("uzhe")-1 && strcasecmp(str_pos, "uzhe") == 0) {
				wd_pos |= WP_AUX_ZHE;
			} else if (len==sizeof("ule")-1 && strcasecmp(str_pos, "ule") == 0) {
				wd_pos |= WP_AUX_LE;
				// 了 喽
			} else if (len==sizeof("uguo")-1 && strcasecmp(str_pos, "uguo") == 0) {
				wd_pos |= WP_AUX_GUO;
				// 过
			} else if (len==sizeof("ude1")-1 && strcasecmp(str_pos, "ude1") == 0) {
				wd_pos |= WP_AUX_DE1;
				// 的 底
			} else if (len==sizeof("ude2")-1 && strcasecmp(str_pos, "ude2") == 0) {
				wd_pos |= WP_AUX_DE2;
				// 地
			} else if (len==sizeof("ude3")-1 && strcasecmp(str_pos, "ude3") == 0) {
				wd_pos |= WP_AUX_DE3;
				// 得
			} else if (len==sizeof("usuo")-1 && strcasecmp(str_pos, "usuo") == 0) {
				wd_pos |= WP_AUX_SUO;
				// 所
			} else if (len==sizeof("udeng")-1 && strcasecmp(str_pos, "udeng") == 0) {
				wd_pos |= WP_AUX_DENG;
				// 等 等等 云云
			} else if (len==sizeof("uyy")-1 && strcasecmp(str_pos, "uyy") == 0) {
				wd_pos |= WP_AUX_YB;
				// 一样 一般 似的 般
			} else if (len==sizeof("udh")-1 && strcasecmp(str_pos, "udh") == 0) {
				wd_pos |= WP_AUX_DH;
				// 的话
			} else if (len==sizeof("uls")-1 && strcasecmp(str_pos, "uls") == 0) {
				wd_pos |= WP_AUX_LS;
				// 来说
			} else if (len==sizeof("uzhi")-1 && strcasecmp(str_pos, "uzhi") == 0) {
				wd_pos |= WP_AUX_ZHI;
				// 之
			} else if (len==sizeof("ulian")-1 && strcasecmp(str_pos, "ulian") == 0) {
				wd_pos |= WP_AUX_LIAN;
				// 连
			} else {
				// 
			} 
			break;
		// 叹词
		case 'e': case 'E':
			wd_pos |= WP_INTER;
			break;
		// 语气词
		case 'y': case 'Y':
			wd_pos |= WP_MODAL;
			break;
		// 拟声词
		case 'o': case 'O':
			wd_pos |= WP_ONOM;
			break;
		// 前缀
		case 'h': case 'H':
			wd_pos |= WP_PREV;
			break;
		// 后缀
		case 'k': case 'K':
			wd_pos |= WP_POST;
			break;
		// 字符串
		case 'x': case 'X':
			wd_pos |= WP_STRING;
			if (len < 2) break;
			switch (str_pos[1]) {
				// 非语素字
				case 'x': case 'X':
					wd_pos |= WP_STRING_NE;
					break;
				// 网址URL
				case 'u': case 'U':
					wd_pos |= WP_STRING_URL;
					break;
				default:
					break;
			}
			break;
		// 标点符号
		case 'w': case 'W':
			wd_pos |= WP_PUNCTION;
			if (len < 2) break;
			switch (str_pos[1]) {
				// 括号
				case 'k': case 'K':
					if (len < 3) break;
					switch (str_pos[2]) {
						// 左括号
						wd_pos |= WP_PUNCTION_LP;
						case 'z': case 'Z':
							break;
						// 右括号
						case 'y': case 'Y':
							wd_pos |= WP_PUNCTION_RP;
							break;
						default:
							break;
					}
					break;
				// 引号
				case 'y': case 'Y':
					if (len < 3) break;
					switch (str_pos[2]) {
						// 左引号
						case 'z': case 'Z':
							wd_pos |= WP_PUNCTION_LQM;
							break;
						// 右引号
						case 'y': case 'Y':
							wd_pos |= WP_PUNCTION_RQM;
							break;
						default:
							break;
					}
					break;
				// 句号
				case 'j': case 'J':
					wd_pos |= WP_PUNCTION_PER;
					break;
				// 问号
				case 'w': case 'W':
					wd_pos |= WP_PUNCTION_QUM;
					break;
				// 叹号
				case 't': case 'T':
					wd_pos |= WP_PUNCTION_EXM;
					break;
				// 逗号
				case 'd': case 'D':
					wd_pos |= WP_PUNCTION_COMMA;
					break;
				// 分号
				case 'f': case 'F':
					wd_pos |= WP_PUNCTION_SEMI;
					break;
				// 顿号
				case 'n': case 'N':
					wd_pos |= WP_PUNCTION_BSL;
					break;
				// 冒号
				case 'm': case 'M':
					wd_pos |= WP_PUNCTION_COLON;
					break;
				// 省略号
				case 's': case 'S':
					wd_pos |= WP_PUNCTION_ELLIP;
					break;
				// 破折号
				case 'p': case 'P':
					wd_pos |= WP_PUNCTION_DASH;
					break;
				// 百分号
				case 'b': case 'B':
					wd_pos |= WP_PUNCTION_PERS;
					break;
				// 单位符号
				case 'h': case 'H':
					wd_pos |= WP_PUNCTION_UNIT;
					break;
				default:
					break;
			}
			break;
		default:
			break;
	}
}
