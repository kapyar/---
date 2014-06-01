#include"Pair.h"
#include"Array.h"
#include"Map.h"
#include"HashMap.h"
using namespace std;



int main()
{
	try
	{
		Pair<string ,int> p("first",3);
		//cout<<"Key: "<<p.getKey()<<endl;
		cout<<"Val: "<<p.getVal()<<endl;
		p.setVal(5);
		//cout<<"Key: "<<p.getKey()<<endl;
		cout<<"Val: "<<p.getVal()<<endl;

		Array<int,int> ar;
		cout<<ar<<endl;;
		cout<<ar.size()<<endl;
		Map<string,int> map;
		map.put(p);
		Pair<string,int> pp("second",234);
		map.put(pp);
		cout<<"Deploy map: "<<map<<endl;
		map.clear();
		cout<<map<<endl;
		cout<<"capacity: "<<map.capacity()<<endl;
		map.put(Pair<string,int>("one",1));
		map.put(Pair<string,int>("two",2));
		map.put(Pair<string,int>("three",3));
		map.put(Pair<string,int>("four",4));
		map.put(Pair<string,int>("five",5));
		cout<<"capacity: "<<map.capacity()<<endl;
		map.get("one");
		cout<<map<<endl;
		map.remove("one");
		map.remove("five");
		map.remove("two");
		cout<<"after remove capacity: "<<map.capacity()<<endl;
		cout<<map<<endl;


		HashMap<int> h;
		h.put(Pair<string,int>("one",1));
		h.put(Pair<string,int>("noe",21));
		cout<<"get from hash: "<<h.get("one")<<endl;
		cout<<"get from hash: "<<h.get("noe")<<endl;
	//	h.clear();
//		cout<<"get from hash: "<<h.get("one")<<endl;
//		cout<<"get from hash: "<<h.get("noe")<<endl;
		if(!h.remove("one"))
			cout<<"get from hash: "<<h.get("one")<<endl;
		cout<<"get from hash: "<<h.get("noe")<<endl;

		cout<<boolalpha<<h.isContainsKey("noe")<<endl;
		cout<<boolalpha<<h.isContainsVal(21)<<endl;
		


	}
	catch(const Map<string,int>::NotFoundElement& bd)
	{
		cout<<"COUGHT"<<endl;
		bd.diagnose();
	}

	
	return 0;
}