/*
 * Author: huang chunping
 * Date  : 2013-1-31
 * Desc  : it encapsulates the iconv library
 */

#ifndef __LANG_CONV_H
#define __LANG_CONV_H

#include <iconv.h>

#include "common.h"

class lang_conv {
public:
	lang_conv(const std_str &frm, const std_str &to);
	~lang_conv();

	void set(const std_str &frm, const std_str &to);
	// return the position failed converted. if return value
	// is not equal to in_len+1, then the caller should check the
	// result and function's return value.
	size_t conv(const char *in, size_t in_len);
	size_t len() { return conv_len; }
	const char * data() { return buf; }
	bool ok() { return result==0?true:false; }
private:
	bool enlarge(size_t new_size);

private:
	iconv_t convertor;
	int		rate;  // byte rate between frm_code to, utf8->ucs2 ,rate is 2/4 = 0.5, if the size of data input is len0, then the output buffer size needs len0*rate.
	std_str frm;
	std_str to;
	size_t 	size; 	//
	size_t 	conv_len; 	// the length of data converted successfully.
	char * 	buf;
	int		result;
};

#endif // __LANG_CONV_H
