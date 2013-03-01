/*
 * Author: huang chunping
 * Date  : 2013-01-30
 * Desc  : inherit std::string
 */

#ifndef __SN_STRING_H
#define __SN_STRING_H

typedef std::string std_str;

//class sn_string : public std_str {
class sn_string{
public:
	sn_string();
	sn_string(char *str, int len);
	sn_string(const std_str &a);
	~sn_string();

	size_t find(const std_str &str, size_t pos=0) const;
	std_str substr(size_t pos, size_t len=std_str::npos) { return data.substr(pos, len); }
	size_t length() { return data.length(); }
	char* operator <<(const sn_string& ) {
		return this->data.c_str();
	}
private:
	std_str data;

};

#endif // __SN_STRING_H
