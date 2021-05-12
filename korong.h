
#ifndef KORONG
#define KORONG

#include<iostream>
using namespace std;

struct korong
{
	int korong_sorszam; //korong sorszama    /*A korongokon lévõ csempéket tárolja 4-elemû karaktertömbökben!*/
	char korongon_levo[4]; //korongon lévõ csempék karaktertömbje
};

korong* korong_lefoglal(int n);


#endif
