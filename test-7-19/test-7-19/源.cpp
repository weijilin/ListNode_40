#if 0
// 模拟一份简答的SharedPtr,了解原理
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
			// 释放管理的旧资源
			Release();
			// 共享管理新对象的资源，并增加引用计数
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
		// 加锁或者使用加1的原子操作
		_pMutex->lock();
		++(*_pRefCount);
		_pMutex->unlock();
	}
private:
	void Release()
	{
		bool deleteflag = false;
		// 引用计数减1，如果减到0，则释放资源
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
	int* _pRefCount; // 引用计数
	T* _ptr; // 指向管理资源的指针
	mutex* _pMutex; // 互斥锁
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

// 向map中插入元素的方式：    
// 将键值对<"peach","桃子">插入map中，用pair直接来构造键值对    
	m.insert(pair<string, string>("peach", "桃子"));

// 将键值对<"peach","桃子">插入map中，用make_pair函数来构造键值对

   m.insert(make_pair("banan", "香蕉"));        // 借用operator[]向map中插入元素    
	/*    operator[]的原理是：      
	用<key, T()>构造一个键值对，然后调用insert()函数将该键值对插入到map中      
	如果key已经存在，插入失败，insert函数返回该key所在位置的迭代器      
	如果key不存在，插入成功，insert函数返回新插入元素所在位置的迭代器      
	operator[]函数后将insert返回值键值对中的value返回    */    
	// 将<"apple", "">插入map中，插入成功，返回value的引用，将“苹果”赋值给该引用结果，    
   m["apple"] = "苹果";

// key不存在时抛异常    //m.at("waterme") = "水蜜桃";    
   cout << m.size() << endl;

// 用迭代器去遍历map中的元素，可以得到一个按照key排序的序列    
   for (auto& e : m)        
	   cout << e.first << "--->" << e.second << endl;    
   cout << endl;

// map中的键值对key一定是唯一的，如果key存在将插入失败    
   auto ret = m.insert(make_pair("peach", "桃色"));    
   if (ret.second)        
	   cout << "<peach, 桃色>不在map中, 已经插入" << endl;    
   else        
	   cout << "键值为peach的元素已经存在：" << ret.first->first << "--->" << ret.first->second <<" 插入失败"<< endl;

// 删除key为"apple"的元素    
   m.erase("apple");

   if (1 == m.count("apple"))        
	   cout << "apple还在" << endl;    
   else        
	   cout << "apple被吃了" << endl; 
}


void TestSet() 
{    // 用数组array中的元素构造set    
	int array[] = { 1, 3, 5, 7, 9, 2, 4, 6, 8, 0, 1, 3, 5, 7, 9, 2, 4, 6, 8, 0 };    
	set<int> s(array, array+sizeof(array)/sizeof(array));    
	cout << s.size() << endl;

// 正向打印set中的元素，从打印结果中可以看出：set可去重    
	for (auto& e : s)        
		cout << e << " ";    
	cout << endl;

// 使用迭代器逆向打印set中的元素 


    for (auto it = s.rbegin(); it != s.rend(); ++it)       
		cout << *it << " ";    cout << endl;

// set中值为3的元素出现了几次    
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

	AVLTreeNode<T>* _pLeft;   // 该节点的左孩子     
	AVLTreeNode<T>* _pRight;  // 该节点的右孩子     
	AVLTreeNode<T>* _pParent; // 该节点的双亲     
	T _data;
	int _bf;                  // 该节点的平衡因子 


	bool Insert(const T& data)
	{    // 1. 先按照二叉搜索树的规则将节点插入到AVL树中    
		 // ...        
		 // 2. 新节点插入后，AVL树的平衡性可能会遭到破坏，此时就需要更新平衡因子，并检测是否破坏了AVL树    
		//    的平衡性        
		/*     pCur插入后，pParent的平衡因子一定需要调整，在插入之前，
		pParent     的平衡因子分为三种情况：-1，0, 1, 分以下两种情况：
		1. 如果pCur插入到pParent的左侧，只需给pParent的平衡因子-1即可
		2. 如果pCur插入到pParent的右侧，只需给pParent的平衡因子 + 1即可
		此时：pParent的平衡因子可能有三种情况：0，正负1， 正负2
		1. 如果pParent的平衡因子为0，说明插入之前pParent的平衡因子为正负1，插入后被调整成0，
		此时满 足AVL树的性质，插入成功
		2. 如果pParent的平衡因子为正负1，说明插入前pParent的平衡因子一定为0，插入后被更新成正负1，
		此时以pParent为根的树的高度增加，需要继续向上更新
		3. 如果pParent的平衡因子为正负2，则pParent的平衡因子违反平衡树的性质，需要对其进行旋转处理    */

		while (pParent) {
			// 更新双亲的平衡因子        
			if (pCur == pParent->_pLeft)
				pParent->_bf--;
			else
				pParent->_bf++;

			// 更新后检测双亲的平衡因子        
			if (0 == pParent->_bf)
				break;
			else if (1 == pParent->_bf || -1 == pParent->_bf)
			{              // 插入前双亲的平衡因子是0，插入后双亲的平衡因为为1 或者 -1 ，说明以双亲为根的二叉 树              
						   // 的高度增加了一层，因此需要继续向上调整             
				pCur = pParent;
				pParent = pCur->_pParent;
			}
			else
			{             // 双亲的平衡因子为正负2，违反了AVL树的平衡性，需要对以pParent             
						  // 为根的树进行旋转处理              
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

// 注意：假如实现的哈希表中元素唯一，即key相同的元素不再进行插入 
// 为了实现简单，此哈希表中我们将比较直接与元素绑定在一起 
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
	{       // 检测哈希表底层空间是否充足       
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
		   /*     转一圈也没有找到，注意：动态哈希表，该种情况可以不用考虑，哈希表中元素个数到达 一定的数量，哈希冲突概率会增大，需要扩容来降低哈希冲突，因此哈希表中元素是不会存满的           if(hashAddr == startAddr)               return false;           */       
		}              
		// 插入元素       
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
