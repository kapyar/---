#ifndef _STOREHOUSE_H_
#define _STOREHOUSE_H_

#include"Array.h"
#include"Goods.h"

//��� ���� ��� �������� ���� ���� ��������
//�������� singletone

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
// ������ ����� �����
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
//	�����������
	Storehouse(size_t size);
//	instance
	static Storehouse* pStorehouse;
//	����� �� �� �������� ������� �� Goods
	Array<Goods*> *_allocator;
//	������ ��������� ������ �� ���� ������
	size_t _size;
//	����������� ����� ����� ����������
   static  size_t _defaultBlock;
//	�������� ������
	void enlarge(size_t times=1);
//	�������� � ������� ����
	void reduce(size_t times=1);

	bool allow(const Goods&)const;
//��������� ����������� �� ���������
	Storehouse(const Storehouse&);
	Storehouse& operator=(const Storehouse&);
};

inline ostream& operator<<(ostream& os, const Storehouse& g)
{
	return g.show(os);
}

#endif