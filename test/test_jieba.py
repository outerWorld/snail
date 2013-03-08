# -*- encoding=utf-8 -*-

import sys
import jieba

f = open(sys.argv[1], "r")

buf = f.read()

seg_list = jieba.cut(buf, cut_all=False)

print "/ ".join(seg_list)
