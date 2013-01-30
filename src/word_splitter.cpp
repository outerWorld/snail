
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

int	word_splitter::split(const std_str & data, const std_str & sep, word_vec & wds)
{
	size_t b_pos = 0;
	size_t e_pos = 0;

	b_pos = 0;
	e_pos = data.find_first_of(sep, b_pos);
	while (e_pos != std_str::npos) {
		wds.push_back(data.substr(b_pos, e_pos-b_pos));
		b_pos = e_pos + 1;
		e_pos = data.find_first_of(sep, b_pos);
	}
	
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
