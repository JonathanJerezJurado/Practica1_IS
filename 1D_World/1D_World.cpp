// 1D_Game.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <conio.h>
#include <windows.h>

#define IZQUIERDA 75
#define DERECHA 77
#define ESC 27

int g_anchoMundo = 52;
int playerPosition = 26;
int leftShootPosition;
int rightShootPosition = 53;
//int leftEnemyPosition = 0;
//int rightEnemyPosition = 41;
int veinteFps = 1000 / 20;
int cuarentaFps = 1000 / 40;
int sesentaFps = 1000 / 60;
int closeGame = 0;
char key;

void HideCursor();
void Paint();
void Actions();

int main()
{
	HideCursor();

	printf("\n\n");
	printf("                  *-----------------------------------*\n");
	printf("                  |         ONE DIMENSION WORLD       |\n");
	printf("                  *-----------------------------------*\n");
	printf("\n\n");
	printf("         *  *      *    *     *     *  *       *    *   *    *  *\n");
	printf("              *       *    *     *         *      *    *   *     \n");
	printf("           *      *    *     *     *  *       *    *   *    *  * \n");
	printf("         *     *     *    *     *     *      *       *   *      *\n");
	printf("\n\n");

	while (closeGame == 0) {
		Paint();
		Actions();
		Sleep(veinteFps);
	}
}

void Actions() {
	key = ' ';

	if (_kbhit()) {
		key = _getch();

		// Tratamiento de la tecla pulsada
		if (key == IZQUIERDA) {
			playerPosition -= 1;
		}
		else if (key == DERECHA) {
			playerPosition += 1;
		}
		else if (key == 'z') {
			leftShootPosition = playerPosition;
		}
		else if (key == 'x') {
			rightShootPosition = playerPosition;
		}
		else if (key == ESC) {
			closeGame = 1;
		}
	}

	// Actualiza avance de las balas
	if (leftShootPosition > 0) {
		leftShootPosition--;
	}
	if (rightShootPosition < g_anchoMundo) {
		rightShootPosition++;
	}

	// Actualiza posicion de enemigos
	//if (leftEnemyPosition < g_anchoMundo) {
	//	leftShootPosition++;
	//}
	//if (rightEnemyPosition > 0) {
	//	rightEnemyPosition--;
	//}

	//Comprueba colision de enemigos con las balas
	//if (leftEnemyPosition == leftShootPosition || leftEnemyPosition == rightShootPosition) {
	//	leftShootPosition = 0;
	//}
	//if (rightEnemyPosition == rightShootPosition || rightEnemyPosition == leftShootPosition) {
	//	rightEnemyPosition = 41;
	//}

	// Comprueba colisiones con los bordes del mundo
	if (playerPosition >= g_anchoMundo) {
		playerPosition = g_anchoMundo - 1;
	}
	else if (playerPosition < 0) {
		playerPosition = 0;
	}

	if (rightShootPosition >= g_anchoMundo) {
		rightShootPosition = g_anchoMundo;
	}
	else if (leftShootPosition < 0) {
		leftShootPosition = 0;
	}
}

void Paint() {

	// Pinta en pantalla los caracteres segun su posicion en el mundo
	printf("          |");
	for (int i = 0; i < g_anchoMundo; i++) {
		if (i == playerPosition) {
			printf("#");
		}
		else if (i == leftShootPosition && leftShootPosition != 0) {
			printf("<");
		}
		else if (i == rightShootPosition && rightShootPosition < g_anchoMundo) {
			printf(">");
		}
		else {
			printf("_");
		}
	}
	printf("|\r");
}

void HideCursor() {

	// Oculta el cursor de la consola
	CONSOLE_CURSOR_INFO cci = { 100, FALSE };
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);
}


