#ifndef POLYNOM
#define POLYNOM

#include <vector>
#include "complex.h"


enum Tvar{
	graf,
	koef 
	};

class polynom
{
	friend std::ostream & operator << (std::ostream & ostr, polynom &);
	friend polynom operator * (const polynom & l, const polynom & p);

	std::vector<complex> repre;
	Tvar tvar;

	void  srovnejVelikost(polynom & );
	void doplnNuly(int cilovaVelikost);

public:

	explicit polynom(int velikost, Tvar);
	explicit polynom(std::vector<complex>, Tvar);
	polynom(const polynom & p);	
	polynom & operator = (const polynom & p); //return *this;
	polynom & operator *= (const polynom &);
	polynom & operator *= (const double &);
	polynom & operator /= (const double &);

	complex & at(size_t );
	const complex & polynom::at(size_t ind) const;


	void velikostNaMocninu(size_t);

	const std::size_t velikost() const {return repre.size();}

	polynom vyber(int zbytekPoDeleniDvemi);
	void prohod();

	void zmenTvar();
	const Tvar vratTvar() const;

};

polynom operator * (const polynom & , const polynom & );

polynom preFourier(const polynom &);

//polynom & fourier(int n, complex primit, polynom & p);

polynom & paraFourier(int n, complex primit, polynom & p, int depth);

std::ostream & operator << (std::ostream & ostr, polynom &);
#endif