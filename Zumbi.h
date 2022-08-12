#pragma once
#include <iostream>
#include <chrono>
#include "Colete.h"

using namespace std;

class Zumbi {
private:
	int vidaAtual = 20, vidaMaxima = 20;
	int dano = 5; //testando
	bool estaVivo = true;
	//Posição
	int posIniX, posIniY; //posição inicial
	int posX, posY; //posição atual
public:
	//Construtor
	Zumbi() {};

	Zumbi(int posIniX, int posIniY) {
		this->posIniX = posIniX;
		this->posIniY = posIniY;
		this->posX = posIniX;
		this->posY = posIniY;
	};

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

	int getPosIniX() {
		return this->posIniX;
	}

	int getPosIniY() {
		return this->posIniY;
	}

	int getPosX() {
		return this->posX;
	}

	void setPosX(int posX) {
		this->posX = posX;
	}

	int getPosY() {
		return this->posY;
	}

	void setPosY(int posY) {
		this->posY = posY;
	}

	bool getEstaVivo() {
		return this->estaVivo;
	}

	void setEstaVivo(bool estaVivo) {
		this->estaVivo = estaVivo;
	}

	//Metodos
	int atacar(Colete c) {
		srand(chrono::system_clock::now().time_since_epoch().count());
		if ((rand() % 100) < 50) {
			cout << "\nZumbi erra seu ataque!\n";
			system("pause");
			return 0;
		}
		else {
			cout << "\nZumbi dá uma mordida. Causando " << (this->dano - c.getProtecao()) << " de dano\n";
			system("pause");
			return this->dano - c.getProtecao();
		}
	}
};