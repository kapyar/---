#include "Goods.h"
#include "Products.h"
#include "Clothers.h"
#include "Storehouse.h"
#include "Lack.h"
#include "ShelfLife.h"
#include "CashRegister.h"
#include"CantAdd.h"

int main()
{
	
	Money m(3,102);
	Products g(3,Date(3,4,2013),m,"Bananna","Africa",Date(3,9,2013));
	cout<<"--==Start testing program==--"<<endl;
	
	cout<<"**Storehouse**"<<endl;
	Storehouse *sh = Storehouse::getInstance(2);
	cout<<(*sh)<<endl;
	sh->exclude(3);

	Products snik (2,Date(13,4,2012),Money(5,50),"Snikers","chocolate",Date(3,12,2013));
	Clothers colins(44,Date(23,4,2010),Money(345),"colins","blue",32);
	Clothers jeans(45,Date(23,4,2010),Money(500),"jeans","red",36);
	Products apple(5,Date(5,7,2010),Money(10,50),"Apple","SLAVA",Date(3,9,2009));
	Products orange(130,Date(15,11,2009),Money(13,76),"Orange","Africa",Date(3,12,2014));
	Products orange1(130,Date(15,11,2009),Money(13,77),"Orange","Africa",Date(3,12,2014));

	
	sh->showInfo();
	cout<<"--==ADD==--"<<endl;
	try
	{
		sh->include(snik).include(colins).include(jeans).include(apple).
			include(orange).include(jeans).include(apple);
		sh->include(orange).include(snik).include(snik).include(snik).
			include(snik).include(snik).include(snik);
		sh->include(orange1);
	}
	catch(const CantAdd& a)
	{
		cout<<"CANT ADD"<<endl;
		cout<<a<<endl;
	}
	sh->showInfo();
	
	cout<<"--==EXCLUDE==--"<<endl;
	sh->exclude(45).exclude(45).exclude(2);
	sh->showInfo();

	cout<<"--==FIND BY CODE==--"<<endl;
	cout<<"Code 5: "<<sh->find(5)<<endl;
	cout<<"Code 45: "<<sh->find(45)<<endl;
	cout<<"Code 130: "<<sh->find(130)<<endl;

	cout<<"-==ADD MORE GOODS==--"<<endl;
	Clothers jack(456,Date(2,4,2018),Money(1100,32),"jacket","black",44);
	Clothers shoes(78,Date(23,4,2010),Money(654,56),"timberland","blue",41);
	try
	{
		sh->include(jack).include(shoes).include(jeans).include(jeans).include(apple);
	}
	catch(const CantAdd& a)
	{
		cout<<"CANT ADD"<<endl;
		cout<<a<<endl;
	}
	cout<<(*sh)<<endl;
	cout<<"--==ONE STORE HOUSE IN PROGRAM==--"<<endl;
	Storehouse *sth = Storehouse::getInstance(55);
	cout<<(*sth)<<endl;
	cout<<"--==LOOK FOR EXCEPTION==--"<<endl;
	try
	{
		sh->checkForLack(5,3);
	}
	catch(const Lack& lack)
	{
		cout<<"LACK"<<endl;
		cout<<lack<<endl;
	}
	try
	{
		sh->checkForDate(Date());
	}
	catch(const ShelfLife& s)
	{
		cout<<"SHELFLIFE"<<endl;
		cout<<s<<endl;
		cout<<"Solve the problem: delete this Product"<<endl;
		sh->exclude(s.getId());
	}

	CashRegister cr;
	cr.setDisDate(Date());
	cr.setDisMoney(Money(1100,99));
	cr.setDisNumb(11);
	cout<<"++++++++START BUYING++++++++"<<endl;
	cr.add(78);
	cr.add(456);
	cr.add(45);
	cr.add(45);
	cout<<cr<<endl;
	cout<<(*sh)<<endl;
	cout<<"--==REFUSE FROM  #2==--"<<endl;
	cr.remove(2);
	cout<<cr<<endl;
	sh->showInfo();
	
	cout<<"--==END Testing==--"<<endl;
	return 0;
}