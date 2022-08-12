#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include "Mobilia.h"
#include "Zumbi.h"

using namespace std;

class Mapa {
private:
	//Para mover os inimigos
	int res, antigoX, antigoY;
public:
	string nome, descricao = "";
	string mapa[10][10];
	int posX, posY;//Posição inicial do jogador num certo cenario
	vector <Mobilia> mobilias;
	vector <Zumbi> inimigos;

	void reajustarMobilias() {
		for (int n = 0; n < this->mobilias.size(); n++) {
			this->mobilias[n].setVasculhado(false);
			this->mobilias[n].setTrancaEspecial(0);
		}
	}

	void moverInimigos() {
		for (int n = 0; n < this->inimigos.size(); n++) {
			if (this->inimigos[n].getEstaVivo() == true) {
				this->antigoX = this->inimigos[n].getPosX();
				this->antigoY = this->inimigos[n].getPosY();

				while (true) {
					srand(chrono::system_clock::now().time_since_epoch().count());
					this->res = (rand() % 40);
					if (this->res < 10) {//cima
						if (this->inimigos[n].getPosX() != 0 &&
							this->mapa[this->inimigos[n].getPosX() - 1][this->inimigos[n].getPosY()] != "# " &&
							this->mapa[this->inimigos[n].getPosX() - 1][this->inimigos[n].getPosY()] != "[]") {
							this->inimigos[n].setPosX(this->inimigos[n].getPosX() - 1);
							break;
						}
					}
					else if (this->res >= 10 && this->res < 20) {//baixo
						if (this->inimigos[n].getPosX() != 9 &&
							this->mapa[this->inimigos[n].getPosX() + 1][this->inimigos[n].getPosY()] != "# " &&
							this->mapa[this->inimigos[n].getPosX() + 1][this->inimigos[n].getPosY()] != "[]") {
							this->inimigos[n].setPosX(this->inimigos[n].getPosX() + 1);
							break;
						}
					}
					else if (this->res >= 20 && this->res < 30) {//esquerda
						if (this->inimigos[n].getPosY() != 0 &&
							this->mapa[this->inimigos[n].getPosX()][this->inimigos[n].getPosY() - 1] != "# " &&
							this->mapa[this->inimigos[n].getPosX()][this->inimigos[n].getPosY() - 1] != "[]") {
							this->inimigos[n].setPosY(this->inimigos[n].getPosY() - 1);
							break;
						}
					}
					else if (this->res >= 30) {//direita
						if (this->inimigos[n].getPosY() != 9 &&
							this->mapa[this->inimigos[n].getPosX()][this->inimigos[n].getPosY() + 1] != "# " &&
							this->mapa[this->inimigos[n].getPosX()][this->inimigos[n].getPosY() + 1] != "[]") {
							this->inimigos[n].setPosY(this->inimigos[n].getPosY() + 1);
							break;
						}
					}
				}
				this->mapa[this->antigoX][this->antigoY] = ". ";
				this->mapa[this->inimigos[n].getPosX()][this->inimigos[n].getPosY()] = "Z ";
			}
		}
	}

	void reajustarInimigos() {
		//Limpar os zumbis restantes
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				if (this->mapa[i][j] == "Z ") {
					this->mapa[i][j] = ". ";
				}
			}
		}

		//Settar vida, posição inicial, recolocar o sprite...
		for (int n = 0; n < this->inimigos.size(); n++) {
			this->inimigos[n].setPosX(this->inimigos[n].getPosIniX());
			this->inimigos[n].setPosY(this->inimigos[n].getPosIniY());
			this->inimigos[n].setVidaAtual(this->inimigos[n].getVidaMaxima());
			this->inimigos[n].setEstaVivo(true);

			this->mapa[this->inimigos[n].getPosIniX()][this->inimigos[n].getPosIniY()] = "Z ";
		}
	}
};