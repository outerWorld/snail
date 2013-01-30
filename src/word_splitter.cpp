#include <stdlib.h>
#include <string.h>

#include <iostream>
#include <string>

#include "word_splitter.h"

const std_str word_splitter::err = "";

word_splitter::word_splitter(const std_str & line, const std_str & sep)
{
	this->raw = line;
	this->sep = sep;
	words.clear();

	split(line, sep, words);
}

word_splitter::~word_splitter()
{
	words.clear();
}

#if 0
int word_splitter::redo(std_str sep)
{
}
#endif

static size_t find_pos(const std_str & d1,  const std_str & sub_d, size_t b_pos = 0)
{
	const char * p_d1;
	const char * p_sub_d;
	size_t len0;
	size_t len1;
	size_t i = 0;

	p_d1 = d1.data();
	len0 = d1.length();
	p_sub_d = sub_d.data();
	len1 = sub_d.length();
	i = b_pos;

	if (len0-i < len1) return std_str::npos;

	while (len0-i >= len1) {
		if (memcmp(p_d1+i, p_sub_d, len1) == 0) break;
		i++;
	}

	if (len0-i < len1) return std_str::npos;

	return i;
}

int	word_splitter::split(const std_str & data, const std_str & isep, word_vec & wds)
{
	size_t b_pos = 0;
	size_t e_pos = 0;

	b_pos = 0;
	e_pos = find_pos(data, isep, b_pos);
	while (e_pos != std_str::npos) {
		wds.push_back(data.substr(b_pos, e_pos-b_pos));
		b_pos = e_pos + sep.length();
		e_pos = find_pos(data, isep, b_pos);
	}
	
	if (e_pos == std_str::npos) e_pos = data.length();
	if (b_pos == std_str::npos) b_pos = data.length();
	if (b_pos != e_pos) {
		wds.push_back(data.substr(b_pos, e_pos-b_pos));
	}

	return 0;
}

int word_splitter::work_on(const std_str & line)
{
	raw = line;
	return split(line, sep, words);
}

const std_str& word_splitter::operator [](int id)
{
	if (id >= words.size()) {
		return word_splitter::err; 
	}

	return this->words[id];
}

void word_splitter::debug()
{
	int i = 0;
	word_vec::iterator ib = words.begin();
	
	std::cout << "raw data [" << raw << "]" << std::endl;
	std::cout << "seperator [" << sep << "]" << std::endl;
	std::cout << "word num = " << words.size() << std::endl;
	while (ib != words.end()) {
		std::cout << "word[" << i << "] [" << *ib << "]" << std::endl;
		i++;
		ib++;
	}
}
