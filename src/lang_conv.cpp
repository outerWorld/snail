
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#include "common.h"
#include "lang_conv.h"


lang_conv::lang_conv(const std_str &frm, const std_str &to)
{
	this->frm = frm;
	this->to = to;

	// compute rate between different code
	rate = 6; // default set to be 6

	buf = NULL;
	size = 0;
	conv_len = 0;
	result = 0;

	convertor = iconv_open(to.c_str(), frm.c_str());
	if (size_t(-1) == size_t(convertor)) result = 1;

}

lang_conv::~lang_conv()
{
	if (buf) free(buf);
	
	iconv_close(convertor);
}

void lang_conv::set(const std_str &frm, const std_str &to)
{
	this->frm = frm;
	this->to = to;

	// compute rate between different code
}

bool lang_conv::enlarge(size_t new_size)
{
	char * temp = NULL;

	temp = (char*)malloc(new_size);
	if (!temp) {
		result = 1;
		return false;
	}

	if (conv_len > 0) memcpy(temp, buf, conv_len);
	if (buf) free(buf);

	buf = temp;
	size = new_size;

	return true;
}

size_t lang_conv::conv(const char *in, size_t in_len)
{
	size_t 		len0 = 0;
	size_t		remain = 0;
	char * 		in_temp = (char*)in;
	size_t		in_len_temp = in_len;
	char *		temp_buf;

	if (rate*in_len > size) { enlarge(rate*in_len); }

	remain = size;
	temp_buf = buf;
	len0 = iconv(convertor, &in_temp, &in_len_temp, &temp_buf, &remain);
	if (len0 == size_t(-1)) {
		switch (errno) {
			// not enough space in buf, so a capacity enlargement seems possible.
			// however, a capacity has been promised ahead, so this error must
			// occur never.
			case E2BIG:
				result = -1;
				break;
			// An invalid multibyte sequence has been encountered in the input,
			// which means the input data is incorrect and it should ask the 
			// caller to quit or do more checkings to the input.
			case EILSEQ:
				result = -1;
				break;
			// An incomplete multibyte sequence has been encountered in the input,
			// i think the caller should connect the incomplete bytes with the
			// remained data not processed and try again.
			case EINVAL:
				result = 0;
				break;
			default:
				break;
		}
	} else result = 0;

	conv_len = size - remain;
	
	// all the data has been converted successfully.
	if (0 == in_len_temp) in_len_temp = in_len + 1;

	return in_len_temp;
}
