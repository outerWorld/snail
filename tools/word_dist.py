# -*- encoding=utf8 -*-
import sys

punct_list = [u'.', u',', u'。', u'!', u'！', u'?', u'？', u'（', u'〔', u'［', u'｛', u'《', u'【', u'〖', u'〈', u'(', u'[', u'{', u'<', u'）', u'〕',  u'］', u'｝', u'》', u'】', u'〗', u'〉', u')', u']', u'{', u'>', u'“', u'‘', u'『', u'”', u'’',  u'』', u'。', u'，', u',', u'；', u';', u'、', u'：', u':', u'…', u'—', u'－', u'-', u'％', u'‰', u'%', u'￥', u'＄', u'￡', u'°', u'℃' , u'$']

class word_dist():
	def __init__(self, max_wordlen):
		self.words = { }
		self.max_wordlen = max_wordlen
		pass

	def add_file(self, article):
		for line in open(article, 'rb'):
			chars = line.strip('\n').decode('utf-8')
			pure_chars = [w for w in chars if w not in punct_list]
			temp = ''
			count = 0
			for c in pure_chars:
				if c not in self.words:
					self.words[c] = 0
				self.words[c] += 1
				if count < self.max_wordlen:
					temp = temp + c
					count += 1
					continue
				temp_len = len(temp)
				for i in range(0, temp_len-1):
					for j in range(i+1, temp_len):
						w = temp[i:j+1]
						if w not in self.words:
							self.words[w] = 0
						self.words[w] += 1
				if temp not in self.words:
					self.words[c] = 0

				temp = temp[1:]
				count -= 1

	def sort_by_freq(self):
		w_freq = { }
		sorted_freq = []
		for w in self.words:
			f = self.words[w]
			if f not in w_freq:
				w_freq[f] = []
			w_freq[f].append(w)

		for freq in sorted(w_freq.keys()):
			sorted_freq.append((freq, w_freq[freq]))	

		return sorted_freq

	def get(self, top_n):
		sorted_data = self.sort_by_freq()
		if len(sorted_data) < top_n:
			return sorted_data[:]
		else:
			return sorted_data[0:top_n+1]

# python word_dist topN file1 file2 ...
if __name__ == "__main__":
	if len(sys.argv) > 3:
		w_dist = word_dist(10)
		for i in range(2, len(sys.argv)):
			w_dist.add_file(sys.argv[i])
		word_freq = w_dist.get(int(sys.argv[1]))
		for wf in word_freq:
			print "%d\t%s" %(wf[0], ":".join(wf[1][:]))
