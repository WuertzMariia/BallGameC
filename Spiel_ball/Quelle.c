#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<conio.h>
#include<time.h>
#pragma warning (disable: 4996)

void gotoXY(int x, int y) {
	HANDLE hConsoleOutput;
	COORD koords;
	koords.X = x;
	koords.Y = y;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, koords);
}

struct ball {
	int x, y;
	int dx, dy;
	char z; //zeichen für den Ball
};

struct spielfeld {
	int breite, hoehe;
	int anz;
	//struct ball baelle[20]; //statisch mit festdefiniertem array von Bällen. Aber wir wollen dynamisch
	struct ball* b;  // dynamisch
};

void rendern(const struct spielfeld* pf) {
	system("cls");
	for (int i = 0; i < pf->anz; i++) {
		gotoXY(pf->b[i].x, pf->b[i].y);
		printf("%c", pf->b[i].z);
	}
}

void berechnen(struct spielfeld* pf) {
	
	for (int i = 0; i < pf->anz; i++) {
		if ((pf->b[i].x + pf->b[i].dx >= pf->breite) || (pf->b[i].x + pf->b[i].dx<0)) {
			pf->b[i].dx *= -1; 
		}
		pf->b[i].x += pf->b[i].dx;


		if ((pf->b[i].y + pf->b[i].dy >= pf->hoehe) || (pf->b[i].y + pf->b[i].dy < 0)) {
			pf->b[i].dy *= -1;
		}
		pf->b[i].y += pf->b[i].dy;
		
	}

}

void init(struct spielfeld* pf) {
	char c[] = { '+', '-', '*', '.', 'o', 'x', '@', '€' };
	srand(time(0));
	pf->b = (struct ball*)malloc((pf->anz) * sizeof(struct ball));
	for (int i = 0; i < pf->anz; i++) {
		pf->b[i].x = rand() % pf->breite;
		pf->b[i].y = rand() % pf->hoehe;
		do {
			pf->b[i].dx = (rand() % 3) - 1; // -1 bringt das Ergebnis zwischen -1 ... 1
			pf->b[i].dy = (rand() % 3) - 1;
		} while (pf->b[i].dx == 0 && pf->b[i].dy == 0);
		pf->b[i].z = c[rand() % 8];
	}
}

int main() {
	struct spielfeld f = { 70,20,0,0 }; //b ist zu initialisieren
	printf("Wieviel Baelle moechtest du? ");
	scanf("%d", &(f.anz));
	srand(time(0)); //Initialisierung von rand()
	init(&f);
	while (1) {
		
		rendern(&f); //aktuellen Spielfeld zeichnen
		berechnen(&f); //neue Ballposition berechnen
		Sleep(150); //warten 50 Millisekunden (20 fps frames per second); 
		if (_kbhit()) break; //beendet die Schleife bei gedückter Taste; 
	}
	printf("Spiel beendet");
	free(f.b);
	return 0;
}