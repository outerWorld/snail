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
	int chg_sep(const std_str &sep) { this->sep = sep; }
	void clear() { words.clear(); }
	int work_on(const std_str & line);
	const std_str & operator [](int id);
	void debug();
public:
	const static std_str err;

private:
	int	split(const std_str & data, const std_str & sep, word_vec & wds);

private:
	std_str		raw;
	std_str 	sep;
	word_vec 	words;
};

#endif // __WORD_SPLITTER_H
