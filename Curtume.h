#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>
#include "Estrutura.h"
#include "Colete.h"
#include "Arma.h"

using namespace std;

class Curtume : public Estrutura {
private:
	vector <pair<Colete, int>> coletes;

	string Opc; int opc, opc2;
public:
	//Construtor
	Curtume(string nome, int recursos, vector <pair<Colete, int>> coletes) : Estrutura(nome, recursos) {
		this->coletes = coletes;
	}

	//Metodos
	void entrarEstrutura(Personagem* p, int* recursos, vector<Arma>* armasCompradas) override {
		while (true) {
			system("cls");
			cout << "Opa, meu amigo! Bem-vindo ao curtume.\nAqui eu produzo e vendo diversos coletes que v�o lhe proteger l� fora.\n\n"
				<< "1.Ver coletes\n2.Conversar com o vendedor\n3.Sair\n\nComando:\n";
			getline(cin, Opc);
			try {
				opc = stoi(Opc);
				if (opc == 1) {
					verColetes(p, recursos);
				}
				else if (opc == 2) {
					conversar();
				}
				else if (opc == 3) {
					break;
				}
				else {
					throw "Comando inv�lido!";
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

	void verColetes(Personagem* p, int* recursos) {
		while (true) {
			system("cls");
			cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n";
			for (int n = 0; n < this->coletes.size(); n++) {
				cout << n + 1 << ". " << this->coletes[n].first.getNome() << ":\n\n"
					<< this->coletes[n].first.getDescricao() << "\n\n"
					<< "Pre�o: " << this->coletes[n].second << " recursos.\n"
					<< "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n";
			}
			cout << "Recursos: " << *recursos;
			cout << "\n\nDigite o n�mero do colete que deseja, ou \"c\" para voltar:\n";
			getline(cin, Opc);
			if (Opc == "c" || Opc == "C") {
				break;
			}
			try {
				opc = stoi(Opc);
				//Checando se o colete existe
				if (opc > 0 && opc <= this->coletes.size()) {
					//Checando se h� recursos suficientes
					if (this->coletes[opc - 1].second <= *recursos) {
						//Confirmando a compra
						if (confirmarCompra()) {
							(*p).setColete(this->coletes[opc - 1].first);
							(*recursos) -= this->coletes[opc - 1].second;
							cout << "\nColete comprado!\n";
							system("pause");
						}
					}
					else {
						cout << "\nRecursos insuficientes!\n";
						system("pause");
					}
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

	bool confirmarCompra() {
		cout << "\nAo comprar este colete, o colete equipado atualmente ser� perdido!\n"
			<< "Deseja continuar com a compra?\ns-sim\nn-n�o\n";
		while (true) {
			getline(cin, Opc);
			if (Opc == "s" || Opc == "S") {
				return true;
			}
			else if (Opc == "n" || Opc == "N") {
				return false;
			}
		}
	}

	void conversar() {
		escrever("\n\nAh... voc� n�o entendeu como os coletes funcionam? Eu te explico...\n\n", 50, 1000);
		escrever("Basicamente, eles v�o reduzir o dano que voc� recebe. Incr�vel, n�o?\nEnfim, caso voc� fosse tomar 5 pontos de dano e estivesse com o colete\nde couro, voc� receberia 1 ponto de dano a menos. Caso fosse o colete de\ncouro refor�ado, 2 pontos a menos. Por ai vai!\n\n", 50, 1500);
		escrever("Qu�o mais caro o colete, melhor a prote��o gerada por ele!\n\n", 50, 500);
		system("pause");
	}

	void escrever(string txt, int delay, int delayFim) {
		for (auto n : txt) {
			cout << n;
			Sleep(delay);
		}
		Sleep(delayFim);
	}
};