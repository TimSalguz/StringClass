#include <iostream>
#include <random>
#include <time.h>
#include <algorithm>
#include <math.h>
#include <chrono>
#include <fstream>

#include "functions.hpp"
#include "classes.hpp"

using namespace std::chrono_literals;

int main()
{
	std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");

	std::cout << "Hello, world!" << std::endl;
	fout << "Hello, world!";

    return 0;
}