#include<iostream>
#include<stdlib.h>
#include<cstring>
#include<string>
using namespace std;
# if 0
class date {
public:
	date(int year, int mouth, int day) {
		_year = year;
		_mouth = mouth;
		_day = day;
		cout << "date()" << endl;
	}
private:
	int _year;
	int _mouth;
	int _day;
};
int main() {
	date d(2020, 7, 11);
	system("pause");
	return 0;
}
#endif

#if 0



class String {
public:    
	String(const char* str = "jack") 
	{ _str = (char*)malloc(strlen(str) + 1);        
	strcpy(_str, str); }

    ~String() { 
    cout << "~String()" << endl;        
     free(_str); } 
private:    
		 char* _str;
};

class Person { 
private:    
	String _name;    
	int    _age; 
};

int main() {
	Person p;
	system("pause");
	return 0;
}
#endif // 0

#if 0
class A
{ public:    
A() { ++_scount; }    
A(const A& t) { ++_scount; }    
static int GetACount() { return _scount; } 
private:    
	static int _scount; };

int A::_scount = 0;

void TestA() {
	cout << A::GetACount() << endl;
	A a1, a2;
	A a3(a1);
	cout << A::GetACount() << endl;
	system("pause");
}

#endif


#if 0



void TestString() {
	string str;    
	str.push_back(' ');   // ��str�����ո�    
	str.append("hello");  // ��str��׷��һ���ַ�"hello"    
	str += 'b';           // ��str��׷��һ���ַ�'b'       
	str += "it";          // ��str��׷��һ���ַ���"it"    
	cout<<str<<endl;    
	cout<<str.c_str()<<endl;   // ��C���Եķ�ʽ��ӡ�ַ���        
							   // ��ȡfile�ĺ�׺    
	string file("string.cpp");    
	size_t pos = file.rfind('.');    
	string suffix(file.substr(pos, file.size()-pos));    
	cout << suffix << endl;        
	// npos��string�����һ����̬��Ա����    
	// static const size_t npos = -1;        
	// ȡ��url�е�����    
	string url("http://www.cplusplus.com/reference/string/string/find/");    
	cout << url << endl;    
	size_t start = url.find("://");    
	if (start == string::npos)    {        
		cout << "invalid url" << endl;        
		return;    }    
	start += 3;    
	size_t finish = url.find('/', start);    
	string address = url.substr(start, finish - start); 

		cout << address << endl;        // ɾ��url��Э��ǰ׺    
		pos = url.find("://");    
		url.erase(0, pos+3);    
		cout<<url<<endl; 
}
int main() {
	TestString();
	system("pause");
	return 0;
}
#endif

#if 0
class String {
public:    
	String(const char* str = "") 
	{ if (nullptr == str)            
		str = "";                
	_str = new char[strlen(str) + 1];        
	strcpy(_str, str); }        
	String(const String& s) : 
		_str(nullptr) 
	{ String strTmp(s._str);        
	swap(_str, strTmp); 
	}        // �Ա��º�����ĸ�ֵ�Ǹ�ʵ�ֱȽϺã�    
	String& operator=(String s)    
	{        swap(_str, s._str);           
	return *this;    }        
	/*    String& operator=(const String& s)    
	{        if(this != &s)
{


		String strTmp(s);          
		swap(_str, strTmp._str);        }                return *this;
}    */ 
~String() { if (_str) { delete[] _str;            
_str = nullptr; } }    
private:    char* _str; };

int main() {
	string();
	system("pause");
	return 0;
}

#endif


 #include <assert.h>
#if 0
// ע������namespace�����ȥ�Ͳ�Ҫȡ��Ϊbit�ˣ������ȥ���׷�����^^ 
namespace bit { 
template<class T> 
class vector { 
public:    // Vector�ĵ�������һ��ԭ��ָ��    
	typedef T* iterator;    
	typedef const T* 
		const_iterator;

iterator begin() 
{ return _start; }    
iterator end() 
{ return _finish; }

const_iterator cbegin() const { return _start; }    
const_iterator cend() const { return _finish; }

// construct and destroy    
vector()        
	: _start(nullptr)        
	, _finish(nullptr)        
	, _endOfStorage(nullptr)    {}

vector(int n, const T& value = T()) 
	: _start(nullptr)
	, _finish(nullptr)
	, _endOfStorage(nullptr) 
{ reserve(n);        
while (n--) { push_back(value); } }

// ���ʹ��iterator�����������ᵼ�³�ʼ���ĵ���������[first,last)ֻ����vector�ĵ�����    // ��������������������������[first,last]���������������ĵ�����    
template<class InputIterator>    
vector(InputIterator first, InputIterator last)    
{        reserve(last - first);        
while (first != last)        
{            
	push_back(*first);            
	++first;        }    }

vector(const vector<T>& v) 
	: _start(nullptr)
	, _finish(nullptr)
	, _endOfStorage(nullptr) 
{
	reserve(v.capacity());        
	iterator it = begin();        
	const_iterator vit = v.cbegin();        
	while (vit != v.cend()) { *it++ = *vit++; }

	_finish = _start + v.size();        
	_endOfStorage = _start + v.capacity();
}

vector<T>& operator= (vector<T> v) 
{ swap(v);        
return *this; }

~vector() 
{ delete[] _start;        
_start = _finish = _endOfStorage = nullptr; 
}                // capacity         
size_t size() const { return _finish - _start; }    
size_t capacity() const { return _endOfStorage - _start; }

void reserve(size_t n) {
	if (n > capacity()) {
		size_t oldSize = size();           
		T* tmp = new T[n];

		// ����ֱ��ʹ��memcpy���������           
		// �Ժ����ǻ��ø��õķ������            
		//if (_start)            
		//  memcpy(tmp, _start, sizeof(T)*size);            
		if (_start)            
		{                
			for (size_t i = 0; i < oldSize; ++i)                    
				tmp[i] = _start[i];            }

		_start = tmp;            
		_finish = _start + size;           
		_endOfStorage = _start + n;
	}
	
}

void resize(size_t n, const T& value = T()) {        // 1.���nС�ڵ�ǰ��size�������ݸ�����С��n        
	if (n <= size())        
	{            _finish = _start + n;            
	return;        }

	// 2.�ռ䲻��������        
	if (n > capacity())            
		reserve(n);

	// 3.��size����n        
	iterator it = _finish;        
	iterator _finish = _start + n;        
	while (it != _finish)        {            
		*it = value;            ++it;        
	}    }

	///////////////access///////////////////////////////        
T& operator[](size_t pos){return _start[pos];}        
const T& operator[](size_t pos)const {return _start[pos];}                ///////////////modify/////////////////////////////    
void push_back(const T& x){insert(end(), x);}    
void pop_back(){erase(--end());}                 
void swap(vector<T>& v)    {        
	swap(_start, v._start);        
swap(_finish, v._finish);        
swap(_endOfStorage, v._endOfStorage);    }            
iterator insert(iterator pos, const T& x)    {        
	assert(pos <= _finish);

	// �ռ䲻���Ƚ�������        
if (_finish == _endOfStorage)        
{            size_t size = size();            
size_t newCapacity = (0 == capacity())? 1 : capacity() * 2;            
reserve(newCapacity);

		// ������������ݣ���Ҫ����pos
	pos = _start + size; 

}

iterator end = _finish - 1;        
while (end >= pos) { *(end + 1) = *end;            
--end; }

*pos = x;        
++_finish;        
return pos;    }

// ����ɾ�����ݵ���һ������    // ������:һ�߱���һ��ɾ���ĵ�����ʧЧ����    
iterator erase(Iterator pos)    
{        // Ų�����ݽ���ɾ��        
	iterator begin = pos + 1;        
	while (begin != _finish) {            
		*(begin - 1) = *begin;            
		++begin;        }

--_finish;

		return pos;    
} private:    
	iterator _start;        // ָ�����ݿ�Ŀ�ʼ    
	iterator _finish;       // ָ����Ч���ݵ�β    
	iterator _endOfStorage; // ָ��洢������β 
}
	; }
#endif

#include <vector>

void PrintVector(const vector<int>& v) 
{    // const����ʹ��const���������б�����ӡ    
	vector<int>::const_iterator it = v.begin();    
	while (it != v.end())    
	{        
		cout << *it << " ";        
		++it;    }    
	    cout << endl; }

int main() {    // ʹ��push_back����4������    
	vector<int> v;    
	v.push_back(1);    
	v.push_back(2);    
	v.push_back(3);    
	v.push_back(4);

	// ʹ�õ��������б�����ӡ    
	vector<int>::iterator it = v.begin();    
	while (it != v.end())    
	{        
		cout << *it << " ";        
		++it;
		}

    cout << endl;

	// ʹ�õ����������޸�    
	it = v.begin();    
	while (it != v.end())    
	{        *it *= 2;       
	      ++it;    }

    // ʹ�÷�����������б����ٴ�ӡ    
	vector<int>::reverse_iterator rit = v.rbegin();    
	while (rit != v.rend())    
	{        
		cout << *rit << " ";        
		++rit;    }    
	cout << endl;

		PrintVector(v);
		system("pause");
		return 0;
	}


