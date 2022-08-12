#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Estrutura.h"
#include "Arma.h"
#include "Cura.h"
#include "Personagem.h"

using namespace std;

class Loja : public Estrutura {
private:
	vector <pair<Cura, int>> curas;
	vector <pair<Arma, int>> armas;

	string Opc; int opc;
public:
	//Construtor
	Loja(string nome, int recursos, vector <pair<Arma, int>> armas,
		vector <pair<Cura, int>> curas) : Estrutura(nome, recursos) {
		this->armas = armas;
		this->curas = curas;
	}

	//Getters e setters
	vector <pair<Arma, int>> getArmas() override {
		return this->armas;
	}

	//Metodos
	void entrarEstrutura(Personagem* p, int* recursos, vector<Arma>* armasCompradas) override {
		while (true) {
			system("cls");
			cout << "Olá! Bem-vindo a minha loja.\nAqui eu vendo itens de cura e armamentos.\n\n"
				<< "1.Itens de cura\n2.Armamentos\n3.Sair\n\nComando:\n";
			getline(cin, Opc);
			try {
				opc = stoi(Opc);
				if (opc == 1) {
					mostrarCuras(p, recursos);
				}
				else if (opc == 2) {
					mostrarArmas(armasCompradas, recursos);
				}
				else if (opc == 3) {
					break;
				}
				else {
					throw "Comando inválido!";
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

	void mostrarCuras(Personagem* p, int* recursos) {
		while (true) {
			system("cls");
			cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n";
			for (int n = 0; n < this->curas.size(); n++) {
				cout << n + 1 << ". " << this->curas[n].first.getNome() << ":\n\n"
					<< this->curas[n].first.getDescricao() << "\n\n"
					<< "Preço: " << this->curas[n].second << " recursos\n"
					<< "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n";
			}
			cout << "Recursos: " << *recursos << endl;
			cout << "\nDigite o número do item que dejesa, ou \"c\" para sair:\n";
			getline(cin, Opc);
			if (Opc == "c" || Opc == "C") {
				break;
			}
			else {
				try {
					opc = stoi(Opc);
					//Checando se opc existe no vector
					if (opc > 0 && opc <= this->curas.size()) {
						//Checando se você tem recursos
						if (this->curas[opc - 1].second <= *recursos) {
							//Checando se o inventário está cheio
							if ((*p).tamanhoInventario() < 5) {
								(*p).adicionarItemInventario(this->curas[opc - 1].first);
								(*recursos) -= this->curas[opc - 1].second;
								cout << "\nItem comprado!\n";
								system("pause");
							}
							else {
								cout << "\nSeu inventário está cheio!\n";
								system("pause");
							}
						}
						else {
							cout << "\nRecursos insuficientes!\n";
							system("pause");
						}
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
	}

	void mostrarArmas(vector<Arma>* armasCompradas, int* recursos) {
		while (true) {
			system("cls");
			cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n";
			for (int n = 0; n < this->armas.size(); n++) {
				cout << n + 1 << ". " << this->armas[n].first.getNome() << ":\n"
					<< "Capacidade: " << this->armas[n].first.getMunicaoMaxima() << " munições.\n"
					<< "Dano: " << this->armas[n].first.getDano() << " pontos de dano.\n"
					<< "Preço: " << this->armas[n].second << " recursos.\n"
					<< "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n";
			}
			cout << "Recursos: " << *recursos << endl;
			cout << "\nDigite o número do item que dejesa, ou \"c\" para sair:\n";
			getline(cin, Opc);
			if (Opc == "c" || Opc == "C") {
				break;
			}
			else {
				try {
					opc = stoi(Opc);
					//Checando se opc existe
					if (opc > 0 && opc <= this->armas.size()) {
						//Checando se há recursos suficiente
						if (this->armas[opc - 1].second <= *recursos) {
							//Checando se você já tem a arma desejada
							if (!this->armas[opc - 1].first.getComprado()) {
								(*armasCompradas).push_back(this->armas[opc - 1].first);
								(*recursos) -= this->armas[opc - 1].second;
								this->armas[opc - 1].first.setComprado(true);
								cout << "\nArma comprada!\n";
								system("pause");
							}
							else {
								cout << "\nVocê já comprou esta arma!\n";
								system("pause");
							}
						}
						else {
							cout << "\nRecursos insuficientes!\n";
							system("pause");
						}
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
	}
};