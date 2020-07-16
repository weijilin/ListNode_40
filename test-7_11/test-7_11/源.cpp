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
	str.push_back(' ');   // 在str后插入空格    
	str.append("hello");  // 在str后追加一个字符"hello"    
	str += 'b';           // 在str后追加一个字符'b'       
	str += "it";          // 在str后追加一个字符串"it"    
	cout<<str<<endl;    
	cout<<str.c_str()<<endl;   // 以C语言的方式打印字符串        
							   // 获取file的后缀    
	string file("string.cpp");    
	size_t pos = file.rfind('.');    
	string suffix(file.substr(pos, file.size()-pos));    
	cout << suffix << endl;        
	// npos是string里面的一个静态成员变量    
	// static const size_t npos = -1;        
	// 取出url中的域名    
	string url("http://www.cplusplus.com/reference/string/string/find/");    
	cout << url << endl;    
	size_t start = url.find("://");    
	if (start == string::npos)    {        
		cout << "invalid url" << endl;        
		return;    }    
	start += 3;    
	size_t finish = url.find('/', start);    
	string address = url.substr(start, finish - start); 

		cout << address << endl;        // 删除url的协议前缀    
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
	}        // 对比下和上面的赋值那个实现比较好？    
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
// 注意这里namespace大家下去就不要取名为bit了，否则出去容易翻车。^^ 
namespace bit { 
template<class T> 
class vector { 
public:    // Vector的迭代器是一个原生指针    
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

// 如果使用iterator做迭代器，会导致初始化的迭代器区间[first,last)只能是vector的迭代器    // 重新声明迭代器，迭代器区间[first,last]可以是任意容器的迭代器    
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

		// 这里直接使用memcpy是有问题的           
		// 以后我们会用更好的方法解决            
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

void resize(size_t n, const T& value = T()) {        // 1.如果n小于当前的size，则数据个数缩小到n        
	if (n <= size())        
	{            _finish = _start + n;            
	return;        }

	// 2.空间不够则增容        
	if (n > capacity())            
		reserve(n);

	// 3.将size扩大到n        
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

	// 空间不够先进行增容        
if (_finish == _endOfStorage)        
{            size_t size = size();            
size_t newCapacity = (0 == capacity())? 1 : capacity() * 2;            
reserve(newCapacity);

		// 如果发生了增容，需要重置pos
	pos = _start + size; 

}

iterator end = _finish - 1;        
while (end >= pos) { *(end + 1) = *end;            
--end; }

*pos = x;        
++_finish;        
return pos;    }

// 返回删除数据的下一个数据    // 方便解决:一边遍历一边删除的迭代器失效问题    
iterator erase(Iterator pos)    
{        // 挪动数据进行删除        
	iterator begin = pos + 1;        
	while (begin != _finish) {            
		*(begin - 1) = *begin;            
		++begin;        }

--_finish;

		return pos;    
} private:    
	iterator _start;        // 指向数据块的开始    
	iterator _finish;       // 指向有效数据的尾    
	iterator _endOfStorage; // 指向存储容量的尾 
}
	; }
#endif

#include <vector>

void PrintVector(const vector<int>& v) 
{    // const对象使用const迭代器进行遍历打印    
	vector<int>::const_iterator it = v.begin();    
	while (it != v.end())    
	{        
		cout << *it << " ";        
		++it;    }    
	    cout << endl; }

int main() {    // 使用push_back插入4个数据    
	vector<int> v;    
	v.push_back(1);    
	v.push_back(2);    
	v.push_back(3);    
	v.push_back(4);

	// 使用迭代器进行遍历打印    
	vector<int>::iterator it = v.begin();    
	while (it != v.end())    
	{        
		cout << *it << " ";        
		++it;
		}

    cout << endl;

	// 使用迭代器进行修改    
	it = v.begin();    
	while (it != v.end())    
	{        *it *= 2;       
	      ++it;    }

    // 使用反向迭代器进行遍历再打印    
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


