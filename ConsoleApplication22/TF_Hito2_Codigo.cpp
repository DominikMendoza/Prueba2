#include "pch.h"
#include <iostream>
#include "Graficos.h"
#include "Funcionalidades.h"

using namespace System;
using namespace std;


void MostrarMenu(short* Opcion)
{
	system("color 7b");
	do
	{
		escribirMenu();
		color(1);
		cursor(25, 17); cout << "1. Nueva partida";
		cursor(25, 18); cout << "2. Instrucciones";
		cursor(25, 19); cout << "3. Cr" << char(130) << "ditos";
		cursor(25, 20); cout << "4. Configurar Partida";
		cursor(25, 21); cout << "5. Salir";
		cursor(25, 23); cout << "Ingrese opci" << char(162) << "n: ";
		cin >> *Opcion;

	} while (*Opcion < 1 || *Opcion > 5);

}

void presentacion()
{
	color(10);
	escribir_weRecycle();
	cursor(22, 24); cout << "APRENDIENDO A CLASIFICAR DESECHOS";
	cursor(21, 26); cout << "¡CUIDADO CON EL TIEMPO Y LAS HORDAS!";
	cursor(23, 28); cout << "Presione ENTER para continuar...";
}

int main()
{
	//  Un comentario simple
	// Otro comentario
	// una implementacion
	//p
	short* Opcion = new short; 
	bool* nivel2Desbloqueado = new bool, * nivel3Desbloqueado = new bool;
	*nivel2Desbloqueado = false;   
	*nivel3Desbloqueado = false;      
	bool* menu = new bool; *menu = true;
	Console::SetWindowSize(WIDTH, HEIGHT);
	Console::Clear();
	Console::CursorVisible = false;
	system("color 7b");
	int a = 0;

	presentacion(); 
	system("pause>0");

	while (true)
	{
		while (*menu)
		{
			system("cls");
			MostrarMenu(Opcion);

			switch (*Opcion)
			{
			case 1:
				system("cls");
				*menu = false;
				system("color 0b");
				Nueva_Partida(nivel2Desbloqueado, nivel3Desbloqueado, menu);
				break;

			case 2:
				system("cls");
				Instrucciones();
				break;

			case 3:
				system("cls");
				Creditos();
				break;

			case 4:
				system("cls");
				Configurar_partida();
				break;

			case 5:
				system("cls");
				Console::SetCursorPosition(30, 10); cout << "GRACIAS POR JUGAR";
				_sleep(500);
				exit(0);
				break;

			default: break;
			}
			system("pause>0");
		}
	}

	delete menu;
	delete nivel2Desbloqueado;
	delete nivel2Desbloqueado;
	delete Opcion;

	system("pause>0");
	return 0;
}

