#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <Windows.h>
#include "Base.h"
#include "Estrutura.h"
#include "Loja.h"
#include "Curtume.h"
#include "FabricaMunicao.h"
#include "Laboratorio.h"
#include "Cenario.h"
#include "Mapa.h"
#include "Mobilia.h"
#include "Personagem.h"
#include "Arma.h"
#include "Cura.h"
#include "Colete.h"
#include "Zumbi.h"

using namespace std;

class Inicializador {
private:
	//Operações com arquivos
	fstream arquivo;
	string linha, elemento, elemento2;
	int elemento3;

	//Construção dos mapas
	vector <Mapa> mapas;
	Mapa mapaBase;
	int x = 0, y = 0;

	//Dados de entrada
	string Opc; int opc;
public:
	void menu() {
		while (true) {
			system("cls");
			cout << "  ______                  _      _               _          _   \n |___  /                 | |    (_)             | |        | |  \n    / /  ___   _ __ ___  | |__   _   ___  ___   | |_ __  __| |_ \n   / /  / _ \\ | '_ ` _ \\ | '_ \\ | | / _ \\/ __|  | __|\\ \\/ /| __|\n  / /__| (_) || | | | | || |_) || ||  __/\\__ \\ _| |_  >  < | |_ \n /_____|\\___/ |_| |_| |_||_.__/ |_| \\___||___/(_)\\__|/_/\\_\\ \\__|\n\n";

			cout << "\n1.Novo jogo\n2.Carregar save\n3.Créditos\n4.Fechar\n\nComando:\n";
			getline(cin, Opc);
			try {
				opc = stoi(Opc);
				if (opc == 1) {
					historiaInicial();
				}
				else if (opc == 2) {
					carregarSave();
				}
				else if (opc == 3) {
					creditos();
				}
				else if (opc == 4) {
					cout << "\nFechando...\n";
					system("pause");
					break;
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

	//Novo save
	void historiaInicial() {
		system("cls");
		Sleep(1500);
		escrever("1 de março de 1988, Craylden Harbour.", 40, "\n\n", 1000);
		escrever("A cidade portuária de Craylden Harbour era muito conhecida pela\ngrande empresa farmacéutica Innovation X, que tinha sua base na cidade.", 40, "\n\n", 1500);
		escrever("O porto da cidade era muito utilizado para o escoamento dos produtos da\nInnovation X. Porém, durante o manuseio de um contêiner contendo um novo\nremédio, houve um grande acidente no porto.", 40, "\n\n", 500);
		system("pause");

		system("cls");
		escrever("O acidente causou um vazamento do que pensava-se ser um remédio,\nentretanto a Innovation X havia produzido um vírus para um grupo\nterrorista que atuava no norte da Europa.", 40, "\n\n", 1500);
		escrever("Como resultado do acidente, a cidade foi isolada rapidamente, e acredita-se que\ntodos os habitantes foram transformados em algum tipo de criatura que tem uma\nfome insaciável e desejo por carne humana.", 40, "\n\n", 500);
		system("pause");

		system("cls");
		escrever("E cá está você, um agente enviado pelo serviço secreto estadunidense\nbuscando descobrir se há um modo de curar esta cidade...", 60, "\n\n", 1000);
		escrever("30 de junho de 1990.", 100, "\n\n", 1000);
		escrever("Bem-vindo a Craylden Harbour", 100, "\n\n", 0);
		cout << "        __   __                     ___      _\n"
			<< "       |HH| |  |      /|           |H  |   _/ \\_\n"
			<< "       |H | |: |  _  |I|__         |  :|_-/     \\-_     _\n"
			<< "     __|  | |  |_|I| | |: |/\\_     |: H|  \\     /  |___|\n"
			<< "    |  |  | | :| | __| | :|   |_   |  H|   |___|   |:I:|\n"
			<< "    |  | H|^|  | ||  |I|  |   | |__|H  |   |   |   |:I:|\n"
			<< "    |  |  |||  | ||  | |  |   | /\\ |   |   |   |   |   |\n"
			<< "    ~~~~~~~~~~~~~~~~~~~~~~~~~~~/  \\~~~~~~~~~~~~~~~~~~~~~~~\n"
			<< "   ~ ~~  ~ ~~ ~~~ ~ ~ ~~ ~~ ~~ \\   \\__   ~  ~  ~~~~ ~~~ ~~\n"
			<< " ~~ ~ ~ ~~~ ~~  ~~ ~~~~~~~~~~ ~ \\   \\o\\  ~~ ~ ~~~~ ~ ~ ~~~\n"
			<< "   ~ ~~~~~~~~ ~ ~ ~~ ~ ~ ~ ~ ~~~ \\   \\o\\=   ~~ ~~  ~~ ~ ~~\n"
			<< "~ ~ ~ ~~~~~~~ ~  ~~ ~~ ~ ~~ ~ ~ ~~ ~ ~ ~~ ~~~ ~ ~ ~ ~ ~~~~\n\n";
		system("pause");

		system("cls");
		escrever("Durante uma breve exploração pela cidade, você nota que o centro da cidade é\nmuito perigoso, então logo você desiste de se estabelecer por lá.", 40, "\n\n", 1500);
		escrever("Após andar um pouco por uma área mais afastada da cidade, você encontra um\npequeno conjunto de sobreviventes, com apenas 4 pessoas.\nPor sorte, você consegue se juntar a eles.", 40, "\n\n\n\n\n", 1500);
		escrever("(Se você não conhece o jogo, é indicado ler o menu de ajuda antes de iniciar!)", 40, "\n\n", 500);
		system("pause");
		iniciarNovoSave();
	}

	void iniciarNovoSave() {
		//Criando o cenário de exploração
		carregarCenarios();
		Cenario cenario{ this->mapas };

		//Criando os itens
		vector <pair<Arma, int>> armasLoja = criarArmas();
		vector <pair<Cura, int>> curasLoja = criarCuras();
		vector <pair<Colete, int>> coletesCurtume = criarColetes();

		//Criando o personagem
		Personagem personagem{ armasLoja[0].first, 25, coletesCurtume[0].first };

		armasLoja.erase(armasLoja.begin()); //tirando a faca
		coletesCurtume.erase(coletesCurtume.begin()); //tirando a camisa comum

		//Criando estruturas
		vector <Estrutura*> estruturas;

		Loja loja{ "Loja", 75, armasLoja, curasLoja };
		Curtume curtume{ "Curtume", 100, coletesCurtume };
		FabricaMunicao fabr{ "Fábrica de munição", 175 };
		Laboratorio lab{ "Laboratório", 200 };
		Estrutura* estr0 = &loja;
		Estrutura* estr1 = &curtume;
		Estrutura* estr2 = &fabr;
		Estrutura* estr3 = &lab;
		estruturas.push_back(estr0);
		estruturas.push_back(estr1);
		estruturas.push_back(estr2);
		estruturas.push_back(estr3);

		//Criando a base do jogador
		Base base{ "Base", estruturas, cenario, personagem };
		base.entrarBase();

		//Checando final
		if (estruturas[3]->getFinalConfirm()) {
			creditos();
		}
	}

	//Carregar save
	void carregarSave() {
		arquivo.open("zombiesSave.txt", ios::in);
		if (!arquivo.is_open()) {
			cout << "\nSem arquivo de save!\n";
			system("pause");
			arquivo.close();
			return;
		}
		arquivo.close();

		//Base
		string nomeAtual; int recursosAtuais;
		vector <Arma> armasCompradas;
		//Personagem
		vector <Arma> armasSelecionadas;
		vector <Cura> curas;
		Colete coleteAtual; int vidaAtual;

		//Criando o cenário de exploração
		carregarCenarios();
		Cenario cenario{ this->mapas };

		//Criando os itens
		vector <pair<Arma, int>> armasLoja = criarArmas();
		vector <pair<Cura, int>> curasLoja = criarCuras();
		vector <pair<Colete, int>> coletesCurtume = criarColetes();

		//Organizar as armas
		arquivo.open("zombiesSave.txt", ios::in);
		if (arquivo.is_open()) {
			while (arquivo) {
				getline(arquivo, linha);
				if (linha.find("%armaLj%") != string::npos) {
					linha.erase(linha.begin(), linha.begin() + 8);
					elemento2 = linha.substr(linha.find("-") + 1, linha.find("-") + 2);
					if (elemento2 != "0") {
						elemento = linha.substr(0, linha.find("-"));
						for (int n = 0; n < armasLoja.size(); n++) {
							if (armasLoja[n].first.getNome() == elemento) {
								armasLoja[n].first.setComprado(true);
							}
						}
					}
				}
				else if (linha.find("%armaCp%") != string::npos) {
					linha.erase(linha.begin(), linha.begin() + 8);
					if (linha != "none") {
						elemento = linha.substr(0, linha.find("-")); //nome
						linha.erase(linha.begin(), linha.begin() + (linha.find("-") + 1));
						elemento3 = stoi(linha);//munição
						for (int n = 0; n < armasLoja.size(); n++) {
							if (armasLoja[n].first.getNome() == elemento) {
								armasLoja[n].first.setMunicao(elemento3);
								armasCompradas.push_back(armasLoja[n].first);
							}
						}
					}
				}
				else if (linha.find("%armaEq%") != string::npos) {
					linha.erase(linha.begin(), linha.begin() + 8);
					elemento = linha.substr(0, linha.find("-")); //nome
					linha.erase(linha.begin(), linha.begin() + (linha.find("-") + 1));
					elemento3 = stoi(linha);//munição
					for (int n = 0; n < armasLoja.size(); n++) {
						if (armasLoja[n].first.getNome() == elemento) {
							armasLoja[n].first.setMunicao(elemento3);
							armasSelecionadas.push_back(armasLoja[n].first);
						}
					}
				}
			}
		}
		arquivo.close();
		armasLoja.erase(armasLoja.begin());

		//Criando e organizando o jogador
		arquivo.open("zombiesSave.txt", ios::in);
		if (arquivo.is_open()) {
			while (arquivo) {
				getline(arquivo, linha);
				if (linha.find("%joga%") != string::npos) {
					linha.erase(linha.begin(), linha.begin() + 6);
					elemento = linha.substr(0, linha.find("-"));
					elemento3 = stoi(elemento);//vida
					linha.erase(linha.begin(), linha.begin() + (linha.find("-") + 1));//colete

					vidaAtual = elemento3;
					for (int n = 0; n < coletesCurtume.size(); n++) {
						if (coletesCurtume[n].first.getNome() == linha) {
							coleteAtual = coletesCurtume[n].first;
						}
					}
				}
				else if (linha.find("%cura%") != string::npos) {
					linha.erase(linha.begin(), linha.begin() + 6);
					if (linha != "none") {
						for (int n = 0; n < curasLoja.size(); n++) {
							if (curasLoja[n].first.getNome() == linha) {
								curas.push_back(curasLoja[n].first);
							}
						}
					}
				}
			}
		}
		arquivo.close();
		coletesCurtume.erase(coletesCurtume.begin());

		Personagem personagem{ armasSelecionadas, vidaAtual, coleteAtual, curas };

		//Criando e organizando a base e as estruturas
		vector <Estrutura*> estruturas;

		Loja loja{ "Loja", 75, armasLoja, curasLoja };
		Curtume curtume{ "Curtume", 100, coletesCurtume };
		FabricaMunicao fabr{ "Fábrica de munição", 175 };
		Laboratorio lab{ "Laboratório", 200 };
		Estrutura* estr0 = &loja;
		Estrutura* estr1 = &curtume;
		Estrutura* estr2 = &fabr;
		Estrutura* estr3 = &lab;
		estruturas.push_back(estr0);
		estruturas.push_back(estr1);
		estruturas.push_back(estr2);
		estruturas.push_back(estr3);

		arquivo.open("zombiesSave.txt", ios::in);
		if (arquivo.is_open()) {
			while (arquivo) {
				getline(arquivo, linha);
				if (linha.find("%estr%") != string::npos) {
					linha.erase(linha.begin(), linha.begin() + 6);
					elemento2 = linha.substr(linha.find("-") + 1, linha.find("-") + 2);
					if (elemento2 != "0") {
						elemento = linha.substr(0, linha.find("-"));
						for (int n = 0; n < estruturas.size(); n++) {
							if (estruturas[n]->getNome() == elemento) {
								estruturas[n]->setFoiConstruido(true);
							}
						}
					}
				}
				else if (linha.find("%base%") != string::npos) {
					linha.erase(linha.begin(), linha.begin() + 6);
					elemento = linha.substr(0, linha.find("-"));
					linha.erase(linha.begin(), linha.begin() + (linha.find("-") + 1));
					elemento3 = stoi(linha);

					nomeAtual = elemento;
					recursosAtuais = elemento3;
				}
			}
		}
		arquivo.close();

		Base base{ nomeAtual, estruturas, cenario, personagem, recursosAtuais, armasCompradas };
		base.entrarBase();

		//Checando final
		if (estruturas[3]->getFinalConfirm()) {
			creditos();
		}
	}

	//Criar itens
	vector <pair<Arma, int>> criarArmas() {
		Arma arma1{ "Faca", 1000, 2 };
		Arma arma2{ "Pistola", 10, 4 };
		Arma arma3{ "Revolver", 6, 8 };
		Arma arma4{ "Fuzil", 30, 10 };
		Arma arma5{ "Escopeta", 8, 15 };
		Arma arma6{ "Granadeira", 6, 30 };

		//Arma + preço
		vector <pair<Arma, int>> armas;
		armas.push_back(make_pair(arma1, 0));
		armas.push_back(make_pair(arma2, 50));
		armas.push_back(make_pair(arma3, 80));
		armas.push_back(make_pair(arma4, 150));
		armas.push_back(make_pair(arma5, 175));
		armas.push_back(make_pair(arma6, 250));

		return armas;
	}

	vector <pair<Cura, int>> criarCuras() {
		Cura cura1{ "Esparadrapo", "Curativo pequeno feito com um esparadrapo.\nCura 5 de pontos de vida.", 5 };
		Cura cura2{ "Gaze e alcool", "Curativo médio e eficiente feito com gaze e álcool.\nCura 10 pontos de vida.", 10 };
		Cura cura3{ "Kit medico", "Kit de primeiros socorros completo.\nQuebra qualquer galho.\nCura 20 pontos de vida.", 20 };

		vector <pair<Cura, int>> curas;
		curas.push_back(make_pair(cura1, 10));
		curas.push_back(make_pair(cura2, 20));
		curas.push_back(make_pair(cura3, 35));

		return curas;
	}

	vector <pair<Colete, int>> criarColetes() {
		Colete col1{ "Camisa comum", "Uma camisa padrão.\nNão oferece nenhuma proteção.", 0 };
		Colete col2{ "Colete de couro", "Um colete feito à base de couro.\nOferece um pouco de proteção.", 1 };
		Colete col3{ "Colete de couro reforçado", "Um colete feito de couro e algumas placas de aço.\nForneçe considerável proteção.", 2 };
		Colete col4{ "Colete balistico", "Uma peça bastante rara. Feita com kevlar.\nForneçe muita proteção.", 3 };

		vector <pair<Colete, int>> coletes;
		coletes.push_back(make_pair(col1, 0));
		coletes.push_back(make_pair(col2, 90));
		coletes.push_back(make_pair(col3, 200));
		coletes.push_back(make_pair(col4, 300));

		return coletes;
	}

	//Carregar cenarios
	void carregarCenarios() {
		//Abrindo o arquivo com os cenarios
		arquivo.open("mapaZombies.txt", ios::in);
		if (arquivo.is_open()) {
			while (arquivo) {
				getline(arquivo, linha);
				if (linha.find("%nome%") != string::npos) {
					linha.erase(linha.begin(), linha.begin() + 6);
					this->mapaBase.nome = linha;
				}
				else if (linha.find("%desc%") != string::npos) {
					linha.erase(linha.begin(), linha.begin() + 6);
					if (this->mapaBase.descricao == "") {
						this->mapaBase.descricao = linha;
					}
					else {
						this->mapaBase.descricao += "\n";
						this->mapaBase.descricao += linha;
					}
				}
				else if (linha == "%=%") {//Finalizar mapa
					this->x = 0;
					this->y = 0;
					Mapa mapaFinal = mapaBase;
					mapas.push_back(mapaFinal);
					limparMapaBase();
				}
				else { //Construir o mapa em si
					for (; this->x < 10; this->x++) {
						elemento = linha.substr(0, 2);
						linha.erase(0, 2);
						this->mapaBase.mapa[y][x] = elemento;
						if (elemento == "O ") {
							mapaBase.posX = y;
							mapaBase.posY = x;
						}
						else if (elemento == "[]") {
							Mobilia mob{ y, x };
							mapaBase.mobilias.push_back(mob);
						}
						else if (elemento == "Z ") {
							Zumbi z{ y, x };
							mapaBase.inimigos.push_back(z);
						}
					}
					this->y++; this->x = 0;
				}
			}
		}
		arquivo.close();
		mapas.pop_back();
	}

	void limparMapaBase() {
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				this->mapaBase.mapa[i][j] = "";
			}
		}
		this->mapaBase.mobilias.clear();
		this->mapaBase.inimigos.clear();
		this->mapaBase.nome = "";
		this->mapaBase.descricao = "";
	}

	//Creditos
	void creditos() {
		system("cls");
		escrever("Programação: Arthur de Sá Tenório", 50, "\n\n", 1000);
		escrever("História: Arthur de Sá Tenório", 50, "\n\n", 1000);
		escrever("Cenários: Arthur de Sá Tenório", 50, "\n\n", 1000);
		escrever("Sites utilizados:\n- Buscas e ajuda: https://cplusplus.com/\n- Fonte da logo: http://patorjk.com/software/taag/\n- Arte da cidade (artista desconhecido): https://www.asciiart.eu/buildings-and-places/cities\n- Ideias de alguns nomes: https://www.name-generator.org.uk/", 40, "\n\n", 1000);
		escrever("Agradecimento especial a Jeasiel Abner", 50, "\n\n", 1000);
		escrever("Feito com C++ na plataforma Visual Studio 2022", 50, "\n\n", 500);
		system("pause");
	}

	void escrever(string txt, int delay, string final, int delayFim) {
		for (auto n : txt) {
			cout << n;
			Sleep(delay);
		}
		cout << final;
		Sleep(delayFim);
	}
};