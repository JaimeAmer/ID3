#include <iostream>
#include <string>
#include <fstream>
#include "TablasDatos.h"
#include "ID3.h"

using namespace std;


int main() {
	string rutaFicheroAtributos;
	string rutaFicheroDatos;

	TablasDatos datos(rutaFicheroAtributos, rutaFicheroDatos);
	
	ID3(datos.listaAtributos(), datos.listaEjemplos())

	return 0;
}