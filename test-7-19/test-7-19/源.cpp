#if 0
// ģ��һ�ݼ���SharedPtr,�˽�ԭ��
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
#include <set> 
using namespace std;

#if 0
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


void TestSet() 
{    // ������array�е�Ԫ�ع���set    
	int array[] = { 1, 3, 5, 7, 9, 2, 4, 6, 8, 0, 1, 3, 5, 7, 9, 2, 4, 6, 8, 0 };    
	set<int> s(array, array+sizeof(array)/sizeof(array));    
	cout << s.size() << endl;

// �����ӡset�е�Ԫ�أ��Ӵ�ӡ����п��Կ�����set��ȥ��    
	for (auto& e : s)        
		cout << e << " ";    
	cout << endl;

// ʹ�õ����������ӡset�е�Ԫ�� 


    for (auto it = s.rbegin(); it != s.rend(); ++it)       
		cout << *it << " ";    cout << endl;

  
	cout << s.count(3) << endl; 
}

int main() {
	TestMap();
	 TestSet();
	system("pause");
	return 0;
}

#endif
template<class T> 
struct AVLTreeNode {
	AVLTreeNode(const T& data) :
		_pLeft(nullptr), _pRight(nullptr), _pParent(nullptr), _data(data), _bf(0)
	{}

	AVLTreeNode<T>* _pLeft;   // �ýڵ������     
	AVLTreeNode<T>* _pRight;  // �ýڵ���Һ���     
	AVLTreeNode<T>* _pParent; // �ýڵ��˫��     
	T _data;
	int _bf;                  // �ýڵ��ƽ������ 


	bool Insert(const T& data)
	{    // 1. �Ȱ��ն����������Ĺ��򽫽ڵ���뵽AVL����    
	       
		 // 2. �½ڵ�����AVL����ƽ���Կ��ܻ��⵽�ƻ�����ʱ����Ҫ����ƽ�����ӣ�������Ƿ��ƻ���AVL��    
		//    ��ƽ����        
		/*     pCur�����pParent��ƽ������һ����Ҫ�������ڲ���֮ǰ��
		pParent     ��ƽ�����ӷ�Ϊ���������-1��0, 1, ���������������
		1. ���pCur���뵽pParent����ֻ࣬���pParent��ƽ������-1����
		2. ���pCur���뵽pParent���Ҳֻ࣬���pParent��ƽ������ + 1����
		��ʱ��pParent��ƽ�����ӿ��������������0������1�� ����2
		1. ���pParent��ƽ������Ϊ0��˵������֮ǰpParent��ƽ������Ϊ����1������󱻵�����0��
		��ʱ�� ��AVL�������ʣ�����ɹ�
		2. ���pParent��ƽ������Ϊ����1��˵������ǰpParent��ƽ������һ��Ϊ0������󱻸��³�����1��
		��ʱ��pParentΪ�������ĸ߶����ӣ���Ҫ�������ϸ���
		3. ���pParent��ƽ������Ϊ����2����pParent��ƽ������Υ��ƽ���������ʣ���Ҫ���������ת����    */

		while (pParent) {
			// ����˫�׵�ƽ������        
			if (pCur == pParent->_pLeft)
				pParent->_bf--;
			else
				pParent->_bf++;

			// ���º���˫�׵�ƽ������        
			if (0 == pParent->_bf)
				break;
			else if (1 == pParent->_bf || -1 == pParent->_bf)
			{              // ����ǰ˫�׵�ƽ��������0�������˫�׵�ƽ����ΪΪ1 ���� -1 ��˵����˫��Ϊ���Ķ��� ��              
						   // �ĸ߶�������һ�㣬�����Ҫ�������ϵ���             
				pCur = pParent;
				pParent = pCur->_pParent;
			}
			else
			{             // ˫�׵�ƽ������Ϊ����2��Υ����AVL����ƽ���ԣ���Ҫ����pParent             
						  // Ϊ������������ת����              
				if (2 == pParent->_bf)
				{                  // ...              
				}
				else
				{                  // ...              
				}
			}
		}

		return true;
	}
};

// ע�⣺����ʵ�ֵĹ�ϣ����Ԫ��Ψһ����key��ͬ��Ԫ�ز��ٽ��в��� 
// Ϊ��ʵ�ּ򵥣��˹�ϣ�������ǽ��Ƚ�ֱ����Ԫ�ذ���һ�� 
template<class K, class V> 
class HashTable
{    struct Elem    {           
pair<K, V> _val;        
State _state;    
}; 
public:    
	HashTable(size_t capacity = 3)        
		: _ht(capacity), _size(0)    
	{        
		for(size_t i = 0; i < capacity; ++i)            
			_ht[i]._state = EMPTY;    
	}   
	bool Insert(const pair<K, V>& val)   
	{       // ����ϣ��ײ�ռ��Ƿ����       
			// _CheckCapacity();       
		size_t hashAddr = HashFunc(key);       
		// size_t startAddr = hashAddr;      
		while(_ht[hashAddr]._state != EMPTY)       
		{           
			if(_ht[hashAddr]._state == EXIST && _ht[hashAddr]._val.first == key)
          return false; 
           hashAddr++;           
		   if (hashAddr == _ht.capacity())               
			   hashAddr = 0;           
		   /*     תһȦҲû���ҵ���ע�⣺��̬��ϣ������������Բ��ÿ��ǣ���ϣ����Ԫ�ظ������� һ������������ϣ��ͻ���ʻ�������Ҫ���������͹�ϣ��ͻ����˹�ϣ����Ԫ���ǲ��������           if(hashAddr == startAddr)               return false;           */       
		}              
		// ����Ԫ��       
	_ht[hashAddr]._state = EXIST;       
	_ht[hashAddr]._val = val;       
	_size++;       
	return true;   
	}   
int Find(const K& key)   
{       size_t hashAddr = HashFunc(key);       
while(_ht[hashAddr]._state != EMPTY)       
{           
if(_ht[hashAddr]._state == EXIST && _ht[hashAddr]._val.first == key)               
return hashAddr;                      
hashAddr++;       }       
return hashAddr;   
}   
bool Erase(const K& key)   
{       int index = Find(key);       
if(-1 != index)       
{           _ht[index]._state = DELETE;           
_size++;           
return true;       
}       return false;   
}   size_t Size()const;   
bool Empty() const;       
void Swap(HashTable<K, V, HF>& ht); 
private:    
size_t HashFunc(const K& key)    
{        return key % _ht.capacity();    
} private:    
	vector<Elem> _ht;    
	size_t _size;
};
