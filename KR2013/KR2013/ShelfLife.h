#ifndef _SHELFLIFE_H_
#define _SHELFLIFE_H_

#include<iostream>
using namespace std;

class ShelfLife
{
private:
	Date _date;
	string _reason;
	size_t _id;//для того щоб видалити потім з комори

public:
	explicit ShelfLife(const string & reason="unknown",
		const Date& d = Date(),size_t id = 0):_reason(reason),_date(d),_id(id)
	{
#ifndef NDEBUG
	cout<<"Constructor ShelfLife"<<endl;
#endif
	}
	~ShelfLife()
	{
#ifndef NDEBUG
	cout<<"Destructor ShelfLife"<<endl;
#endif
	}
	
	ShelfLife(const ShelfLife& s):
		_reason(s.getReason()),_id(s.getId()), _date(s.getDate())
	{
#ifndef NDEBUG
	cout<<"Copyconstructor ShelfLife"<<endl;
#endif
	}
	const string & getReason()const
	{
		return _reason;
	}
	const Date& getDate()const
	{
		return _date;
	}
	void setId(const size_t n)
	{
		_id = n;
	}
	size_t getId()const
	{
		return _id;
	}

	ostream& diagnos(ostream& os)const
	{
		os<<"ShelfLife: "<<endl;
		os<<"Reason: ";
			for(size_t i(0);i<_reason.length();++i)
			os<<_reason[i];
		cout<<endl;
		os<<"Date: "<<_date<<endl;
		os<<"Id: "<<_id<<endl;
		return os;
	}
};


inline ostream& operator<<(ostream& os, const ShelfLife& s)
{
	return s.diagnos(os);
}
#endif