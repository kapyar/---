//yaroslav kaplunskiy

//Клас визначає спільний інтерфейс для похідних класів

#ifndef _GOODS_H_
#define _GOODS_H_
#include<iostream>
#include"Date.h"

#include"Money.h"

class Goods
{
private:
//	атрибути що є у кожному класі
	size_t _code;
	Date _date;
	Money _price;
	string _name;
	string _other;

//	селектори
	virtual const size_t do_get_code() const {return Goods::_code;}
	virtual const Date& do_get_date() const {return Goods::_date;}
	virtual const Money& do_get_price() const {return Goods::_price;}
	virtual const string& do_get_name() const {return Goods::_name;}
	virtual const string& do_get_other()const {return Goods::_other;}
	virtual  void do_get_spec()const=0; 
	

//модифікатори
	virtual void do_set_code(size_t id) 
	{
		Goods::_code = id;
	}
	virtual void do_set_date(const Date& d) 
	{
		Goods::_date = d;
	}
	virtual void do_set_price(const Money& d) 
	{
		Goods::_price = d;
	}
	virtual void do_set_name(const string & s) 
	{
		Goods::_name = s;
	}
	virtual void do_set_other(const string& s) 
	{
		Goods::_other = s;
	}

protected:
	void showBasic()const
	{
		 cout<<"Code: "<<do_get_code()<<endl;
		 cout<<"Date of issue: "<<do_get_date()<<endl;
	//	 cout<<"Price: "<<do_get_price()<<endl;
		 cout<<"Name: ";
		 for(size_t i = 0;i<do_get_name().length();++i)	
			 cout<<do_get_name()[i];
		 cout<<endl;
		 cout<<"Other: ";
		 for(size_t i = 0;i<do_get_other().length();++i)
			 cout<<do_get_other()[i];
			 cout<<endl;
	}
public:
//віртуальний конструктор
	virtual Goods* clone()=0;
//	конструктор
	Goods(size_t id = 0, const Date& d = Date(), const Money& p = Money() , string name="unknown", string other="unknown" )
		:_code(id), _date(d), _price(p), _name(name), _other(other)
	{
#ifndef NDEBUG
	cout<<"Constructor Goods"<<endl;
#endif
	}
//	копіювальний конструктор
	Goods(const Goods& g)
		:_code(g.getCode()),_date(g.getDate()), _price(g.getPrice()),_name(g.getName()),_other(g.getOther())
	{
#ifndef NDEBUG
	cout<<"Copyconstructor Goods"<<endl;
#endif
	}
//	деструктор
	virtual ~Goods()
	{
#ifndef NDEBUG
	cout<<"Destructor Goods"<<endl;
#endif
	}
	
//	селектори
	const size_t getCode() const
	{
		return do_get_code();
	}
	const Date& getDate() const 
	{
		return do_get_date();
	}
	const Money& getPrice() const
	{
		return do_get_price();
	}
	const string& getName() const
	{
		return do_get_name();
	}
	const string& getOther()const
	{
		return do_get_other();
	}
	void showInfo()const 
	{
		 do_get_spec();
	}
	
//	модифікатори

	 void setCode(size_t id)
	 {
		do_set_code(id);
	 }
	 void setDate(const Date& d)
	 {
		do_set_date(d);
	 }
	 void setPrice(const Money& d) 
	 {
		do_set_price(d);
	 }
	 void setName(const string & s)
	 {
		do_set_name(s);
	 }
	 void setOther(const string& s)
	 {
		do_set_other(s);
	 }

	virtual ostream& show (ostream & os) const = 0;
};
inline ostream& operator<<(ostream& os, const Goods& g)
{
	return g.show(os);
}

inline bool operator ==(const string&  a, const string& b)
{
	if(a.length()!=b.length())
		return false;
	else
	{
		for(size_t i = 0;i<a.length();++i)
			if(a[i]!=b[i]) return false;
	}
	return true;

}


#endif