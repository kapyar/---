#ifndef _ARRAY_H_
#define _ARRAY_H_
#include"Pair.h"

#include<iostream>
using namespace std;

#define NDEBUG

template<class KeyType,class ValueType>
class Array
{
	template <class K,class V>
	friend class Map;
private :
	Pair<KeyType,ValueType>* _allocator;
	size_t _size;
	const static size_t _default_size = 4;

	bool operator==(const Array&)const;
	Array(const Array &);
	Array &operator=(const Array &);

public:
	class BadIndex;
	explicit Array();
	Array(const size_t size);
	Array(KeyType k ,ValueType v);
	~Array();
	Pair<KeyType,ValueType>& operator[](size_t index);
	const Pair<KeyType,ValueType>& operator[](size_t index)const;
	size_t size()const;
};
//constructor
template <class KeyType,class ValueType>
	Array<KeyType,ValueType>::Array()
		:_allocator(new Pair<KeyType,ValueType>[_default_size]),_size(_default_size)
{
#ifndef NDEBUG
	cout<<"Array constructor"<<endl;
#endif
}

//constructor whith size parametr
template <class KeyType,class ValueType>
	Array<KeyType,ValueType>::Array(const size_t size)
		:_allocator(new Pair<KeyType,ValueType>[size]),_size(size)
{
#ifndef NDEBUG
	cout<<"Array constructor with size parametr"<<endl;
#endif
}


//деструктор
template <class KeyType,class ValueType>
	Array<KeyType,ValueType>::~Array()
{
	delete [] _allocator;
	_allocator = 0;
}


//розмір масиву
template <class KeyType,class ValueType>
	size_t Array<KeyType,ValueType>::size() const
{
	return _size;
}

	// Модифікатор елемента масиву
template <class KeyType,class ValueType>
Pair<KeyType,ValueType>& Array<KeyType,ValueType>::operator[](size_t index)
{
	if(index<0 || index>=_size) 
		throw BadIndex("out of border", index);
	else
		return _allocator[index];
};

// Селектор елемента масиву
template <class KeyType,class ValueType>
const Pair<KeyType,ValueType>& Array<KeyType,ValueType>::operator[](size_t index)const
{
	if(index<0 || index>=_size) 
		throw BadIndex("out of border", index);
	else
		return _allocator[index];
};

template <class KeyType,class ValueType>
ostream& operator<<(ostream & os, const Array<KeyType,ValueType>& a)
{
	os<<'[';
	for(size_t i = 0;i<a.size();++i)
	{
		os<<a[i];
		if(i!=a.size()-1)
			os<<", ";
	}
	os<<']';
	return os;
};








//BAD INDEX
template <class KeyType,class ValueType>
class Array<KeyType,ValueType>::BadIndex
{
	private:
// Причина аварійної ситуації
    string _reason;
// Місце її виявлення
    size_t _index;
public:
// Конструктор обробника
	BadIndex
		(string reason="unknown", size_t index=0):
	_reason(reason), _index(index)
	{
#ifndef NDEBUG
	cout<<"Constructor of BadIndex"<<endl;
#endif
	return;
	};

//селектори
	const string getReason()const{return _reason;}
	const size_t getIndex()const{return _index;}
// Деструктор обробника
	~BadIndex() {};

//вивід інформації
	void diagnose() const 
	{
		cerr<<"****"<<endl;
		cerr<<"Size of array: "<<getIndex()<<endl;
		cerr<<"Reason: ";
		for(size_t i = 0;i<_reason.length();++i)
			cerr<<getReason()[i];
		cerr<<endl;
		cerr<<"Index: "<<getIndex()<<endl;
		cerr<<"****"<<endl;
		return;
	}
};


#endif