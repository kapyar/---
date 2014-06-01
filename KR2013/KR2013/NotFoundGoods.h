#ifndef _NOTFOUNDGOODS_H_
#define _NOTFOUNDGOODS_H_

#include <iostream>
using namespace std;

class NotFoundGoods
{
private:
	size_t _id;//за яким номером
	string _reason;

public:
	explicit NotFoundGoods(size_t id = 0,const string& reason="NotFoundElement")
		:_id(id), _reason(reason)
	{
#ifndef NDEBUG
	cout<<"Constructor NotFoundGoods"<<endl;
#endif
	}
	NotFoundGoods(const NotFoundGoods& a):_id(a.getId()),_reason(a.getReason())
	{
#ifndef NDEBUG
	cout<<"Copyconstructor NotFoundGoods"<<endl;
#endif
	}
	~NotFoundGoods()
	{
#ifndef NDEBUG
	cout<<"Destructor NotFoundGoods"<<endl;
#endif
	}
	
	size_t getId()const
	{
		return _id;
	}
	const string& getReason()const
	{
		return _reason;
	}
	

	ostream& diagnos(ostream& os)const
	{
		os<<"NotFoundGoods: ";
		for(size_t i(0);i<_reason.length();++i)
			os<<_reason[i];
		os<<"\nCode: "<<_id<<endl;
		return os;
	}

};


inline ostream& operator<<(ostream& os, const NotFoundGoods& a)
{
	return a.diagnos(os);
}

#endif