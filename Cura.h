#pragma once
#include <iostream>
#include <string>

using namespace std;

class Cura {
private:
	string nome;
	string descricao;
	int quantCura;
public:
	//Construtor
	Cura(string nome, string descricao, int quantCura) {
		this->nome = nome;
		this->descricao = descricao;
		this->quantCura = quantCura;
	}

	//Getters e setters
	string getNome() {
		return this->nome;
	}

	string getDescricao() {
		return this->descricao;
	}

	int getQuantCura() {
		return this->quantCura;
	}
};