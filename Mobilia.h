#pragma once
#include <iostream>
#include <vector>
#include <chrono>
#include "Arma.h"

using namespace std;

class Mobilia {
private:
	int recursos = 0;
	int posX, posY;
	bool vasculhado = false;
	int trancaEspecial = 0; //0 = não setado, 1 = não tem, 2 = tem
public:
	//Construtor
	Mobilia(int posX, int posY) {
		this->posX = posX;
		this->posY = posY;
	}

	//Getters e setters
	int getPosX() {
		return this->posX;
	}

	int getPosY() {
		return this->posY;
	}

	void setVasculhado(bool vasculhado) {
		this->vasculhado = vasculhado;
	}

	void setTrancaEspecial(int trancaEspecial) {
		this->trancaEspecial = trancaEspecial;
	}

	//Metodos
	int vasculhar(vector <Arma>* armas) {
		//Settando a tranca
		if (this->trancaEspecial == 0) {
			srand(chrono::system_clock::now().time_since_epoch().count());
			if ((rand() % 100) < 30) {
				this->trancaEspecial = 2;
			}
			else {
				this->trancaEspecial = 1;
			}
		}

		this->recursos = 0;
		if (this->vasculhado == true) {
			cout << "\nEsta mobília já foi vasculhada!" << endl;
		}
		else {
			if (this->trancaEspecial == 2) {
				cout << "\nEssa mobília tem uma tranca...";
				if (temFaca(armas)) {
					cout << " Felizmente eu tenho uma faca pra abrir.";
					gerarRecursos();
				}
				else {
					cout << " Se eu tivesse uma faca, talvez eu pudesse abrí-la\n";
				}
			}
			else {
				gerarRecursos();
			}
		}
		system("pause");
		return this->recursos;
	}

	void gerarRecursos() {
		srand(chrono::system_clock::now().time_since_epoch().count());
		if ((rand() % 100) < 70) {
			srand(chrono::system_clock::now().time_since_epoch().count());
			this->recursos = (rand() % 10) + 1;
			cout << "\nVocê encontrou " << this->recursos << " recursos!" << endl;
		}
		else {
			cout << "\nEsta mobília está vazia!" << endl;
		}
		this->vasculhado = true;
	}

	bool temFaca(vector <Arma>* armas) {
		for (auto n : *armas) {
			if (n.getNome() == "Faca") {
				return true;
			}
		}
		return false;
	}
};