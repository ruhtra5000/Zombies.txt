#pragma once
#include <iostream>
#include <string>
#include <Windows.h>
#include "Estrutura.h"
#include "Arma.h"

using namespace std;

class Laboratorio : public Estrutura {
private:
	bool finalConfirm = false;
	string Opc; int opc;
public:
	//Construtor
	Laboratorio(string nome, int recursos) : Estrutura(nome, recursos) {

	}

	//Getters e setters
	bool getFinalConfirm() override {
		return this->finalConfirm;
	}

	//Metodos
	void entrarEstrutura(Personagem* p, int* recursos, vector<Arma>* armasCompradas) override {
		finalConfirm = false;
		while (true) {
			system("cls");
			cout << "Bom dia, amigo. Bem-vindo ao laboratório.\n"
				<< "Finalmente com todas essas ferramentas, eu posso fazer uma\n"
				<< "vacina pra curar esta cidade!\n\n";

			cout << "1.Fazer vacina\n2.Conversar com o cientista\n3.Sair\n\nComando:\n";
			getline(cin, Opc);
			try {
				opc = stoi(Opc);
				if (opc == 1) {
					fazerVacina(recursos);
					if (this->finalConfirm) {
						break;
					}
				}
				else if (opc == 2) {
					conversar();
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

	void fazerVacina(int* recursos) {
		if ((*recursos) < 1000) {
			cout << "\n\nEu preciso de 1000 recursos para produzir uma vacina!\n";
			system("pause");
		}
		else {
			if (confirmarFinal()) {
				system("cls");
				Sleep(2500);
				escrever("Depois de algumas semanas com os recursos, o cientista conseguiu\nfazer a engenharia reversa no vírus.\n\n", 40, 1500);
				escrever("Após a vacina ter sido criada com sucesso, você pôde avisar ao\nserviço secreto estadunidense, que, por sua vez, enviou diversos\nagentes para ajudarem na cura da cidade.\n\n", 40, 1500);
				escrever("Por mais que houvessem inúmeros agentes do serviço secreto em\nCraylden Harbour, o paradeiro dos chefes da Innovation X permanece\ndesconhecido.\n\n", 40, 1000);
				system("pause");

				//Tela final
				system("cls");
				cout << "\n\n\n\n";
				escrever("                           ________  _                \n                          |_   __  |(_)               \n                            | |_ \\_|__   _ .--..--.   \n                            |  _|  [  | [ `.-. .-. |  \n                           _| |_    | |  | | | | | |  \n                          |_____|  [___][___||__||__] \n\n                         =-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n                              Obrigado por jogar!\n\n\n\n\n\n", 25, 4000);
				system("pause");
				this->finalConfirm = true;
			}
		}
	}

	bool confirmarFinal() {
		cout << "\nAo entregar todos os recursos, você só poderá voltar do\nseu último save. Deseja continuar?\n\ns-sim\nn-não\n\nComando:\n";
		while (true) {
			getline(cin, Opc);
			if (Opc == "n" || Opc == "N") {
				return false;
			}
			else if (Opc == "s" || Opc == "S") {
				return true;
			}
		}
	}

	void conversar() {
		escrever("\n\nBem... eu era um dos cientistas da Innovation X, e sim, eu\ntrabalhei diretamente com o vírus, então fazer uma engenharia reversa\ncom todo esse equipamento não deve ser tão difícil.\n\n", 50, 1500);
		escrever("E também, por algum milagre, eu sobrevivi a toda essa loucura\nque aconteceu na cidade.\n\n", 50, 500);
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