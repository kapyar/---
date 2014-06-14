#include "Date.h"
#include "Time.h"


class Timer
{
private:

	Date _finalDate;
	Time _finalTime;
	Time _beepIn;
public:
	//в тймер подається число та час коли він має увімкнути 
	//будильник, також там є параметри за замовчуванням
	//час та число
	Timer(const Time& when=Time(),
			 const Date& FDate=Date(),const Time& _beepIn=Time(0,0,0));
	Timer (const Timer& t)
		:_finalTime(t._finalTime), _finalDate(t._finalDate), _beepIn(t._beepIn)
	{}
	~Timer()
	{}

	Timer& operator=(const Timer& t)
	{
		_beepIn = t._beepIn;
	_finalDate = t._finalDate;
	_finalTime = t._finalTime;

	return*this;
	}
	//перевіряє чи потрібно дзвеніти будильнику
	void check() const;

	void setTime(const Time& t){_finalTime=t;}
	void setDate(const Date& t){_finalDate=t;}
	void setBeep(const Time& t){_beepIn=t;}


	const Date& getFDay()const{return _finalDate; }
	const Time& getFTime()const{return _finalTime; }
	const Time& getBeepIn()const{return _beepIn; }
};

inline ostream& operator<<(ostream& os,const Timer& t)
{
	os<<"Finish time of timer: "<<endl;
	os<<"\t"<<t.getFDay()<<endl;
	os<<"\t"<<t.getFTime();
	return os;
}

