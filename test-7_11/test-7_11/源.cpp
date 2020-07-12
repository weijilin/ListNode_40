#include<iostream>
#include<stdlib.h>
#include<cstring>
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