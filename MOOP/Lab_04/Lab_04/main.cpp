#include"Convex.h"
using namespace std;


int main()
{
	try
	{
		Convex c;
		c.add(Point(0,0));
		c.show();
		c.add(Point(1,0));
		c.show();
		c.add(Point(0,1));
		c.show();
		c.add(Point(1,1));
		c.add(Point(0.5,0.5));
		c.show();
		c.add(Point(2,2));
		c.add(Point(2,0));
		c.add(Point(0,2));
		c.show();
		c.add(Point(1,5));
		c.add(Point(1,1.4));
		c.add(Point(0.2,0.2));
		cout<<"Show smt"<<endl;
		c.show();
	
		Convex cc;
		cc.add(Point(0,0));
		cc.add(Point(0,0));
		cc.add(Point(0,0));
	}
	catch(const Polygon::BadInit& bd)
	{
		bd.diagnos();
	}
	return 0;
}