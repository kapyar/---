#include"Timer.h"
/*
		Програма дозволяє працювати з від'ємними хвилинами секундами годинами,
	але є обмеження,якщо сума секунд: годин, хвилин та секунд має
	бути величина додатня, в іншому разі спрацює обробка аварійної ситуації.
		Також є можливість використання дати та годин за замавчуванням, які 
	беруться з системи.
		В класі Timer можна задавати час та дату для спрацювання таймер та час через
	який він подасть сигнал,першим параметром є час, другим дата, якщо вони не задаються то встановлюються
	з системного часу.Найбільше значення для кінцевої дати будильника є:  
	03:14:07 UTC on Tuesday, 19 January 2038
	:)
*/

int main()
{
	setlocale(LC_ALL,"Ukrainian");
	try
	{
		cout<<"Current date: ";
		Date::showDefault();
		cout<<"\nCurrent time: ";
		Time::showDefault();

		Date d(9,3,2013);
		Time t1,t2(60),t3(t2);

		cout<<"\n==Changing time: "<<t1<<endl;
		t1.setHours(14);
		t1.setMinutes(-44);
		t1.setSeconds(-69);
		cout<<"==Changed time: "<<t1<<endl;
		
		t1.setDefault();
		cout<<"t1: "<<t1<<endl;

		cout<<"operator++,--"<<endl;
		cout<<"t1: "<<t1<<endl;
		cout<<"++t1: "<<++t1<<endl;
		cout<<"t1: "<<t1<<endl;
		cout<<"t1++"<<t1++<<endl;
		cout<<"t1: "<<t1<<endl;
		cout<<"t1--: "<<t1--<<endl;
		cout<<"--t1: "<<--t1<<endl;
		cout<<"t1: "<<t1<<endl;
		cout<<"end of operators ++ --"<<endl;
		
		cout<<"t1: "<<t1<<endl;
		cout<<"t2: "<<t2<<endl;
		cout<<"t1+t2= "<<t1+t2<<'h'<<endl;
		
		cout<<"static_cast<int>(t1): "<<static_cast<int>(t1)<<endl;
		cout<<"static_cast<double>(t1): "<<static_cast<double>(t1)<<endl;
		
		Date dt;
		Time ttt(5,0,0);
		Timer timer(t2);
		Timer timer2(timer);
		timer.setTime(t3);
		timer.setDate(dt);
		timer.setBeep(ttt);
		cout<<"Time when timer finish: "<<timer.getFTime()<<endl;
		cout<<"Date when timer finish: "<<timer.getFDay()<<endl;
		cout<<timer<<endl;
		timer.check();
	}

	catch(const Time::BadTime& bt)
	{
		cerr<<"*Incorect Time: "<<bt<<endl;
	}
	catch(const Date::BadDate& bd)
	{
		cerr<<"*Incorect Date: "<<bd<<endl;
	}
	return 0;
}