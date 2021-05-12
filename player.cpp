#include "player.h"

void tabla_init(Player* p, int n) { // elkesziti a falat, mintasort, padlovonalat minden jatekosnak 
	for (int i = 0; i < n; i++) {
		p[i].pontszam = 0;
		for (int k = 0; k < 5; k++) {
			for (int j = 0; j < 5; j++) {
				p[i].tabla.fal[k][j] = '.';// init fal
				if (k == 0) {
					if (j == 0) {
						p[i].tabla.mintasor[k][j] = '_'; //init mintasor
					}
					else {
						p[i].tabla.mintasor[k][j] = ' ';
					}
				}
				else if (k == 1) {
					if ((j == 0) or (j == 1)) {
						p[i].tabla.mintasor[k][j] = '_';
					}
					else {
						p[i].tabla.mintasor[k][j] = ' ';
					}
				}
				else if (k == 2) {
					if (j == 0 or j == 1 or j == 2) {
						p[i].tabla.mintasor[k][j] = '_';
					}
					else {
						p[i].tabla.mintasor[k][j] = ' ';
					}
				}
				else if (k == 3) {
					if (j == 0 or j == 1 or j == 2 or j == 3) {
						p[i].tabla.mintasor[k][j] = '_';
					}
					else {
						p[i].tabla.mintasor[k][j] = ' ';
					}
				}
				else if (k == 4) {
					if (j == 0 or j == 1 or j == 2 or j == 3 or j == 4) {
						p[i].tabla.mintasor[k][j] = '_';
					}
					else {
						p[i].tabla.mintasor[k][j] = ' ';
					}
				}
			}
		}
		for (int k = 0; k < 7; k++) {
			cout << " ";
			p[i].tabla.padlovonal[k] = '_';
		}
		cout << endl;
	}
}

Player* jatekos_hely_foglalas(int n) {  // lefoglal annyi helyet, amennyi jatekos van
	Player* p = 0;
	if (n == 2) {
		p = new Player[2];
		tabla_init(p, n);
	}

	else if (n == 3) {
		p = new Player[3];
		tabla_init(p, n);
	}

	else if (n == 4) {
		p = new Player[4];
		tabla_init(p, n);
	}
	return p;
}

void player_megjelenit(Player* player, int jatekos_szam) { // megjeleniti a jatekosot tablait, pontjait
	for (int i = 0; i < jatekos_szam; i++) {
		cout << i + 1 << ". jatekos tablai: " << endl;
		cout << "12345   Pontok: " << player[i].pontszam << endl;
		for (int k = 0; k < 5; k++) {
			for (int j = 0; j < 5; j++) {
				cout << player[i].tabla.fal[k][j];
			}
			cout << k + 1 << " ";
			for (int g = 0; g < 5; g++) {
				cout << player[i].tabla.mintasor[k][g];
			}
			cout << endl;
		}
		cout << " ";
		for (int k = 0; k < 7; k++) {
			cout << player[i].tabla.padlovonal[k] << "  ";
		}
		cout << endl;
		for (int k = 0; k < 7; k++) {
			cout << player[i].tabla.padlovonal_ertekek[k] << " ";
		}
		cout << endl << endl;
	}

}

bool AktualisSorUresE(Player* player, int sorszam) { // megnezi, hogy a mintasor ures e
	bool ures = true;
	for (int i = 0; i < sorszam; i++) {
		if (player->tabla.mintasor[sorszam - 1][i] != '_') {
			ures = false;
		}
		else {
			ures = true;
			break;
		}
	}
	return ures;
}

bool MintasorTelevanE_Tombbel(Player* player, int mintaSorszama) {  // mintasor tele van mar? , tombot hasznalja
	bool televan = false;
	if (player->tabla.mintasor_ures[mintaSorszama] != mintaSorszama) {
		televan = false; // NINCS TELE
	}
	else {
		televan = true;
	}
	return televan;
}

bool MintasorTelevanE(Player* player, int mintaSorszama/*Game* game*/) { // mintasor tele van mar? , siman megnezi a mintasor utolso elemet
	bool televan = false;
	//for (int i = 0; i < mintaSorszama; i++) {
	if (player->tabla.mintasor[mintaSorszama - 1][mintaSorszama - 1] == '_' || player->tabla.mintasor[mintaSorszama - 1][mintaSorszama - 1] == ' ') {
		televan = false; // NINCS TELE
	}
	else {
		televan = true;
	}
	return televan;
}

int PadlovonalonEnnyivan(Player* player) { // visszaadja a padlovonal elso ures helyenek indexet
	int uresTombkezdoIndex = 0;
	for (int i = 0; i < 7; i++) {
		if (player->tabla.padlovonal[i] == '_' or player->tabla.padlovonal[i] == ' ') {
			uresTombkezdoIndex = i;
			break;
		}
		else {
			continue;
		}
	}
	return uresTombkezdoIndex;
}

bool PaldlovonalonVanE(Player* player) { // padlovonal ures e?
	bool van = false;
	if (player->tabla.padlovonal[0] != '_') {
		van = true;
	}
	return van;
}

bool PadloVonalTelevanE(Player* player) { // padlovonal tele van ?
	bool televan = false;
	if (player->tabla.padlovonal[6] == '_' || player->tabla.padlovonal[6] == ' ') {
		televan = false;
	}
	else {
		televan = true;
	}

	return televan;
}

bool van_ilyen_szin_a_fal_soraban(char karakter, int mintaSorszam, Player* player) { //megnezi,hogy a megadott mintasorral egy sorban lévõ csempéket a falon
	bool van = false;
	for (int i = 0; i < 5; i++) {
		if (player->tabla.fal[mintaSorszam][i] == karakter) {
			van = true;
			break;
		}
		else {
			continue;
		}
	}
	return van;
}

void  Pontok_hozzaadasa(Player* player, int sor, int oszlop) {//Pontok hozzáadása a csempék falra helyezése közben
	bool fuggoleges = false;
	bool vizszintes = false;
	player->pontszam = player->pontszam + 1;
	// balra vizsgal
	if (player->tabla.fal[sor][oszlop - 1] != '.' and oszlop - 1 < 5 and oszlop - 1 >= 0) {
		player->pontszam = player->pontszam + 1;
		vizszintes = true;
		if (player->tabla.fal[sor][oszlop - 2] != '.' and oszlop - 2 < 5 and oszlop - 2 >= 0) {
			player->pontszam = player->pontszam + 1;
			if (player->tabla.fal[sor][oszlop - 3] != '.' and oszlop - 3 < 5 and oszlop - 3 >= 0) {
				player->pontszam = player->pontszam + 1;
				if (player->tabla.fal[sor][oszlop - 4] != '.' and oszlop - 4 < 5 and oszlop - 4 >= 0) {
					player->pontszam = player->pontszam + 1;
				}
			}
		}
	}
	//jobbra vizsgal
	if (player->tabla.fal[sor][oszlop + 1] != '.' and oszlop + 1 < 5 and oszlop + 1 >= 0) {
		player->pontszam = player->pontszam + 1;
		vizszintes = true;
		if (player->tabla.fal[sor][oszlop + 2] != '.' and oszlop + 2 < 5 and oszlop + 2 >= 0) {
			player->pontszam = player->pontszam + 1;
			if (player->tabla.fal[sor][oszlop + 3] != '.' and oszlop + 3 < 5 and oszlop + 3 >= 0) {
				player->pontszam = player->pontszam + 1;
				if (player->tabla.fal[sor][oszlop + 4] != '.' and oszlop + 4 < 5 and oszlop + 4 >= 0) {
					player->pontszam = player->pontszam + 1;
				}
			}
		}
	}
	//felfele vizsgal
	if (player->tabla.fal[sor - 1][oszlop] != '.' and sor - 1 < 5 and sor - 1 >= 0) {
		player->pontszam = player->pontszam + 1;
		fuggoleges = true;
		if (player->tabla.fal[sor - 2][oszlop] != '.' and sor - 2 < 5 and sor - 2 >= 0) {
			player->pontszam = player->pontszam + 1;
			if (player->tabla.fal[sor - 3][oszlop] != '.' and sor - 3 < 5 and sor - 3 >= 0) {
				player->pontszam = player->pontszam + 1;
				if (player->tabla.fal[sor - 4][oszlop] != '.' and sor - 4 < 5 and sor - 4 >= 0) {
					player->pontszam = player->pontszam + 1;
				}
			}
		}

	}
	//lefele vizsgal
	if (player->tabla.fal[sor + 1][oszlop] != '.' and sor + 1 < 5 and sor + 1 >= 0) {
		player->pontszam = player->pontszam + 1;
		fuggoleges = true;
		if (player->tabla.fal[sor + 2][oszlop] != '.' and sor + 2 < 5 and sor + 2 >= 0) {
			player->pontszam = player->pontszam + 1;
			if (player->tabla.fal[sor + 3][oszlop] != '.' and sor + 3 < 5 and sor + 3 >= 0) {
				player->pontszam = player->pontszam + 1;
				if (player->tabla.fal[sor + 4][oszlop] != '.' and sor + 4 < 5 and sor + 4 >= 0) {
					player->pontszam = player->pontszam + 1;
				}
			}
		}
	}
	if ((fuggoleges == true) and (vizszintes == true)) { // ha mindkét irányban vannak csempek akkor meg egyet hozza  kell adni, mert alapbol eggyel kevesebbet szamolna
		player->pontszam = player->pontszam + 1;
	}
}

bool mintasor_televan(Player* player, int sor) {
	bool tele = false;
	if (player->tabla.mintasor[sor][sor] != '_') {
		tele = true;
	}
	return tele;
}

bool oszlop_tartalmazza_a_betut(Player* jatekos, int sor, int oszlopszam) {
	bool tartalmazza = false;
	for (int j = 0; j < 5; j++) {
		if (jatekos->tabla.fal[j][oszlopszam - 1] == jatekos->tabla.mintasor[sor][0]) {
			tartalmazza = true;
		}
	}
	return tartalmazza;
}


bool VanEszabadLepes(Player* jatekos, char karakter, int mintasor)
{ // mintasor az adott sor, amibõl át akarom rakni a mintasor[0] karaktert
	bool vanszabadlepes = false;  

	for (int i = 0; i < 5; i++) // vízszintesen nézi 
	{
		if (jatekos->tabla.fal[mintasor][i] == '.') // ha talált üres karaktert, akkor annak az oszlopát meg kell nézni
		{
			for (int j = 0; j < 5; j++)
			{
				if (jatekos->tabla.fal[j][i] == karakter) // ha talál ugyanolyan karaktert az oszlopban, akkor false
				{
					vanszabadlepes = false;
					break;
				}
				else if (jatekos->tabla.fal[j][i] == '.') // ha üres helyet talál
				{
					if (j == mintasor) // ha az oszlop j-edik eleme megegyezik a mintasorral
					{
						continue; // folytassa
					}
					else // ha az oszlop j-edik eleme nem egyezik meg a mintasorral
					{
						vanszabadlepes = true;
					}
				}
				else // ha más karaktert talál
				{
					vanszabadlepes = true;
				}
			}
			if (vanszabadlepes == true) {
				break;
			}
			
		}
	}

	return vanszabadlepes;
}


void bonuszpontok(Player* player) {
	int karaktertomb[5] = { 0,0,0,0,0 };// ez tarolja, hogy mennyi van az adott szinbol
	for (int i = 0; i < 5; i++) { // ELLENORIZZUK,  MENNYI VAN AZ ADOTT KARAKTEREKBOL
		for (int j = 0; j < 5; j++) {
			if (player->tabla.fal[i][j] == 'A') {
				karaktertomb[0]++;
			}
			else if (player->tabla.fal[i][j] == 'B') {
				karaktertomb[1]++;
			}
			else if (player->tabla.fal[i][j] == 'C') {
				karaktertomb[2]++;
			}
			else if (player->tabla.fal[i][j] == 'D') {
				karaktertomb[3]++;
			}
			else if (player->tabla.fal[i][j] == 'E') {
				karaktertomb[4]++;
			}
		}
	}

	for (int j = 0; j < 5; j++) {
		if (karaktertomb[j] == 5) {
			cout << "10 Bonuszpont, mert egy szinbol osszejott 5 db!\n" << endl;
			player->pontszam = player->pontszam + 10;
		}
	}

	// sorok ellenorzese
	for (int i = 0; i < 5; i++) {
		if (player->tabla.fal[i][0] != '.' and player->tabla.fal[i][1] != '.' and player->tabla.fal[i][2] != '.' and player->tabla.fal[i][3] != '.' and player->tabla.fal[i][4] != '.') {
			cout << "Egy sor teljes, +2 bonuszpont!\n" << endl;
			player->pontszam = player->pontszam + 2;
			player->teljes_sorok_szama++;
		}
	}

	//oszlopok ellenorzese
	for (int i = 0; i < 5; i++) {
		if (player->tabla.fal[0][i] != '.' and player->tabla.fal[1][i] != '.' and player->tabla.fal[2][i] != '.' and player->tabla.fal[3][i] != '.' and player->tabla.fal[4][i] != '.') {
			cout << "egy oszlop teljes, plusz 7 bonuszpont!\n" << endl;
			player->pontszam = player->pontszam + 7;
		}

	}
}

