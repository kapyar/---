#include"Sequence.h"
#include"Point.h"

//тестова функція
template <typename Elem>
void test(Sequence<Elem>& a)
{
	try
	{	cout<<endl;
		cout<<"*Testing sequence*"<<endl;
		cout<<a<<endl;
		cout<<a<<endl;
		cout<<"Capacity: "<<a.capacity()<<endl;
		cout<<"Size: "<<a.size()<<endl;
		cout<<"*Before cut*"<<endl;
		cout<<a<<endl;
		cout<<"cut: "<<a.cut()<<endl;
		cout<<a<<endl;
		a.clear();
		cout<<"after clearing"<<endl;
		cout<<a<<endl;
		cout<<"*End of testing*"<<endl;
		a[a.size()];
	}
	catch(const Sequence<Elem>::BadSeq &b)
	{
		cout<<"-=Cought=-"<<endl;
		b.showInfo();
	}
}


int main()
{
	setlocale(LC_ALL,"Ukrainian");
	Sequence<int> a;
	Sequence<Point> p;
	for(size_t i = 0;i<13;++i)
			a.add(i);
	for(size_t i = 0;i<14;++i)
		p.add(Point(i));
	cout<<"44 is not in sequence: "<<boolalpha<<a.isIndepend(44)<<endl;
	test(a);
	test(p);
	return 0;
}