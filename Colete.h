#pragma once
#include <iostream>
#include <string>

using namespace std;

class Colete {
private:
	string nome;
	string descricao;
	int protecao;
public:
	//Construtor
	Colete() {}

	Colete(string nome, string descricao, int protecao) {
		this->nome = nome;
		this->descricao = descricao;
		this->protecao = protecao;
	}

	//Getters e setters
	string getNome() {
		return this->nome;
	}

	string getDescricao() {
		return this->descricao;
	}

	int getProtecao() {
		return this->protecao;
	}
};