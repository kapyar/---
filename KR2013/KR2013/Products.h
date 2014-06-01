// На базі класу Goods визначити конкретний
//клас продуктів харчування Product. 
//Додатковою характеристикою служить термін придатності.
#ifndef _PRODUCTS_H
#define _PRODUCTS_H

class Products : public Goods
{
private:
	Date _exDate;
	virtual const Date& do_get_date_of_expiry()const{return _exDate;}
	virtual void do_set_date_of_expiry(const Date& d){_exDate = d;return;}
	virtual  void do_get_spec()const
	{	
		Goods::showBasic();
		cout<<"Date of expiry: "<<_exDate<<endl;
		return;
	}

public:
	class BadProducts;
	Products* clone(){return new Products(*this);}//клонуємо з викликом копіювального конструкора
	explicit Products(size_t id = 0, const Date& d = Date(), const Money& p = Money(), string name="unknown", string other="unknown", Date exd = Date())
		: Goods(id,d,p,name,other), _exDate(exd)
	{
#ifndef NDEBUG
	cout<<"Constructor Products"<<endl;
#endif
	}
	Products (const Products& g)
		:Goods((g.getCode()),(g.getDate()), 
		(g.getPrice()),(g.getName()),(g.getOther())),
		_exDate(g.getDateOfExpiry())  
	{
#ifndef NDEBUG
	cout<<"Copyconstructor Products"<<endl;
#endif
	}
		
	
	virtual ~Products()
	{
#ifndef NDEBUG
	cout<<"Destructor Goods"<<endl;
#endif
	}

	const Date& getDateOfExpiry() const
	{
		return do_get_date_of_expiry();
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

		os<<"Date of expiry: "<<getDateOfExpiry()<<endl;
		return os;
	}
};

//inline ostream& operator<<(ostream& os, const Products& g)
//{
//	return g.show(os);
//}


#endif