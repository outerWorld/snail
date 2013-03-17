# -*- encoding=utf-8 -*-

# raw data to list as a character, the input content must be utf-8 encoded
def raw_word(content):
	"""
	ucs-4						utf-8
	U+00000000-U+0000007F	0xxxxxxx
	U+00000080-U+000007FF	110xxxxx 10xxxxxx
	U+00000800-U+0000FFFF	1110xxxx 10xxxxxx 10xxxxxx
	U+00010000-U+001FFFFF	11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
	U+00200000-U+03FFFFFF	111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
	U+04000000-U+7FFFFFFF	1111110x 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 
	"""
	num = 0
	p = content
	chars = []
	length = len(p)

	data = []
	for i in range(0, length):
		if p[i] <= 0x7F:
			chars[num] = p[i]
			num += 1
		elif p[i] & 0xB0:
			pass
		elif p[i] & 0x

if __name__ == "__main__":
	pass	
