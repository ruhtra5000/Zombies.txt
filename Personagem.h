#pragma once
#include <iostream>
#include <vector>
#include "Arma.h"
#include "Cura.h"
#include "Colete.h"

using namespace std;

class Personagem {
private:
	int vidaAtual, vidaMaxima = 25;
	Colete colete;
	vector <Arma> armasSelecionadas;//Max: 2
	vector <Cura> inventario; //Max: 5
public:
	//Construtor
	Personagem() {}

	Personagem(Arma arma1, int vidaAtual, Colete colete) {
		this->vidaAtual = vidaAtual;
		this->armasSelecionadas.push_back(arma1);
		this->colete = colete;
	}

	Personagem(vector <Arma> armasSelecionadas, int vidaAtual, Colete colete, vector<Cura> inventario) {
		this->vidaAtual = vidaAtual;
		this->armasSelecionadas = armasSelecionadas;
		this->colete = colete;
		this->inventario = inventario;
	}

	//Getters e setters
	int getVidaAtual() {
		return this->vidaAtual;
	}

	void setVidaAtual(int vidaAtual) {
		if (vidaAtual > this->vidaMaxima) {
			this->vidaAtual = this->vidaMaxima;
		}
		else {
			this->vidaAtual = vidaAtual;
		}
	}

	int getVidaMaxima() {
		return this->vidaMaxima;
	}

	auto getColete() {
		return this->colete;
	}

	void setColete(Colete colete) {
		this->colete = colete;
	}

	auto getArmasSelecionadas() {
		return &this->armasSelecionadas;
	}

	auto getInventario() {
		return &this->inventario;
	}

	//Metodos
	void mostrarStatus() {
		system("cls");
		cout << "Pontos de vida: " << this->vidaAtual << "/" << this->vidaMaxima << "\n\n"
			<< "Colete: " << this->colete.getNome() << "\n"
			<< "\nArmas selecionadas: ";
		if (this->armasSelecionadas.size() == 1) {
			cout << this->armasSelecionadas[0].getNome() << ".\n";
		}
		else if (this->armasSelecionadas.size() == 2) {
			cout << this->armasSelecionadas[0].getNome() << ", "
				<< this->armasSelecionadas[1].getNome() << ".\n";
		}
		cout << "\nItens de cura: ";
		if (this->inventario.empty()) {
			cout << "Sem itens de cura.\n\n";
		}
		else {
			for (int n = 0; n < this->inventario.size(); n++) {
				cout << this->inventario[n].getNome();
				if (n == this->inventario.size() - 1) {
					cout << ".\n\n";
				}
				else {
					cout << ", ";
				}
			}
		}
		system("pause");
	}

	void adicionarItemInventario(Cura c) {
		if (this->inventario.size() < 5) {
			this->inventario.push_back(c);
		}
	}

	int tamanhoInventario() {
		return this->inventario.size();
	}

	void usarCura(int pos) {
		if ((this->vidaAtual + this->inventario[pos].getQuantCura()) > this->vidaMaxima) {
			this->vidaAtual = this->vidaMaxima;
		}
		else {
			this->vidaAtual += this->inventario[pos].getQuantCura();
		}
		this->inventario.erase(this->inventario.begin() + pos);
		cout << "\nVocê se curou!\n";
		system("pause");
	}
};