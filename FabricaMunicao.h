#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>
#include "Estrutura.h"
#include "Arma.h"

using namespace std;

class FabricaMunicao : public Estrutura {
private:
	string texto = "Fabricando...", texto2 = "Consertando...";
	string Opc; int opc;
public:
	//Construtor
	FabricaMunicao(string nome, int recursos) : Estrutura(nome, recursos) {

	}

	//Metodos
	void entrarEstrutura(Personagem* p, int* recursos, vector<Arma>* armasCompradas) override {
		while (true) {
			system("cls");
			cout << "Bom dia, patr�o! Eis aqui a minha f�brica de muni��o!\n"
				<< "Aqui voc� pode fabricar muni��o para qualquer arma de gra�a!\n"
				<< "Basta apenas esperar um pouco.\n\n"
				<< "1.Fabricar muni��o\n2.Consertar faca\n3.Sair\n\nComando:\n";
			getline(cin, Opc);
			try {
				opc = stoi(Opc);
				if (opc == 1) {
					fabricarMunicao((*p).getArmasSelecionadas());
				}
				else if (opc == 2) {
					consertarFaca((*p).getArmasSelecionadas());
				}
				else if (opc == 3) {
					break;
				}
				else {
					throw "Comando inv�lido";
				}
			}
			catch (const char* msg) {
				cout << "Houve um erro: " << msg << endl;
				system("pause");
			}
			catch (exception& err) {
				cout << "Houve um erro: " << err.what() << endl;
				system("pause");
			}
		}
	}

	void fabricarMunicao(vector<Arma>* armas) {
		while (true) {
			system("cls");
			cout << "Escolha uma arma para fabricar sua muni��o:\n\n";
			for (int n = 0; n <= (*armas).size(); n++) {
				if (n == (*armas).size()) {
					cout << n + 1 << ".Voltar\n\nComando:\n";
				}
				else {
					cout << n + 1 << "." << (*armas)[n].getNome()
						<< " (" << (*armas)[n].getMunicao() << "/" << (*armas)[n].getMunicaoMaxima() << ")\n";
				}
			}

			getline(cin, Opc);
			try {
				opc = stoi(Opc);
				if (opc == (*armas).size() + 1) {
					break;
				}
				else if (opc > 0 && opc <= (*armas).size()) {
					//Checando se � uma faca
					if ((*armas)[opc - 1].getNome() == "Faca") {
						cout << "\nQuer fazer bala pra uma faca �?\n";
						system("pause");
					}
					else {
						//Checando a muni��o
						if ((*armas)[opc - 1].getMunicao() < (*armas)[opc - 1].getMunicaoMaxima()) {
							escreverTexto(this->texto, 380);
							(*armas)[opc - 1].setMunicao((*armas)[opc - 1].getMunicao() + 1);
						}
						else {
							cout << "\nEsta arma j� est� com a muni��o cheia!\n";
							system("pause");
						}
					}
				}
				else {
					throw "Comando inv�lido";
				}
			}
			catch (const char* msg) {
				cout << "\nHouve um erro: " << msg << endl;
				system("pause");
			}
			catch (exception& err) {
				cout << "\nHouve um erro: " << err.what() << endl;
				system("pause");
			}
		}
	}

	void consertarFaca(vector <Arma>* armas) {
		opc = buscarArmaPorNome(armas, "Faca");
		if (opc == -1) {
			cout << "\nU�... cad� a faca pra eu consertar, amig�o?\n";
			system("pause");
		}
		else {
			if ((*armas)[opc].getMunicao() == (*armas)[opc].getMunicaoMaxima()) {
				cout << "\nRapaz... tua faca t� s� o fil�. Tem o que consertar aqui n�o!\n";
				system("pause");
			}
			else {
				escreverTexto(this->texto2, 500);
				(*armas)[opc].setMunicao((*armas)[opc].getMunicaoMaxima());
				cout << "\n\nAgora sim. Sua faca t� �tima, aproveite!\n";
				system("pause");
			}
		}
	}

	void escreverTexto(string txt, int delay) {
		cout << "\n";
		for (auto n : txt) {
			cout << n;
			Sleep(delay);
		}
	}

	int buscarArmaPorNome(vector <Arma>* armas, string nome) {
		for (int n = 0; n < (*armas).size(); n++) {
			if ((*armas)[n].getNome() == nome) {
				return n;
			}
		}
		return -1;
	}
};