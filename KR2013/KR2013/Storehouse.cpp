#include"Storehouse.h"
#include"Products.h"
#include"Clothers.h"
#include"Lack.h"
#include"ShelfLife.h"
#include"NotFoundGoods.h"
#include"CantAdd.h"
#include<cassert>
//≥н≥ц≥ал≥зуЇмо статичн≥ атрибути
Storehouse* Storehouse::pStorehouse = 0;
size_t Storehouse::_defaultBlock(2);


//–еал≥зуЇмо закритий конструктор
Storehouse::Storehouse(size_t size)
	:_allocator(new Array<Goods*>(size)),_size(0)
{
	
#ifndef NDEBUG
	cout<<"Constructor Storehouse"<<endl;
#endif
}
//метод €кий сворюЇ Storehouse
Storehouse* Storehouse::getInstance(size_t t)
{
	if (pStorehouse == 0) {
		pStorehouse = new Storehouse(t);
	}
	return pStorehouse;
}

//–озм≥р комори
const size_t Storehouse::getCapacity()const
{
	return _allocator->size();
}
const size_t Storehouse::getSize()const
{
	return _size;
}
Storehouse& Storehouse::include( Goods& g)
{
	bool isInLoop(false);

	if(getSize() == 0)
	{
		(*_allocator)[0] = g.clone();
		++_size;
	}
	//END IF SIZE==0
	else
	{
		//перев≥римо чи можна додати цей товар
		if(allow(g))
		{
//			зб≥льшуЇмо розм≥р комори в раз≥ необх≥дност≥
			if(getSize()+1>getCapacity())
				enlarge();
//			зб≥льшимо к≥льк≥сть елемент≥в
			++_size;
			//тепер поставимо елемент в правильне м≥сце
			for(size_t i(0);i<getSize()-1;++i)
			{
				if(g.getCode()<(*_allocator)[i]->getCode())
				{
					isInLoop =true;
					
	//			зм≥стили вправо на один елемент
				for(size_t j(getSize()-1);j>i;j--)
					(*_allocator)[j] = (*_allocator)[j-1];
//				поставимо на своЇм≥сце
				(*_allocator)[i] = g.clone();
				break;
				}//END IF
			}//END FOR
//кладемо в к≥нець€кщо не поклали в цикл≥
			if(!isInLoop)
			{
				(*_allocator)[getSize()-1] = g.clone();
			}
		}//END ALLOW
		else
		{
			throw CantAdd(g.getCode());
			//cout<<"WARNING: Can add Goods with same id but different other atributes"<<endl;
		}
	}//END _size!=0
	return *this;
}
//¬идал€Їмо за штрих-кодом
Storehouse& Storehouse::exclude(const size_t n)//незм≥нюЇ значенн€ n при передач≥ параметра
{
	bool isDelete(false);
	if(empty())
		cout<<"Storehouse is empty"<<endl;
	else
	{	
		if((getCapacity()-getSize())>_defaultBlock)
		{
			reduce();
		}
		for(size_t i(0);i<getSize();++i)
		{
			if((*_allocator)[i]->getCode() == n)
			{
				if(i!=getSize()-1)//€кщо останн≥й то просто забуваЇмо про нього
				{
					for(size_t j(i);j<getSize()-1;++j)
						(*_allocator)[j] = (*_allocator)[j+1];
				}
				--_size;
				isDelete = true;
				break;//виходимо з циклу
			}
		}
		if(!isDelete)
			cout<<"Havent been found"<<endl;
	}
	return *this;
}
size_t Storehouse::find(const size_t id)const
{
	size_t numb(0);
	if(empty())
	{
		cout<<"Empty"<<endl;
	}
	else
	{
		if(id>=(*_allocator)[0]->getCode())
		{
			for(size_t i(0);i<getSize();++i)
			{
				if((*_allocator)[i]->getCode() == id)
					++numb;
				if((*_allocator)[i]->getCode()>id)
					break;
			}
		}
	}
	
	return numb;
}
bool Storehouse::empty()const
{
	return _size == 0;
}

//«м≥нили розм≥р стандартного блоку
void Storehouse::setBlockSize(size_t t)
{
	Storehouse::_defaultBlock = t;
}
void Storehouse::showInfo()const
{
	cout<<"==============STOREHOUSE================"<<endl;
	
	if(empty())
		cout<<"Storehouse is empty: "<<endl;
	else{
		cout<<"Size: "<<getSize()<<endl;
		cout<<"Capacity: "<<getCapacity()<<endl;
		for(size_t i(0);i<getSize();++i)
		{
#ifndef NDEBUG
			cout<<typeid((*_allocator)[i]).name()<<endl;
#endif
			cout<<i<<' '<<endl;
			(*_allocator)[i]->showInfo();
		
		}
	}
	cout<<"====================================="<<endl;
	return;
}


// допом≥жн≥ методи
void Storehouse::enlarge(size_t times)
{
// ¬ид≥л€Їмо новий масив потр≥бного розм≥ру
   Array<Goods*> *newArray=
	   new Array<Goods*>(times*_defaultBlock+getCapacity());
// ѕереписуЇмо до нього стар≥ значенн€
   for(size_t i=0; i<_size; i++)
	   (*newArray)[i]=(*_allocator)[i];
// ¬идал€Їмо старий масив
   delete _allocator;
// «ам≥нюЇмо його новим ≥ перевстановлюЇмо ≥тератори
   _allocator=newArray;
   return;
}


//	«меншити у к≥льк≥сть раз≥в
void Storehouse::reduce(size_t times)
{
	size_t newLenght = getCapacity()-_defaultBlock;
	 Array<Goods*> *newArray = 
	  new Array<Goods*>(newLenght);
// ѕереписати до нього вм≥ст старого масиву
  for(size_t i = 0; i< newLenght;++i)
	  (*newArray)[i]=(*_allocator)[i];
// ¬идалити старий масив
   delete _allocator;
// ѕереспр€мувати розпод≥лювач памТ€т≥ на новий масив
   _allocator=newArray;
   return;
}


const Storehouse& Storehouse::checkForLack(const size_t n, const size_t num)const
{
	if(n<(*_allocator)[0]->getCode())
	{
		cout<<"Invalid code"<<endl;
	}
	else
	{
		size_t count(0);
		for(size_t i(0);i<getSize();++i)
		{
			if((*_allocator)[i]->getCode()>n)
				break;
			else if((*_allocator)[i]->getCode()==n)
			{
				++count;
			}
		}
		if(count<num)
			 throw Lack("Few things",n);
		
	}
return *this;
}

const Storehouse& Storehouse::checkForDate(const Date& d)const
{
	if(empty())
		cout<<"StoreHouse is empty"<<endl;
	else
	{
		Products p;
		const Products *pb = 0;
		for(size_t i(0);i<getSize();++i)
		{
			if(typeid(*(*_allocator)[i]) == typeid(p))
			{
				pb = reinterpret_cast<const Products*>((*_allocator)[i]);
				if(pb->getDateOfExpiry()<=d)
					throw ShelfLife("Out of Date",(*_allocator)[i]->getDate(),(*_allocator)[i]->getCode());
			}
		}
	}
	return *this;
}



Goods& Storehouse::getThing(const size_t id)const
{
	for(size_t i(0);i<getSize();++i)
	{
		if((*_allocator)[i]->getCode() == id)
		{
			return *(*_allocator)[i];
		}
	}
	throw NotFoundGoods(id);
	
}

bool Storehouse::allow(const Goods& g)const
{
	if(g.getCode()<=(*_allocator)[0]->getCode())
		return true;
	else
	{
		for(size_t i(0);i<getSize();++i)
		{
			if(g.getCode() == (*_allocator)[i]->getCode())
			{
				if(g.getName() == (*_allocator)[i]->getName() &&
					g.getPrice() == (*_allocator)[i]->getPrice())
				{
					//«Ќј„»“№ —ѕџ¬¬ѕјƒјЁ Ќџ„ќ√ќ Ќ≈ ѕќ“–џЅЌќ –ќЅ»“»
				}
				else
					return false;
			}
		}
		return true;
	}
}