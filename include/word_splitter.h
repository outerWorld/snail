/*
 * Author: huang chunping
 * Date  : 2013-1-30
 * Desc  : word_splitter for splitting word in line
 */

#ifndef __WORD_SPLITTER_H
#define __WORD_SPLITTER_H

#include <vector>

typedef std::string std_str;
typedef std::vector<std_str> word_vec;

class word_splitter {
public:
	word_splitter(const std_str & line, const std_str & sep=" ");
	~word_splitter();
#if 0
	int redo(std_str sep);
#endif
	void clear() { words.clear(); }
	int work_on(const std_str & line);
	const std_str & operator [](int id);
	void debug();

private:
	int	split(const std_str & data, const std_str & sep, word_vec & wds);

private:
	const static std_str err;
	std_str		raw;
	std_str 	sep;
	word_vec 	words;
};

#endif // __WORD_SPLITTER_H
