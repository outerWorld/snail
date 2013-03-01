
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <string>

#include "sn_string.h"

#if 0
sn_string::sn_string():std_str() {}

sn_string::sn_string(char *str, int len):std_str(str, len)
{
}

sn_string::sn_string(const std_str &a):std_str(a)
{
}
#else
sn_string::sn_string()
{
}

sn_string::sn_string(char *str, int len)
{
	data = std_str(str, len)
}

sn_string::sn_string(const std_str &a)
{
	data = std_str(a)
}

#endif

sn_string::~sn_string()
{
	//std_str::~string();
}


size_t sn_string::find(const std_str &str, size_t pos) const
{
	const char * sub_str;
	const char * f_str;
	size_t len0 = 0;
	size_t len1 = 0;
	size_t i = 0;

	len0 = str.length();
	sub_str = str.data();

	len1 =  data.length();
	f_str = data.data();

	if (len1 < len0) return std_str::npos;

	while (len1-i >= len0) {
		if (memcmp(f_str+i, sub_str, len0) == 0) break;	
		i++;
	}

	if (len1-i < len0) return std_str::npos;

	return i;
}
