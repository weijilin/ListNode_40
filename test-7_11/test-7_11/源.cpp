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

