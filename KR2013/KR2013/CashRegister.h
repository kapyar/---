#ifndef _CASHREGISTER_H_
#define _CASHREGISTER_H_
#include "Storehouse.h"
class CashRegister
{
private:

//закриваємо копіювальний та присвоєння
	CashRegister(const CashRegister&);
	CashRegister& operator=(const CashRegister&);
//	параметри для скидок
	static Date _disDate;
	static size_t _disNumb;
	static Money _disMoney;

//
	size_t _size;
	Storehouse *_storeHouse;//за допомогою getInstance повертаємо указник нна наш магазин
	void enlarge(size_t times = 1);
	void reduce(size_t times = 1); 
	Array<Goods*> *_basket;
//	Стандартний розмір блоку контейнера
   static  size_t _defaultBlock;
public:
	explicit CashRegister(size_t n = _defaultBlock)
		:_storeHouse(Storehouse::getInstance()), _basket(new Array<Goods*>(n)), _size(0)
	{
#ifndef NDEBUG
		cout<<"Constructor CashRegister"<<endl;
#endif
	}
	~CashRegister()
	{
		delete _basket;
#ifndef NDEBUG
		cout<<"Destructor CashRegister"<<endl;
#endif
	}

	CashRegister& add(const size_t code);
	CashRegister& remove(size_t id);

	size_t getSize()const;
	size_t getCapacity()const;

//	Змінити розмір блоку
   static void setBlockSize(size_t);
//	встановити дату виготовлення продукту пысля якоъ дыэ скидка
    const CashRegister& CashRegister::setDisDate(const Date& d);
	const CashRegister& CashRegister::setDisNumb(const size_t n);
    const CashRegister& CashRegister::setDisMoney(const Money& m);
	
//рахує без знижок
	Money makeSum()const; 

// а) терміну придатності продукту;
    Money makeSumWithDate()const;
//б) кількості одиниць виробів у одному чеку;
    Money CashRegister::makeSumWithNumb(const Money& m)const;
//		в) загальної вартості усього чеку.*/
	Money CashRegister::makeSumWithPrice(const Money& m)const;
//		рахуємо суму зі усіма можливими знижками
	Money CashRegister::makeTotal()const;
   

	ostream& show(ostream & os)const
   {
		cout<<"==========YOUR BILL==========="<<endl;
		for(size_t i(0);i<getSize();++i)
		{
			cout<<i+1<<endl;
			cout<<"Name: ";
			for(size_t j(0);j<(*_basket)[i]->getName().length();++j)
				cout<<(*_basket)[i]->getName()[j];
			cout<<endl;
			cout<<"Code "<<(*_basket)[i]->getCode()<<endl;
			cout<<"Price: "<<(*_basket)[i]->getPrice()<<endl;
			cout<<endl;
		}
		cout<<endl;
		cout<<'\t'<<"TOTAL SUM: "<<makeSum()<<endl;
		cout<<'\t'<<"SUM WITH DISCOUNT: "<<makeTotal()<<endl;
		cout<<'\t'<<"DIscount: "<<makeSum() - makeTotal()<<endl;
		cout<<"==========END BILL============"<<endl;
		return os;
   }

};

inline ostream& operator<<(ostream& os,const CashRegister& c)
{
	return c.show(os);
}

#endif