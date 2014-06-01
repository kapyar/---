#ifndef _CANTADD_H_
#define _CANTADD_H_

#include<iostream>
using namespace std;
#include"Goods.h"
class CantAdd
{
private:
	string _reason;
	size_t _id;
public:
	explicit CantAdd( size_t id = 0, const string& s="Have same id but different other atributes" )
		:_reason(s),_id(id)
	{
#ifndef NDEBUG
	cout<<"Constructor CantAdd"<<endl;
#endif
	}
	CantAdd(const CantAdd& a):_reason(a.getReason()),_id(a.getId())
	{
#ifndef NDEBUG
	cout<<"Copyconstructor CantAdd"<<endl;
#endif
	}
	~CantAdd()
	{
#ifndef NDEBUG
	cout<<"Destructor CantAdd"<<endl;
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
		os<<"CantAdd: ";
		for(size_t i(0);i<_reason.length();++i)
			os<<_reason[i];
		os<<endl;
		os<<"Id: "<<_id<<endl;
		return os;
	}
};
inline ostream& operator<<(ostream& os,const CantAdd& a)
{
	return a.diagnos(os);
}

#endif