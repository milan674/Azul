#ifndef PLAYER
#define PLAYER

#include<iostream>
#include "tabla.h"
#include "korong.h"
using namespace std;

struct Player
{
	tabla tabla;
	int pontszam = 0;
	int teljes_sorok_szama = 0;
};

void tabla_init(Player* p, int n);
Player* jatekos_hely_foglalas(int n);
void player_megjelenit(Player* player, int jatekos_szam);
bool AktualisSorUresE(Player* player, int sorszam);
bool MintasorTelevanE_Tombbel(Player* player, int mintaSorszama);
bool MintasorTelevanE(Player* player, int mintaSorszama);
int PadlovonalonEnnyivan(Player* player);
bool PaldlovonalonVanE(Player* player);
bool PadloVonalTelevanE(Player* player);
bool van_ilyen_szin_a_fal_soraban(char karakter, int mintaSorszam, Player* player);
void  Pontok_hozzaadasa(Player* player, int sor, int oszlop);
bool mintasor_televan(Player* player, int sor);
bool oszlop_tartalmazza_a_betut(Player* jatekos, int sor, int oszlopszam);
bool VanEszabadLepes(Player* jatekos, char karakter, int mintasor);
void bonuszpontok(Player* player);



#endif

