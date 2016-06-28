// *** LINKS 
// https://www.youtube.com/watch?v=8cdbmsPaR-k
// https://www.youtube.com/watch?v=PsH737U2Mnc
// http://www.ime.usp.br/~pf/algoritmos/aulas/binst.html
// https://pt.wikibooks.org/wiki/Programar_em_C/%C3%81rvores_bin%C3%A1rias

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
//	"Total" é um dos valores da lista que vamos buscar na arvore
	int cd, epao, tpd, 
			lb, tsb, asb,
			apd, epo;
	int total;
	struct LISTA *next;
};

typedef struct LISTA info;

//arvore de busca para estado.
struct ufTreeSearch {
	
	int line;
	int total;
	struct ufTreeSearch *left;
  struct ufTreeSearch *right;
};

typedef struct ufTreeSearch ufNo;

// função que insere valor na uf tree, ufNo
void insertUfNo(ufNo *ufTree, int lineNumber) {

	if (ufTree == NULL) {
		return ;
	}

  ufNo *helperUfTree = (ufNo *) malloc(sizeof(ufNo));

  if (helperUfTree == NULL) {
		return ;
	}

  helperUfTree->line = lineNumber;
  helperUfTree->left = NULL;
  helperUfTree->right = NULL;

  if (ufTree == NULL) {
		ufTree = helperUfTree;
	}

  else {
		ufNo *current = ufTree;
		ufNo *behind = NULL;
		while (current != NULL) {
			behind = current;

			if (lineNumber > current->line) {
				current = current->right;
			}
			else {
				current = current->left;
			}
		}
		if (lineNumber > behind->line) {
			behind->right = helperUfTree;
		}
		else {
			behind->left = helperUfTree;
		}
   
  }
  return ;
}

// função que recebe o valor Total de linha atual no arquivo.
int getValueTotal() {

	char w;
	int total, count=0;
	while (count != 10) {
		w = fgetc(csvFile);
		if (w == ';') {
			count++;
		}
	}
	if (count == 10) {
		fscanf(csvFile, "%d", &total);
	}
	return total;
}

// lendo arquivo csv e inserindo dados arvore de busca por estado(UF)
void getStateLines(ufNo *ufTree, char *STATE) {

	int line=1, count=0;
	int valueTotal=0;
	csvFile = fopen ("dados.csv", "r");
	char u;
	do {
		  u = fgetc(csvFile);
		  count++;
		  if (u==EOF) break;

			else if (count>2) {
					while (u != '\n') {
						u = fgetc(csvFile);
						if (u == '\n') {
							line++;
							count=0;
							break;
					}
				}
			}
		
		  else if (count < 3 && u == STATE[0]) {
				u = fgetc(csvFile);
				if (count < 3 && u == STATE[1]) {
					//cout << "Numero da linha = " << line << endl;
					//valueTotal = getValueTotal(); // essa função vai receber a linha toda e verificar
					 //qual é o valor depois do ultimo ";" (o decimo) que corresponde ao valor da variavel total 
					//cout << "valor total = " << valueTotal << endl;
					insertUfNo(ufTree, line);
					valueTotal = 0;
					while (u != '\n') {
						u = fgetc(csvFile);
						if (u == '\n') {
							line++;
							count = 0;
							break;
						}
					}
				}
		  }
			else { // não faz nada!
			}

	} while(u!=EOF);
	fclose(csvFile);
}
// recebe o estado para ser usado na busca
char *Uf() {
	
	char *state = (char *) malloc(2*sizeof(char));
	cout << "Digite o estado que deseja consultar\n";
	cin >> state;
	return state; 
}

// essa função mostra o conteúdo da árvore
void showUfTree(ufNo *ufTree) {

	if (ufTree != NULL) {
		showUfTree(ufTree->left);
		cout << "Número da linha: "<< ufTree->line << endl; 
		showUfTree(ufTree->right);
	}
}

// menu principal
void subOptions(int subOption);

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
void Options (ufNo *ufTree, int Option) {
	
	int choose=0;
	char *uf;
	
	switch (Option) {
		
		case 1:
			break;

		case 2:
			choose = subMenu();
			subOptions(choose);
			break;

		case 4:
			uf = Uf();
			getStateLines(ufTree, uf);
			showUfTree(ufTree);
			break;

		case 5: 
			cout << "\nThank you for using the program.\n";			
			break;

		default: 
			cout << "\nYou can't do this!\nPlease choose another option.\n";
	}
}

//opcões de ordenamento da opção 2 do menu principal
void subOptions (int subOption) {

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
	ufNo *ufTree = (ufNo *) malloc(sizeof(ufNo));

	while (option!=5) {
		Options(ufTree, option);
		option = 0;
		free(ufTree);
		ufNo *ufTree = (ufNo *) malloc(sizeof(ufNo));
		option = menu();
	}
	
}
