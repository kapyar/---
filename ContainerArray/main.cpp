#include "Array.h"
#include "Point.h"

//тестова функція
template <size_t n, typename Elem>
void test(const Array<n,Elem>& a)
{
	try
	{
		cout<<"*Testing array*"<<endl;
		cout<<a<<endl;
		for(size_t i = 0;i<a.size();++i)
			cout<<a[i]<<endl;
		cout<<"*End of testing*"<<endl;
		a[a.size()];
	}
	catch(const Array<n, Elem>::BadIndex &b)
	{
      b.diagnose();
	}
}

int main()
{
	setlocale(LC_ALL, "Ukrainian");
	const Array<2,double> a;
	Array<5,char> c;
	Array<8,int> i;
	Array<3,Point> point;

	cout<<"---==First==---"<<endl;
	test(a);
	cout<<endl;

	cout<<"---==Second==---"<<endl;
	test(c);
	cout<<endl;

	cout<<"---===Third==---"<<endl;
	test(point);
	cout<<endl;

	cout<<"---==Fourth==---"<<endl;
	test(i);
	cout<<endl;

	return 0;
}