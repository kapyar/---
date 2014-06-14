#include"Timer.h"
#include"Windows.h"

Timer::Timer(const Time& when, const Date& FDate, const Time& beepIn)
			 :_finalTime(when),_finalDate(FDate), _beepIn(beepIn)
{
#ifndef NDEBUG
		cout<<"*Constructing Timer"<<endl;
#endif
}
void Timer::check() const
	{
		//1.переведемо години в секунди
		Date currentDate;
		time_t start=static_cast<int>(Time())+currentDate.toSeconds();
		time_t end=static_cast<int>( _finalTime)+_finalDate.toSeconds();

		if(end<start)
		{
			if(currentDate==_finalDate)
			{
				cerr<<"Bad finish time "<<endl;
				throw Time::BadTime(_finalTime);
			}
			else
			{
				cerr<<"Bad finish date "<<endl;
				throw Date::BadDate(_finalDate);
			}
		}
		else
		{
			while(end!=start)
			{
				++start;
				Sleep(1000);	
			}
			
			time_t beepIn=static_cast<int>(_beepIn);
			cout<<"Beep after: "<<beepIn<<endl;
			while(beepIn!=0)
			{
				cout<<"Beep in: "<<beepIn--;
				Sleep(1000);
				cout<<"					"<<char(13);
			}
			cout<<"*Beeping          "<<endl;
			for(int i = 0;i<3;++i)
				Beep(1000,200);
			Beep(300,200);
			Beep(300,100);
			Beep(440,100);
			Beep(300,200);
			Beep(900,500);
		}

	}

