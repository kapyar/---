#ifndef _STOREHOUSE_H_
#define _STOREHOUSE_H_

#include"Array.h"
#include"Goods.h"

//для того щоб існувала лише одна кладовка
//реалізуємо singletone

class Storehouse
{
public:

	~Storehouse()
	{
		delete _allocator;
		return;
	}
	static Storehouse* getInstance(size_t = 4);
	const size_t getCapacity()const;
	const size_t getSize()const;
	Storehouse& include( Goods&);
	Storehouse& exclude(const size_t);
	size_t find(const size_t id)const;
	void showInfo()const;
	
	bool empty()const;
// Змінити розмір блоку
   static void setBlockSize(size_t);

	const Storehouse& checkForLack(const size_t id, const size_t numOfLack = 2)const;
	const Storehouse& checkForDate(const Date&)const;

	 Goods& getThing(const size_t index)const;

	ostream& show(ostream & os)const
	{
		os<<"==============STOREHOUSE================"<<endl;
	
	if(empty())
		os<<"Storehouse is empty: "<<endl;
	else{
		os<<"Size: "<<getSize()<<endl;
		os<<"Capacity: "<<getCapacity()<<endl;
		for(size_t i(0);i<getSize();++i)
		{
			os<<i<<' '<<endl;
			os<<*(*_allocator)[i];
		}
	}
	os<<"====================================="<<endl;
	return os;
	}


	
private:
//	конструктор
	Storehouse(size_t size);
//	instance
	static Storehouse* pStorehouse;
//	масив де ми зберігаємо указник на Goods
	Array<Goods*> *_allocator;
//	кількіть нанесених товарів до нашої комори
	size_t _size;
//	Стандартний розмір блоку контейнера
   static  size_t _defaultBlock;
//	Збільшити ємність
	void enlarge(size_t times=1);
//	Зменшити у кількість разів
	void reduce(size_t times=1);

	bool allow(const Goods&)const;
//закриваємо копіювальний та присвоєння
	Storehouse(const Storehouse&);
	Storehouse& operator=(const Storehouse&);
};

inline ostream& operator<<(ostream& os, const Storehouse& g)
{
	return g.show(os);
}

#endif