#include "complex.h"
#include <math.h>
#include <sstream>
#include <string>

#define M_PI 3.141592653589793238462643383279502884197

complex operator + (const complex & l, const complex & r)
{
        complex c(l);  
        c += r;        
        return c;      
};

complex operator * (const complex & l, const complex & r)
{
        complex c(l);  
        c *= r;        
        return c;      
};

complex operator - (const complex & l, const complex & r)
{
		complex c(l);  
		c -= r;        
		return c; 
}

bool operator == (const complex & l, const complex & r)
{
	if (l.rel == r.rel && l.img == r.img)
	{
		return true;
	}
	else return false;
}


std::ostream & operator << (std::ostream & ostr, const complex & c)
{
		ostr << '[' << c.rel << ';' << c.img << ']';
        return ostr;
}

complex primitZJedni(int n)
{
	typ arg((2* M_PI)/n);
	typ rel(cos(arg)), img(sin(arg));
	if (rel == 1 || rel == -1) {img = 0;}
	if (img == 1 || img == -1) {rel = 0;}
	
	complex x(rel, img);
	return x;
}

complex complex::power(int n)
{
	if (n == 0)
	{
		return complex(1.0,0.0);
	}

	typ arg(acos(rel));
	arg *= n;
	typ rel(cos(arg)), img(sin(arg));
	if (rel == 1 || rel == -1) {img = 0;}
	if (img == 1 || img == -1) {rel = 0;}
	
	complex x(rel, img);
	return x;
	/*
	complex puvodni(*this);
	complex temp(*this);
	for (int i = 1; i < n; i++)
	{
		temp *= puvodni;
	}
	return temp; */
}

complex Read(std::string radek)
{
	typ r, i;
	std::string real(radek.substr(0, radek.find(";"))) , imag(radek.substr(radek.find(";")+1));
	std::stringstream sr(real);
	sr >> r ? r : 0;
	std::stringstream si(imag);
	si >> i ? i : 0;
	return complex(r,i);
}