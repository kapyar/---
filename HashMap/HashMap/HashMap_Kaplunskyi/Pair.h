#ifndef _PAIR_H_
#define _PAIR_H_

#include<iostream>
#include<string>
using namespace std;

#define NDEBUG

template<class KeyType,class ValueType>
class Pair
{
private:
	KeyType _key;
	ValueType _val;

public:
	//default Pair ctor
	Pair()
		:_key(KeyType()),_val(ValueType())
	{
	#ifndef NDEBUG
		cout<<"Constructor Pair"<<endl;
#endif
	}

	Pair(KeyType k ,ValueType v):
		_key(k), _val(v)
	{
		std::cout<<"Pair"<<std::endl;
	}

	~Pair()
	{
#ifndef NDEBUG
		cout<<"Destructor Pair"<<endl;
#endif
	}

	const KeyType& getKey()const
	{
		return _key;
	}

	void setKey(const KeyType& k)
	{
		_key = k;
	}

	const ValueType& getVal()const
	{
		return _val;
	}

	void setVal(const ValueType& v)
	{
		 _val = v;
	}
};

//оператор виводу
template<class KeyType,class ValueType>
ostream& operator<<(ostream & os , const Pair<KeyType, ValueType>& a)
{
	os<<"[ "<<a.getKey()<<", "<<a.getVal()<<"]";
	return os;
};


#endif