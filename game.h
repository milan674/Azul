#ifndef GAME
#define GAME

#include<iostream>
#include "player.h" // a player.h includeolja már a korong.h-t és a tabla.h-t


using namespace std;

struct Game
{
	int korongok_szama;
	int korongon_levo[9] = { 0,0,0,0,0,0,0,0,0 }; // korongokon ennyi csempe van, vagy 0 vagy 4
	int asztalkozepe[6] = { 0,0,0,0,0,1 };// Az asztal közepén lévõ csempék eltárolható a darabszámok tömbjeként, a kezdõjátékos jelzõ miatt eggyel több elemre van szükség.
	int asztalkozepe_db = 0;  // asztalkozepen ennyi csempe van 
	int zsak[5];
	int dobott_csempek[5];
	korong* tomb_mutato;
	bool fordulovege = false;
	bool jatekvege = false;
	int resztvevo_szam;
	int aktualis_jatekos = 0;
	int KoviX = -1; // ez fogja tárolni a következõ játékos indexét
};


char kihuz(Game jatek);
bool korongok_uresek_e(Game jatek, bool valtozo);
Game korongfeltolt(Game jatek);
int KovetkezoPlayerKivalasztasa(int jelenlegi_index, Game* jatekmutato);
void PadlovonalraHelyezes(Game* game, Player* player, char karakter, int szinCounter);
int mintasor_bekeres();
void mintasorba_helyez(Game* game, Player* player, char karakter, int szinCounter);
void korong_esete(Player* jatekos, Game* jatekmutato, int korong_sorszam);
void asztalkozepe_esete(Player* jatekos, Game* jatekmutato, int korong_sorszam);
bool fordulo_vege_v02(Game* jatek);
bool fordulo_vege(Game* jatek);
void csempe_valasztas(Player* jatekos, Game* jatekmutato);
void PadlovonalTörlése(Player* player, Game* game);
void csempe_falra_helyezese(Player* jatekos, Game* jatek);
void megjelenit(Game game);
bool jatekvege(Player* jatekos, Game* jatek);
void egy_fordulo(Game* jatekmutato, Player* jatekos);

#endif




