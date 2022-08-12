#pragma once
#include <iostream>
#include "Personagem.h"

using namespace std;

class Estrutura {
protected:
	string nome;
	int recursosParaConstruir;
	bool foiConstruido = false;
public:
	//Construtor
	Estrutura(string nome, int recursosParaConstruir) {
		this->nome = nome;
		this->recursosParaConstruir = recursosParaConstruir;
	}

	//Getters e Setters
	string getNome() {
		return this->nome;
	}

	int getRecursosParaConstruir() {
		return this->recursosParaConstruir;
	}

	bool getFoiConstruido() {
		return this->foiConstruido;
	}

	void setFoiConstruido(bool foiConstruido) {
		this->foiConstruido = foiConstruido;
	}

	vector <pair<Arma, int>> virtual getArmas() {
		vector<pair<Arma, int>> tmp;
		return tmp;
	}

	bool virtual getFinalConfirm() {
		return false;
	}

	//Metodos
	void checarSeFoiConstruido(Personagem* p, int* recursos, vector<Arma>* armasCompradas) {
		if (!this->foiConstruido) {
			cout << "\nEsta estrutura ainda não foi construída!\n";
			system("pause");
		}
		else {
			entrarEstrutura(p, recursos, armasCompradas);
		}
	}

	void virtual entrarEstrutura(Personagem* p, int* recursos, vector<Arma>* armasCompradas) {}
};