#include "polynom.h"
#include <future>
#include <iostream>


//========================================== Konstruktory etc. ========================================================


polynom::polynom(int velikost, Tvar t): tvar(t)
{
	for (int i = 0; i < velikost; i++)
	{
		repre.push_back(complex());
	}
}

polynom::polynom(std::vector<complex> v, Tvar t): tvar(t)
{
	repre = v;	
}

polynom::polynom(const polynom & p)
{
	tvar = p.tvar;
	repre = p.repre;
}

polynom & polynom::operator = (const polynom & p)
{
	tvar = p.tvar;
	repre = p.repre;

	return *this;
}

//========================================== Hlavni funkce ========================================================


polynom preFourier(const polynom & p) 
{
	//vytvorime si kopii polynomu a s ni budeme pracovat
	polynom novy(p);
	
	//vytvorime spravnou primitivni odmocninu z 1
	complex primit(primitZJedni(novy.velikost()));

	//odlisime inverzi od normalniho FFT
	if (p.vratTvar() == graf)
	{
		novy.prohod();
	}

	polynom out(0,koef);
	//pro paralelyzaci
	if (novy.velikost() > 8)
	{
		out = paraFourier(novy.velikost(), primit, novy, 0);
	}
	else{
		//a vratime polynom, ktery je vysledkem FFT (pozor na vraceni odkazem, mozna budes muset zmenit predavani do FFT pomoci odkazu !!!!!!!!!! )
		out = paraFourier(novy.velikost(), primit, novy, 2);
	}
	//zde se rozhoduje, jestli je to inverze nebo ne. if se pta na tvar repre, se kterym polynom vstupoval do funkce, fce fourier nemeni tvar repre
	size_t n(out.velikost());
	if (out.vratTvar() == graf)
	{
		out *= 1/pow(n,1);
		out.prohod();
	}

	out.zmenTvar();

	return out;
}

polynom & paraFourier(int n, complex primit, polynom & p, int depth)
{
	++depth;
	//konec rekurze
	if (n == 2) 
	{
		complex pNula(p.at(0) +  p.at(1));
		p.at(1) = p.at(0) -  p.at(1);
		p.at(0) = pNula;
		return p;
	}

	//rozelime p na dve casti
	polynom sude(p.vyber(0)); 
	polynom liche(p.vyber(1));

	if (depth > 2 )
	{
		sude = paraFourier(n/2, primit.power(2), sude, depth);
		liche = paraFourier(n/2, primit.power(2), liche, depth);
	}
	else
	{
		auto futSud = std::async(paraFourier, n/2, primit.power(2), sude, depth);
		auto futLic = std::async(paraFourier, n/2, primit.power(2), liche, depth);
		sude = futSud.get(); liche = futLic.get();
	}

	//vysledky rekurze 
	for (int i = 0; i <= n/2 -1; i++)
	{
		complex pwO(primit.power(i));
		p.at(i) = sude.at(i) + pwO*  liche.at(i);
		p.at(i+n/2) = sude.at(i) - pwO*  liche.at(i);
	}

	//vracime odkazem a bez kopirovani
	return p;	
}



polynom & polynom::operator *= (const polynom & l) 
{
	polynom grafL(l);

	//srovname velikost do takove vhodne pro nasobeni
	srovnejVelikost(grafL);

	//zmenime reprezentace grafu z koeficientu na grafy
	grafL = preFourier(grafL); 
	*this=preFourier(*this);

	//vytvorim si polynom na zapsani vysledku nasobeni
	polynom grafVysl(grafL.velikost(), graf);

	//maly bug-catcher
	if (grafL.velikost() != velikost() || grafL.velikost() != grafVysl.velikost() ) std::cerr << "spatne srovnane velikosti grafu \n" ;
	
	//samotne nasobeni
	for (int i = 0; i < grafVysl.velikost(); i++)
	{
		grafVysl.at(i) = grafL.at(i) * at(i);
	}

	//vratime vysledny polynom, ale az po pruchodu inverzni FFT
	*this = preFourier(grafVysl);
	return *this;
}

//================================================== Pomocne funkce ====================================================

//srovna velikosti reprezentaci polynomu
void polynom::srovnejVelikost(polynom & p)
{
	std::size_t cil(p.velikost() + velikost());

	//reprezentace polynomu doplnim nulami na pozadovanou velikost
	p.velikostNaMocninu(cil);
	velikostNaMocninu(cil);
}

//zajisti, ze velikost polynomu bude mocnina dvojky, horni koeficienty doplni nulami
void polynom::velikostNaMocninu(size_t cil)
{
	int n(2);

	while (cil > n)
	{
		n *=2;
	}

	doplnNuly(n);
}

//doplni zvrchu nuly do cilove velikosti
void polynom::doplnNuly(int cil)
{
	int rozdil(cil - velikost());
	for (int i = 0; i < rozdil; i++)
	{
		repre.push_back(0);
	}
}

//vrati prvek reprezentace na miste indexovane cislem v parametru
complex & polynom::at(size_t ind)
{	
	if (ind > velikost() - 1)
	{
		throw std::runtime_error("Range error");
	}
	else return repre.at(ind);
}

const complex & polynom::at(size_t ind) const
{
	if (ind > velikost() - 1)
	{
		throw std::runtime_error("Range error");
	}
	else return repre.at(ind);
}

//vybere z polynomu pouze ty prvky, jejich indexy z reprezentaci maji zbytek po deleni dvema stejny jako parametr
polynom polynom::vyber(int zbytek)
{
	std::vector<complex> temp;
	for (int i = zbytek; i < velikost(); i += 2)
	{
		temp.push_back(at(i));
	}

	return polynom(temp, tvar);
}

//zmeni tvar polynomu
void polynom::zmenTvar()
{
	if (tvar == graf) tvar = koef;
	else tvar = graf;	
}

const Tvar polynom::vratTvar() const
{
	return tvar;
}

polynom & polynom::operator*= (const double & x)
{
	for (int i = 0; i < repre.size(); i++)
	{
		at(i) *= x;
	}

	return *this;
}

polynom operator * (const polynom & l, const polynom & p)
{
	polynom n(l);
	n *= p;
	return n;
}

std::ostream & operator << (std::ostream & ostr, polynom & p)
{
	const complex nula(0,0); 
	while (p.at(p.velikost()-1) == nula && p.velikost() > 1 && p.vratTvar() == koef)
	{
		p.repre.pop_back();
	}

	ostr.setf(std::ios::fixed);
	//ostr.setf(std::ios::showpoint);
	ostr.precision(2);

	size_t size(p.velikost());
	if (p.vratTvar() == koef)
	{
		for (int i = size-1; i >0; --i)
		{
			ostr << p.at(i)<< " * x^" << i << " + ";
		}
		ostr << p.at(0)<< " * x^" << 0;
	}
	else
	{
		for (int i = 0; i < size-1; i++)
		{
			ostr << "P(w^" << i << ") = " << p.at(i) << " ; ";
		}

		ostr << "P(w^" << size-1 << ") = " << p.at(size-1);

	}
	ostr << std::endl;
	return ostr;
}

void polynom::prohod()
{
	for (int i = 0; i < velikost(); i++)
		{			
			at(i).swap();
		}
}


