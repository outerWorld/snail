# -*- encoding=utf-8 -*-

import sys
import math
import jieba.posseg as pseg

class punctuation():
	def __init__(self):
		pass
	def load(self, punc_file):
		pass
	def is_sent_punct(self, wd):
		pass
	def is_punct(self, wd):
		pass

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
			segs = line.strip('\n').split()
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

	# sentence flag: . or ? or !
	def chk_sent_flag(self, char):
		if char == u'。' or char == u'.' or char == u'?' or char == u'？' or char == u'!' or char == u'！':
			return True
		else:
			return False

	# punctuation: .~`!@#$%^&*()-_=+;:'"/?.>,<
	def chk_
	
	def file_ws(self, raw_file):
		#words = pseg.cut(content)
		if not hasattr(self, "wordlist"):
			self.wordlist = {}
		else:
			self.wordlist.clear()

		if not hasattr(self, "linelist"):
			self.linelist = {}
		else:
			self.linelist.clear()

		for line in open(raw_file, 'rb'):
			data = []
			p = line.decode('utf-8')
			for i in range(0, len(p)):
				print "word = %s" %(p[i])
				if self.chk_sent_flag(p[i]):
					if len(data) > 0:
						print "sentence = [%s]" %(''.join(data))
					data = []
				else:
					data.append(p[i])

		return 0

		for wd in words:
			wd_seg = wd.strip('\n').split('/')
			if len(wd_seg) < 2:
				continue
			w = wd_seg[0]
			pol = wd_seg[1]
			

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
			else:
				p2 = 0.0
		else:
			#p1 = 0.0
			pass

		# p(wd2)
		if wd2 in self.wd_prob_dic:
			wd2_prob = self.wd_prob_dic[wd2][wd2]

		if wd2_prob == 0 or wd12_prob == 0:
			return 0
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
	if len(sys.argv) > 2:
		digger = word_digger(sys.argv[1])
		digger.load_wd_prob()
		# digger.show_dic()
		digger.wd_dig(sys.argv[2])
