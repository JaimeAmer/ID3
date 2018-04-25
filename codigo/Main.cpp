#include <iostream>
#include <string>
#include <fstream>
#include "TablasDatos.h"
#include "ID3.h"
#include "termcolor.hpp"

using namespace std;


int main(int argc, char **argv) {
	setlocale(LC_ALL, "spanish");

	string rutaFicheroAtributos = "AtributosJuego.txt";
	string rutaFicheroEjemplos = "Juego.txt";

	if (argc == 3) {
		rutaFicheroAtributos = argv[1];
		rutaFicheroEjemplos = argv[2];
	}
	else if (argc == 2) {
		cout << "ERROR DE LECTURA DE FICHEROS" << endl;
		return 0;
	}

	TablasDatos datos;
	datos.lecturaDatos(rutaFicheroAtributos, rutaFicheroEjemplos);
	
	ID3 algoritmo(datos);

	cout << termcolor::blue << "     Bienvenido al Algoritmo ID3" << endl;
	cout << termcolor::red << "-------------------------------------" << endl << endl;
	algoritmo.solucion();
	cout << endl;

	system("pause");

	return 0;
}