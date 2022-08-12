#include <iostream>
#include "Inicializador.h"

using namespace std;

int main() {
	setlocale(LC_ALL, "");

	Inicializador init{};
	init.menu();

	return 0;
}