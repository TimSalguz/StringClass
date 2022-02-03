#include <iostream>
#include <random>
#include <time.h>
#include <algorithm>
#include <math.h>
#include <chrono>
#include <fstream>

#include "functions/functions.cpp"
#include "classes/classes.cpp"

using namespace std::chrono_literals;

int main()
{
	std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");
	
	ts::var Peremennaya21;


	ts::var Peremennaya2;
	Peremennaya21.Add('1');
	Peremennaya21.Add('0');
	Peremennaya21.Add('4');
	Peremennaya21.Add(',');
	Peremennaya21.Add('0');
	Peremennaya21.Add('0');
	Peremennaya21.Add('0');
	Peremennaya21.Add('0');
	Peremennaya21.Add('2');
	Peremennaya21.Add('0');
	Peremennaya21.Add('0');
	Peremennaya21.Add('0');
	Peremennaya21.Add('1');


	std::cout << "IsNumber " << Peremennaya21.IsNumber() <<std::endl;
	std::cout << "SearchZero: " << Peremennaya21.SearchZero() << std::endl;
	std::cout << "Size: " << Peremennaya21.Size() << std::endl;

	std::cout << "Size: " << Peremennaya21.Size() << std::endl;
	
	Peremennaya2.Add('1');
	Peremennaya2.Add('0');
	Peremennaya2.Add('0');
	Peremennaya2.Add(',');
	Peremennaya2.Add('0');
	Peremennaya2.Add('0');
	Peremennaya2.Add('1');
	Peremennaya2.Add('0');
	Peremennaya2.Add('0');
	Peremennaya2.Add('8');
	Peremennaya2.Add('0');
	Peremennaya2.Add('9');

	//Peremennaya2.Add('1');
	//Peremennaya2.Add('2');

	//Peremennaya21.FormatNumberString(Peremennaya2);
	//Peremennaya21.ReduceBeginBy(1);
	//Peremennaya2.ReduceBeginBy(1);

	//Peremennaya21.FormatNumberString(Peremennaya2);

	std::cout << "Point: " << Peremennaya21.SearchPoint() << std::endl;
	std::cout << "ZERO: " << Peremennaya21.SearchZero() << std::endl;

	Peremennaya21.Sum(Peremennaya2);
	std::cout << "Razmer massiva" << Peremennaya21.Size() << std::endl;

	for (int i = 0; i < Peremennaya21.Size(); i++)
	{
		fout << Peremennaya21.Get(i);
	}

	fout << std::endl;

	int Boool = 0;
	std::cout << Boool <<std::endl;
	Boool +=1;
	std::cout << Boool <<std::endl;
	Boool = Boool+1;
	std::cout << Boool <<std::endl;



	std::cout << "COMPLETE" << std::endl;

    return 0;
}