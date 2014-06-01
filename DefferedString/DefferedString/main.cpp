#include"DeferredString.h"


int main()
{

	try{
		DeferredString d("tro-lo-lo");
		const DeferredString dd(d);

		tester(d);
		cout<<endl;
		d[2] = 's';
		tester(d);
		cout<<endl;
		tester(dd);
	}
	catch(const DeferredString::BadString& bd)
	{
		bd.diagnose();
	}
	return 0;
}