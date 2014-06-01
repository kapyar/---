#ifndef _HashMap_H_
#define _HashMap_H_

#include"Map.h"
#include<string>
#include<iostream>
using namespace std;


template <class KeyType, class ValueType>
class Map;

/*
template <class DEF,class KeyType,class ValType>
class HashMap;

template <class KeyType,class ValType>
class HashMap<string,KeyType,ValType>
*/
template <class ValType>
class HashMap
{
private:
	const static size_t _tableSize = 3559;//просте число
	typedef  Map<string,ValType> Item;
	Item *_allocator;
	size_t do_HashMap(const string& key)const ;
public:
	HashMap();
	
	const string& getKey()const;
	void put(const Pair<string,ValType>&);
	const ValType& get(const string& str)const;
	void clear();
	bool isEmpty()const;
	bool remove(const string&);
	bool isContainsKey(const string& key)const;
	bool isContainsVal(const ValType& val)const;

};
template <class V>
bool HashMap<V>::isContainsVal(const V& val)const
{
	for(int i = 0;i<_tableSize;++i)
	{
		if(_allocator[i].isContainsVal(val))
		{
			return true;
		}
	}
	return false;
}

template <class V>
bool HashMap<V>::isContainsKey(const string& key)const
{
	size_t index = do_HashMap(key);
	return _allocator[index].isContainsKey(key);
}

template <class V>
bool HashMap<V>::remove(const string& key)
{
	size_t index = do_HashMap(key);
	try
	{
		_allocator[index].remove(key);
		return true;
	}
		catch(const Map<string,V>::NotFoundElement)
	{
		return false;
	}
}

template <class V>
void HashMap<V>::clear()
{
	for(size_t i = 0;i<_tableSize;++i)
	{
		_allocator[i].clear();
	}
}

template <class V>
const V& HashMap<V>::get(const string& str)const
{
	//знайдемо індекс де знаходиться МАР
	size_t index = do_HashMap(str);
	return _allocator[index].get(str);
	
}

template <class V>
void HashMap<V>::put(const Pair<string,V>& pair)
{
	size_t index = do_HashMap(pair.getKey());
	_allocator[index].put(pair);
}

//конструктор
template <class V>
HashMap<V>::HashMap()
	:_allocator(new Item[_tableSize])
{
#ifndef NDEBUG
	cout<<"HashMap constructor"<<endl;
#endif
}

//хеш - функція
template <class V>
size_t HashMap<V>::do_HashMap(const string& key)const
{
	size_t index(0);
	for(size_t i = 0;i<key.length();++i)
	{
		index+=static_cast<int>(key[i]);
	}
	return index % _tableSize;
}



#endif