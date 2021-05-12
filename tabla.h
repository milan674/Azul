
#ifndef TABLA
#define TABLA

#include<iostream>
using namespace std;

struct tabla {
	char fal[5][5];
	char mintasor[5][5];
	char padlovonal[7];
	const int padlovonal_ertekek[7] = { -1,-1,-2,-2,-2,-3,-3 };
	bool padlovonalTele = false;
	int mintasor_ures[6] = { {0},{0},{0},{0},{0},{0} }; // 0. a padlo
};




#endif