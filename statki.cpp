#include<iostream>
#include <windows.h>
#include<ctype.h>
#include<fstream>
#include<string>
#include<stdio.h> 
#include <conio.h>
#include<cstdlib>
#include<time.h>

using namespace std;

VOID WINAPI Sleep(DWORD dwMilliseconds);

void los(int, int, char**, char**, int, int, int, int, int, char**, char**);// deklaracja 


bool wcisniecie_klawisza()
{
	int klawisz;
	klawisz = _getch();
	if (klawisz == 32) return true;
	else return false;
}
void wypelnij(int rozmiar, char** tabA)
{
	char alf[] = { 'A','B','C','D', 'E','F','G', 'H','I', 'J' };
	int cyf[] = { 1,2,3,4,5,6,7,8,9,10 };

	for (int i = 0; i < rozmiar; i++)
	{
		tabA[i] = new char[rozmiar];//alokacja pamięci 
		for (int n = 0; n < rozmiar; n++)
		{
			tabA[i][n] = '~';
		}
	}
}
int wprowadz_literke()
{
	string literka;

	cout << "Wprowadz literke:" << endl;

	while (1) {//powtarza sie do czasu gdy zostanie podana literka
		cin >> literka;
		if (literka[0] <= 'z' && literka[0] >= 'a') {
			return ((int)literka[0] - 'a');
		}
		else if (literka[0] <= 'Z' && literka[0] >= 'A') {
			return ((int)literka[0] - 'A');
		}
		cout << "Wprowadz poprawna literke!" << endl;
	}
}
int wprowadz_liczbe()
{
	string liczba;
	int liczba_int;
	cout << "Wprowadz liczbe:";

	while (1) {
		cin >> liczba;
		if (liczba[0] <= '9' && liczba[0] >= '0') {

			liczba_int = (int)liczba[0] - '0';

			if (liczba[1] <= '9' && liczba[1] >= '0') {

				return (liczba_int * 10 + (int)liczba[1] - '0');

			}
			return liczba_int;
		}
		cout << "Wprowadz poprawna liczbe!";

	}

}
void boom(string plik)
{
	fstream odczyt;
	odczyt.open(plik);
	if (odczyt.good() == true)
	{
		string linia;
		while (getline(odczyt, linia))
		{

			cout << linia << endl;

		}
	}
	else cout << "Blad odczytu";
	odczyt.close();


}
void wyswietl_plansze(char** tab, int rozmiar)
{
	char alf[] = { 'A', 'B','C','D','E','F','G','H','I','J' };
	cout << "   ";
	for (int a = 0; a < rozmiar; a++)
	{
		cout << " " << a + 1;
	}
	cout << endl << endl;

	for (int i = 0; i < rozmiar; i++)
	{
		cout << alf[i] << "   ";
		for (int n = 0; n < rozmiar; n++)
		{

			cout << tab[i][n] << " ";
		}

		cout << endl;
	}
	cout << endl;

}
void ustaw(int rozmiar, char** tab, int maszt, int ile)
{
	int i, m, k, j;
	char literka;
	char cyferka;
	cout << endl;
	for (int n = 0; n < ile; n++)
	{
		i = wprowadz_literke() + 1;// BO A TO 1 A NIE 0
		j = wprowadz_liczbe();
		cout << endl;

		if (i > rozmiar || j > rozmiar || i < 0 || j < 0)
		{
			cout << "\nPoza plansza :(. Jeszcze raz. \n";
			n--;
			continue;
		}

		else if (tab[i - 1][j - 1] != '~')
		{
			cout << "\nZajete pole. jesze raz.\n";
			n--;
			continue;
		}
		else

		{
			tab[i - 1][j - 1] = 'H';// jesli jest wolne i w planszy 

		}

		if (maszt == 1) {
			for (int a = 0; a < (maszt + 2); a++)
			{
				if ((i - 2) >= 0 && (i - 2) < rozmiar && (j - 2 + a) >= 0 && (j - 2 + a) < rozmiar && tab[i - 2][j - 2 + a] != 'H')tab[i - 2][j - 2 + a] = '-';
				if (i >= 0 && i < rozmiar && (j - 2 + a) >= 0 && (j - 2 + a) < rozmiar && tab[i][j - 2 + a] != 'H')tab[i][j - 2 + a] = '-';// DOL
				if (0 <= j < rozmiar && 0 <= (i - 1) < rozmiar && (tab[i - 1][j] != 'H'))tab[i - 1][j] = '-';// prawa
				if (0 <= (j - 2) < rozmiar && 0 <= (i - 1) < rozmiar && (tab[i - 1][j - 2] != 'H')) tab[i - 1][j - 2] = '-';// lewo
			}

			wyswietl_plansze(tab, rozmiar);
			continue;
		}

		char kierunek;
		cout << "W ktorym kierunku druga wspolrzedna?\n Wprowadz N, S, E lub W: ";
		cin >> kierunek;
		int m, k, spr;
		spr = 0;
		switch (kierunek)
		{
		case 'N':
			m = i - (maszt - 1);// wspolrzedne konca i=m+3

			for (int b = 0; b < (maszt - 1); b++)
			{
				if (0 > (m - 1 + b) || (m - 1 + b) >= rozmiar)
				{
					break;
				}
				if (tab[m - 1 + b][j - 1] == '~') spr++;
			}


			if (spr == (maszt - 1))
			{
				for (int a = 0; a < (maszt - 1); a++)
				{
					tab[m - 1 + a][j - 1] = 'H';
				}

				for (int a = 0; a < (maszt + 2); a++)// dlugość
				{

					if ((i - a) < rozmiar && (j - 2) < rozmiar && (tab[i - a][j - 2] != 'H'))tab[i - a][j - 2] = '-';// minusy po lewej
					if ((i - a) < rozmiar && j < rozmiar && (tab[i - a][j] != 'H')) tab[i - a][j] = '-';// minusy po prawej
					if (0 <= (m - 2) < rozmiar && (tab[m - 2][j - 1] != 'H')) tab[m - 2][j - 1] = '-';// minus daszek
					if (i < rozmiar && (j - 1) < rozmiar && (tab[i][j - 1] != 'H')) tab[i][j - 1] = '-';// minus dol
				}

			}
			else
			{
				cout << "Nie mozna tam ustawic statku.\n";
				tab[i - 1][j - 1] = '~';// zwalniamy początek 
				n--;
			}
			break;


		case 'S':
			spr = 0;
			m = i + (maszt - 1);
			for (int b = 0; b < (maszt - 1); b++)
			{
				if (0 > (m - 1 - b) || (m - 1 - b) >= rozmiar)
				{

					break;

				}
				if (tab[m - 1 - b][j - 1] == '~') spr++;
			}
			if (spr == (maszt - 1))
			{

				for (int a = 0; a <= (maszt - 1); a++)
				{
					tab[m - 1 - a][j - 1] = 'H';
				}

				for (int a = 0; a < (maszt + 2); a++)
				{
					if ((i - 2 + a) < rozmiar && (i - 1 + a) > 0 && (j - 2) < rozmiar && (tab[i - 2 + a][j - 2]) != 'H') tab[i - 2 + a][j - 2] = '-';
					if ((i - 2 + a) < rozmiar && (i - 1 + a) > 0 && 0 < j < rozmiar && (tab[i - 2 + a][j]) != 'H') tab[i - 2 + a][j] = '-';
					if (m < rozmiar && j - 1 < rozmiar && (tab[m][j - 1] != 'H'))tab[m][j - 1] = '-';// minus daszek
					if (0 <= (i - 2) && (j - 1) < rozmiar && (tab[i - 2][j - 1] != 'H')) tab[i - 2][j - 1] = '-';

				}
			}
			else
			{
				cout << "Nie mozan tam ustawic statku.\n";
				tab[i - 1][j - 1] = '~';// zwalniamy początek 
				n--;
			}


			break;
		case 'E':
			spr = 0;
			k = j + (maszt - 1);
			for (int b = 0; b < (maszt - 1); b++)
			{
				if (0 > (k - 1 - b) || (k - 1 - b) >= rozmiar)
				{
					break;
				}
				if (tab[i - 1][k - 1 - b] == '~') spr++;
			}
			if (spr == (maszt - 1))
			{

				for (int a = 0; a <= (maszt - 1); a++)
				{
					tab[i - 1][k - 1 - a] = 'H';
				}

				for (int a = 0; a < (maszt + 2); a++)
				{
					if ((i - 2) >= 0 && (i - 2) < rozmiar && (j - 2 + a) >= 0 && (j - 2 + a) < rozmiar && tab[i - 2][j - 2 + a] != 'H')tab[i - 2][j - 2 + a] = '-';
					if (i >= 0 && i < rozmiar && (j - 2 + a) >= 0 && (j - 2 + a) < rozmiar && tab[i][j - 2 + a] != 'H')tab[i][j - 2 + a] = '-';// DOL
					if (0 <= k < rozmiar && 0 <= (i - 1) < rozmiar && (tab[i - 1][k] != 'H'))tab[i - 1][k] = '-';// prawa
					if (0 <= (j - 2) < rozmiar && 0 <= (i - 1) < rozmiar && (tab[i - 1][j - 2] != 'H')) tab[i - 1][j - 2] = '-';// lewo
				}
			}
			else
			{
				cout << "Nie mozna tam ustawic statku.";
				tab[i - 1][j - 1] = '~';// zwalniamy początek 
				n--;
			}

			break;
		case 'W':
			k = j - (maszt - 1);// wspolrzedne konca

			for (int b = 0; b < (maszt - 1); b++)
			{
				if (0 > (k - 1 + b) || (k - 1 - b) >= rozmiar)break;

				if (tab[i - 1][k - 1 + b] == '~') spr++;
			}


			if (spr == (maszt - 1))
			{
				for (int a = 0; a < (maszt - 1); a++)
				{
					tab[i - 1][k - 1 + a] = 'H';
				}

				for (int a = 0; a < (maszt + 2); a++)
				{
					if ((i - 2) >= 0 && rozmiar > (j - (maszt + 1 - a)) >= 0 && tab[i - 2][j - (maszt + 1 - a)] != 'H') tab[i - 2][j - (maszt + 1 - a)] = '-';// gora
					if (i<rozmiar && rozmiar>j - (maszt + 1 - a) >= 0 && tab[i][j - (maszt + 1 - a) != 'H'])     tab[i][j - (maszt + 1 - a)] = '-';
					if (rozmiar > j >= 0 && tab[i - 1][j] != 'H')tab[i - 1][j] = '-';
					if (rozmiar > (k - 2) >= 0 && tab[i - 1][k - 2] != 'H') tab[i - 1][k - 2] = '-';

				}
			}

			else
			{
				cout << "Nie mozna tam ustawic statku.\n";
				tab[i - 1][j - 1] = '~';// zwalniamy początek 
				n--;
			}
			break;

		default:
			cout << "Wprowadzono zle dane.";
			tab[i - 1][j - 1] = '~';// zwalniamy początek 
			n--;

		}


		cout << endl;

		wyswietl_plansze(tab, rozmiar);
	}
	Sleep(3500);


}
void wsp(int rozmiar, char** tabA)
{
	int i;
	int j;
	int maszt;
	int ile;

	if (rozmiar > 8)
	{
		cout << "\nTwoje okrety to: 2x czteromasztowiec, 2x trojmasztowiec 1x dwumasztowiec 3x jednomasztowiec\n";
		cout << "Podaj wspolrzedne polozenia statkow.";
		for (maszt = 4; maszt > 0; maszt--)
		{
			if (maszt == 4)ile = 2;
			if (maszt == 3)ile = 3;
			if (maszt == 2)ile = 1;
			if (maszt == 1) ile = 3;
			ustaw(rozmiar, tabA, maszt, ile);


		}
	}
	else
	{
		cout << "\nTwoje okrety to:  1x trojmasztowiec 2x dwumasztowiec 3x jednomasztowiec\n";
		cout << "Podaj wspolrzedne statkow.";
		for (maszt = 4; maszt > 0; maszt--)
		{
			if (maszt == 4)ile = 0;
			if (maszt == 3)ile = 1;
			if (maszt == 2)ile = 2;
			if (maszt == 1) ile = 3;
			ustaw(rozmiar, tabA, maszt, ile);


		}


	}

}
void atak(int kolorAtak, int kolorObrona, char** tabAtak, char** tabObrona, int rozmiar, int mocAtak, int mocObrona, int iloscAtak, int iloscObrona, char** tab1, char** tab2)
{
	system("cls");
	char literka;
	int j;
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (kolorAtak == 1)
	{
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);// kolory gracza A
	}

	else if (kolorAtak == 0)
	{
		SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);// kolory gracza B
	}

	cout << "\nTwoje zasoby wynosza:" << mocAtak << " a ilosc Twoich masztow to: " << iloscAtak;
	cout << "\nGdzie chcesz wyslac swoja flote aby zaatakowac przeciwnika?\n Podaj pole:\n\n";

	wyswietl_plansze(tab1, rozmiar);

	cin >> literka;
	cin >> j;
	int i = ((int)literka - (int)'A' + 1);

	if (i > rozmiar || j > rozmiar || i < 0 || j < 0)
	{
		cout << "\nPoza plansza :(. Jeszcze raz. \n";
		atak(kolorAtak, kolorObrona, tabAtak, tabObrona, rozmiar, mocAtak, mocObrona, iloscAtak, iloscObrona, tab1, tab2);// ponowny ruch gracza, bo źle wybral pole

	}

	if (tabObrona[i - 1][j - 1] == 'H')
	{
		tabObrona[i - 1][j - 1] = 'o';
		tab1[i - 1][j - 1] = 'o';// plansza ze strzałami

		boom("boom.txt");
		Sleep(3000);

		iloscObrona--;// zmienna odpawiadajaca wszytskim masztom gracza, jesli jest rowna 0 gracz nie ma zadnych statkow
		int a = 0;
		if (0 <= (i - 2)) { if (tabObrona[i - 2][j - 1] != 'H') a++; }
		else  a++;
		if (i < rozmiar) { if (tabObrona[i][j - 1] != 'H') a++; }
		else a++;
		if (0 <= (j - 2)) { if (tabObrona[i - 1][j - 2] != 'H') a++; }
		else a++;
		if ((j) < rozmiar) { if (tabObrona[i - 1][j] != 'H') a++; }
		else a++;

		if (a == 4) { boom("zatopione.txt"); }

		if (mocAtak >= 90) { mocAtak += 5; mocObrona -= 5; }
		else if (90 > mocAtak >= 70) { mocAtak += 3; mocObrona -= 5; }
		else if (70 > mocAtak >= 50) { mocAtak += 2; mocObrona -= 3; }
		else if (50 > mocAtak >= 30) { mocAtak += 1; mocObrona -= 2; }
		else { mocObrona -= 1; }



		if (iloscObrona == 0) {
			cout << "\nWygrales. Koniec gry. Zatopione wszystkie statki.\n";
			cout << "Statystyki gry:\n";
			cout << "Liczba pozostalych masztow wygranego: " << iloscAtak << endl;
			cout << "Zasoby wygranego: " << mocAtak;
			cout << "\nLiczba pozostalych masztow przegranego: " << iloscObrona << endl;
			cout << "Zasoby przegranego: " << mocObrona;
			exit(0);

		}
		else
		{
			cout << "Grasz dalej\n"; Sleep(1000);
			atak(kolorAtak, kolorObrona, tabAtak, tabObrona, rozmiar, mocAtak, mocObrona, iloscAtak, iloscObrona, tab1, tab2);
		}// ponowny ruch gracza


	}
	else
	{
		cout << "\nPudlo!\n";
		tab1[i - 1][j - 1] = '*';

		mocAtak--;

		cout << "Ruch drugiego gracza.\n";
		Sleep(2000);
		int lo = rand() % 3;// 33% NA SYTUACJE LOSOWA
		if (lo == 1) los(kolorObrona, kolorAtak, tabObrona, tabAtak, rozmiar, mocObrona, mocAtak, iloscObrona, iloscAtak, tab2, tab1);// drugi gracz ma sytuacje losowa
		else
			atak(kolorObrona, kolorAtak, tabObrona, tabAtak, rozmiar, mocObrona, mocAtak, iloscObrona, iloscAtak, tab2, tab1);// atak drugiego przeciwnika

	}






}

int main()

{
	boom("start.txt");
	srand(time(NULL));
	Sleep(3000);
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	int rozmiar;
	int mocA = 100;// zasoby gracza, jesli wynasza 0 przegrywa

	int mocB = 100;

	int wybor;


	cout << "Witajcie w grze konsolowej STATKI ++" << endl;
	Sleep(2500);
	cout << "Rozgrywaka przewidziana jest dla dwoch graczy." << endl;
	Sleep(2500);
	cout << "Na poczatku kazdy z graczy ustawia swoje statki na planszy o wybranym rozmiarze." << endl;
	Sleep(3000);
	cout << "Waszym zadaniem jest zatopienie wszystkich okretow przeciwnika " << endl;
	cout << "Zaleznosc miedzy punktami zasobow a rozgrywka:\n\n 1) >=90pkt  Przy zbiciu Twoje zasoby wzrastaja o 5 pkt, zasoby przeciwnika maleja o 5,\n 2) 90-70pkt Przy zbiciu zasoby przeciwnika maleja o 5,\n 3) 70-50pkt Przy zbiciu zasoby przeciwnika maleja o 3,\n 4) 50-30pkt Przy zbiciu zasoby przeciwnika maleja o 2,\n 5) >30pkt Przy zbiciu zasoby przeciwnika maleja o 1.  ";
	Sleep(2500);
	cout << "ABY ROZPOCZAC GRE WCISNIJ SPACJE";

	while (true) {
		if (wcisniecie_klawisza()) {
			Sleep(1000);
			cout << "\n\n\n\n\n\n\n\n\t\tWITAJCIE! JESTESCIE GOTOWI NA NIEZAPOMNIANA PODROZ W NIEZNANE?\n\n";
			Sleep(3000);
			cout << "\t\tSPRYT, ODWAGA ORAZ DOBRY LOS POMOGA WAM POKONAC PRZECIWNIKA.\n\n";
			Sleep(3000);
			cout << "\t\tCZEKA WAS WIELE TRUDNYCH DEZYCJI, KTORE MOGA ZMIENIC CALY BIEG WYDARZEN\n\n";
			Sleep(3000);
			cout << "\t\tPAMIETAJCIE ABY POSTEPOWAC ROZSADNIE. POWODZENIA!\n\n\n";
			break;
		}
		continue;
	}

	cout << "Podaj rozmiar planszy: " << endl;
	cin >> rozmiar;
	if (rozmiar > 10 || rozmiar < 6)
	{
		cout << "Nieprawidlowe dane.";
		exit(-10);

	}
	int iloscA;// ilosc masztwow na planszy
	if (rozmiar > 8)  iloscA = 22;
	else iloscA = 10;
	int iloscB;
	if (rozmiar > 8)  iloscB = 22;
	else iloscB = 10;
	char** tabA = new char* [rozmiar];// plansze na statki
	char** tabB = new char* [rozmiar];

	char** tab1 = new char* [rozmiar];//plansze puste na zagadywanie polozenia
	char** tab2 = new char* [rozmiar];

	int maszt = 0;

	wypelnij(rozmiar, tabA);
	cout << endl;
	wypelnij(rozmiar, tabB);

	SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);// kolory gracza A
	system("cls");
	cout << "\nUstawianie statkow gracza A:\n\n";
	wyswietl_plansze(tabA, rozmiar);

	SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY | FOREGROUND_RED);// kolory standardowe
	wsp(rozmiar, tabA);
	SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);// kolory gracza B
	system("cls");
	cout << "\nUstawianie statkow gracza B:\n\n";
	wyswietl_plansze(tabB, rozmiar);
	SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY | FOREGROUND_RED);// kolory standardowe
	wsp(rozmiar, tabB);
	system("cls");

	int kolorA = 1;
	int kolorB = 0;

	cout << "\nGre rozpoczyna gracz A:\n";
	wypelnij(rozmiar, tab1);
	wypelnij(rozmiar, tab2);
	atak(kolorA, kolorB, tabA, tabB, rozmiar, mocA, mocB, iloscA, iloscB, tab1, tab2);


	//for (int i = 0; i < rozmiar; i++) //uwolnienie pamieci 
	//{
	//	delete[] tabA[i];
	//	delete[] tabB[i];

	//}

	//delete[] tabA;
	//delete[] tabB;
	//tabA = NULL;
	//tabB = NULL;

	return 1;
}
void los(int kolorAtak, int kolorObrona, char** tabAtak, char** tabObrona, int rozmiar, int mocAtak, int mocObrona, int iloscAtak, int iloscObrona, char** tab1, char** tab2)
{
	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (kolorAtak == 1)
	{
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);// kolory gracza A
	}

	else if (kolorAtak == 0)
	{
		SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);// kolory gracza B
	}
	int liczba = rand() % 8 + 1;
	char a;
	for (int n = 0; n < 1; n++)
	{
		switch (liczba)
		{
		case 1:
			system("cls");
			cout << "W pogoni za okretem wroga, wsrod wzburzonych fal zauwazasz starca na tratwie. Co robisz?\n\n";
			cout << "A) Przyjmuje go na swoj poklad, pomimo zmniejszenia zasobow\n\n";
			cout << "B) Zostawiam go na pastwe losu.Atakuje wroga." << endl;
			for (int n = 0; n < 1; n++)
			{
				cin >> a;
				//Po wyborze :

				cout << "Starzec okazal sie byc magiem!" << endl;
				boom("czar.txt");
				Sleep(3000);
				if (a == 'A') {

					cout << "Odwdziecza sie za pomoc. Dostajesz szanse na trafienie masztu przewnika oraz nie tracisz zasobow." << endl;
					Sleep(3000);
					atak(kolorAtak, kolorObrona, tabAtak, tabObrona, rozmiar, mocAtak, mocObrona, iloscAtak, iloscObrona, tab1, tab2);
				}

				else if (a == 'B') {
					cout << "Rzuca klatwe na Twoja zaloge. Atakujesz wroga z mniejszymi zasobami." << endl;
					Sleep(3000);
					mocAtak - +10;
					atak(kolorAtak, kolorObrona, tabAtak, tabObrona, rozmiar, mocAtak, mocObrona, iloscAtak, iloscObrona, tab1, tab2);
				}
				else {
					n--; liczba = 1; cout << "Wprowadziles zle dane. Podaj A lub B.\n";
				}
			}
			break;
		case 2://WYCZERPANIE
			system("cls");
			cout << "Po dlugiej podrozy Twoja zaloga skarzy sie na wyczerpanie. Co robisz?";
			cout << "\n\nA) Nie atakuje przeciwnika. Pozwalam na odpoczynek i regeneracje moich ludzi.";
			cout << "\n\nB) Atakuje przeciwnika. Chce wykorzytsac wszystkie okazje" << endl;
			char a;
			cin >> a;
			if (a == 'A') {
				boom("zzz.txt");
				Sleep(3000);
				mocAtak += 5;
				atak(kolorObrona, kolorAtak, tabObrona, tabAtak, rozmiar, mocObrona, mocAtak, iloscObrona, iloscAtak, tab2, tab1);// ruch przeciwnika
			}
			else if (a == 'B') { mocAtak -= 5;  atak(kolorAtak, kolorObrona, tabAtak, tabObrona, rozmiar, mocAtak, mocObrona, iloscAtak, iloscObrona, tab1, tab2); }// atak
			else { n--; liczba = 2; cout << "Wprowadziles zle dane. Podaj A lub B"; }
			break;
		case 3://WYSPA
			system("cls");
			boom("palma.txt");
			Sleep(3000);
			cout << "Na statku rozlegly sie wesole krzyki majtkow: WYSPA NA HORYZONCIE! Co robisz?\n\nA) Odpuszczam atak, chce poznac tajemnice tej wyspy.\n\nB) Atakuje wroga." << endl;

			cin >> a;
			if (a == 'A') {
				mocAtak += 10; cout << "\nZwiedzajac wyspe znalazles skarb! Towje zasoby sie zwiekszyly." << endl;
				Sleep(3500);
				atak(kolorObrona, kolorAtak, tabObrona, tabAtak, rozmiar, mocObrona, mocAtak, iloscObrona, iloscAtak, tab2, tab1);// ruch przeciwnika
			}
			else if (a == 'B') atak(kolorAtak, kolorObrona, tabAtak, tabObrona, rozmiar, mocAtak, mocObrona, iloscAtak, iloscObrona, tab1, tab2);
			else { n--; liczba = 3; cout << "Wprowadziles zle dane. Podaj A lub B"; }
			break;
		case 4://PRZYJACIEL +zasoby 
			system("cls");
			cout << "Na horyzoncie pojawil sie okret Twojego sojusznika. Co robisz?\n\nA) Prosze o pomoc w naprawieniu jednego z masztów.\n\nB) Atakuje przeciwnika" << endl;

			cin >> a;
			if (a == 'A') {
				mocAtak += 5; cout << "\nTwoje zasoby sie zwiekszyly." << endl;
				Sleep(3000);
				cout << "Ruch drugiego gracza";
				Sleep(1000);
				atak(kolorObrona, kolorAtak, tabObrona, tabAtak, rozmiar, mocObrona, mocAtak, iloscObrona, iloscAtak, tab2, tab1);// ruch przeciwnika

			}
			else if (a == 'B') { atak(kolorAtak, kolorObrona, tabAtak, tabObrona, rozmiar, mocAtak, mocObrona, iloscAtak, iloscObrona, tab1, tab2); }
			else { n--; liczba = 4; cout << "Wprowadziles zle dane. Podaj A lub B"; }
			break;
		case 5: // PIRACI
			system("cls");
			boom("piraci.txt");
			Sleep(3000);
			cout << "Piraci napadaja na jeden z Twoich statkow, Twoje zasoby zmniejszyly się. Twoja zaloga jest oslabiona przed atakiem.";
			mocAtak -= 5;
			Sleep(3000);
			atak(kolorAtak, kolorObrona, tabAtak, tabObrona, rozmiar, mocAtak, mocObrona, iloscAtak, iloscObrona, tab1, tab2);
			break;
		case 6://SOJUSZNIK +zasoby
			system("cls");
			cout << "Na morzu spotykasz sojusznika, który przekazuje Ci czesc swoich zapasow. Atakujesz silniejszy." << endl;
			mocAtak += 5;
			Sleep(3000);
			atak(kolorAtak, kolorObrona, tabAtak, tabObrona, rozmiar, mocAtak, mocObrona, iloscAtak, iloscObrona, tab1, tab2);
			break;
		case 7://SZTORM
			system("cls");
			boom("fala.txt");
			cout << "Nagly sztorm niszczy Twoj statek. Zaloga koncentruje sie na zminimalizowaniu strat. Przepada Twoja mozliwosc ataku." << endl;
			Sleep(3500);
			cout << "Ruch drugiego gracza";
			Sleep(1500);
			atak(kolorObrona, kolorAtak, tabObrona, tabAtak, rozmiar, mocObrona, mocAtak, iloscObrona, iloscAtak, tab2, tab1);// ruch przeciwnika
			break;
		case 8:// PLASTIK
			system("cls");
			cout << "Za burta dostrzegles delfina zawinietego w siec rybacka oraz foliowe reklamowki. Co robisz?\n";
			cout << "A) Pomagasz uwonic zwierze, ale tracisz okazje na atak przeciwnika.\n";
			cout << "B) Ignorujesz cierpiace zwierze. Atakujesz.\n";
			cin >> a;
			if (a == 'A') {
				mocAtak += 10; cout << "Organizacja dzialajaca na rzecz ochrony srodowiska docenila Twoje czyny. Twoje zasoby sie zwiekszyly.";
				Sleep(3500);
				atak(kolorAtak, kolorObrona, tabAtak, tabObrona, rozmiar, mocAtak, mocObrona, iloscAtak, iloscObrona, tab1, tab2);
			}
			else if (a == 'B') {
				atak(kolorObrona, kolorAtak, tabObrona, tabAtak, rozmiar, mocObrona, mocAtak, iloscObrona, iloscAtak, tab2, tab1);// ruch przeciwnika
			}
			else { n--; liczba = 8; cout << "Wprowadziles zle dane. Podaj A lub B"; }
			break;
		}

	}
}