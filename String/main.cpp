#include"String.h"

int main()
{
	try
	{
		String s;
		String s1('q');
		char a[7] = {'q','w','e','r','t','y','\0'};
		String s2(a);
		String s3("Mars");
		
		cout<<"String(): "<<s<<endl;
		cout<<"String(const char): "<<s1<<endl;
		cout<<"String(const char*): "<<s2<<endl;
		cout<<"String(string): "<<s3<<endl<<endl;
		
		cout<<"*****operator="<<endl;
		cout<<"s: "<<s<<" s1: "<<s1<<endl;
		(s = s1);
		cout<<"s: "<<s<<endl;
		cout<<"s3: "<<s3<<" s2: "<<s2<<endl;
		s3 = s2;
		cout<<"s3: "<<s3<<endl;

		cout<<"*****operator+="<<endl;
		cout<<"s: "<<s<<endl;
		cout<<"s1: "<<s1<<endl;
		cout<<"s2: "<<s2<<endl;
		cout<<"s3: "<<s3<<endl<<endl;

		cout<<"s: "<<s<<" s1: "<<s1;
		cout<<" s=+s1 "<<(s+=s1)<<endl;
		cout<<"s1: "<<s1<<" s2: "<<s2<<endl;
		cout<<"s1=+s2 "<<(s1+=s2)<<endl;
		cout<<"s2: "<<s2<<" s3: "<<s3<<endl;
		cout<<"s2=+s3 "<<(s2+=s3)<<endl;
		cout<<"s3: "<<s3<<" s: "<<s<<endl;
		cout<<"s3=+s "<<(s3+=s)<<endl<<endl;

		cout<<"s: "<<s<<endl;
		cout<<"s1: "<<s1<<endl;
		cout<<"s2: "<<s2<<endl;
		cout<<"s3: "<<s3<<endl;
		
		cout<<boolalpha;
		cout<<s.empty()<<endl;
		s.clear();
		cout<<s.empty()<<endl;
		cout<<s<<endl;

		cout<<"--==utilities==--"<<endl;
		cout<<"s==s2 "<<(s==s2)<<endl;
		cout<<"s1!=s2 "<<(s1!=s2)<<endl;
		cout<<"s2==s2 "<<(s2==s2)<<endl;
		cout<<"s1>s3 "<<(s1>s3)<<endl;
		cout<<"s1<=s "<<(s1<=s)<<endl;
		cout<<"s3>s "<<(s3>s)<<endl;
		cout<<"s3>=s2 "<<(s3>=s2)<<endl;

		cout<<"s3+s2 "<<(s3+s2)<<endl;

		
	}
	catch(const String::BadString& s)
	{
		cerr<<s<<endl;
	}
	catch(const String::BadIndex& b)
	{
		cerr<<"Bad index at the position: "<<b<<endl;
	}
	return 0;
}