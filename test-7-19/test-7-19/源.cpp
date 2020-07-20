#if 0
// ģ��ʵ��һ�ݼ���SharedPtr,�˽�ԭ��
#include <thread>
#include <mutex>
#include<iostream>
using namespace std;
template <class T>
class SharedPtr
{
public:
	SharedPtr(T* ptr = nullptr)
		: _ptr(ptr)
		, _pRefCount(new int(1))
		, _pMutex(new mutex)
	{}
	~SharedPtr() { Release(); }
	SharedPtr(const SharedPtr<T>& sp)
		: _ptr(sp._ptr)
		, _pRefCount(sp._pRefCount)
		, _pMutex(sp._pMutex)
	{
		AddRefCount();
	}
	// sp1 = sp2
	SharedPtr<T>& operator=(const SharedPtr<T>& sp)
	{
		//if (this != &sp)
		if (_ptr != sp._ptr)
		{
			// �ͷŹ���ľ���Դ
			Release();
			// ��������¶������Դ�����������ü���
			_ptr = sp._ptr;
			_pRefCount = sp._pRefCount;
			_pMutex = sp._pMutex;
			AddRefCount();
		}
		return *this;
	}
	T& operator*() { return *_ptr; }
	T* operator->() { return _ptr; }
	int UseCount() { return *_pRefCount; }
	T* Get() { return _ptr; }
	void AddRefCount()
	{
		// ��������ʹ�ü�1��ԭ�Ӳ���
		_pMutex->lock();
		++(*_pRefCount);
		_pMutex->unlock();
	}
private:
	void Release()
	{
		bool deleteflag = false;
		// ���ü�����1���������0�����ͷ���Դ
		_pMutex->lock();
		if (--(*_pRefCount) == 0)
		{
			delete _ptr;
			delete _pRefCount;
			deleteflag = true;
		}
		_pMutex->unlock();
		if (deleteflag == true)
			delete _pMutex;
	}
private:
	int* _pRefCount; // ���ü���
	T* _ptr; // ָ�������Դ��ָ��
	mutex* _pMutex; // ������
};
int main()
{
	SharedPtr<int> sp1(new int(10));
	SharedPtr<int> sp2(sp1);
	*sp2 = 20;
	cout << sp1.UseCount() << endl;
	cout << sp2.UseCount() << endl;
	SharedPtr<int> sp3(new int(10));
	sp2 = sp3;
	cout << sp1.UseCount() << endl;
	cout << sp2.UseCount() << endl;
	cout << sp3.UseCount() << endl;
	sp1 = sp3;
	cout << sp1.UseCount() << endl;
	cout << sp2.UseCount() << endl;
	cout << sp3.UseCount() << endl;
	system("pause");
	return 0;
}

#endif
#include<iostream>
#include <string> 
#include <map> 
void TestMap() {    
	map<string, string> m;

// ��map�в���Ԫ�صķ�ʽ��    
// ����ֵ��<"peach","����">����map�У���pairֱ���������ֵ��    
	m.insert(pair<string, string>("peach", "����"));

// ����ֵ��<"peach","����">����map�У���make_pair�����������ֵ��

   m.insert(make_pair("banan", "�㽶"));        // ����operator[]��map�в���Ԫ��    
	/*    operator[]��ԭ���ǣ�      
	��<key, T()>����һ����ֵ�ԣ�Ȼ�����insert()�������ü�ֵ�Բ��뵽map��      
	���key�Ѿ����ڣ�����ʧ�ܣ�insert�������ظ�key����λ�õĵ�����      
	���key�����ڣ�����ɹ���insert���������²���Ԫ������λ�õĵ�����      
	operator[]������insert����ֵ��ֵ���е�value����    */    
	// ��<"apple", "">����map�У�����ɹ�������value�����ã�����ƻ������ֵ�������ý����    
   m["apple"] = "ƻ��";

// key������ʱ���쳣    //m.at("waterme") = "ˮ����";    
   cout << m.size() << endl;

// �õ�����ȥ����map�е�Ԫ�أ����Եõ�һ������key���������    
   for (auto& e : m)        
	   cout << e.first << "--->" << e.second << endl;    
   cout << endl;

// map�еļ�ֵ��keyһ����Ψһ�ģ����key���ڽ�����ʧ��    
   auto ret = m.insert(make_pair("peach", "��ɫ"));    
   if (ret.second)        
	   cout << "<peach, ��ɫ>����map��, �Ѿ�����" << endl;    
   else        
	   cout << "��ֵΪpeach��Ԫ���Ѿ����ڣ�" << ret.first->first << "--->" << ret.first->second <<" ����ʧ��"<< endl;

// ɾ��keyΪ"apple"��Ԫ��    
   m.erase("apple");

   if (1 == m.count("apple"))        
	   cout << "apple����" << endl;    
   else        
	   cout << "apple������" << endl; 
}

int main() {
	void TestMap();
	system("pause");
	return 0;
}