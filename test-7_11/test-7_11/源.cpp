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