//Запрограмувати створення і обробку аварійних ситуацій 
//а) Lack, викликаної наявністю 
//критичної кількості виробів з даним штрих-кодом в коморі;
//
//б) ShelfLife — критичністю терміну зберігання.-
#ifndef _LACK_H_
#define _LACK_H_
#include<iostream>
using namespace std;
class Lack
{
private:
	size_t _id;//за яким номером
	string _reason;

public:
	explicit Lack(const string& reason="unknown", size_t id = 0)
		:_id(id), _reason(reason)
	{
#ifndef NDEBUG
	cout<<"Constructor Lack"<<endl;
#endif
	}
	Lack(const Lack& a):_id(a.getId()),_reason(a.getReason())
	{
#ifndef NDEBUG
	cout<<"Copyconstructor Lack"<<endl;
#endif
	}
	~Lack()
	{
#ifndef NDEBUG
	cout<<"Destructor Lack"<<endl;
#endif
	}
	
	size_t getId()const
	{
		return _id;
	}
	const string& getReason()const
	{
		return _reason;
	}
	

	ostream& diagnos(ostream& os)const
	{
		os<<"Lack: ";
		for(size_t i(0);i<_reason.length();++i)
			os<<_reason[i];
		os<<"\nCode: "<<_id<<endl;
		return os;
	}

};


inline ostream& operator<<(ostream& os, const Lack& a)
{
	return a.diagnos(os);
}

#endif