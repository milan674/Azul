
#ifndef KORONG
#define KORONG

#include<iostream>
using namespace std;

struct korong
{
	int korong_sorszam; //korong sorszama    /*A korongokon l�v� csemp�ket t�rolja 4-elem� karaktert�mb�kben!*/
	char korongon_levo[4]; //korongon l�v� csemp�k karaktert�mbje
};

korong* korong_lefoglal(int n);


#endif
