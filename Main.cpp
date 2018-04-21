#include <iostream>
#include <string>
#include <fstream>
#include "TablasDatos.h"
#include "ID3.h"

using namespace std;


int main() {
	string rutaFicheroAtributos = "AtributosJuego2.txt";
	string rutaFicheroEjemplos = "Juego2.txt";

	TablasDatos datos;
	datos.lecturaDatos(rutaFicheroAtributos, rutaFicheroEjemplos);
	
	//ID3(datos.listaAtributos(), datos.listaEjemplos());

	return 0;
}