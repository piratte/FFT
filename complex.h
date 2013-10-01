#ifndef COMPLEX
#define COMPLEX

#include <iostream>

typedef long double typ;

class complex
{
	typ rel, img;
	friend std::ostream & operator << (std::ostream & ostr, const complex & c); 
	friend bool operator == (const complex & l, const complex & r);

public:
	complex(typ r = 0,typ i = 0) : rel(r), img(i) {}  


	complex( const complex & c )
	{
			rel = c.rel;
			img = c.img;
	}

	complex & operator = (const complex & c)
	{
			rel = c.rel;
			img = c.img;

			return *this;
	}

	complex & operator += (const complex & c) //definovani "unarnich operatoru je uvnitr tridy"
	{
			rel += c.rel;
			img += c.img;

			return *this;
	}

	complex & operator -= (const complex & c) 
	{
		rel -= c.rel;
		img -= c.img;

		return *this;
	}

	complex & operator *= (const complex & c)
	{
			typ relT(rel*c.rel -img*c.img);
			img	= rel*c.img + img*c.rel;
			rel=relT;

			return *this;
	}

	complex power(int n);

	complex & sdruzene() { img = -img; return *this;}

	void swap()
	{
		typ tmp(img);
		img = rel;
		rel = tmp;
	}
};

complex operator + (const complex & l, const complex & r);


complex operator * (const complex & l, const complex & r);

complex operator - (const complex & l, const complex & r);

bool operator == (const complex & l, const complex & r);


std::ostream & operator << (std::ostream & ostr, const complex & c);

complex primitZJedni(int n);

complex Read(std::string);

#endif

