#ifndef _MAP_H_
#define _MAP_H_

#include "Array.h"

#define NDEBUG

template<class KeyType,class ValueType>
class Map
{
private:
	Array<KeyType,ValueType> *_allocator;
	size_t _size;
	static const size_t _default;
	bool operator == (const Map&)const;
	Map(const Map&);
	Map &operator=(const Map&);

	void enlarge(size_t times = 1);
	void reduce(size_t times = 2);

	bool checkIfConsist(Pair<KeyType,ValueType>);

public:
	class NotFoundElement;
	explicit Map();
	~Map();
	void clear();
	void put(const Pair<KeyType,ValueType>&);
	const ValueType& get(const KeyType&)const;
	void remove(const KeyType&);
	const size_t capacity()const{return _allocator->size();}
	bool isEmpty()const{return _size == 0;}
	bool isContainsKey(const KeyType&)const;
	bool isContainsVal(const ValueType&)const;
	ostream& show(ostream& os)const
	{
		os<<'[';
		for(size_t i = 0;i<_size;++i)
		{
		
			os<<_allocator->_allocator[i];
			if(i!=_size-1)
				os<<", ";
		}
		os<<']';
		return os;
	}

};

//ініціалізація
template<class KeyType,class ValueType>
const size_t Map<KeyType,ValueType>::_default(4);


//конструктор
template<class KeyType,class ValueType>
Map<KeyType,ValueType>::Map():
	_allocator(new Array<KeyType,ValueType>), _size(0)
{
#ifndef NDEBUG
	cout<<"Constructor Map"<<endl;
#endif
}

//деструктор
template<class KeyType,class ValueType>
Map<KeyType,ValueType>::~Map()
{
#ifndef NDEBUG
	cout<<"Destructor Map"<<endl;
#endif
	delete _allocator;
	_allocator = 0;
}

//видалили усі елементи з Map
template<class KeyType,class ValueType>
void Map<KeyType,ValueType>::clear()
{
	delete _allocator;
	_allocator = 0;
	_size = 0;
	_allocator = new Array<KeyType,ValueType>;
}

//кладемо елемент в Map
template<class KeyType,class ValueType>
void  Map<KeyType,ValueType>::put(const Pair<KeyType,ValueType>& p)
{
	checkIfConsist(p);
	if(_size+1>capacity())
		enlarge();
	//збільшуємо кількість елементів
	(*_allocator)[_size++] = p;
	return ;
}

template<class KeyType,class ValueType>
const ValueType& Map<KeyType,ValueType>::get(const KeyType& key)const
{
	for(size_t i = 0;i<_size;++i)
	{
		if(_allocator->_allocator[i].getKey() == key)
		{
			return _allocator->_allocator[i].getVal();
		}
	}
	throw NotFoundElement("Not found element");
}

template<class KeyType,class ValueType>
void Map<KeyType,ValueType>::remove(const KeyType& key)
{
	
	if(capacity()>_size*2 + 1)
		reduce();

	for(size_t i = 0;i<_size;++i)
	{
		if(_allocator->_allocator[i].getKey() == key)
		{
			if(i != _size)
			{
				for(size_t j = i;j<_size-1;++j)
				{
					_allocator->_allocator[j] = _allocator->_allocator[j+1];
				}
			}
			--_size;
			return;
		}
	}
	throw NotFoundElement("NotFoundElement remove");
}

template<class KeyType,class ValueType>
bool Map<KeyType,ValueType>::isContainsKey(const KeyType& key)const
{
	for(size_t i = 0;i<_size;++i)
	{
		if(_allocator->_allocator[i].getKey() == key)
			return true;
	}
	return false;
}

template<class KeyType,class ValueType>
bool Map<KeyType,ValueType>::isContainsVal(const ValueType& val)const
{
	for(size_t i = 0;i<_size;++i)
	{
		if(_allocator->_allocator[i].getVal() == val)
			return true;
	}
	return false;
}

///////////////////////////////////////

//if exist element whith this key
template<class KeyType,class ValueType>
bool Map<KeyType,ValueType>::checkIfConsist(const Pair<KeyType,ValueType> p)
{
	for(size_t i = 0;i<_size;++i)
	{
		if(_allocator->_allocator[i].getKey() == p.getKey())
			return false;
	}
	return true;
}


//збільшуємо розмір нашого масиву
template<class KeyType,class ValueType>
void Map<KeyType,ValueType>::enlarge(size_t times = 1)
{
	// Дати запит на новий масив
   Array<KeyType,ValueType> *newArray=
      new Array<KeyType,ValueType>(times*_default+capacity());
// Переписати до нього вміст старого масиву
   for (size_t i=0; i<_size; i++)
      (*newArray)[i]=(*_allocator)[i];
// Видалити старий масив
   delete _allocator;
// Переспрямувати розподілювач пам’яті на новий масив
   _allocator=newArray;
   return;
};


template<class KeyType,class ValueType>
void Map<KeyType,ValueType>::reduce(size_t times = 2)
{
	size_t newLenght = capacity()/times + 1;
	if(newLenght<_default) newLenght = _default;//стандартний розмір блоку
	// Дати запит на новий масив
  Array<KeyType,ValueType> *newArray = 
	  new Array<KeyType,ValueType>(newLenght);
// Переписати до нього вміст старого масиву
  for(size_t i = 0; i< newLenght;++i)
	  (*newArray)[i]=(*_allocator)[i];
// Видалити старий масив
   delete _allocator;
// Переспрямувати розподілювач пам’яті на новий масив
   _allocator=newArray;
   return;
}

//оператор виведення
template<class KeyType,class ValueType>
ostream& operator<<(ostream& os,  const Map<KeyType,ValueType>& m)
{
	return m.show(os);
};




//NotFoundElement
template <class KeyType,class ValueType>
class Map<KeyType,ValueType>::NotFoundElement
{
	private:
// Причина аварійної ситуації
    string _reason;
public:
// Конструктор обробника
	NotFoundElement
		(string reason="unknown"):
	_reason(reason)
	{
#ifndef NDEBUG
	cout<<"Constructor of NotFoundElement"<<endl;
#endif
	return;
	};

//селектори
	const string getReason()const{return _reason;}
	
// Деструктор обробника
	~NotFoundElement() {};

//вивід інформації
	void diagnose() const 
	{
		cerr<<"****"<<endl;
		cerr<<"Reason: ";
		for(size_t i = 0;i<_reason.length();++i)
			cerr<<getReason()[i];
		cerr<<endl;
		cerr<<"****"<<endl;
		return;
	}
};

#endif