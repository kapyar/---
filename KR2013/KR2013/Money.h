#ifndef _MONEY_H_
#define _MONEY_H_
#include<math.h>
class Money
{
private:
	size_t _hr;
	size_t _cop;
	void normalize()
	{
		_hr+= _cop/100;
		_cop= _cop%100;
	}
public:
	explicit Money(size_t hr = 0, size_t cop = 0)
		:_hr(hr), _cop(cop)
	{
//	перетворюємо в правильний тип
		normalize();
#ifndef NDEBUG
	cout<<"Constructor Money"<<endl;
#endif
	}

	operator double()
	{
		return _hr*100+_cop;
	}

	~Money()
	{
#ifndef NDEBUG
	cout<<"Destructor Money"<<endl;
#endif
	}

	Money(const Money& m):_hr(m.getHr()),_cop(m.getCop())
	{
#ifndef NDEBUG
	cout<<"Copyconstructor Money"<<endl;
#endif
	}

	const size_t getHr()const
	{
		return _hr;
	}
	const size_t getCop()const
	{
		return _cop;
	}
	void setHr(size_t s)
	{
		_hr = s;
	}
	void setCop(size_t s)
	{
		_cop = s;
	}
	const Money& operator+=(const Money& m)
	{
		_hr+=m.getHr();
		_cop+=m.getCop();
		return *this;
	}
	const Money& operator-=(const Money& m)
	{
		if(_cop<m.getCop())
		{
			--_hr;
			_cop+=100;
		}
		_hr-=m.getHr();
		_cop-=m.getCop();
		return *this;
	}
};

inline bool operator>(const Money& a, const Money& b)
{
	if(a.getHr()>b.getHr())
		return true;
	if(a.getHr()<b.getHr())
		return false;
	if(a.getCop()>b.getCop())
		return true;
	return false;
}


inline Money operator*(const Money& a, double d)
{
	Money res(a);
	double c(a.getCop()*d + a.getHr()*100*d);			//зробили з суми копійки
	size_t cc = static_cast<size_t>(c);
	res.setHr(cc/100);
	res.setCop(cc%100);
	return res;
}

inline Money operator*(double d, const Money& a)
{
	return a*d;
}

inline ostream& operator<<(ostream& os, const Money& m)
{
	os<<m.getHr()<<" grn "<<m.getCop()<<" cop";
	return os;
}

inline Money operator+(const Money& a, const Money& b)
{
	Money res(a);
	return res+=b;
}

inline Money operator-(const Money& a, const Money& b)
{
	Money res(a);
	return res-=b;
}


inline bool operator == (const Money& a, const Money& b)
{
	if(a.getCop() != b.getCop())
		return false;
	if(a.getHr()!=b.getHr())
		return false;
	return true;
}

inline bool operator != (const Money& a, const Money& b)
{
	return !(a==b);
}

#endif