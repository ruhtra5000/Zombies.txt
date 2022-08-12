#pragma once
#include <iostream>
#include <string>
#include <chrono>

using namespace std;

class Arma {
private:
	string nome;
	int municao, municaoMaxima;
	int dano;
	bool comprado = false;
public:
	//Construtor
	Arma(string nome, int municaoMaxima, int dano) {
		this->nome = nome;
		this->municaoMaxima = municaoMaxima;
		this->municao = municaoMaxima;
		this->dano = dano;
	}

	//Getters e setters
	string getNome() {
		return this->nome;
	}

	int getMunicao() {
		return this->municao;
	}

	void setMunicao(int municao) {
		this->municao = municao;
	}

	int getMunicaoMaxima() {
		return this->municaoMaxima;
	}

	int getDano() {
		return this->dano;
	}

	bool getComprado() {
		return this->comprado;
	}

	void setComprado(bool comprado) {
		this->comprado = comprado;
	}

	//Metodos
	int atirar() {
		if (this->municao > 0) {
			this->municao--;
			srand(chrono::system_clock::now().time_since_epoch().count());
			if ((rand() % 100) < 90) {
				cout << "\nAcertou! Causando " << this->dano << " de dano.\n";
				system("pause");
				return this->dano;
			}
			else {
				cout << "\nErraste!\n";
				system("pause");
				return 0;
			}
		}
		else {
			cout << "\nSem munição!\n";
			system("pause");
			return 0;
		}
	}
};