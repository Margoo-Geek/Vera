#include "VObject.h"

class VString {
_private
	size_t size_;
	char* buffer_;
_public
	VString();
	VString(const VString& string);
	VString(const VString& string, size_t pos, size_t len = npos);
	VString(const char* string);
	VString(const char* string, size_t size);
	VString(size_t n, char c);
	~VString();

	const char* c_str() const;
	size_t length() const;
	size_t size() const;

	char& operator[] (size_t pos);
	const char& operator[] (size_t pos) const;
	VString& operator= (const VString& string);
	VString& operator= (const char* s);
	VString& operator= (char c);
	VString& operator+= (const VString& str);
	VString& operator+= (const char* s);
	VString& operator+= (char c);
	friend std::ostream& operator<< (std::ostream& o, const VString& s);
	friend std::istream& operator>> (std::istream& i, VString& s);

	VString& append(const VString& str);
	VString& append(const char* s);
	VString& prepend(VString& str);
	VString& prepend(const char* s);

	VString& assign(const VString& str);
	VString& assign(const char* s);

	char& at(size_t pos);
	const char& at(size_t pos) const;

	void clear();

	void pop();

	int compare(const VString& str) const;
	int compare(const char* s) const;

	const char* data() const;
	bool empty() const;

	void fromNum(size_t n);
	void fromStdString(std::string string);
	void fromStdWstring(std::wstring string);
	void fromDouble(double n);
	void fromFloat(float n);

	char* begin();
	char* end();

	size_t find(const char* s);
	size_t find(const char* s, size_t pos);

	const char* slice(size_t s, size_t n);
	void slice(const char* s);

	size_t statistics(char s);
	size_t statistics(size_t sta, char s);

	void chop(size_t n);

	void replace(const char* s, const char* c);

	void insert(size_t x, const char* s);

	void trimmed();

	VString substr(size_t length, size_t pos = 0);

	bool startsWith(const char* s);
	bool startsWith(size_t t, const char* s);
	bool endsWith(const char* s);

	void upper();
	void lower();

	size_t toNum();
	float toFloat();
	double toDouble();
	std::wstring toStdWstring();
	std::string toUtf8();
	std::string toStdString();

	void swap(VString l, VString r);

	static const size_t npos = -1;
};

std::string varx_to_string(int value) {
	std::ostringstream os;
	os << value;
	return os.str();
}
std::string varx_to_string(float value) {
	std::ostringstream os;
	os << value;
	return os.str();
}
std::string varx_to_string(double value) {
	std::ostringstream os;
	os << value;
	return os.str();
}
std::string varx_to_string(long long value) {
	std::ostringstream os;
	os << value;
	return os.str();
}
std::string varx_to_string(size_t value) {
	std::ostringstream os;
	os << value;
	return os.str();
}
void varx_replace_use(char* source_str, char* targ_str, char* val)
{
	char temp_sstr[513], result[513];
	char* p, * q;
	size_t len; len = 0; q = p = NULL;
	memset(result, 0, sizeof(result));
	memset(temp_sstr, 0, sizeof(temp_sstr));
	strcpy(temp_sstr, source_str);
	p = q = temp_sstr;
	len = strlen(targ_str);
	while (q != NULL) {
		if ((q = strstr(p, targ_str)) != NULL) {
			strncat_s(result, p, q - p);
			strcat_s(result, val);
			strcat_s(result, "\0");
			q += len;
			p = q;
		}
		else
			strcat(result, p);
	}
	strcpy(source_str, result);
}
char* varx_replace_return(const char* original, const char* substr, const char* replace) {
	char* tok = NULL;
	char* newstr = NULL;
	char* oldstr = NULL;
	char* head = NULL;

	if (original == NULL || substr == NULL || replace == NULL) return NULL;

	newstr = _strdup(original);
	head = newstr;
	while ((tok = strstr(head, substr))) {
		oldstr = newstr;
		newstr = (char*)malloc(strlen(oldstr) - strlen(substr) + strlen(replace) + 1);
		if (newstr == NULL) {
			free(oldstr);
			return NULL;
		}
		memcpy(newstr, oldstr, tok - oldstr);
		memcpy(newstr + (tok - oldstr), replace, strlen(replace));
		memcpy(newstr + (tok - oldstr) + strlen(replace), tok + strlen(substr), strlen(oldstr) - strlen(substr) - (tok - oldstr));
		memset(newstr + strlen(oldstr) - strlen(substr) + strlen(replace), 0, 1);
		head = newstr + (tok - oldstr) + strlen(replace);
		free(oldstr);
	}
	return newstr;
}
char* varx_insert(char* s1, char* s2, size_t n) {
	size_t len1 = 0, len2 = 0, tmp = 0, tmp_ = 0;
	char s4[30];
	char* s3 = s4;
	if (s1 == NULL) return NULL;
	if (s2 == NULL) return s1;
	len1 = strlen(s1);
	len2 = strlen(s2);
	if (n > len1) return NULL;
	for (size_t i = 0; i < n; i++) tmp++;
	for (size_t i = 0; i < len1; i++) s4[tmp_++] = s1[i];
	for (size_t i = 0; i < len2; i++) s1[tmp++] = s2[i];
	for (size_t i = n; i < len1; i++) s1[tmp++] = s4[i];
	s1[tmp] = '\0';
	return s1;
}
char* varx_trimmed(char* aims) {
	varx_replace_use(aims, (char*)(" "), (char*)(""));
	varx_replace_use(aims, (char*)("\r"), (char*)(""));
	varx_replace_use(aims, (char*)("\n"), (char*)(""));
	varx_replace_use(aims, (char*)("\t"), (char*)(""));
	return aims;
}
VString toVString(std::string string) {
	VString tmp;
	const char* temp = string.c_str();
	std::cout << temp;
	tmp = temp;
	std::cout << tmp;
	return tmp;
}
VString toVString(std::wstring string) {
	VString temp;
	size_t len = string.size() * 4;
	setlocale(LC_CTYPE, "");
	char* p = new char[len];
	wcstombs(p, string.c_str(), len);
	std::string tmp(p);
	delete[] p;
	temp = tmp.c_str();
	return temp;
}
VString toVString(float num) {
	VString tmp(varx_to_string(num).c_str());
	return tmp;
}
VString toVString(double num) {
	VString tmp(varx_to_string(num).c_str());
	return tmp;
}
VString toVString(long int num) {
	VString tmp(varx_to_string(num).c_str());
	return tmp;
}
VString toVString(long long num) {
	VString tmp(varx_to_string(num).c_str());
	return tmp;
}
VString toVString(int num) {
	VString tmp(varx_to_string(num).c_str());
	return tmp;
}
VString toVString(size_t num) {
	VString tmp(varx_to_string(num).c_str());
	return tmp;
}

inline
void VString::slice(const char* s) {
	replace(s, "");
	size_ -= strlen(s);
}
inline
VString VString::substr(size_t length, size_t pos) {
	VString tmp = *this;
	tmp.slice(pos, length);
	return tmp;
}
inline
void VString::swap(VString l, VString r) {
	VString tmp = l;
	l = r;
	r = tmp;
}
inline
size_t VString::statistics(size_t sta, char s) {
	assert(sta < 0 || sta <= size_);
	size_t tmp = 0;
	for (size_t i = sta; i < size_; i++)
		if (buffer_[i] == s) tmp++;
	return tmp;
}
inline
size_t VString::statistics(char s) {
	size_t tmp = 0;
	for (size_t i = 0; i < size_; i++)
		if (buffer_[i] == s) tmp++;
	return tmp;
}
inline
void VString::upper() {
	for (size_t i = 0; i < size_; i++)
		if (buffer_[i] >= 'a' && buffer_[i] <= 'z') buffer_[i] = toupper(buffer_[i]);
}
inline
void VString::lower() {
	for (size_t i = 0; i < size_; i++)
		if (buffer_[i] <= 'Z' && buffer_[i] >= 'A') buffer_[i] = (char)tolower(buffer_[i]);
}
inline
void VString::trimmed() {
	replace("\n", "");
	replace(" ", "");
	replace("\r", "");
	replace("\t", "");
}
inline
bool VString::startsWith(size_t t, const char* s) {
	const char* tmp = slice(t, strlen((char*)s));
	if (strcmp(s, tmp) == false) return true;
	else return false;
}
inline
bool VString::startsWith(const char* s) {
	const char* tmp = slice(0, strlen((char*)s));
	if (strcmp(s, tmp) == false) return true;
	else return false;
}
inline
bool VString::endsWith(const char* s) {
	return startsWith(strlen(buffer_) - strlen(s), s);
}
inline
void VString::insert(size_t x, const char* s) {
	char* tmp = buffer_;
	buffer_ = varx_insert(buffer_, (char*)s, x);
	if (buffer_ == NULL) {
		buffer_ = tmp;
		throw "insert error";
	}
}
inline
void VString::pop() {
	const char* tmp = slice(1, size_ - 1);
	buffer_ = (char*)tmp;
	size_ -= 1;
}
inline
char* VString::begin() {
	return buffer_;
}
inline
char* VString::end() {
	return buffer_ + size_;
}
inline
std::string VString::toUtf8() {
	std::wstring_convert<std::codecvt_utf8<wchar_t>> myconv;
	return myconv.to_bytes(toStdWstring());
}
inline
double VString::toDouble() {
	std::fstream tmp(buffer_);
	double retu;
	tmp >> retu;
	_flushall();
	return retu;
}
inline
float VString::toFloat() {
	std::fstream tmp(buffer_);
	float retu;
	tmp >> retu;
	_flushall();
	return retu;
}
inline
size_t VString::toNum() {
	std::fstream tmp(buffer_);
	size_t retu;
	tmp >> retu;
	_flushall();
	return retu;
}
inline
std::string VString::toStdString() {
	std::string tmp = buffer_;
	_flushall();
	return tmp;
}
inline
std::wstring VString::toStdWstring() {
	char* pszSrc = buffer_;
	int nLen = MultiByteToWideChar(CP_ACP, 0, pszSrc, -1, NULL, 0);
	if (nLen == 0)
		return std::wstring(L"");

	wchar_t* pwszDst = new wchar_t[nLen + 1];
	if (!pwszDst)
		return std::wstring(L"");

	MultiByteToWideChar(CP_ACP, 0, pszSrc, -1, pwszDst, nLen);
	std::wstring wstr = pwszDst;
	delete[] pwszDst;
	_flushall();

	return wstr;
}
inline
void VString::replace(const char* s, const char* c) {
	if (varx_replace_return(buffer_, s, c) != NULL) buffer_ = varx_replace_return(buffer_, s, c);
	else throw "replace error";
}
inline
void VString::chop(size_t n) {
	size_ -= n;
	const char* tmp = new char;
	tmp = slice(0, size_);
	strcpy(buffer_, tmp);
	_flushall();
}
inline
const char* VString::slice(size_t s, size_t n) {
	char* tmp = new char;
	strncpy_s(tmp, strlen(buffer_), buffer_ + s, n);
	return tmp;
}
inline
size_t VString::find(const char* s, size_t pos) {
	assert(s != nullptr);
	assert(pos >= 0);
	return strcspn(buffer_ + pos, s);
}
inline
size_t VString::find(const char* s) {
	assert(s != nullptr);
	return strcspn(buffer_, s);
}
inline
VString& VString::prepend(VString& str) {
	size_ += str.length();
	VString tmp(*this);
	tmp = str += tmp;
	*this = tmp;
	return *this;
}
inline
VString& VString::prepend(const char* s) {
	size_ += strlen(s);
	assert(s != nullptr);
	VString tmp(s);
	VString temp(*this);
	*this = tmp += temp;
	return *this;
}
inline
void VString::fromStdWstring(std::wstring string) {
	*this = toVString(string);
}
inline
void VString::fromFloat(float n) {
	*this = toVString(n);
}
inline
void VString::fromDouble(double n) {
	*this = toVString(n);
}
inline
void VString::fromNum(size_t n) {
	*this = toVString(n);
}
inline
void VString::fromStdString(std::string string) {
	*this = toVString(string);
}
inline
VString::VString() {
	size_ = 0;
	buffer_ = new char[1];
	buffer_[0] = '\0';
}
inline
VString::VString(const VString& str) {
	size_ = str.size();
	buffer_ = new char[size_ + 1];
	strcpy(static_cast<char*>(buffer_),
		static_cast<char const*>(str.buffer_));
}
inline
VString::VString(const VString& str, size_t pos, size_t len) {
	if (pos > static_cast<size_t>(str.size_)) {
		size_ = 0;
		buffer_ = new char[1];
		buffer_[0] = '\0';
	}
	else {
		if (pos + len > str.size_) size_ = str.size_ - pos;
		else size_ = len;
		buffer_ = new char[size_ + 1];
		const char* point = str.c_str() + pos;
		for (size_t i = 0; i < size_; i++) buffer_[i] = point[i];
		buffer_[size_] = '\0';
	}
}
inline
VString::VString(const char* s) {
	size_ = strlen(s);
	buffer_ = new char[size_ + 1];
	strcpy(buffer_, s);
}
inline
VString::VString(const char* s, size_t n) {
	if (strlen(s) <= n) {
		size_ = strlen(s);
		buffer_ = new char[size_ + 1];
		strcpy(buffer_, s);
	}
	else {
		size_ = n;
		buffer_ = new char[size_ + 1];
		strncpy_s(buffer_, strlen(s), s, n);
	}
}
inline
VString::VString(size_t n, char c) {
	size_ = n;
	buffer_ = new char[size_ + 1];
	memset(buffer_, c, n);
}
inline
VString::~VString() {

}
inline
const char* VString::c_str() const {
	return buffer_;
}
inline
size_t VString::length() const {
	return size_;
}
inline
size_t VString::size() const {
	return sizeof(buffer_);
}
inline
char& VString::operator[] (size_t pos) {
	return buffer_[pos];
}
inline
const char& VString::operator[] (size_t pos) const {
	if (pos >= size_) {
		static char retu = '\0';
		return retu;
	}
	else {
		char* temp = buffer_;
		return temp[pos];
	}
}
inline
VString& VString::operator=(const VString& str) {
	size_ = str.size();
	buffer_ = new char[this->size_ + 1];
	strcpy(buffer_, str.c_str());
	return *this;
}
inline
VString& VString::operator= (const char* str) {
	if (size_ != 0) delete[] buffer_;
	size_ = strlen(str);
	buffer_ = new char[size_ + 1];
	strcpy(buffer_, str);
	return *this;
}
inline
VString& VString::operator=(char c) {
	if (size_ != 1) delete[] buffer_;
	size_ = 1;
	buffer_ = new char[size_ + 1];
	buffer_[0] = c;
	buffer_[size_] = '\0';
	return *this;
}
inline
VString& VString::operator+=(const char* s) {
	size_ += strlen(s);
	char* data = new char[strlen(s)];
	data = (char*)s;
	strcat(buffer_, data);
	return *this;
}
inline
VString& VString::operator+= (char c) {
	size_ += 1;
	char* data = new char[size_ + 1];
	strcpy(data, buffer_);
	strcat_s(data, size_, &c);

	delete[] buffer_;
	buffer_ = data;
	return *this;
}
inline
VString& VString::append(const VString& str) {
	//Yes ... just so casual
	if (str.size() <= INT_MAX)
		*this += str;
	else
		throw str;
	return *this;
}
inline
VString& VString::append(const char* s) {
	//Yes ... just so casual
	if (strlen(s) <= INT_MAX)
		*this += (s);
	else
		throw s;
	return *this;
}
inline
VString& VString::assign(const VString& str) {
	*this = str;
	return *this;
}
inline
VString& VString::assign(const char* s) {
	*this = s;
	return *this;
}
inline
char& VString::at(size_t pos) {
	return buffer_[pos];
}
inline
const char& VString::at(size_t pos) const {
	return buffer_[pos];
}
inline
void VString::clear() {
	delete[] buffer_;
	size_ = 0;
	buffer_ = new char[1];
	buffer_[0] = '\0';
}
inline
int VString::compare(const VString& str) const {
	return strcmp(buffer_, str.buffer_);
}
inline
int VString::compare(const char* s) const {
	return strcmp(buffer_, s);
}
inline
const char* VString::data() const {
	return buffer_;
}
inline
bool VString::empty() const {
	return (size_ == 0);
}
static inline
VString operator+ (const VString& l, const char* r) {
	VString str(l);
	str += r;
	return str;
}
static inline
VString operator+ (const char* l, const VString& r) {
	VString str(l);
	str += r;
	return str;
}
static inline
VString operator+ (const VString& l, char r) {
	VString str(l);
	str += r;
	return str;
}
static inline
VString operator+ (char l, const VString& r) {
	VString str(&l);
	str += r;
	return str;
}
static inline
bool operator== (const VString& l, const VString& r) {
	return (l.compare(r) == 0);
}
static inline
bool operator== (const char* l, const VString& r) {
	return (r.compare(l) == 0);
}
static inline
bool operator!= (const VString& l, const VString& r) {
	return (l.compare(r) != 0);
}
static inline
bool operator!= (const char* l, const VString& r) {
	return (r.compare(l) != 0);
}
static inline
bool operator< (const VString& l, const VString r) {
	return static_cast<bool>((l.compare(r)!=0));
}
static inline
bool operator< (const char* l, const VString r) {
	return (r.compare(l) >= 0);
}
static inline
bool operator<= (const VString& l, const VString& r) {
	return (l.compare(r) <= 0);
}
static inline
bool operator<= (const VString& l, const char* r) {
	return (l.compare(r) <= 0);
}
static inline
bool operator<= (const char* l, const VString& r) {
	return(r.compare(l) > 0);
}
static inline
bool operator> (const VString& l, const VString& r) {
	return (l.compare(r) > 0);
}
static inline
bool operator> (const char* l, const VString& r) {
	return (r.compare(l) <= 0);
}
static inline
bool operator>= (const VString& l, const char* r) {
	return (l.compare(r) >= 0);
}
static inline
bool operator>= (const char* l, const VString& r) {
	return (r.compare(l) < 0);
}
inline
VString& VString::operator+=(const VString& str) {
	size_ += str.size_;
	char* data = new char[size_ + 1];
	strcpy(data, buffer_);
	strcat(data, str.buffer_);

	delete[] buffer_;
	buffer_ = data;
	return *this;
}
std::ostream& operator<< (std::ostream& o, const VString& s) {
	o << s.buffer_;
	return o;
}
std::istream& operator>> (std::istream& o, VString& s) {
	char* tmp = new char;
	o >> tmp;
	s.buffer_ = tmp;
	return o;
}
using VStringList = std::vector<VString>;