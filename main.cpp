#include <iostream>
#include <cstdlib>
#include <ctime>
#include "game.h" // a game.h includeolja már a player.h-t az pedig a masik 2-t


struct pontok // a helyezesek megallapitasanal hasznalom majd
{
	int pontok;
	int sorszam;
	int teljes = 0;
};

using namespace std;

int main() {
	srand(time(0));
	bool osszes_korong_ures = true; bool jatek_vege = false; bool egyenlo = false;

	Game* jatekmutato = new Game;
	if (jatekmutato == NULL) {
		cerr << "memoriafoglalasi hiba \n";
		exit(1); // program kilépési kódját állítja be egyre  --> kell hozza a #include <cstdlib>  header
	}

	while (cout << "Add meg a jatekosok szamat!\n" && !(std::cin >> jatekmutato->resztvevo_szam)) {
		cin.clear(); //clear bad input flag
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		cout << "Nem egesz szamot adtal meg, adj meg egy egeszet 2-4 kozott!\n";
	}

	while (jatekmutato->resztvevo_szam < 2 or jatekmutato->resztvevo_szam>4) {
		while (cout << "2,3 vagy 4 jatekos jatszhat! add meg ujra a jatekosok szamat!\n" && !(std::cin >> jatekmutato->resztvevo_szam)) {
			cin.clear();
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << "Nem egesz szamot adtal meg, adj meg egy egeszet 2-4 kozott!\n";
		}
	}

	Player* jatekosok_cime = new Player[jatekmutato->resztvevo_szam];
	jatekosok_cime = jatekos_hely_foglalas(jatekmutato->resztvevo_szam);

	if (jatekmutato->resztvevo_szam == 2) {
		jatekmutato->korongok_szama = 5;
	}
	else if (jatekmutato->resztvevo_szam == 3) {
		jatekmutato->korongok_szama = 7;
	}
	else if (jatekmutato->resztvevo_szam == 4) {
		jatekmutato->korongok_szama = 9;
	}
	for (int i = 0; i < jatekmutato->korongok_szama; i++) {
		jatekmutato->korongon_levo[i] = 4;
	}

	jatekmutato->tomb_mutato = korong_lefoglal(jatekmutato->resztvevo_szam); //lefoglalja annyi korongot, amennyi kell, a jatekosok szama miatt  // KELL

	for (int i = 0; i < 5; i++) {
		jatekmutato->zsak[i] = 20;
		jatekmutato->asztalkozepe[i] = 0; //beallitja az asztalkozepe elso 5 cellajat 0-ra
		jatekmutato->dobott_csempek[i] = 0; // beallitja az eldobott csempek szamat 0-ra
	}
	jatekmutato->asztalkozepe[5] = 1; //asztalkozepen van egy db kezdojatekos token

	for (int n = 0; n < 50; n++) { // fordulók 
		if ((jatekmutato->zsak[0] + jatekmutato->zsak[1] + jatekmutato->zsak[2] + jatekmutato->zsak[3] + jatekmutato->zsak[4]) < jatekmutato->korongok_szama * 4) {
			for (int j = 0; j < 5; j++) {
				jatekmutato->zsak[j] = jatekmutato->zsak[j] + jatekmutato->dobott_csempek[j];
				jatekmutato->dobott_csempek[j] = 0; // beallitja az eldobott csempek szamat 0-ra
			}

			egy_fordulo(jatekmutato, jatekosok_cime);
			for (int k = 0; k < jatekmutato->resztvevo_szam; k++) {
				jatekmutato->aktualis_jatekos = k;
				jatek_vege = jatekvege(jatekosok_cime, jatekmutato);
				if (jatek_vege == true) {
					break;
				}
			}
			if (jatek_vege == true) {
				cout << "a jateknak vege, pontszamitas jon!\n" << endl;
				break;
			}
		}
		else {
			egy_fordulo(jatekmutato, jatekosok_cime);
			for (int k = 0; k < jatekmutato->resztvevo_szam; k++) {
				jatekmutato->aktualis_jatekos = k;
				jatek_vege = jatekvege(jatekosok_cime, jatekmutato);
				if (jatek_vege == true) {
					break;
				}
			}
			if (jatek_vege == true) {
				cout << "a jateknak vege, pontszamitas jon!\n" << endl;
				break;
			}
		}
	}
	// pontszamitas
	for (int i = 0; i < jatekmutato->resztvevo_szam; i++) {
		cout << i + 1 << ". jatekos pontszamitasa:\n" << endl;
		cout << i + 1 << ". jatekos pontjai a bonuszok nelkul: " << jatekosok_cime[i].pontszam << endl;
		bonuszpontok(jatekosok_cime + i);
		cout << i + 1 << ". jatekos pontjai a bonuszok utan: " << jatekosok_cime[i].pontszam << endl;
		cout << i + 1 << ". jatekos teljes sorai: " << jatekosok_cime[i].teljes_sorok_szama << endl;
		cout << endl << endl;
	}

	pontok* sorrend = new pontok[jatekmutato->resztvevo_szam];

	for (int i = 0; i < jatekmutato->resztvevo_szam; i++) {
		sorrend[i].sorszam = i;
		sorrend[i].pontok = jatekosok_cime[i].pontszam;
		sorrend[i].teljes = jatekosok_cime->teljes_sorok_szama;
	}


	int csere = 0;
	for (int i = 0; i < jatekmutato->resztvevo_szam - 1; i++) {
		for (int j = i + 1; j < jatekmutato->resztvevo_szam; j++) {
			if (sorrend[i].pontok < sorrend[j].pontok){
					csere = sorrend[i].pontok;
					sorrend[i].pontok = sorrend[j].pontok;
					sorrend[j].pontok = csere;
					csere = sorrend[i].sorszam;
					sorrend[i].sorszam = sorrend[j].sorszam;
					sorrend[j].sorszam = csere;
		}
			if (sorrend[i].pontok == sorrend[j].pontok) {
				if (sorrend[i].teljes < sorrend[j].teljes) {
					csere = sorrend[i].pontok;
					sorrend[i].pontok = sorrend[j].pontok;
					sorrend[j].pontok = csere;
					csere = sorrend[i].sorszam;
					sorrend[i].sorszam = sorrend[j].sorszam;
					sorrend[j].sorszam = csere;
				}
			}
	}
}

	if (sorrend[0].pontok == sorrend[1].pontok) {
		if (sorrend[0].teljes == sorrend[1].teljes) {
			cout << "Egyenloseg alakult ki az elso helyen!\n";
		}
	}
	else {
		for (int i = 0; i < jatekmutato->resztvevo_szam; i++) {
			cout << "A(z) " << sorrend[i].sorszam + 1 << ". jatekos helyezese:" << i + 1 <<"\t Pontszama: "<<sorrend[i].pontok<< endl;
		}
	}

	delete[] sorrend;
	delete[] jatekosok_cime;
	delete[] jatekmutato->tomb_mutato;
	delete jatekmutato;
	return 0;
}