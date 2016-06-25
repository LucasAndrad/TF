#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std;

//arquivo que recebe o csv
FILE *csvFile;

struct LISTA {

	char uf[2];	
	char munucipio[30];

//	colonas do arquivo CSV, essas siglas estão explicadas no PDF 
//	"Total" é um dos valores que vamos buscar na arvore
	int cd, epao, tpd, 
			lb, tsb, asb,
			apd, epo;
	int total;
	struct LISTA *next;
};

typedef struct LISTA info;

//arvore de busca para estado.
struct ufTreeSearch {
	
	//char ufKey[2];
	int line;
	struct ufTreeSearch *left;
  struct ufTreeSearch *right;
};

typedef struct ufTreeSearch ufNo;

// lendo arquivo csv e inserindo dados arvore de busca por estado(UF)
void getStateLines(char *STATE) {

	int line=1;
	csvFile = fopen ("dados.csv", "r");
	char u;
	  do {
		  u = fgetc(csvFile);
		  if (u==EOF) break;

			else if (u == ';') {
					while (u != '\n') {
						u = fgetc(csvFile);
						if (u == '\n') {
							line++;
							break;
					}
				}
			}
		

		  else if (u == STATE[0]) {
				u = fgetc(csvFile);
				if (u == STATE[1]) {
					cout << "Numero da linha = " << line << endl;
// apagar linha de cima. E inserir valor das linhas na ufTree
					//insertUfTree(ufNo **ufTree, line);
					while (u != '\n') {
						u = fgetc(csvFile);
						if (u == '\n') {
							line++;
							break;
						}
					}
				}
		  }
			else { // não faz nada!
			}

  } while(u!=EOF);
}
// recebe o estado para ser usado na busca
char *Uf() {
	
	char *state = (char *) malloc(2*sizeof(char));
	cout << "Digite o estado que deseja consultar\n";
	cin >> state;
	return state; 
}

//menu principal
void subOptions(info *list, int subOption);

int menu() {
	int opt=0;
	cout << "\n\nEscolha uma opção:\n";
	cout << "1 - Importar dados\n";
	cout << "2 - Gerar relatório (ordenados por):\n";
	cout << "3 - Relatório de um Estado\n";
	cout << "4 - Consultadar dados de um Município\n";
	cout << "5 - Sair do sistema\n";
	cin >> opt;
	return opt;
}

// menu da opção 2 do menu principal
int subMenu() {

	int opt=0;
	cout << "\n1 - Município\n";
	cout << "2 - CD\n";
	cout << "3 - Total\n";
	cin >> opt;
	return opt;
}

// executando ações do menu
void Options (info *list, int Option) {
	
	int choose=0;
	char *uf;
	
	switch (Option) {
		
		case 1:
			break;

		case 2:
			choose = subMenu();
			subOptions(list, choose);
			break;

		case 4:
			uf = Uf();
			getStateLines(uf);
			break;

		case 5: 
			cout << "\nThank you for using the program.\n";			
			break;

		default: 
			cout << "\nYou can't do this!\nPlease choose another option.\n";
	}
}

//opcões de ordenamento da opção 2 do menu principal
void subOptions (info *list, int subOption) {

	switch (subOption) {
		case 1:
			break;
			
		case 2:
			break;
			
		case 3:
			cout << "It's working\n";
			break;
	}
}

int main() {

	int option=0;
	option = menu();
	info *list = (info *) malloc(sizeof(info));

	while (option!=5) {
		Options(list, option);
		option = 0;
		option = menu();
	}
	
}
