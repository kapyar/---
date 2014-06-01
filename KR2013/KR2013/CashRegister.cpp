#include"CashRegister.h"
#include"NotFoundGoods.h"
#include"Products.h"
//	визначимо статичні змінні
size_t CashRegister::_defaultBlock(2);

//	параметри для скидок

Date CashRegister::_disDate = Date();
size_t CashRegister:: _disNumb(10);
Money CashRegister::_disMoney(Money(100,99));
//----------------------------------------

void CashRegister::setBlockSize(size_t n)
{
	_defaultBlock = n;
	return;
}

const CashRegister& CashRegister::setDisMoney(const Money& m)
{
	_disMoney = m;
	return *this;
}

const CashRegister& CashRegister::setDisNumb(const size_t n)
{
	_disNumb = n;
	return *this;
}	

const CashRegister& CashRegister::setDisDate(const Date& d)
{
	_disDate = d;
	return *this;
}

size_t CashRegister::getSize()const
{
	return _size;
}

CashRegister& CashRegister:: add(const size_t code)
{

	if((*_storeHouse).empty())
		cout<<"StoreHouse is empty"<<endl;
	else
	{
		try
		{
			if(_size == 0)
			{
				(*_basket)[0] = &(*_storeHouse).getThing(code);
				//	забираємо з магазину і кладемо собі в корзину
				(_storeHouse)->exclude((*_basket)[0]->getCode());
				++_size;
			}
			else
			{
				if((*_storeHouse).find(code)!=0)
				{
//			збільшуємо розмір комори в разі необхідності
				if(getSize()+1>getCapacity())
					enlarge();
				++_size;
//				додали в кінець
				(*_basket)[getSize()-1] = &(*_storeHouse).getThing(code);
				(_storeHouse)->exclude((*_basket)[getSize()-1]->getCode());
	
				}
			}
		}
		catch(const NotFoundGoods& nfg)
		{
			cout<<nfg<<endl;
		}
		
	}
	return *this;
}
//відміна покупки за порядковим номером в чеку
CashRegister& CashRegister::remove( size_t index)
{
	--index;//бо вмасивы з 0 а в чеку з 1
	if(index<0 || index>getSize()-1)
		cout<<"Out of board"<<endl;
	else
	{
		(_storeHouse)->include(*(*_basket)[index]);
		if(getCapacity()-getSize()>_defaultBlock)
			reduce();
		for(size_t i(index);(i<_size-1);++i)
			(*_basket)[i] = (*_basket)[i+1];
		--_size;
	}

	return *this;
}


size_t CashRegister::getCapacity()const
{
	return (*_basket).size();
}

void CashRegister::enlarge(size_t times)
{
	size_t newLenght = times*_defaultBlock+getCapacity();
	Array<Goods*> *newArray =
		new Array<Goods*>(newLenght);
//		переписуэмо стары значення
	 for(size_t i=0; i<_size; i++)
		 (*newArray)[i]=(*_basket)[i];
	 delete _basket;
	 _basket = newArray;
	return;
}

void CashRegister::reduce(size_t times)
{
	size_t newLenght = getCapacity()-_defaultBlock;
	 Array<Goods*> *newArray = 
	  new Array<Goods*>(newLenght);
// Переписати до нього вміст старого масиву
  for(size_t i = 0; i< newLenght;++i)
	  (*newArray)[i]=(*_basket)[i];
// Видалити старий масив
   delete _basket;
// Переспрямувати розподілювач пам’яті на новий масив
   _basket=newArray;
	return;
}


 Money CashRegister::makeSum()const
{
	Money sum;
	for(size_t i(0);i<getSize();++i)
		sum+=(*_basket)[i]->getPrice();

	return sum;
}

//а) терміну придатності продукту; d - дата після якої розпочинаємо давати знижку
//рахуємо суму знижки за датаю
 Money CashRegister::makeSumWithDate()const
{
	Products p;
	Money sum(0,0);
	const Products *pb = 0;
	double per(0.5);//50% скидка
	for(size_t i(0);i<getSize();++i)
	{
		if(typeid(*(*_basket)[i]) == typeid(p))
		{
			const Products *pb = 0;
			pb = reinterpret_cast<const Products*>((*_basket)[i]);
			if((pb->getDateOfExpiry()) < _disDate)
			{
				//	порахуємо суму скидки
				sum += (*_basket)[i]->getPrice();
			}
		}
	}
	return sum*per; //	сума знижки за датою
}

 
Money CashRegister::makeSumWithNumb(const Money& m)const
{//10%
	Money mm;
	if(getSize()>_disNumb)
	{
		mm =m * 0.1;
	}
	return mm;
	
}

 //		в) загальної вартості усього чеку.*/
Money CashRegister::makeSumWithPrice(const Money& m)const
{
	Money mm;
	if(m>_disMoney)			//зробити скидку 5%
	{
		mm = m*0.05;
	}
	return mm;
}

Money CashRegister::makeTotal( )const
{
	Money res(makeSum());
	res-=makeSumWithDate();
	res-=makeSumWithNumb(res);
	res-=makeSumWithPrice(res);

	return res;
}