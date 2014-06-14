#include"ArrayHandler.h"
#include"Time.h"


void test(void)
{
	ArrayHandler <int> x(20);
	for (unsigned int i=0;i<x.size();i++)
	{
		x[i]=i;
	}
	for (unsigned int i=0;i<x.size();i++)
	{
		cout<<i<<") &x["<<i<<"] "<<&x[i]<<':'<<x[i]<<endl;
	}
	cout<<endl;
	for (unsigned int i=0;i<x.size();i++)
	{
		cout<<i<<") &*(x+i)= "<<&*(x+i)<<':'<<*(x+i)<<endl;
	}
	cout<<endl;
	cout<<"******* ***** OK"<<endl;
	return;
}

int main()
{
	try
	{
		Time t;
		const ArrayHandler<int> a(2);
		ArrayHandler<int> b(4);
		ArrayHandler<Time> time(10);

		cout<<time[3].getMinutes()<<endl;
		time[9].setMinutes(33);
		cout<<time;
		for(size_t i = 0;i<time.size();++i)
		{
			cout<<time[i]<<endl;
		}
		cout<<"test"<<endl;
		test();
	}
	catch(const ArrayHandler<int>::MisUse& bd)
	{

		cout<<"COUGHT int"<<endl;
		bd.diagnos();
	}
	catch(const ArrayHandler<Time>::MisUse& bd)
	{
		cout<<"COUGHT Time"<<endl;
		bd.diagnos();
	}
	
	return 0;
}