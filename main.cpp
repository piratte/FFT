#include "complex.h"
#include "polynom.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>


using namespace std;

void Nacti(polynom & x, polynom & y, string);

int main( int argc, char ** argv)
{
	/*
	polynom x(0,koef), y(0,koef); string s;
	if (argc > 1) s = argv[1];
	Nacti(x, y, s);
	polynom vysledek = x*y;
	//cout <<"   "<< x << " * " << y ;
	cout << vysledek << endl; 
	return 0; */
	
	



	vector<complex> a, b;

	//vytvoreni si nejakych defaultnich polynomu
	//a.push_back(0); a.push_back(complex(1,1)); a.push_back(complex(1,2)); a.push_back(complex(1,3)); a.push_back(complex(1,4)); a.push_back(complex(1,5)); a.push_back(complex(1,6)); 
	/*a.push_back(0); a.push_back(0); a.push_back(1); 
	b.push_back(0); b.push_back(1); b.push_back(0); b.push_back(0); */
	a.push_back(1); a.push_back(-1); a.push_back(1); a.push_back(-1); a.push_back(1); a.push_back(-1); a.push_back(1); a.push_back(-1); 
	b.push_back(0); b.push_back(1); b.push_back(0); b.push_back(1); b.push_back(0); b.push_back(1); b.push_back(0); b.push_back(1); 
	cout << preFourier(polynom(a,koef)) << "  " << preFourier(polynom(b,koef));
	
	

	/* TEST KOMUINIKATIVITY AT()
	cout << x.at(5) << endl;
	x.at(5) = complex();
	cout << x.at(5);  */

	/* TEST MOCNENI COMPLEXU
	complex neco(0.5,0);
	cout << neco.power(3); */

	/*TEST SPRAVNE FUNKCE VYBIRANI FOURIERA
	cout << x.vyber(1); cout << x.vyber(0); */

	/* TEST SPRAVNEHO NASOBENI COMPLEXU 
	cout << a.at(1) * a.at(2) << " ... " << a.at(0) * a.at(3) << " ... " << a.at(3) * a.at(6); */

	//TEST SPRAVNEHO POCITANI FOURIERA
	//cout << y << preFourier(y) <<  preFourier(preFourier(y));

	
	
}

void Nacti(polynom & x, polynom & y, string s)
{
	string soub;
	if (s.empty()) {		
		cout << "Insert path to source file:" << endl;
		cin >> soub;	
	}
	else soub = string(s);
	
	ifstream vstup(soub);

	if (! vstup.good())
	{
		cerr << "File failed" << endl;
	}
	
	vector<complex> a, b; string radek;

	int radekX, radekY;
	vstup >> radekX; getline(vstup, radek);
	for (int i = 0; i < radekX; i++)
	{
		getline(vstup, radek);
		a.push_back(Read(radek));
	}
	vstup >> radekY; getline(vstup, radek);
	for (int i = 0; i < radekY; i++)
	{
		getline(vstup, radek);
		b.push_back(Read(radek));
	}

	x = polynom(a,koef), y = polynom(b,koef);

}