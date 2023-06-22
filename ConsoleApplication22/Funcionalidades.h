#pragma once
#include "pch.h"
#include "conio.h"
#include "iostream"
#include "Graficos.h"

using namespace System;
using namespace std;

#define WIDTH 80
#define HEIGHT 40

#define ESCAPE      27 
//#define ESPACIO     32  
#define ARRIBA      72 
#define ABAJO       80
#define IZQUIERDA   75
#define DERECHA     77

struct Aliados
{
	int x;
	int y;

};

struct Principal
{
	int x;
	int y;
	int dx;
	int dy;

};

float tAgentesY[2] = { 22, 32 };
struct Agentes
{
	float x;
	float y;
	float agDirX;
	bool botarDesecho;
};

struct Desechos
{
	float cartonesX;
	float cartonesY;
	int contCartones;
	int cantCartones = 0;
};

void moverConTeclas(Principal* principal, int nivel)
{
	if (kbhit())
	{
		//borrar
		switch (nivel)
		{
		case 1:
			Borrar_personaje_principal1(principal->x, principal->y);      
			break;
		case 2:
			Borrar_personaje_principal2(principal->x, principal->y);
			break;
		case 3:
			Borrar_personaje_principal3(principal->x, principal->y);
			break;
		default: break;
		}

		char tecla = getch();

		//mover
		if (tecla == ARRIBA && principal->y > 18)			  principal->y -= principal->dy;
		if (tecla == ABAJO && principal->y + 5 < HEIGHT - 1)   principal->y += principal->dy;
		if (tecla == DERECHA && principal->x + 5 < WIDTH - 1)  principal->x += principal->dx;
		if (tecla == IZQUIERDA && principal->x > 0)			  principal->x -= principal->dx;

		//dibujar
		if (nivel == 1)
		{
			if (tecla == IZQUIERDA)
				dibujarPersonajePrincipalIzquierda1(principal->x, principal->y);
			else dibujarPersonajePrincipalDerecha1(principal->x, principal->y);
		}
		else
		{
			if (tecla == IZQUIERDA)
				dibujarPersonajePrincipalIzquierda2(principal->x, principal->y);
			else dibujarPersonajePrincipalDerecha2(principal->x, principal->y);
		}

	}

}

bool identificarColision(int x1, int y1, int ancho, int altura, int ancho2, int altura2, float x2, float y2)
{

	if (x1 <= x2 + ancho2 - 1 && x1 + ancho - 1 >= x2 && y1 < y2 + altura2 - 1 && y1 + altura - 1 >= y2)

		return true;
	else
		return false;

}

void Nivel_3(bool* menu)
{
	int* minutos = new int; *minutos = 1;
	Principal* principal = new Principal; 

	Console::Clear();
	generar_escenario3();

	while (*menu == false)
	{
		vida();
		mostrarNivel(3);
		tiempo(minutos);

		moverConTeclas(principal, 3);
		_sleep(60);

		if (kbhit())
		{
			char tecla = getch();
			tecla = toupper(tecla);

			if (tecla == ESCAPE)
				*menu = true;

			if (tecla == 'X')
				break;
		}
	}

	delete principal;
	delete[] minutos; 

	Console::Clear();
	system("color 7b");
	Ganaste();

	system("pause>0");
	Console::Clear();
	Perdiste(); 
}

void Nivel_2(bool* nivel3Desbloqueado, bool* menu)
{
	int* minutos = new int; *minutos = 2;
	Principal* principal = new Principal; 

	bool nivel3 = false;

	Console::Clear();
	generar_escenario2();

	while (*menu == false)
	{
		vida();
		mostrarNivel(2);
		tiempo(minutos);

		moverConTeclas(principal, 2);
		_sleep(60); 

		if (kbhit())
		{
			char tecla = getch();
			tecla = toupper(tecla);

			if (tecla == ESCAPE)
				*menu = true;

			if (tecla == 'X')
			{
				*nivel3Desbloqueado = true;
				break;
			}
		}
	}

	//...

	delete[] minutos; 
	delete principal;

	if (*nivel3Desbloqueado)
		Nivel_3(menu);
}

void Nivel_1(bool* nivel2Desbloqueado, bool* nivel3Desbloqueado, bool* menu) 
{
	int* minutos = new int; *minutos = 3;

	Principal* principal = new Principal; 
 
	//aliados
	int* cantAliados = new int; *cantAliados = 3;
	float* aliadosX = new float[*cantAliados];
	float* aliadosY = new float[*cantAliados];
	float dirX = 0.5, dirY = 0.5;

	Random r;
	//agentes
	int* cantAgentes = new int; *cantAgentes = 2;
	Agentes* agentes = new Agentes[*cantAgentes];
	float* agDirX = new float; *agDirX = 1;
	bool movAgentes = true;

	//Desechos
	Desechos* cartones = new Desechos; cartones->cantCartones = 0;
	Desechos* posCartones = new Desechos[cartones->cantCartones];
	cartones->contCartones = 7;

	dibujarPlatano(2, 2);
	for (int i = 0; i < *cantAgentes; i++)
	{
		agentes[i].botarDesecho = true;
		agentes[i].y = tAgentesY[r.Next(0, 2)];
		agentes[i].x = 3;
	}

	for (int i = 0; i < *cantAliados; i++)
	{
		aliadosY[i] = r.Next(20, HEIGHT - 10);
		aliadosX[i] = r.Next(3, WIDTH - 3);
	}

	generar_escenario1();
	dibujarPersonajePrincipalDerecha1(principal->x, principal->y);  

	cursor(67, 4); cout << "-CONTADORES-";
	cursor(67, 5); cout << "Cartones: ";

	while (*menu == false)
	{
		cursor(77, 5); cout << cartones->contCartones << " ";

		vida();
		mostrarNivel(1);
		tiempo(minutos);

		moverConTeclas(principal, 1);

		//MOVIMIENTO AGENTES

		for (int cont = 0; cont < *cantAgentes; cont++)
		{
			if (movAgentes)
			{
				//borrar
				borrarAgentes(agentes[cont].x, agentes[cont].y);

				//mover
				if (agentes[cont].x + *agDirX < 0 || agentes[cont].x + 4 >= WIDTH)
				{
					agentes[cont].y = tAgentesY[r.Next(0, 2)];
					agentes[cont].x = 3;
				}
				agentes[cont].x = agentes[cont].x + *agDirX;

				//dibujar
				dibujarAgentes(agentes[cont].x, agentes[cont].y);
				
			}

			//Botar Desechos

			if (agentes[cont].botarDesecho)
			{
				if (agentes[cont].x == r.Next(20, 61))
				{
					cartones->cantCartones += 1;

					// agregarCajaDeCarton(int x, int y)
					/*
					*
						Carton* cartones = new Carton [cartones->cantCartones];



						for (int i = 0; i < cartones->cantCartones - 1; ++i) {
							carontes[i] = antiguoArregloDeCartones[i];
						}



						cartones[cartones->cantCartones - 1].x = x;
						cartones[cartones->cantCartones - 1].y = y;
					*/

					//Dibujar Carton
					for (int i = 0; i < cartones->cantCartones; i++)
					{
						posCartones[cont].cartonesX = agentes[cont].x;
						posCartones[cont].cartonesY = agentes[cont].y + 4;
						dibujarCarton(posCartones[cont].cartonesX, posCartones[cont].cartonesY);

					}
				}
			}

		}

		//MOVIMIENTO ALIADOS

		if (cartones->contCartones != 0 && cartones->contCartones % 7 == 0)
		{
			for (int cont = 0; cont < *cantAliados; cont++)
			{
				//borrar
				borrarAliados(aliadosX[cont], aliadosY[cont]); 

				//mover
				if (aliadosX[cont] + dirX < 0 || aliadosX[cont] + 4 >= WIDTH) dirX *= -1;
				if (aliadosY[cont] + dirY < 17 || aliadosY[cont] + 4 + dirY >= HEIGHT) dirY *= -1;
				aliadosX[cont] += dirX;
				aliadosY[cont] += dirY;

				//dibujar
				dibujarAliados(aliadosX[cont], aliadosY[cont]);

			}
			_sleep(60);
		}

		//COLISIONES

		for (int i = 0; i < *cantAgentes; i++)
		{
			if (identificarColision(principal->x, principal->y, 6, 5, 3, 4, agentes[i].x, agentes[i].y))
			{
				agDirX = 0;  movAgentes = false;
				agentes[i].botarDesecho = false; 
				for (int i = 0; i < *cantAgentes; i++)
					borrarAgentes(agentes[i].x, agentes[i].y);
			}
		}

		for (int i = 0; i < cartones->cantCartones; i++)
		{
			if (identificarColision(principal->x, principal->y, 6, 5, 3, 2, posCartones[i].cartonesX, posCartones[i].cartonesY))
			{
				principal->x = 0;
				cartones->contCartones++;
				borrarCarton(posCartones[i].cartonesX, posCartones[i].cartonesY);
			}
		}

		if (kbhit())
		{
			char tecla = getch();
			tecla = toupper(tecla);
			if (tecla == 'X')
			{
				*nivel2Desbloqueado = true;
				break;
			}

			if (tecla == ESCAPE)
				*menu = true;
		}

	}

	delete[] minutos; 
	delete principal;
	delete cantAliados;
	delete cantAgentes;
	delete[] agentes; 
	delete agDirX;
	delete cartones;
	delete[] posCartones; 
	delete[] aliadosX;
	delete[] aliadosY;

	if (*nivel2Desbloqueado)
		Nivel_2(nivel3Desbloqueado, menu);

} 


void configurarTiempo()
{

}

void configurarVelocidadJugador()
{

}

void configurarVelocidadAgentesContaminadores()
{

}

void configurarControles()
{
	short opcion;
	system("cls");
	setlocale(LC_ALL, "spanish");
	do
	{
		Console::SetCursorPosition(10, 1); cout << "CONFIGURAR CONTROLES";
		Console::SetCursorPosition(10, 3); cout << "[1] Jugar con Teclas Direccionales";
		Console::SetCursorPosition(10, 4); cout << "[2] Jugar con WASD";
		Console::SetCursorPosition(10, 6); cout << "Ingrese una opción: ";
		cin >> opcion;
	} while (opcion < 1 || opcion > 2);
}

void configurarSonido()
{

}

void configurarDificultad()
{
	short opcion;
	system("cls");
	setlocale(LC_ALL, "spanish");

	do
	{
		cursor(10, 1); cout << "CONFIGURAR DIFICULTAD";
		cursor(10, 3); cout << "[1] Tiempo";
		cursor(10, 4); cout << "[2] Velocidad del Jugador";
		cursor(10, 5); cout << "[3] Velocidad de los Agentes Contaminadores";
		cursor(10, 7); cout << "Ingrese una opción: ";
		cin >> opcion;
	} while (opcion < 1 || opcion > 3);

	switch (opcion)
	{
	case 1:
		configurarTiempo();
		break;
	case 2:
		configurarVelocidadJugador();
		break;
	case 3:
		configurarVelocidadAgentesContaminadores();
		break;
	default:
		break;
	}
}

void Nueva_Partida(bool* nivel2Desbloqueado, bool* nivel3Desbloqueado, bool* menu)
{
	short Opcion1;
	system("cls");
			
	if (*nivel2Desbloqueado)
	{
		do
		{
			cursor(12, 1); cout << "---------- SELECCIONE UN NIVEL ----------";
			cursor(9, 3); cout << "|\t1\t|\t2\t|\t3\t|";
			cursor(18, 5); cout << "Ingrese el n" << char(163) << "mero de nivel : ";
			cin >> Opcion1;

		} while (Opcion1 < 1 || Opcion1 > 3);

		switch (Opcion1)
		{
		case 1:
			system("cls");
			Nivel_1(nivel2Desbloqueado, nivel3Desbloqueado, menu);
			break;

		case 2:
			system("cls");
			Nivel_2(nivel3Desbloqueado, menu);
			break;

		case 3:
			if (*nivel3Desbloqueado)
			{
				system("cls");
				Nivel_3(menu);
			}
			else
				Console::SetCursorPosition(9, 7); cout << "Nivel no Desbloqueado. A" << char(163) << "n no puede acceder a " << char(130) << "l.";
			break;
		default: break;
		}
	}
	else
		Nivel_1(nivel2Desbloqueado, nivel3Desbloqueado, menu);
}

void Instrucciones()
{
	escribirInstrucciones();

	cursor(15, 11); cout << "El objetivo del juego es colocar los desechos en los";
	cursor(15, 12); cout << "tachos correspondientes dentro del tiempo l" << char(161) << "mite.";

	escribirNivel(22, 15);
	escribir1(52, 15);

	cursor(12, 21); cout << "Deber" << char(160) << "s recoger 30 desechos para ganar. Si hay m" << char(160) << "s de 5 ";
	cursor(12, 22); cout << "desechos en el piso simult" << char(160) << "neamente, se disminuir" << char(160) << " la vida.";
	cursor(12, 23); cout << "Al juntar 5 cartones, podr" << char(160) << "s recuperar vida.";

	escribirNivel(22, 26);
	escribir2(52, 26);

	cursor(12, 32); cout << "Deber" << char(160) << "s recoger 35 desechos para ganar. Si hay m" << char(160) << "s de 5 ";
	cursor(12, 33); cout << "desechos en el piso simult" << char(160) << "neamente o un desecho reciclable";
	cursor(12, 34); cout << "termina en un tacho org" << char(160) << "nico, se disminuir" << char(160) << " la vida. ";
	cursor(12, 35); cout << "Al juntar 7 cartones, podr" << char(160) << "s recuperar vida. Al juntar 7 latas";
	cursor(12, 36); cout << "podr" << char(160) << "s llamar a un aliado.";
	
	cursor(23, 38); cout << "Presiona ENTER para continuar...";

	system("pause>0");
	Console::Clear();
	
	escribirNivel(22, 2);
	escribir3(52, 2);

	cursor(12, 10); cout << "Deber" << char(160) << "s recoger 40 desechos para ganar. Si alg" << char(163) << "n desecho";
	cursor(12, 11); cout << "reciclable termina en un tacho org" << char(160) << "nico, se disminuir" << char(160) << " la vida.";
	cursor(11, 12); cout << " Al juntar 10 cartones, podr" << char(160) << "s recuperar vida. Al juntar 10 latas";
	cursor(12, 13); cout << "podr" << char(160) << "s llamar a un aliado. Al juntar 10 botellas, podr" << char(160) << "s aumentar";
	cursor(12, 14); cout << "la velocidad del Jugador.";

	escribirControles(12, 18);

	cursor(15, 25); cout << "El jugador se mover" << char(160) << " con las teclas direccionales: ";
	cursor(37, 26); cout << char(24);
	cursor(34, 27); cout << "<-" << " " << char(25) << "  " << char(26);
	cursor(15, 28); cout << "RECUERDA: Puedes cambiar los controles en el Men" << char(163) << ".";
	cursor(21, 29); cout << "Presione ENTER para volver al men" << char(163) << "";
	cout << endl;
}

void Creditos()
{
	system("cls");
	setlocale(LC_ALL, "spanish");
	Console::SetCursorPosition(23, 1); cout << "CRÉDITOS";
	Console::SetCursorPosition(17, 3); cout << "1. Gabriela Shapiama";
	Console::SetCursorPosition(17, 4); cout << "2. Antonio Navarro";
	Console::SetCursorPosition(17, 5); cout << "2. Melany Rojas";
}

void Configurar_partida()
{
	short opcion;
	setlocale(LC_ALL, "spanish");
	do
	{
		Console::SetCursorPosition(10, 1); cout << "CONFIGURAR PARTIDA";
		Console::SetCursorPosition(10, 3); cout << "[1] Controles";
		Console::SetCursorPosition(10, 4); cout << "[2] Quitar sonido";
		Console::SetCursorPosition(10, 5); cout << "[3] Dificultad";
		Console::SetCursorPosition(10, 7); cout << "Ingrese opción: ";
		cin >> opcion;
	} while (opcion < 1 || opcion > 3);

	switch (opcion)
	{
	case 1:
		configurarControles();
		break;

	case 2:
		configurarSonido();
		break;

	case 3:
		configurarDificultad();
		break;
	default: break;
	}
}

void dibujarTachos_Nivel3(int x, int y)
{
	color(12);
	cursor(x + 10, y + 20); cout << char(219) << char(220) << char(220) << char(220) << char(219);
	cursor(x + 10, y + 21); cout << char(219) << char(219) << char(219) << char(219) << char(219);
	cursor(x + 10, y + 22); cout << char(219) << char(219) << char(219) << char(219) << char(219);
	cursor(x + 10, y + 23); cout << char(219) << char(219) << char(219) << char(219) << char(219);
	cursor(x + 10, y + 24); cout << char(219) << char(219) << char(219) << char(219) << char(219);

	color(8);
	cursor(x + 16, y + 20); cout << char(219) << char(220) << char(220) << char(220) << char(219);
	cursor(x + 16, y + 21); cout << char(219) << char(219) << char(219) << char(219) << char(219);
	cursor(x + 16, y + 22); cout << char(219) << char(219) << char(219) << char(219) << char(219);
	cursor(x + 16, y + 23); cout << char(219) << char(219) << char(219) << char(219) << char(219);
	cursor(x + 16, y + 24); cout << char(219) << char(219) << char(219) << char(219) << char(219);

	color(11);
	cursor(x + 52, y + 20); cout << char(219) << char(220) << char(220) << char(220) << char(219);
	cursor(x + 52, y + 21); cout << char(219) << char(219) << char(219) << char(219) << char(219);
	cursor(x + 52, y + 22); cout << char(219) << char(219) << char(219) << char(219) << char(219);
	cursor(x + 52, y + 23); cout << char(219) << char(219) << char(219) << char(219) << char(219);
	cursor(x + 52, y + 24); cout << char(219) << char(219) << char(219) << char(219) << char(219);

	color(8);
	cursor(x + 58, y + 20); cout << char(219) << char(220) << char(220) << char(220) << char(219);
	cursor(x + 58, y + 21); cout << char(219) << char(219) << char(219) << char(219) << char(219);
	cursor(x + 58, y + 22); cout << char(219) << char(219) << char(219) << char(219) << char(219);
	cursor(x + 58, y + 23); cout << char(219) << char(219) << char(219) << char(219) << char(219);
	cursor(x + 58, y + 24); cout << char(219) << char(219) << char(219) << char(219) << char(219);

	color(14);
	cursor(x + 10, y + 30); cout << char(219) << char(220) << char(220) << char(220) << char(219);
	cursor(x + 10, y + 31); cout << char(219) << char(219) << char(219) << char(219) << char(219);
	cursor(x + 10, y + 32); cout << char(219) << char(219) << char(219) << char(219) << char(219);
	cursor(x + 10, y + 33); cout << char(219) << char(219) << char(219) << char(219) << char(219);
	cursor(x + 10, y + 34); cout << char(219) << char(219) << char(219) << char(219) << char(219);

	color(8);
	cursor(x + 16, y + 30); cout << char(219) << char(220) << char(220) << char(220) << char(219);
	cursor(x + 16, y + 31); cout << char(219) << char(219) << char(219) << char(219) << char(219);
	cursor(x + 16, y + 32); cout << char(219) << char(219) << char(219) << char(219) << char(219);
	cursor(x + 16, y + 33); cout << char(219) << char(219) << char(219) << char(219) << char(219);
	cursor(x + 16, y + 34); cout << char(219) << char(219) << char(219) << char(219) << char(219);

	color(3);
	cursor(x + 52, y + 30); cout << char(219) << char(220) << char(220) << char(220) << char(219);
	cursor(x + 52, y + 31); cout << char(219) << char(219) << char(219) << char(219) << char(219);
	cursor(x + 52, y + 32); cout << char(219) << char(219) << char(219) << char(219) << char(219);
	cursor(x + 52, y + 33); cout << char(219) << char(219) << char(219) << char(219) << char(219);
	cursor(x + 52, y + 34); cout << char(219) << char(219) << char(219) << char(219) << char(219);

	color(8);
	cursor(x + 58, y + 30); cout << char(219) << char(220) << char(220) << char(220) << char(219);
	cursor(x + 58, y + 31); cout << char(219) << char(219) << char(219) << char(219) << char(219);
	cursor(x + 58, y + 32); cout << char(219) << char(219) << char(219) << char(219) << char(219);
	cursor(x + 58, y + 33); cout << char(219) << char(219) << char(219) << char(219) << char(219);
	cursor(x + 58, y + 34); cout << char(219) << char(219) << char(219) << char(219) << char(219);
}