#include "game.h"

char kihuz(Game jatek) {  // kihuzza a csempeket a zsakbol
	char kihuzott;

	int random = 0;
	int osszes = 0;   // ez lesz a zsakban levo csempek db-szama

	for (int i = 0; i < 5; i++) {
		osszes += jatek.zsak[i];
	}
	random = rand() % osszes + 1;
	if (random <= jatek.zsak[0]) { kihuzott = 'A'; }
	else if (random > jatek.zsak[0] and random <= jatek.zsak[0] + jatek.zsak[1]) { kihuzott = 'B'; }
	else if (random > jatek.zsak[0] + jatek.zsak[1] and random <= jatek.zsak[0] + jatek.zsak[1] + jatek.zsak[2]) { kihuzott = 'C'; }
	else if (random > jatek.zsak[0] + jatek.zsak[1] + jatek.zsak[2] and random <= jatek.zsak[0] + jatek.zsak[1] + jatek.zsak[2] + jatek.zsak[3]) { kihuzott = 'D'; }
	else if (random > jatek.zsak[0] + jatek.zsak[1] + jatek.zsak[2] + jatek.zsak[3]) { kihuzott = 'E'; }

	return kihuzott;
}

bool korongok_uresek_e(Game jatek, bool valtozo) {
	for (int i = 0; i < jatek.korongok_szama; i++) { //megnezem, hogy a korong teljesen ures e, mert csak akkor kell feltolteni
		if (jatek.tomb_mutato[i].korongon_levo[0] == '_' and jatek.tomb_mutato[i].korongon_levo[1] == '_' and jatek.tomb_mutato[i].korongon_levo[2] == '_' and jatek.tomb_mutato[i].korongon_levo[3] == '_') {
			valtozo = true;
		}
	}
	return valtozo;
}

Game korongfeltolt(Game jatek) {  // korongot feltolti csempevel
	for (int i = 0; i < jatek.korongok_szama; i++)
	{
		//cout << i << ".korong: " << endl;
		for (int j = 0; j < 4; j++)
		{
			jatek.tomb_mutato[i].korongon_levo[j] = kihuz(jatek);
			if (jatek.tomb_mutato[i].korongon_levo[j] == 'A') jatek.zsak[0] = jatek.zsak[0] - 1;
			else if (jatek.tomb_mutato[i].korongon_levo[j] == 'B') jatek.zsak[1] = jatek.zsak[1] - 1;
			else if (jatek.tomb_mutato[i].korongon_levo[j] == 'C') jatek.zsak[2] = jatek.zsak[2] - 1;
			else if (jatek.tomb_mutato[i].korongon_levo[j] == 'D') jatek.zsak[3] = jatek.zsak[3] - 1;
			else if (jatek.tomb_mutato[i].korongon_levo[j] == 'E') jatek.zsak[4] = jatek.zsak[4] - 1;
		}
		for (int j = 0; j < jatek.korongok_szama; j++) {
			jatek.korongon_levo[j] = 4;
		}
	}
	return jatek;
}

int KovetkezoPlayerKivalasztasa(int jelenlegi_index, Game* jatekmutato) // visszaadja, a kovetkezo jatekos indexet
{
	int Kovetkezo_player_index = (jelenlegi_index + 1) % jatekmutato->resztvevo_szam;

	return Kovetkezo_player_index;
}

void PadlovonalraHelyezes(Game* game, Player* player, char karakter, int szinCounter) { //padlora helyez
	int uresTombkezdoIndex = -1;
	int aktualis_jatekos = game->aktualis_jatekos;
	int padlovonalonennyivan = 0;
	padlovonalonennyivan = PadlovonalonEnnyivan(player + aktualis_jatekos);
	if (PadloVonalTelevanE(player + aktualis_jatekos) == true) { //tele van a padlovonal
		cout << "tele van a padlovonal, a csempek eldobasra kerulnek!\n";
		if (karakter == 'A') { game->dobott_csempek[0] = game->dobott_csempek[0] + szinCounter; }
		else if (karakter == 'B') { game->dobott_csempek[1] = game->dobott_csempek[1] + szinCounter; }
		else if (karakter == 'C') { game->dobott_csempek[2] = game->dobott_csempek[2] + szinCounter; }
		else if (karakter == 'D') { game->dobott_csempek[3] = game->dobott_csempek[3] + szinCounter; }
		else if (karakter == 'E') { game->dobott_csempek[4] = game->dobott_csempek[4] + szinCounter; }
	}
	else { // nincs tele a padlovonal
		for (int i = 0; i < 7; i++) {
			if (player[aktualis_jatekos].tabla.padlovonal[i] == '_' or player[aktualis_jatekos].tabla.padlovonal[i] == ' ') {
				uresTombkezdoIndex = i;
				player[aktualis_jatekos].tabla.padlovonalTele = false;
				break;
			}
			else {
				player[aktualis_jatekos].tabla.padlovonalTele = true;
				continue;
			}
		}
		int szabadhelyekszama = 0;

		if (uresTombkezdoIndex + szinCounter > 7) {
			cout << " nem fer ra minden csempe a padlovonalra, ami nem fer ra, eldobasra kerul!\n";
			szabadhelyekszama = 7 - uresTombkezdoIndex;
			for (int i = 0; i < szabadhelyekszama; i++) //annyiszor fut le, amennyi meg rafer
			{

				player[aktualis_jatekos].tabla.mintasor_ures[0] = i + uresTombkezdoIndex;
				player[aktualis_jatekos].tabla.padlovonal[i + uresTombkezdoIndex] = karakter;
				szinCounter--;
			}
			// maradek eldobasa

			if (karakter == 'A') { game->dobott_csempek[0] = game->dobott_csempek[0] + szinCounter; }
			else if (karakter == 'B') { game->dobott_csempek[1] = game->dobott_csempek[1] + szinCounter; }
			else if (karakter == 'C') { game->dobott_csempek[2] = game->dobott_csempek[2] + szinCounter; }
			else if (karakter == 'D') { game->dobott_csempek[3] = game->dobott_csempek[3] + szinCounter; }
			else if (karakter == 'E') { game->dobott_csempek[4] = game->dobott_csempek[4] + szinCounter; }

		}
		else {
			for (int i = 0; i < szinCounter; i++) {
				player[aktualis_jatekos].tabla.mintasor_ures[0] = i + uresTombkezdoIndex;
				player[aktualis_jatekos].tabla.padlovonal[i + uresTombkezdoIndex] = karakter;
			}
		}
	}
}

int mintasor_bekeres() {
	int mintasorSzam;
	while (cout << "Melyik mintasorba tegyem a valasztott csempet? 0: az osszes csempe a padlora kerul!\n" && !(std::cin >> mintasorSzam)) { //EZ CSAK SZÁMOT FOGAD EL
		std::cin.clear(); //clear bad input flag
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
		std::cout << "Nem egesz szamot adtal meg, adj meg egy egeszet 0-5 kozott!\n";
	}
	//mintasor ellenorzese egy kulon fgv-el
	while (mintasorSzam < 0 or mintasorSzam>5) {
		while (cout << "Helytelen adat, add meg ujra a mintasor sorszamat!\n" && !(std::cin >> mintasorSzam)) { // EZ CSAK 0-5 KÖZÖTTI SZÁMOT FOGAD EL
			std::cin.clear(); //clear bad input flag
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
			std::cout << "Rossz szamot adtal meg, adj meg egy egeszet 0-5 kozott!\n";
		}
	}
	return mintasorSzam;
}

void mintasorba_helyez(Game* game, Player* player, char karakter, int szinCounter) {
	int aktualis_jatekos = game->aktualis_jatekos; //at kell adni, hogy hanyadik jatekos van, mert a cimzesnel fontos
	int uresTombIndex = -1; // üres helyek keresésénél lesz fontos
	bool nemjo = false; bool mintaSorTeleVan = false;
	bool van_ilyen_szin = false;
	int mintasorSzam = 0;
	mintasorSzam = mintasor_bekeres(); // ez tárolja a választott mintasor szamat

	if (mintasorSzam == 0) { //ha a mintasorszam 0, akkor a padlora dobja
		PadlovonalraHelyezes(game, player, karakter, szinCounter);
	}
	else { //mintasorba helyez
		while (van_ilyen_szin_a_fal_soraban(karakter, mintasorSzam - 1, &player[aktualis_jatekos]) == true) //meg kell nezni, hogy a fal azonos soraban van e mar ilyen karakter
		{
			cout << endl;
			cout << "Ebbe a sorba nem teheted, mert mar van a fal azonos soraban ilyen karakter!" << endl;
			aktualis_jatekos = game->aktualis_jatekos;  // NEM LEHET =0, MERT AKKOR MINDIG AZ ELSO JATEKOST NEZI
			mintasorSzam = mintasor_bekeres();
		}
		aktualis_jatekos = game->aktualis_jatekos;
		while (MintasorTelevanE(&player[aktualis_jatekos], mintasorSzam) == true) // meg kell vizsgalni, hogy a sor tele van e
		{
			cout << endl;
			cout << "a mintasor mar tele van, adj meg egy uj mintasort!\n";
			aktualis_jatekos = game->aktualis_jatekos; 
			mintasorSzam = mintasor_bekeres();
		}

		if (MintasorTelevanE(&player[aktualis_jatekos], mintasorSzam) == false) { // tehat nincs tele
			//megvizsgalni,hogy a valasztott sor hosszusaga kevesebb, vagy egyenlo a valasztot szin mennyisegevel 
			if (szinCounter <= mintasorSzam) {
				//megvizsgalni, hogy az adott soron ugyanaz a szin talalhato e
				if (karakter == player[aktualis_jatekos].tabla.mintasor[mintasorSzam - 1][0] || player[aktualis_jatekos].tabla.mintasor[mintasorSzam - 1][0] == '_') {
					//meg kell szamolni, hogy mennyi van mar a sorban ebbol a szinbol
					for (int i = 0; i < mintasorSzam; i++) {
						if (player[aktualis_jatekos].tabla.mintasor[mintasorSzam - 1][i] == '_' or player[aktualis_jatekos].tabla.mintasor[mintasorSzam - 1][i] == ' ') {
							uresTombIndex = i;
							break;
						}
						else {
							continue;
						}
					}

					int szabadhelyekszama = 0;

					//megnezni, mennyi szabad van meg, ha nem fer ra az osszes, akkor a padlora dobni
					if (uresTombIndex + szinCounter > mintasorSzam) {
						cout << "nem fer ra mind, a leeso csempek a padlora mennek!\n";
						szabadhelyekszama = mintasorSzam - uresTombIndex;
						for (int i = 0; i < szabadhelyekszama; i++) {//amennyi belefer beleteszi
							player[aktualis_jatekos].tabla.mintasor_ures[mintasorSzam]++;
							player[aktualis_jatekos].tabla.mintasor[mintasorSzam - 1][i + uresTombIndex] = karakter;
							szinCounter--;
						}
						//maradek megy a padlora
						PadlovonalraHelyezes(game, player, karakter, szinCounter);
					}
					else {//belefer a sorba
						szabadhelyekszama = mintasorSzam - uresTombIndex;
						for (int j = 0; j < szinCounter; j++) {
							player[aktualis_jatekos].tabla.mintasor_ures[mintasorSzam]++;
							player[aktualis_jatekos].tabla.mintasor[(mintasorSzam - 1)][uresTombIndex + j] = karakter;
						}
					}
				}
				else { // adott soron mas szin talalhato , nem teheti oda
					cout << "A megadott sorban mas csempe van mar, nem teheted oda!\n";
					cout << "Adj meg egy uj sort!\t";
					nemjo = true;
					while (nemjo == true) {
						aktualis_jatekos = 0;//		ITT MEG KELl UJRA HIVNI A MINTASORBAHELYEZ FGV-T 
						mintasorba_helyez(game, player + aktualis_jatekos, karakter, szinCounter);
						nemjo = false;
					}
				}
			}
			else { // a valasztott sor hosszabb, mint a szinCounter
				//megvizsgalni, hogy az adott soron ugyanaz a szin talalhato e
				if (karakter == player[aktualis_jatekos].tabla.mintasor[mintasorSzam - 1][0] or '_' == player[aktualis_jatekos].tabla.mintasor[mintasorSzam - 1][0]) {
					for (int i = 0; i < mintasorSzam; i++) {//meg kell szamolni, hogy mennyi van mar a sorban ebbol a szinbol
						if (player[aktualis_jatekos].tabla.mintasor[mintasorSzam - 1][i] == '_') {
							uresTombIndex = i;
							break;
						}
						else
						{
							continue;
						}
					}
					int szabadhelyekszama = 0;

					//megnezni, mennyi szabad van meg, ha nem fer ra az osszes, akkor a padlora dobni
					if (uresTombIndex + szinCounter > mintasorSzam) {
						cout << "nem fer ra mind, a leeso csempek a padlora mennek!\n";
						szabadhelyekszama = mintasorSzam - uresTombIndex;
						for (int i = 0; i < szabadhelyekszama; i++) {//amennyi belefer beleteszi
							player[aktualis_jatekos].tabla.mintasor_ures[mintasorSzam]++;
							player[aktualis_jatekos].tabla.mintasor[mintasorSzam - 1][i + uresTombIndex] = karakter;
							szinCounter--;
						}
						PadlovonalraHelyezes(game, player, karakter, szinCounter); //maradek megy a padlora
					}

				}
				else { // adott soron mas szin talalhato , nem teheti oda
					cout << "A megadott sorban mas csempe van mar, nem teheted oda!\n";
					//int mintasorSzam = mintasor_bekeres();
					nemjo = true;
					while (nemjo == true) {
						aktualis_jatekos = 0;//			ITT  MEG KELL UJRA HIVNI A MINTASORBAHELYEZ FGV-T 
						mintasorba_helyez(game, player + aktualis_jatekos, karakter, szinCounter);
						nemjo = false;
					}
				}
			}
		}
	}
}

void korong_esete(Player* jatekos, Game* jatekmutato, int korong_sorszam) {
	bool mintasor_ures = true; bool korong_ures = false;
	int  azonosdb = 0;
	char karakter;
	int aktualis_jatekos = jatekmutato->aktualis_jatekos;

	if (korong_sorszam != 0) { //KORONG OLDALI ÁG :valamelyik korongról venne le, meg kell nézni hogy az üres-e vagy sem
		if (jatekmutato->tomb_mutato[korong_sorszam - 1].korongon_levo[0] == '_' or jatekmutato->tomb_mutato[korong_sorszam - 1].korongon_levo[1] == '_'
			or jatekmutato->tomb_mutato[korong_sorszam - 1].korongon_levo[2] == '_' or jatekmutato->tomb_mutato[korong_sorszam - 1].korongon_levo[3] == '_') {
			korong_ures = true;
		}
		while (korong_ures == true || korong_sorszam > jatekmutato->korongok_szama || korong_sorszam < 1) {
			while (cout << "a kivalasztott korong ures, adj meg egy masik korongot, amin van csempe!\n" && !(std::cin >> korong_sorszam)) {
				cin.clear(); //clear bad input flag
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				cout << "Nem egesz szamot adtal meg, adj meg egy egeszet 1-5 kozott!\n";
			}
			if (jatekmutato->tomb_mutato[korong_sorszam - 1].korongon_levo[0] != '_' ) {
				korong_ures = false;
			}
		}
		cout << "melyik karaktert valasztod? ( A,B,C,D, vagy E)\n";
		cin >> karakter;
		while (karakter<'A' or karakter >'E') {
			cout << "Helytelen adat, add meg ujra a valasztott karaktert!\n";
			cin >> karakter;
		}
		for (int i = 0; i < 4; i++) {//megnézem, hogy ilyen karakter van e egyáltalán a kiválaztott korongon
			if (jatekmutato->tomb_mutato[korong_sorszam - 1].korongon_levo[i] == karakter) {
				azonosdb++;
			}
		}
		while (azonosdb == 0) {
			cout << "a megadott karakter nem talalhato a kivalasztott korongon, adj meg egy masik karaktert!\n";
			cin >> karakter;
			while (karakter<'A' or karakter >'E') {
				cout << "Helytelen adat, add meg ujra a valasztott karaktert!\n";
				cin >> karakter;
			}
			for (int i = 0; i < 4; i++) {//megnézem, hogy ilyen karakter van e egyáltalán a kiválasztott korongon
				if (jatekmutato->tomb_mutato[korong_sorszam - 1].korongon_levo[i] == karakter) {
					azonosdb++;
				}
			}
		}
		for (int i = 0; i < 4; i++) { //KICSERÉLI A KIVÁLASZTOTT KARAKTERT '_'-RA, A MAS SZINÛEKET BEDOBJA KÖZÉPRE	
			if (jatekmutato->tomb_mutato[korong_sorszam - 1].korongon_levo[i] == karakter) {
				jatekmutato->tomb_mutato[korong_sorszam - 1].korongon_levo[i] = '_';
			}
			else {
				if (jatekmutato->tomb_mutato[korong_sorszam - 1].korongon_levo[i] == 'A') {
					jatekmutato->asztalkozepe_db++;
					jatekmutato->asztalkozepe[0] = jatekmutato->asztalkozepe[0] + 1;
					jatekmutato->tomb_mutato[korong_sorszam - 1].korongon_levo[i] = '_';
				}
				else if (jatekmutato->tomb_mutato[korong_sorszam - 1].korongon_levo[i] == 'B') {
					jatekmutato->asztalkozepe_db++;
					jatekmutato->asztalkozepe[1] = jatekmutato->asztalkozepe[1] + 1;
					jatekmutato->tomb_mutato[korong_sorszam - 1].korongon_levo[i] = '_';
				}
				else if (jatekmutato->tomb_mutato[korong_sorszam - 1].korongon_levo[i] == 'C') {
					jatekmutato->asztalkozepe_db++;
					jatekmutato->asztalkozepe[2] = jatekmutato->asztalkozepe[2] + 1;
					jatekmutato->tomb_mutato[korong_sorszam - 1].korongon_levo[i] = '_';
				}
				else if (jatekmutato->tomb_mutato[korong_sorszam - 1].korongon_levo[i] == 'D') {
					jatekmutato->asztalkozepe_db++;
					jatekmutato->asztalkozepe[3] = jatekmutato->asztalkozepe[3] + 1;
					jatekmutato->tomb_mutato[korong_sorszam - 1].korongon_levo[i] = '_';
				}
				else if (jatekmutato->tomb_mutato[korong_sorszam - 1].korongon_levo[i] == 'E') {
					jatekmutato->asztalkozepe_db++;
					jatekmutato->asztalkozepe[4] = jatekmutato->asztalkozepe[4] + 1;
					jatekmutato->tomb_mutato[korong_sorszam - 1].korongon_levo[i] = '_';
				}
			}
			jatekmutato->korongon_levo[korong_sorszam - 1] = 0;

		}
		mintasorba_helyez(jatekmutato, jatekos, karakter, azonosdb); //mintasorba pakol

	}

}

void asztalkozepe_esete(Player* jatekos, Game* jatekmutato, int korong_sorszam) {
	bool mintasor_ures = true; bool korong_ures = false; bool fordulo_vege = false;
	bool asztalon_van_ilyen = true;
	int  azonosdb = 0;
	char karakter;
	int aktualis_jatekos = jatekmutato->aktualis_jatekos;
	// meg kell neznem, hogy az asztalkozepe_db DB csempe KÖZÜL van e ilyen karakter, es ha igen mennyi
	cout << "melyik karaktert valasztod? ( A,B,C,D,E)\n";
	cin >> karakter;
	while (karakter<'A' or karakter >'E') {
		cout << "Helytelen adat, add meg ujra a valasztott karaktert!\n";
		cin >> karakter;
	}
	int valasztott_karakter; // EZZEL MEG TUDOM MAJD ADNI, HOGY AZ ASZTALKOZEPE TOMB MELYIK INDEXU CELLAJANAK ELEMSZAMA KELL, ES NULLAZNI IS TUDOM
	if (karakter == 'A') { valasztott_karakter = 0; }
	else if (karakter == 'B') { valasztott_karakter = 1; }
	else if (karakter == 'C') { valasztott_karakter = 2; }
	else if (karakter == 'D') { valasztott_karakter = 3; }
	else if (karakter == 'E') { valasztott_karakter = 4; }

	//megnézem, hogy ilyen karakter van e egyáltalán a kiválasztott korongon
	if (jatekmutato->asztalkozepe[valasztott_karakter] != 0) {
		azonosdb = jatekmutato->asztalkozepe[valasztott_karakter]; //azonosdb innentõl kezdve azt tárolja, hogy mennyi volt abból a színbõl az asztalon
		jatekmutato->asztalkozepe[valasztott_karakter] = 0;
		jatekmutato->asztalkozepe_db = jatekmutato->asztalkozepe_db - azonosdb;
	}
	else {// nem volt abból a színbõl az asztalon
		asztalon_van_ilyen = false;
	}

	while (asztalon_van_ilyen == false) { //mindig lefut, ameddig olyat választ, amibõl nincs az asztalon
		cout << "nincs ilyen karakter az asztalon, adj meg egy uj karaktert!\n";
		cin >> karakter;
		if (karakter == 'A') { valasztott_karakter = 0; }
		else if (karakter == 'B') { valasztott_karakter = 1; }
		else if (karakter == 'C') { valasztott_karakter = 2; }
		else if (karakter == 'D') { valasztott_karakter = 3; }
		else if (karakter == 'E') { valasztott_karakter = 4; }

		//megnézem, hogy ilyen karakter van e egyáltalán a kiválasztott korongon
		if (jatekmutato->asztalkozepe[valasztott_karakter] != 0) {
			azonosdb = jatekmutato->asztalkozepe[valasztott_karakter]; //azonosdb innentõl kezdve azt tárolja, hogy mennyi volt abból a színbõl az asztalon
			jatekmutato->asztalkozepe[valasztott_karakter] = 0;// kinullazom a kivalasztott karakternek a db-szamat az asztalon
			asztalon_van_ilyen = true;
		}
	}

	// most jön az a rész, hogy az azonosdb_mennyiseget a kivalasztott mintasorba atdobom // ez elvileg ugyanaz, mint a korong_eseteben
	if (jatekmutato->asztalkozepe[5] == 1) {
		int ennyivanmost = PadlovonalonEnnyivan(jatekos + aktualis_jatekos);
		if (ennyivanmost != 0) {// ez csak akkor fut le, ha mar van benne valami
			jatekos[aktualis_jatekos].tabla.padlovonal[ennyivanmost] = 'X';
			jatekmutato->asztalkozepe[5] = 0;
			jatekos[aktualis_jatekos].tabla.mintasor_ures[0]++;
			jatekmutato->KoviX = jatekmutato->aktualis_jatekos; // itt adom át, hogy a token miatt ki fogja a kovetkezo kort kezdeni
		}
		else {
			jatekos[aktualis_jatekos].tabla.padlovonal[0] = 'X';
			jatekmutato->asztalkozepe[5] = 0;
			jatekos[aktualis_jatekos].tabla.mintasor_ures[0]++;
			// belerakja az elso helyre a kezdojatekos tokent jelzot
			jatekmutato->KoviX = jatekmutato->aktualis_jatekos; // itt adom át, hogy a token miatt ki fogja a kovetkezo kort kezdeni
		}
	}
	mintasorba_helyez(jatekmutato, jatekos, karakter, azonosdb);
}

void csempe_valasztas(Player* jatekos, Game* jatekmutato) {
	int aktualis_jatekos = jatekmutato->aktualis_jatekos;
	bool mintasor_ures = true; bool korong_ures = false;
	int korong_sorszam=0;
	bool rossz_korong_sorszam = false;

	while (cout << "add meg, hogy honnan szeretnel levenni! 0:asztal kozepe, korongoknak pedig a sorszamat add meg!\n" && !(std::cin >> korong_sorszam)) {
		std::cin.clear(); //clear bad input flag
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
		std::cout << "Nem egesz szamot adtal meg, adj meg egy egeszet 0-5 kozott\n";
	}
	if (korong_sorszam<0 or korong_sorszam>jatekmutato->korongok_szama) {
		rossz_korong_sorszam = true;
	}
	while (rossz_korong_sorszam == true) {
		while (cout << "Helytelen adat, add meg ujra a korong sorszamat!\n" && !(std::cin >> korong_sorszam) || korong_sorszam<0 or korong_sorszam>jatekmutato->korongok_szama) {
			std::cin.clear(); //clear bad input flag
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
			std::cout << "Nem egesz szamot adtal meg, adj meg egy egeszet 1-5 kozott\n";
		}
		if (korong_sorszam >= 0 or korong_sorszam <= jatekmutato->korongok_szama) {
			rossz_korong_sorszam = false;
		}
	}
	if (korong_sorszam != 0) {
		korong_esete(jatekos, jatekmutato, korong_sorszam);
	}
	else {// ebben az esetben vesz le az asztal közepérõl
		if (jatekmutato->asztalkozepe_db == 0) {
			while (cout << "Asztal kozepen nincs semmi, adj meg egy korongot!\n" && !(std::cin >> korong_sorszam) || (korong_sorszam < 1) or (korong_sorszam > jatekmutato->korongok_szama)) {
				std::cin.clear(); //clear bad input flag
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
				std::cout << "Rossz szamot adtal meg, adj meg egy egeszet 1-5 kozott\n";
			}
			if (jatekmutato->tomb_mutato[korong_sorszam - 1].korongon_levo[0] == '_' and jatekmutato->tomb_mutato[korong_sorszam - 1].korongon_levo[1] == '_'
				and jatekmutato->tomb_mutato[korong_sorszam - 1].korongon_levo[2] == '_' and jatekmutato->tomb_mutato[korong_sorszam - 1].korongon_levo[3] == '_') {
				korong_ures = true;
			}
			while (korong_ures == true) {
				cout << "a kivalasztott korong ures, adj meg egy korongot, amin van csempe!\n";
				korong_esete(jatekos, jatekmutato, korong_sorszam);
			}
			if (korong_ures == false) {
				korong_esete(jatekos, jatekmutato, korong_sorszam);
			}
		}
		else {
			asztalkozepe_esete(jatekos, jatekmutato, korong_sorszam);
		}
	}
}

bool fordulo_vege(Game* jatek) { // AZT NÉZI, HOGY A KORONGOK ÉS ASZTAL ÜRES E, HA IGEN, AKKOR VÉGE A FORDULÓNAK
	bool minden_ures = true;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 4; j++) {
			if (jatek->tomb_mutato[i].korongon_levo[j] != '_') {
				minden_ures = false;
				break;
			}
			else {
				minden_ures = true;
				continue;
			}
		}
	}
	
	for (int i = 0; i < jatek->korongok_szama; i++) { 
		if (jatek->korongon_levo[i] != 0) {
			minden_ures = false;
		}
		if (minden_ures == false) {
			break;
		}
	}

	for (int i = 0; i < 6; i++) {
		if (jatek->asztalkozepe[i] != 0) {
			minden_ures = false;
		}
	}
	return minden_ures;
}

bool fordulo_vege_v02(Game* jatek) { // egy masik mod az ellenorzesre
	bool minden_full_ures = true;
	for (int i = 0; i < jatek->korongok_szama; i++) {
		if (jatek->korongon_levo[i] != 0) {
			minden_full_ures = false;
		}
	}
	for (int j = 0; j < 5; j++) {
		if (jatek->asztalkozepe[j] != 0) {
			minden_full_ures = false;
		}
	}
	return minden_full_ures;
}

void PadlovonalTörlése(Player* player, Game* game) {
	int padlovonalonennyivan = PadlovonalonEnnyivan(player);
	if (PaldlovonalonVanE(player) == true) {
		for (int i = 0; i < padlovonalonennyivan; i++) {
			player->pontszam = player->pontszam + player->tabla.padlovonal_ertekek[i];
			if (player->tabla.padlovonal[i] == 'A') { game->dobott_csempek[0]++; }
			else if (player->tabla.padlovonal[i] == 'B') { game->dobott_csempek[1]++; }
			else if (player->tabla.padlovonal[i] == 'C') { game->dobott_csempek[2]++; }
			else if (player->tabla.padlovonal[i] == 'D') { game->dobott_csempek[3]++; }
			else if (player->tabla.padlovonal[i] == 'E') { game->dobott_csempek[4]++; }

			player->tabla.padlovonal[i] = '_';
			if (player->pontszam < 0) {
				player->pontszam = 0;
			}
		}
		if (padlovonalonennyivan == 0) { // tele van a padlo, ezert a fgv nem adott vissza uresTombindexet, ekkor is torolni kell az egeszet, illetve a pontokat levonni
			for (int i = 0; i < 7; i++) {
				player->pontszam = player->pontszam + player->tabla.padlovonal_ertekek[i];
				if (player->tabla.padlovonal[i] == 'A') { game->dobott_csempek[0]++; }
				else if (player->tabla.padlovonal[i] == 'B') { game->dobott_csempek[1]++; }
				else if (player->tabla.padlovonal[i] == 'C') { game->dobott_csempek[2]++; }
				else if (player->tabla.padlovonal[i] == 'D') { game->dobott_csempek[3]++; }
				else if (player->tabla.padlovonal[i] == 'E') { game->dobott_csempek[4]++; }

				player->tabla.padlovonal[i] = '_';
				if (player->pontszam < 0) {
					player->pontszam = 0;
				}
			}
		}
	}
}


void csempe_falra_helyezese(Player* jatekos, Game* jatek) { //Minden forduló végén a falra kell helyezni a megtelt mintasorokból a csempéket
	bool tartalmazza_a_fal = false; bool mintasortelevan = false;
	int oszlopszam;
	int aktualis_jatekos = jatek->aktualis_jatekos;
	if (jatek->fordulovege == true) {
		cout << endl << "A fordulonak vege, a teljes mintasorokbol a falra kerulnek a csempek!\n";
		cout << aktualis_jatekos + 1 << ". jatekos helyezi a csempeket a falra a teljes mintasorokbol!\n";
		for (int i = 0; i < 5; i++) { // FOR CIKLUSSAL VEGIGMEGYEK A MINTASOROKON, ellenõrzöm hogy az egyes mintasorban mintasor db azonos csempe van e I+1=MINTASOR HOSSZA
			//mintasortelevan = MintasorTelevanE(jatekos, i);
			if (jatekos[aktualis_jatekos].tabla.mintasor_ures[i + 1] == i + 1) {// ebben az esetben annyi a mintasornak a számlálója, ahányadik sorban vagyunk , else ág elvileg nem kell
				if (tartalmazza_a_fal == false) { //NEM TARTALMAZZA A KIVÁLASZTOTT SOR, EZÉRT BELEPAKOLHATOM
					bool oszlop_tartalmazza = false;
					int ennyi_oszlop_tartalmazza = 0;

					if (VanEszabadLepes(jatekos + aktualis_jatekos, jatekos[aktualis_jatekos].tabla.mintasor[i][0], i) == true) {
						while (cout << "Melyik oszlopba tegyem a " << jatekos[aktualis_jatekos].tabla.mintasor[i][0] << " karaktert? 1-5\n" << "\t" && !(std::cin >> oszlopszam) || (oszlopszam < 0) || (oszlopszam > 5)) {
							std::cin.clear(); //clear bad input flag
							std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
							std::cout << "Nem jo szamot adtal meg, adj meg egy egeszet 1-5 kozott!\n";
						}
						while (jatekos[aktualis_jatekos].tabla.fal[i][oszlopszam - 1] != '.') {
							while (cout << "Ebben az oszlopban van mar csempe, nem teheted ide! Adj meg egy uj oszlopot!\n" && !(std::cin >> oszlopszam) || (oszlopszam < 0) || (oszlopszam > 5) || (jatekos[aktualis_jatekos].tabla.fal[i][oszlopszam - 1] != '.')) {
								std::cin.clear(); //clear bad input flag
								std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
								std::cout << "Nem jo szamot adtal meg, adj meg egy egeszet 1-5 kozott!\n";
							}
						}
						while (oszlopszam < 1 or oszlopszam>5) {
							while (std::cout << "helytelen oszlopszam! add meg ujra!\n" && !(std::cin >> oszlopszam) || (oszlopszam < 0) || (oszlopszam > 5)) {
								std::cin.clear(); //clear bad input flag
								std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
								std::cout << "Helytelen oszlopszam, adj meg egy egeszet 1-5 kozott!\n";
							}
						}
						for (int j = 0; j < 5; j++) {
							if (jatekos[aktualis_jatekos].tabla.fal[j][oszlopszam - 1] == jatekos[aktualis_jatekos].tabla.mintasor[i][0]) {
								ennyi_oszlop_tartalmazza++;
								player_megjelenit(jatekos, jatek->resztvevo_szam);
							}
						}
						while (oszlop_tartalmazza_a_betut(jatekos + aktualis_jatekos, i, oszlopszam) == true) {// ADOTT OSZLOPBAN MÁR VAN ILYEN - UJ BEKERES
							while (std::cout << "a megadott oszlop mar tartalmazza azt a csempet!\t Adj meg egy uj oszlopot!\t" && !(std::cin >> oszlopszam) || (oszlopszam < 0) || (oszlopszam > 5) || (jatekos[aktualis_jatekos].tabla.fal[i][oszlopszam - 1] != '.')) {
								std::cin.clear(); //clear bad input flag
								std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
								std::cout << "Nem jo szamot adtal meg, adj meg egy egeszet 1-5 kozott!\n";
							}


						}
						if (ennyi_oszlop_tartalmazza == 5) { // 5 oszlop is tartalmazza azt a karaktert a falon, nem tudom hova tenni- padlóra kerül a mintasor összes eleme: padló üres, vagy nem?
							int ennyi_van_a_padlon = PadlovonalonEnnyivan(&jatekos[aktualis_jatekos]);
							if (ennyi_van_a_padlon == 0) { // Padlora rakom, ebben az esetben ures a padlo
								for (int m = 0; m < i; m++) {
									jatekos[aktualis_jatekos].tabla.padlovonal[m] = jatekos[aktualis_jatekos].tabla.mintasor[i][m];
									jatekos[aktualis_jatekos].tabla.mintasor[i][m] = '_';
								}
								jatekos[aktualis_jatekos].tabla.mintasor_ures[i] = 0;
							}
							else { // nem üres a padlo
								for (int m = ennyi_van_a_padlon; m < i; m++) {
									jatekos[aktualis_jatekos].tabla.padlovonal[m] = jatekos[aktualis_jatekos].tabla.mintasor[i][m];
									jatekos[aktualis_jatekos].tabla.mintasor[i][m] = '_';
								}
								jatekos[aktualis_jatekos].tabla.mintasor_ures[i] = 0;
							}
							ennyi_oszlop_tartalmazza = 0;
						}
						// NINCS ILYEN: BELEPAKOLOM
						jatekos[aktualis_jatekos].tabla.fal[i][oszlopszam - 1] = jatekos[aktualis_jatekos].tabla.mintasor[i][0];
						Pontok_hozzaadasa(&jatekos[aktualis_jatekos], i, oszlopszam - 1);

						for (int j = 0; j <= i; j++) {
							if (jatekos[aktualis_jatekos].tabla.mintasor[i][0] == 'A') { jatek->dobott_csempek[0] = jatek->dobott_csempek[0] + i; }
							else if (jatekos[aktualis_jatekos].tabla.mintasor[i][0] == 'B') { jatek->dobott_csempek[1] = jatek->dobott_csempek[1] + i; }
							else if (jatekos[aktualis_jatekos].tabla.mintasor[i][0] == 'C') { jatek->dobott_csempek[2] = jatek->dobott_csempek[2] + i; }
							else if (jatekos[aktualis_jatekos].tabla.mintasor[i][0] == 'D') { jatek->dobott_csempek[3] = jatek->dobott_csempek[3] + i; }
							else if (jatekos[aktualis_jatekos].tabla.mintasor[i][0] == 'E') { jatek->dobott_csempek[4] = jatek->dobott_csempek[4] + i; }
							jatekos[aktualis_jatekos].tabla.mintasor[i][j] = '_';
							jatekos[aktualis_jatekos].tabla.mintasor_ures[i + 1] = 0;
						}
					}
					else { // nincs szabad lépés, akkor el kell dobni a mintasor elemeit, és kiütíteni a mintasort!
						cout << "Nem tudod sehova sem helyezni szabalyosan, a mintasorbol eldobasra kerulnek a csempek!\n" << endl;
						for (int j = 0; j <= i; j++) {
							if (jatekos[aktualis_jatekos].tabla.mintasor[i][0] == 'A') { jatek->dobott_csempek[0] = jatek->dobott_csempek[0] + i; }
							else if (jatekos[aktualis_jatekos].tabla.mintasor[i][0] == 'B') { jatek->dobott_csempek[1] = jatek->dobott_csempek[1] + i; }
							else if (jatekos[aktualis_jatekos].tabla.mintasor[i][0] == 'C') { jatek->dobott_csempek[2] = jatek->dobott_csempek[2] + i; }
							else if (jatekos[aktualis_jatekos].tabla.mintasor[i][0] == 'D') { jatek->dobott_csempek[3] = jatek->dobott_csempek[3] + i; }
							else if (jatekos[aktualis_jatekos].tabla.mintasor[i][0] == 'E') { jatek->dobott_csempek[4] = jatek->dobott_csempek[4] + i; }
							jatekos[aktualis_jatekos].tabla.mintasor[i][j] = '_';
							jatekos[aktualis_jatekos].tabla.mintasor_ures[i + 1] = 0;
						}
					}
				}
				player_megjelenit(jatekos, jatek->resztvevo_szam);
			}
		}
		PadlovonalTörlése(jatekos + aktualis_jatekos, jatek);
	}
	else {
		cout << "A fordulonak nincs vege, valamelyik csempen, vagy az asztalon van meg csempe!\n";
	}
}



void megjelenit(Game game) {
	for (int i = 0; i < game.korongok_szama; i++) {
		cout << i + 1 << ". korongon levo csempek: ";
		for (int j = 0; j < 4; j++) {
			cout << game.tomb_mutato[i].korongon_levo[j];
		}
		if (i % 2 == 0) { cout << "\t"; }
		else { cout << endl; }
	}
	cout << endl;
	cout << "Asztalon levo csempek: " << "\t";
	for (int i = 0; i < 6; i++) {
		if (i == 0) { cout << "A: " << game.asztalkozepe[i] << "\t"; }
		if (i == 1) { cout << "B: " << game.asztalkozepe[i] << "\t"; }
		if (i == 2) { cout << "C: " << game.asztalkozepe[i] << "\t"; }
		if (i == 3) { cout << "D: " << game.asztalkozepe[i] << "\t"; }
		if (i == 4) { cout << "E: " << game.asztalkozepe[i] << "\t"; }
		if (i == 5) { cout << "Kezdojatekos token: " << game.asztalkozepe[i] << endl; }
	}
	cout << "Eldobott csempek:" << "\t";
	for (int i = 0; i < 5; i++) {
		if (i == 0) { cout << "A: " << game.dobott_csempek[i] << "\t"; }
		if (i == 1) { cout << "B: " << game.dobott_csempek[i] << "\t"; }
		if (i == 2) { cout << "C: " << game.dobott_csempek[i] << "\t"; }
		if (i == 3) { cout << "D: " << game.dobott_csempek[i] << "\t"; }
		if (i == 4) { cout << "E: " << game.dobott_csempek[i] << endl; }
	}
	cout << "zsak tartalma:\t\t";
	for (int i = 0; i < 5; i++) {
		if (i == 0) { cout << "A: " << game.zsak[i] << "\t"; }
		if (i == 1) { cout << "B: " << game.zsak[i] << "\t"; }
		if (i == 2) { cout << "C: " << game.zsak[i] << "\t"; }
		if (i == 3) { cout << "D: " << game.zsak[i] << "\t"; }
		if (i == 4) { cout << "E: " << game.zsak[i] << endl; }
	}
}

void egy_fordulo(Game* jatekmutato, Player* jatekos) {
	bool osszes_korong_ures = false;
	if (jatekmutato->jatekvege == false) {

		player_megjelenit(jatekos, jatekmutato->resztvevo_szam);
		for (int i = 0; i < 5; i++) { // Asztalközepét nullázom, és a kezdõjátékost bedobom középre
			jatekmutato->asztalkozepe[i] = 0; //beallitja az asztalkozepe elso 5 cellajat 0-ra
		}
		jatekmutato->asztalkozepe[5] = 1; //asztalkozepen van egy db kezdojatekos token
		*jatekmutato = korongfeltolt(*jatekmutato); //Feltöltöm a korongokat
		jatekmutato->asztalkozepe_db = 0;
		int i = 0;

		if (jatekmutato->KoviX != -1) { // ha ez nem = -1-el, akkor felvett egy értéket. mindig megtörténik a 2. körtõl fogva
			i = jatekmutato->KoviX;
		}

		cout << endl;
		megjelenit(*jatekmutato); // megjelenítem a korongokat és a többit

		// KELL EGY WHILE CIKLUS, AMÍG A KORONGOKRÓL ÉS AZ ASZTALRÓL EL NEM FOGYNAK A CSEMPEK, ADDIG MEHET
		jatekmutato->fordulovege = false; // a fordulo_vege fgv true, ha minden csempe elfogyott mindenhonnan

		while (jatekmutato->fordulovege == false) { // tehát van még csempe, nincs vége a fordulónaK
			cout << i + 1 << ". jatekos kovetkezik!\n";
			jatekmutato->aktualis_jatekos = i;
			csempe_valasztas(jatekos, jatekmutato);
			cout << endl << endl << endl;
			player_megjelenit(jatekos, jatekmutato->resztvevo_szam);
			megjelenit(*jatekmutato);
			cout << endl;
			jatekmutato->fordulovege = fordulo_vege(jatekmutato);  	// a fordulo utan meg kell ujra vizsgalni, hogy elfogyott e minden csempe
			if (jatekmutato->fordulovege == true) {
				break;
			}
			i = KovetkezoPlayerKivalasztasa(i, jatekmutato); // átadom a következõ játékos indexét

		}//csempek mintasorbol valo atrakasa 
		for (int j = 0; j < jatekmutato->resztvevo_szam; j++) {
			jatekmutato->aktualis_jatekos = j;
			csempe_falra_helyezese(jatekos, jatekmutato); // minden forduló után a falra kell pakolni a csempéket 
		}
	}
	else {
		cout << "a jatek veget ert, pontszamitas kovetkezik!\n" << endl;
	}
}

bool jatekvege(Player* jatekos, Game* jatek) { // teli sorok ellenorzese
	bool vege = false;
	int aktualis_jatekos = jatek->aktualis_jatekos;
	for (int i = 0; i < 5; i++) {
		if (jatekos[aktualis_jatekos].tabla.fal[i][0] != '.' and jatekos[aktualis_jatekos].tabla.fal[i][1] != '.' and jatekos[aktualis_jatekos].tabla.fal[i][2] != '.'
			and jatekos[aktualis_jatekos].tabla.fal[i][3] != '.' and jatekos[aktualis_jatekos].tabla.fal[i][4] != '.') {
			vege = true;
		}
	}
	return vege;
}

