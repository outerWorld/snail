# -*- encoding=utf-8 -*-
import sys

# raw data to list as a character, the input content must be utf-8 encoded
def raw_word(content):
	"""
	ucs-4						utf-8
	U+00000000-U+0000007F	0xxxxxxx
	U+00000080-U+000007FF	110xxxxx 10xxxxxx	(0xC0 )
	U+00000800-U+0000FFFF	1110xxxx 10xxxxxx 10xxxxxx (0xE0)
	U+00010000-U+001FFFFF	11110xxx 10xxxxxx 10xxxxxx 10xxxxxx (0xF0)
	U+00200000-U+03FFFFFF	111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx (0xF8)
	U+04000000-U+7FFFFFFF	1111110x 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx (0xFC)
	"""
	num = 0
	p = content
	chars = []
	length = len(p)

	data = []
	#print "length = %d, %s" %(length, content)
	i = 0
	while i < length:
		print ''.join(p[i])
		if ord(p[i]) <= 0x7F:
			chars[num] = ''.join(p[i])
			print p[i]
			i += 1
		elif ord(p[i]) & 0xC0 == 0xC0:
			chars[num] = ''.join(p[i:i+2])
			print p[i:i+2]
			i += 2
		elif ord(p[i]) & 0xE0 == 0xE0:
			chars[num] = ''.join(p[i:i+3])
			print p[i:i+3]
			i += 3
		elif ord(p[i]) & 0xF0 == 0xF0:
			#chars[num] = ''.join(p[i:i+4])
			print p[i:i+4]
			i += 4
		elif ord(p[i]) & 0xF8 == 0xF8:
			chars[num] = ''.join(p[i:i+5])
			print p[i:i+5]
			i += 5
		elif ord(p[i]) & 0xFC == 0xFC:
			chars[num] = ''.join(p[i:i+6])
			print p[i:i+6]
			i += 6
		else:
			# error encoded
			return []
		num += 1
		
	return chars

def show_chars(content):
	p = content.decode('utf-8')	
	for i in range(0, len(p)):
		print p[i]

if __name__ == "__main__":
	if len(sys.argv) > 1:
		#print raw_word(open(sys.argv[1], 'rb').read())
		show_chars(open(sys.argv[1], 'rb').read())
