#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <regex>
#include <fstream>
#include <chrono>
#include "Mapa.h"
#include "Mobilia.h"
#include "Personagem.h"
#include "Arma.h"
#include "Zumbi.h"

using namespace std;

class Cenario {
private:
	vector <Mapa> mapas;
	int cenarioAtual; //Indica qual cenario foi escolhido
	int x, y; //Posição do jogador

	int recursosEncontrados = 0;

	//Variaveis do combate
	int turno = 0; //0 = turno do jogador, 1 = turno do oponente

	//Sprites
	string sprJogador = "O ", sprChao = ". ",
		sprMobilia = "[]", sprParede = "# ",
		sprZumbi = "Z ";

	string Opc; int opc, opc2;
public:
	//Construtor
	Cenario() {}

	Cenario(vector <Mapa> mapas) {
		this->mapas = mapas;
	}

	//Getters e setters
	int getRecursosEncontrados() {
		return this->recursosEncontrados;
	}

	//Metodos
	void escolherCenario(Personagem* p) {
		this->recursosEncontrados = 0;
		srand(chrono::system_clock::now().time_since_epoch().count());
		this->cenarioAtual = (rand() % mapas.size());
		determinarPosicaoJogador();
		entrarCenario(p);
	}

	void determinarPosicaoJogador() {
		this->x = this->mapas[this->cenarioAtual].posX;
		this->y = this->mapas[this->cenarioAtual].posY;
	}

	void entrarCenario(Personagem* p) {
		while (true) {
			desenharCenario();

			cout << "Comando:\n";
			getline(cin, Opc);

			if (Opc == "c" || Opc == "C") {
				cout << "\nSaindo...\n";
				system("pause");
				reposicionarJogador();
				this->mapas[this->cenarioAtual].reajustarMobilias();
				this->mapas[this->cenarioAtual].reajustarInimigos();
				break;
			}
			else if (Opc == "desc") {
				cout << this->mapas[cenarioAtual].descricao << "\n\n";
				system("pause");
			}
			else if (regex_match(Opc, regex("[wWaAsSdD]"))) {
				movimentarJogador(Opc, p);
				checarAoRedorDoJogador(p);
				this->mapas[this->cenarioAtual].moverInimigos();
				checarAoRedorDoJogador(p);
			}
		}
	}

	void desenharCenario() {
		system("cls");
		cout << this->mapas[cenarioAtual].nome << "\n\n";
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				cout << this->mapas[cenarioAtual].mapa[i][j];
				if (j == 9) {
					cout << endl;
				}
			}
		}
		cout << "\n\n";
	}

	void movimentarJogador(string mov, Personagem* p) {
		static int posX, posY;
		posX = this->x; posY = this->y;
		if (mov == "w" || mov == "W") {//cima
			if (x != 0 && this->mapas[cenarioAtual].mapa[x - 1][y] != sprParede
				&& this->mapas[cenarioAtual].mapa[x - 1][y] != sprMobilia) {
				this->x--;
			}
			else if (this->mapas[cenarioAtual].mapa[x - 1][y] == sprMobilia) {
				vasculharMobilia(x - 1, y, (*p).getArmasSelecionadas());
			}
		}
		else if (mov == "s" || mov == "S") {//baixo
			if (x != 9 && this->mapas[cenarioAtual].mapa[x + 1][y] != sprParede
				&& this->mapas[cenarioAtual].mapa[x + 1][y] != sprMobilia) {
				this->x++;
			}
			else if (this->mapas[cenarioAtual].mapa[x + 1][y] == sprMobilia) {
				vasculharMobilia(x + 1, y, (*p).getArmasSelecionadas());
			}
		}
		else if (mov == "a" || mov == "A") {//esquerda
			if (y != 0 && this->mapas[cenarioAtual].mapa[x][y - 1] != sprParede
				&& this->mapas[cenarioAtual].mapa[x][y - 1] != sprMobilia) {
				this->y--;
			}
			else if (this->mapas[cenarioAtual].mapa[x][y - 1] == sprMobilia) {
				vasculharMobilia(x, y - 1, (*p).getArmasSelecionadas());
			}
		}
		else if (mov == "d" || mov == "D") {//direita
			if (y != 9 && this->mapas[cenarioAtual].mapa[x][y + 1] != sprParede
				&& this->mapas[cenarioAtual].mapa[x][y + 1] != sprMobilia) {
				this->y++;
			}
			else if (this->mapas[cenarioAtual].mapa[x][y + 1] == sprMobilia) {
				vasculharMobilia(x, y + 1, (*p).getArmasSelecionadas());
			}
		}
		this->mapas[cenarioAtual].mapa[posX][posY] = this->sprChao;
		this->mapas[cenarioAtual].mapa[this->x][this->y] = this->sprJogador;
	}

	void reposicionarJogador() {
		this->mapas[cenarioAtual].mapa[x][y] = this->sprChao;
		this->mapas[cenarioAtual].mapa[this->mapas[cenarioAtual].posX][this->mapas[cenarioAtual].posY] = this->sprJogador;
	}

	void vasculharMobilia(int coX, int coY, vector<Arma>* armas) {
		for (int n = 0; n < this->mapas[this->cenarioAtual].mobilias.size(); n++) {
			if (this->mapas[this->cenarioAtual].mobilias[n].getPosX() == coX &&
				this->mapas[this->cenarioAtual].mobilias[n].getPosY() == coY) {

				this->recursosEncontrados += this->mapas[this->cenarioAtual].mobilias[n].vasculhar(armas);
			}
		}
	}

	//Sistema de combate
	void checarAoRedorDoJogador(Personagem* p) {
		if (this->x != 0) {//cima
			if (this->mapas[this->cenarioAtual].mapa[x - 1][y] == this->sprZumbi) {
				combate(p, (*p).getArmasSelecionadas(), (*p).getInventario(),
					&this->mapas[cenarioAtual].inimigos[selecionarZumbi(x - 1, y)]);
			}
		}
		if (this->x != 9) {//baixo
			if (this->mapas[this->cenarioAtual].mapa[x + 1][y] == this->sprZumbi) {
				combate(p, (*p).getArmasSelecionadas(), (*p).getInventario(),
					&this->mapas[cenarioAtual].inimigos[selecionarZumbi(x + 1, y)]);
			}
		}
		if (this->y != 0) {//esquerda
			if (this->mapas[this->cenarioAtual].mapa[x][y - 1] == this->sprZumbi) {
				combate(p, (*p).getArmasSelecionadas(), (*p).getInventario(),
					&this->mapas[cenarioAtual].inimigos[selecionarZumbi(x, y - 1)]);
			}
		}
		if (this->y != 9) {//direita
			if (this->mapas[this->cenarioAtual].mapa[x][y + 1] == this->sprZumbi) {
				combate(p, (*p).getArmasSelecionadas(), (*p).getInventario(),
					&this->mapas[cenarioAtual].inimigos[selecionarZumbi(x, y + 1)]);
			}
		}
	}

	int selecionarZumbi(int x, int y) {
		for (int n = 0; n < this->mapas[cenarioAtual].inimigos.size(); n++) {
			if (this->mapas[cenarioAtual].inimigos[n].getPosX() == x &&
				this->mapas[cenarioAtual].inimigos[n].getPosY() == y) {
				return n;
			}
		}
	}

	void combate(Personagem* p, vector<Arma>* armas, vector<Cura>* curas, Zumbi* z) {
		this->turno = 0;
		while (true) {
			if (this->turno == 0) {
				turnoJogador(p, armas, curas, z);
				if ((*z).getVidaAtual() <= 0) {
					cout << "\nVocê matou o inimigo!\n";
					retirarInimigo(z);
					system("pause");
					break;
				}
			}
			else if (this->turno == 1) {
				turnoInimigo(p, z);
				if ((*p).getVidaAtual() <= 0) {
					cout << "\nVocê morreu! GAME OVER\n\n";
					system("pause");
					exit(EXIT_FAILURE);
				}
			}
		}
	}

	void mostrarStatusCombate(Personagem* p, Zumbi* z) {
		cout << "Você: (" << (*p).getVidaAtual() << "/" << (*p).getVidaMaxima() << ") | "
			<< "inimigo: (" << (*z).getVidaAtual() << "/" << (*z).getVidaMaxima() << ")\n\n";
	}

	void turnoJogador(Personagem* p, vector<Arma>* armas, vector<Cura>* curas, Zumbi* z) {
		while (this->turno == 0) {
			system("cls");
			mostrarStatusCombate(p, z);
			cout << "Seu Turno!\n\n"
				<< "1.Atacar\n"
				<< "2.Usar cura\n"
				<< "\nComando:\n";
			getline(cin, Opc);
			try {
				opc = stoi(Opc);
				//Atacar
				if (opc == 1) {
					//Mostrar as armas
					cout << "\nEscolha com qual arma atacar:\n";
					for (int n = 0; n < (*armas).size(); n++) {
						cout << n + 1 << ": " << (*armas)[n].getNome()
							<< " (" << (*armas)[n].getMunicao() << "/" << (*armas)[n].getMunicaoMaxima() << ")\n";
					}

					cout << "\nComando:\n";
					getline(cin, Opc);
					opc2 = stoi(Opc);
					if (opc2 > 0 && opc2 <= (*armas).size()) {
						(*z).setVidaAtual(((*z).getVidaAtual() - (*armas)[opc2 - 1].atirar()));
						this->turno = 1;
					}
				}
				//Curar
				else if (opc == 2) {
					//Checar se o jogador tem curas
					if ((*curas).empty()) {
						cout << "\nSem curas!\n";
						system("pause");
					}
					else {
						//Mostras curas
						cout << "\nEscolha qual cura usar:\n";
						for (int n = 0; n < (*curas).size(); n++) {
							cout << n + 1 << ". " << (*curas)[n].getNome()
								<< " (+" << (*curas)[n].getQuantCura() << ")\n";
						}

						cout << "\nComando:\n";
						getline(cin, Opc);
						opc2 = stoi(Opc);
						if (opc2 > 0 && opc2 <= (*curas).size()) {
							(*p).usarCura(opc2 - 1);
							this->turno = 1;
						}
					}
				}
			}
			catch (const char* msg) {
				cout << "\nHouve um erro: " << msg << endl;
				system("pause");
			}
			catch (exception& err) {
				cout << "\nHouve um erro: " << err.what() << endl;
				system("pause");
			}
		}
	}

	void turnoInimigo(Personagem* p, Zumbi* z) {
		system("cls");
		mostrarStatusCombate(p, z);
		cout << "Turno do inimigo:\n";
		(*p).setVidaAtual(((*p).getVidaAtual() - (*z).atacar((*p).getColete())));
		this->turno = 0;
	}

	void retirarInimigo(Zumbi* z) {
		(*z).setEstaVivo(false);
		this->mapas[cenarioAtual].mapa[(*z).getPosX()][(*z).getPosY()] = sprChao;
	}
};