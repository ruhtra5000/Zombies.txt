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
			cout << "Bom dia, patrão! Eis aqui a minha fábrica de munição!\n"
				<< "Aqui você pode fabricar munição para qualquer arma de graça!\n"
				<< "Basta apenas esperar um pouco.\n\n"
				<< "1.Fabricar munição\n2.Consertar faca\n3.Sair\n\nComando:\n";
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
					throw "Comando inválido";
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
			cout << "Escolha uma arma para fabricar sua munição:\n\n";
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
					//Checando se é uma faca
					if ((*armas)[opc - 1].getNome() == "Faca") {
						cout << "\nQuer fazer bala pra uma faca é?\n";
						system("pause");
					}
					else {
						//Checando a munição
						if ((*armas)[opc - 1].getMunicao() < (*armas)[opc - 1].getMunicaoMaxima()) {
							escreverTexto(this->texto, 380);
							(*armas)[opc - 1].setMunicao((*armas)[opc - 1].getMunicao() + 1);
						}
						else {
							cout << "\nEsta arma já está com a munição cheia!\n";
							system("pause");
						}
					}
				}
				else {
					throw "Comando inválido";
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
			cout << "\nUé... cadê a faca pra eu consertar, amigão?\n";
			system("pause");
		}
		else {
			if ((*armas)[opc].getMunicao() == (*armas)[opc].getMunicaoMaxima()) {
				cout << "\nRapaz... tua faca tá só o filé. Tem o que consertar aqui não!\n";
				system("pause");
			}
			else {
				escreverTexto(this->texto2, 500);
				(*armas)[opc].setMunicao((*armas)[opc].getMunicaoMaxima());
				cout << "\n\nAgora sim. Sua faca tá ótima, aproveite!\n";
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