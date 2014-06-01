#include "DeferredString.h"



int main()
{
	try
	{
		char * t = new char();
		
		string tt("hatuna-matata");
		t = &tt[0];
		
		DeferredString<char> d("tro-lo-lo");
		DeferredString<char> dd(d);
		DeferredString<char> ddd(t);
		//ddd = d;
		cout<<"LOOK AT ME"<<endl;
		cout<<ddd<<endl;
		cout<<"======================"<<endl;
		cout<<"LOOK AT ME"<<endl;
		d.tester();
		cout<<"======================"<<endl;
		cout<<"LOOK AT ME"<<endl;
		dd.tester();
		cout<<"======================"<<endl;
		cout<<"LOOK AT ME"<<endl;
		ddd.tester();
		cout<<"======================"<<endl;

		
		
		DeferredString<wchar_t> w("wchar_t string");
		DeferredString<wchar_t> ww(w);
		DeferredString<wchar_t> www;
		
		www = w;
		
		cout<<"======================"<<endl;
		cout<<"LOOK AT ME"<<endl;
		w.tester();
		cout<<"======================"<<endl;
		cout<<"LOOK AT ME----"<<endl;
		ww.tester();
		cout<<"======================"<<endl;
		cout<<"LOOK AT ME"<<endl;
		www.tester();
		cout<<"=================================================================="<<endl;

		DeferredString<char> theSwiss("Niklaus Wirth, TFH Zurich");
		for (size_t i=0;i<theSwiss.length();++i)
			cout<<theSwiss[i]<<":";
		string ss("Edsger Wybe Dijkstra, University of Texas at Austin & University of Laiden");
		DeferredString<char> theDutchman(ss);
		DeferredString<char> anAmerican(theDutchman);
		DeferredString<char> aEuropean(theSwiss);

		theSwiss.tester();
		theDutchman.tester();
		anAmerican.tester();
		aEuropean.tester();

		cout << "-----\n";
		char * pc = &theSwiss[15];
		*pc ='E';
		theSwiss=theSwiss;
		theSwiss.tester();
		aEuropean.tester();

		cout << "-----\n";
		anAmerican = aEuropean = theDutchman;
		anAmerican.tester();
		char & rc = theDutchman[69];
		rc = 'e';
		anAmerican.tester();
		aEuropean.tester();
		theDutchman.tester();
		cout<<theDutchman[5]<<endl;

		char* c = "111111";
        theSwiss = c;
		theSwiss.tester();

		theSwiss[10000]='a';
	
	}
	catch(const DeferredString<char>::BadString& bd)
	{
		cerr<<"COUGHT"<<endl;
		bd.diagnose();
	}

	catch(const DeferredString<wchar_t>::BadString& bd)
	{
		cerr<<"COUGHT"<<endl;
		bd.diagnose();
	}
	return 0;
}