# -*- encoding=utf-8 -*-

import sys
import math
import jieba.posseg as pseg
from word_dig_config import *

class punctuation():
	def __init__(self):
		pass

	def load(self, punc_file):
		if not hasattr(self, 'punc_list'):
			self.punc_list = { }
		else:
			self.punc_list.clear()

		for line in open(punc_file, 'rb'):
			line = line.decode('utf-8')
			if line[0] == u'#':
				continue
			segs = line.strip(u'\n').split(u'/')
			if len(segs) == 2:
				# sentence flag with 's'
				self.punc_list[segs[0]] = segs[1]
			elif len(segs) == 1:
				# not sentence flag
				self.punc_list[segs[0]] = u'n'
			else:
				continue
		self.punc_list[u'\n'] = u'n'

	def is_sent_punct(self, wd):
		if wd in self.punc_list and self.punc_list[wd] == u's':
			return True
		else:
			return False

	def is_punct(self, wd):
		if wd in self.punc_list:
			return True
		else:
			return False

	def show(self):
		for wd in self.punc_list:
			print "%s/%s" %(wd, self.punc_list[wd])

class word_digger():
	def __init__(self, wd_prob_file):
		self.wd_prob_dic = { }
		self.wd_prob_file = wd_prob_file
		self.threshold = 1.4
		pass

	def set_threshold(self, value):
		self.threshold = value

	def load_wd_prob(self):
		for line in open(self.wd_prob_file, 'r'):
			segs = line.decode('utf-8').strip(u'\n').split(u' ')
			num = len(segs)
			if num < 2:
				continue
			if segs[0][0] == '#':
				continue
			if num == 2:
				if segs[0] not in self.wd_prob_dic:
					self.wd_prob_dic[segs[0]] = { }
				self.wd_prob_dic[segs[0]][segs[0]] = float(segs[1])	
				pass
			elif num == 3:
				if segs[0] not in self.wd_prob_dic:
					self.wd_prob_dic[segs[0]] = { }
				self.wd_prob_dic[segs[0]][segs[1]] = float(segs[2])
				pass
			else:
				continue

	def file_ws(self, raw_file):
		if not hasattr(self, "wordlist"):
			self.wordlist = {}
		else:
			self.wordlist.clear()

		if not hasattr(self, "linelist"):
			self.linelist = []
		else:
			self.linelist.clear()
		
		chara_list = []
		for line in open(character_file, 'rb'):
			if line[0] == '#':
				continue
			chara_list.append(line.strip('\n').decode('utf-8'))

		punct = punctuation()
		punct.load(punct_config_file)

		for line in open(raw_file, 'rb'):
			data = []
			#print "%s" %(line.strip('\n'))
			p = line.strip('\n').decode('utf-8')
			#print "line = %s" %(p)
			for i in range(0, len(p)):
				#print "word=[%s]" %(p[i])
				if punct.is_punct(p[i]):
					if punct.is_sent_punct(p[i]):
						if len(data) > 0:
							self.linelist.append(''.join(data))
							data = []
						else:
							pass
					else:
						pass
				else:
					data.append(p[i])
			# if no sentence punctuation
			if len(data) > 0:
				self.linelist.append(''.join(data))

		for line in self.linelist:
			#print "%s" %(line)
			words = list(pseg.cut(line.encode('utf-8')))
			#print type(words)
			for wd in words:
				#print "w=%s pol=%s" %(wd.word, wd.flag)
				for w in chara_list:
					print "%s %s = %f" %(w, wd.word, self.calc_ir_score(wd.word, w))

	# calculate interrelation score
	# I(wd1, wd2) = log2(p(wd2|wd1)/p(wd2))
	def calc_ir_score(self, wd1, wd2):
		wd2_prob, wd12_prob = 0.0, 0.0

		if wd1 in self.wd_prob_dic:
			# p(wd1)
			#wd1_prob = self.wd_prob_dic[wd1][wd1]
			# p(wd2|wd1)
			if wd2 in self.wd_prob_dic[wd1]:
				wd12_prob = self.wd_prob_dic[wd1][wd2]
				print "[wd12_prob] = %f" %(wd12_prob)
			else:
				p2 = 0.0
		else:
			#p1 = 0.0
			pass

		# p(wd2)
		if wd2 in self.wd_prob_dic:
			wd2_prob = self.wd_prob_dic[wd2][wd2]

		if wd2_prob == 0 or wd12_prob == 0:
			return 0.0
		else:
			return math.log(wd12_prob/wd2_prob, 2)

	def show_dic(self):
		for wd in self.wd_prob_dic:
			for wd2 in self.wd_prob_dic[wd]:
				if wd != wd2:
					print "%s %s %f" %(wd, wd2, self.wd_prob_dic[wd][wd2])
				else:
					print "%s %f" %(wd, self.wd_prob_dic[wd][wd2])

	def wd_dig(self, raw_file):
		self.file_ws(raw_file)

if __name__ == "__main__":
	if len(sys.argv) > 1:
		digger = word_digger(wd_prob_config_file)
		digger.load_wd_prob()
		# digger.show_dic()
		digger.set_threshold(glb_threshold_value)
		digger.wd_dig(sys.argv[1])
