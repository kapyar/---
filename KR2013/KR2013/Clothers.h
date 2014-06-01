#ifndef _CLOTHERS_H_
#define _CLOTHERS_H_

class Clothers : public Goods
{
private:
	size_t _size;
//	селектори
	virtual const size_t do_get_size()const{return _size;}

//модифікатори
	virtual void do_set_size(size_t i){ _size = i;return;}
	virtual void do_get_spec()const
	{
		Goods::showBasic();
		cout<<"Size: "<<_size<<endl;
		return;
	}

public:
	Clothers* clone(){return new Clothers(*this);}//клонуємо з викликом копіювального конструкора
	explicit Clothers(size_t id = 0, const Date& d = Date(), const Money& p = Money(), string name="unknown",
			string other="unknown", size_t size =46)
		: Goods(id,d,p,name,other), _size(size)
	{
#ifndef NDEBUG
	cout<<"Constructor Clothers"<<endl;
#endif
	}
	Clothers(const Clothers& g)
		:Goods((g.getCode()),(g.getDate()), 
		(g.getPrice()),(g.getName()),(g.getOther())),
		_size(g.getSize())
	{
#ifndef NDEBUG
	cout<<"Copyconstructor Clothers"<<endl;
#endif
	}

	
	virtual ~Clothers()
	{
#ifndef NDEBUG
	cout<<"Destructor Products"<<endl;
#endif
	}
	const size_t getSize()const
	{
		return do_get_size();
	}

	void setSize(size_t i)
	{
		do_set_size(i);
		return;
	}
	ostream& show (ostream & os) const
	{
		os<<"Code: "<<getCode()<<endl;
		os<<"Date of issue: "<<getDate()<<endl;
		os<<"Price: "<<getPrice()<<endl;
		os<<"Name: ";
		for(size_t i = 0;i<getName().length();++i)	
			os<<getName()[i];
		os<<endl;
		os<<"Other: ";
		for(size_t i = 0;i<getOther().length();++i)
			os<<getOther()[i];
		os<<endl;

		os<<"Size: "<<getSize()<<endl;
		return os;
	}
};

//inline ostream& operator<<(ostream& os, const Clothers& g)
//{
//	return g.show(os);
//}

#endif