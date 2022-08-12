#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Estrutura.h"
#include "Cenario.h"
#include "Personagem.h"
#include "Arma.h"
#include "Cura.h"

using namespace std;

class Base {
private:
	//Coisas que precisam salvar
	string nome = "Base";
	int recursos = 0;
	vector <Estrutura*> estruturas;
	Personagem personagem;
	vector <Arma> armasCompradas;

	//Coisas que não precisam salvar
	Cenario cenario;
	fstream arquivo;

	//Outros
	bool cond = true;
	string Opc; int opc;
public:
	//Construtor
	Base(string nome, vector <Estrutura*> estruturas, Cenario cenario, Personagem personagem) {
		this->nome = nome;
		this->estruturas = estruturas;
		this->cenario = cenario;
		this->personagem = personagem;
	}
	Base(string nome, vector <Estrutura*> estruturas, Cenario cenario, Personagem personagem,
		int recursos, vector <Arma> armasCompradas) {
		this->nome = nome;
		this->estruturas = estruturas;
		this->cenario = cenario;
		this->personagem = personagem;
		this->recursos = recursos;
		this->armasCompradas = armasCompradas;
	}

	//Metodos
	void entrarBase() {
		cond = true;
		while (cond) {
			system("cls");
			cout << this->nome
				<< "\n=-=-=-=-=-=-=-=-=-=-=-=-=-=\n"
				<< "Recursos: " << this->recursos << "\n\n"
				<< "1.Explorar\n"
				<< "2.Visitar estruturas\n"
				<< "3.Desbloquear estruturas\n"
				<< "4.Ver status do personagem\n"
				<< "5.Administrar armamento\n"
				<< "6.Mudar nome da base\n"
				<< "7.Salvar progreso\n"
				<< "8.Menu de ajuda\n"
				<< "9.Sair\n\nComando:\n";
			getline(cin, Opc);
			try {
				opc = stoi(Opc);
				switch (opc) {
				case 1:
					this->cenario.escolherCenario(&this->personagem);
					this->recursos += this->cenario.getRecursosEncontrados();
					break;
				case 2:
					visitarEstruturas();
					break;
				case 3:
					desbloquearEstruturas();
					break;
				case 4:
					this->personagem.mostrarStatus();
					break;
				case 5:
					trocarArmamento(this->personagem.getArmasSelecionadas());
					break;
				case 6:
					cout << "\n\nInforme o novo nome da sua base:\n";
					getline(cin, Opc);
					this->nome = Opc;
					break;
				case 7:
					salvarProgresso(this->personagem.getInventario(),
						this->personagem.getArmasSelecionadas());
					break;
				case 8:
					menuAjuda();
					break;
				case 9:
					cout << "\nSaindo...\n";
					system("pause");
					cond = false;
					break;
				default:
					throw "Comando não encontrado!";
					break;
				}
				//Checando final
				if (estruturas[3]->getFinalConfirm()) {
					cond = false;
				}
			}
			catch (const char* msg) {
				cout << "Houve um erro: " << msg << endl;
				system("pause");
			}
			catch (exception& err) {
				cout << "Houve um erro:  " << err.what() << endl;
				system("pause");
			}
		}
	}

	//Estruturas
	void visitarEstruturas() {
		while (true) {
			system("cls");
			cout << "Estruturas:\n\n"
				<< "1.Loja\n"
				<< "2.Curtume\n"
				<< "3.Fábrica de munição\n"
				<< "4.Laboratório\n"
				<< "5.Voltar\n\nComando:\n";
			getline(cin, Opc);
			try {
				opc = stoi(Opc);
				if (opc > 0 && opc < 5) {
					estruturas[opc - 1]->checarSeFoiConstruido(&this->personagem, &this->recursos, &this->armasCompradas);
					if (estruturas[opc - 1]->getFoiConstruido()) {
						break;
					}
				}
				else if (opc == 5) {
					break;
				}
				else {
					throw "Comando inválido!";
				}
			}
			catch (const char* msg) {
				cout << "Houve um erro: " << msg << endl;
				system("pause");
			}
			catch (exception& err) {
				cout << "Houve um erro:  " << err.what() << endl;
				system("pause");
			}
		}
	}

	void desbloquearEstruturas() {
		while (true) {
			system("cls");
			cout << "Recursos: " << this->recursos
				<< "\n\nEscolha uma estrutura para desbloquear:\n"
				<< "1.Loja (75 recursos)\n"
				<< "2.Curtume (100 recursos)\n"
				<< "3.Fábrica de munição (150 recursos)\n"
				<< "4.Laboratório (200 recursos)\n"
				<< "5.Voltar\n\nComando:\n";
			getline(cin, Opc);
			try {
				opc = stoi(Opc);
				if (opc > 0 && opc < 5) {
					if (estruturas[opc - 1]->getFoiConstruido()) {
						cout << "\n\nEsta estrutura já foi construída!\n";
						system("pause");
					}
					else {
						if (estruturas[opc - 1]->getRecursosParaConstruir() > this->recursos) {
							cout << "\n\nVocê não tem recursos suficiente para construir a(o) " <<
								estruturas[opc - 1]->getNome() << endl;
							system("pause");
						}
						else {
							this->recursos -= estruturas[opc - 1]->getRecursosParaConstruir();
							estruturas[opc - 1]->setFoiConstruido(true);
							cout << "\n\nA estrutura " << estruturas[opc - 1]->getNome()
								<< " foi construída!\n";
							system("pause");
							break;
						}
					}
				}
				else if (opc == 5) {
					break;
				}
				else {
					throw "Comando não encontrado!";
				}
			}
			catch (const char* msg) {
				cout << "Houve um erro: " << msg << endl;
				system("pause");
			}
			catch (exception& err) {
				cout << "Houve um erro:  " << err.what() << endl;
				system("pause");
			}
		}
	}

	//Administrar armamento
	void trocarArmamento(vector<Arma>* armasSelecionadas) {
		while (true) {
			system("cls");
			cout << "Armas compradas: "; mostrarArmas(this->armasCompradas);
			cout << "\n\nArmas equipadas: "; mostrarArmas((*armasSelecionadas));

			cout << "\n\n1.Equipar arma\n2.Guardar arma\n3.Voltar\n\nComando:\n";
			getline(cin, Opc);
			try {
				opc = stoi(Opc);
				if (opc == 1) {
					if ((*armasSelecionadas).size() >= 2) {
						cout << "\nVocê já tem duas armas equipadas!\n";
						system("pause");
					}
					else if (this->armasCompradas.empty()) {
						cout << "\nVocê não tem armas para equipar!\n";
						system("pause");
					}
					else {
						cout << "\nDigite o nome da arma que deseja equipar:\n";
						getline(cin, Opc);
						opc = buscarArmaPorNome(this->armasCompradas, Opc);
						if (opc == -1) {
							cout << "\nArma não encontrada!\n";
							system("pause");
						}
						else {
							(*armasSelecionadas).push_back(this->armasCompradas[opc]);
							this->armasCompradas.erase(armasCompradas.begin() + opc);
						}
					}
				}
				else if (opc == 2) {
					if ((*armasSelecionadas).empty()) {
						cout << "\nVocê não tem armas para guardar\n";
						system("pause");
					}
					else {
						cout << "\nDigite o nome da arma que deseja guardar:\n";
						getline(cin, Opc);
						opc = buscarArmaPorNome(*armasSelecionadas, Opc);
						if (opc == -1) {
							cout << "\nArma não encontrada!\n";
							system("pause");
						}
						else {
							this->armasCompradas.push_back((*armasSelecionadas)[opc]);
							(*armasSelecionadas).erase((*armasSelecionadas).begin() + opc);
						}
					}
				}
				else if (opc == 3) {
					if ((*armasSelecionadas).empty()) {
						cout << "\nVocê deve ter, no mínimo, uma arma equipada!\n";
						system("pause");
					}
					else {
						break;
					}
				}
				else {
					throw "Comando inválido";
				}
			}
			catch (const char* msg) {
				cout << "Houve um erro: " << msg << endl;
				system("pause");
			}
			catch (exception& err) {
				cout << "Houve um erro:  " << err.what() << endl;
				system("pause");
			}
		}
	}

	void mostrarArmas(vector <Arma> armas) {
		if (armas.empty()) {
			cout << "Sem armas";
		}
		else {
			for (int n = 0; n < armas.size(); n++) {
				cout << armas[n].getNome();
				if (n == armas.size() - 1) {
					cout << ".";
				}
				else {
					cout << ", ";
				}
			}
		}
	}

	int buscarArmaPorNome(vector<Arma> armas, string nome) {
		for (int n = 0; n < armas.size(); n++) {
			if (armas[n].getNome() == nome) {
				return n;
			}
		}
		return -1;
	}

	//Sistema de save
	void salvarProgresso(vector <Cura>* curas, vector <Arma>* armasSelecionadas) {
		arquivo.open("zombiesSave.txt", ios::out);
		if (!arquivo.is_open()) {
			cout << "\n\nArquivo de save não existente.\n(crie um arquivo chamado zombiesSave.txt na pasta do jogo)";
			system("pause");
		}
		else {
			//Armas loja
			for (auto n : this->estruturas[0]->getArmas()) {
				arquivo << "%armaLj%" << n.first.getNome() << "-" << n.first.getComprado() << endl;
			}

			//Armas compradas
			if (this->armasCompradas.empty()) {
				arquivo << "%armasCp%none" << endl;
			}
			else {
				for (auto n : this->armasCompradas) {
					arquivo << "%armaCp%" << n.getNome() << "-" << n.getMunicao() << endl;
				}
			}

			//Dados do jogador
			arquivo << "%joga%" << this->personagem.getVidaAtual() << "-" << this->personagem.getColete().getNome() << endl;
			if (personagem.getInventario()->empty()) {
				arquivo << "%cura%none" << endl;
			}
			else {
				for (auto n : (*curas)) {
					arquivo << "%cura%" << n.getNome() << endl;
				}
			}
			//Armas equipadas
			for (auto n : (*armasSelecionadas)) {
				arquivo << "%armaEq%" << n.getNome() << "-" << n.getMunicao() << endl;
			}

			//Estruturas
			for (auto n : this->estruturas) {
				arquivo << "%estr%" << (*n).getNome() << "-" << (*n).getFoiConstruido() << endl;
			}

			//Base
			arquivo << "%base%" << this->nome << "-" << this->recursos << endl;

			cout << "\nJogo salvo!\n\n";
			system("pause");
		}
		arquivo.close();
	}

	//Menu de ajuda
	void menuAjuda() {
		while (true) {
			system("cls");
			cout << "Menu de ajuda\n\nSelecione o que deseja saber sobre:\n"
				<< "1.Exploração\n2.Estruturas\n3.Armamento\n4.Voltar\n\nComando:\n";
			getline(cin, Opc);
			try {
				opc = stoi(Opc);
				if (opc == 1) {
					system("cls");
					cout << "COMANDOS BÁSICOS:\nW - Mover para cima\nS - Mover para baixo\n"
						<< "A - Mover para a esquerda\nD - Mover para a direita\nC - Sair do cenário\n"
						<< "desc - Ver descrição do cenário atual\n\n";

					cout << "ELEMENTOS DO CENÁRIO:\n"
						<< "O - Representa o jogador\nZ - Representa um zumbi\n# - Representa uma parede\n"
						<< ". - Representa o chão\n[] - Representa uma mobília\n\n";

					cout << "MOBÍLIAS:\n"
						<< "As mobílias são elementos do cenário que podem ser vasculhados gerando\n"
						<< "recursos para o jogador. Para vasculhar uma mobília basta andar na\n"
						<< "direção dela. Algumas mobílias tem uma tranca, a qual só pode ser\n"
						<< "aberta caso você tenha a faca equipada.\n\n";

					cout << "COMBATE:\n"
						<< "Ao chegar próximo de um zumbi, você entrará em combate com ele.\n"
						<< "O combate é dividido por turnos. Durante seu turno é possível atacar\n"
						<< "com as armas equipadas ou usar itens de cura.\n\n";

					system("pause");
				}
				else if (opc == 2) {
					system("cls");
					cout << "DESBLOQUEAR ESTRUTURAS:\n"
						<< "As estruturas podem ser liberadas na base. Cada estrutura custa\n"
						<< "uma quantidade específica de recursos para ser construída.\n\n";

					cout << "O QUE SÃO ESTRUTURAS:\n"
						<< "As estruturas são como estabelecimentos, que vendem itens ou\n"
						<< "realizam algum serviço para o jogador.\n\n";

					system("pause");
				}
				else if (opc == 3) {
					system("cls");
					cout << "COMPRAR ARMAMENTO:\n"
						<< "A estrutura Loja é a responsável por vender armamentos ao jogador.\n"
						<< "Ao comprar armamentos eles são colocados na base, ou seja, eles NÃO\n"
						<< "são equipados sozinhos.\n\n";

					cout << "EQUIPAR ARMAMENTO:\n"
						<< "Na base, é disponível o menu \"Administrar armamento\" e\n"
						<< "é neste menu que é possível equipar e guardar suas armas.\n\n";

					system("pause");
				}
				else if (opc == 4) {
					break;
				}
			}
			catch (exception& err) {
				cout << "Houve um erro: " << err.what() << endl;
				system("pause");
			}
		}
	}
};