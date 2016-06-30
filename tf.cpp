// *** LINKS 
// https://www.youtube.com/watch?v=8cdbmsPaR-k
// https://www.youtube.com/watch?v=PsH737U2Mnc
// http://www.ime.usp.br/~pf/algoritmos/aulas/binst.html
// https://pt.wikibooks.org/wiki/Programar_em_C/%C3%81rvores_bin%C3%A1rias
//*********************
// PRECISA JUNTAR OS GETS. COLOCAR O GET CD, GET TOTAL E GET MUNICIPIO TODOS JUNTOS.

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std;

//arquivo que recebe o csv
FILE *csvFile;

//arvore de busca para UF
typedef struct ufTreeSearch {
	
	int line;
	int total;
	struct ufTreeSearch *left;
  struct ufTreeSearch *right;
}ufNo;

// arvore de busca para CD
typedef struct cdSearch {
	
	int line;
	int cd;
	struct cdSearch *left;
  struct cdSearch *right;
}cdNo;

// arvore de busca para TOTAL
typedef struct totalSearch {
	
	int line;
	int total;
	struct cdSearch *left;
  struct cdSearch *right;
}totalNo;

// funções
void insertUfNo(ufNo *ufTree, int totalValue, int lineNumber);
void freeUfTree(ufNo *&ufTree);
int getValueTotal();
void getStateLines(ufNo *ufTree, char *STATE);
char *Uf();
void showUfTree(ufNo *ufTree);
int menu();
int subMenu();
void Options (totalNo *totalTree, cdNo *cdTree, ufNo *ufTree, int Option);
void subOptions (totalNo *totalTree, cdNo *cdTree, int subOption);

void showCdTree(cdNo *cdTree);
void insertCdTree(cdNo *cdTree, int cdValue, int lineNumber);
void freeCdTree(cdNo *&cdTree);
int getCdValue();
void getCdLines(cdNo *cdTree);


void getTotalLines(totalNo *totalTree);

// main começa aqui
int main() {

	int option=0;
	option = menu();
	cdNo *cdTree = (cdNo *) malloc(sizeof(cdNo));
	totalNo *totalTree = (totalNo *) malloc(sizeof(totalNo));


	while (option!=5) {
		csvFile = fopen ("dados.csv", "r");
		ufNo *ufTree = (ufNo *) malloc(sizeof(ufNo));
		Options(totalTree, cdTree, ufTree, option);
		option = 0;
		option = menu();		
	}
	freeCdTree(cdTree);

	
	return 0;
}

// insere valor CD na cdTree
void insertCdTree(cdNo *cdTree, int cdValue, int lineNumber) {
	
	cdNo *helperCdTree = (cdNo *) malloc(sizeof(cdNo));

	helperCdTree->cd = cdValue;
	helperCdTree->line = lineNumber;
  helperCdTree->left = NULL;
  helperCdTree->right = NULL;

	if (cdTree == NULL) {
			cdTree = helperCdTree;
	}

	else {
		cdNo *current = cdTree;
		cdNo *behind = NULL;
		while (current != NULL) {
			behind = current;

			if (cdValue > current->cd) {
				current = current->right;
			}
			else {
				current = current->left;
			}
		}
		if (cdValue > behind->cd) {
			behind->right = helperCdTree;
		}
		else {
			behind->left = helperCdTree;
		}
   
  }
  return ;
	
}

// insere valor na uf tree, ufNo
void insertUfNo(ufNo *ufTree, int totalValue, int lineNumber) {

  ufNo *helperUfTree = (ufNo *) malloc(sizeof(ufNo));

  helperUfTree->total = totalValue;
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

			if (totalValue > current->total) {
				current = current->right;
			}
			else {
				current = current->left;
			}
		}
		if (totalValue > behind->total) {
			behind->right = helperUfTree;
		}
		else {
			behind->left = helperUfTree;
		}
   
  }
  return ;
}

// libera cada nó da arvore UF
void freeUfTree(ufNo *&ufTree) {
    if(ufTree != NULL) {
        freeUfTree(ufTree->left);
        freeUfTree(ufTree->right);
        free(ufTree);
        ufTree = NULL;
    }
}

// libera cada nó da árvore CD
void freeCdTree(cdNo *&cdTree) {
    if(cdTree != NULL) {
        freeCdTree(cdTree->left);
        freeCdTree(cdTree->right);
        free(cdTree);
        cdTree = NULL;
    }
}

// recebe o valor Total de linha atual no arquivo
int getValueTotal() {

	char w;
	int total=0, count=0;
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

// recebe o valor CD da linha atual do arquivo
int getCdValue() {

	char w;
	int cd=0, count=0;
	while (count != 2) {
		w = fgetc(csvFile);
		if (w == ';') {
			count++;
		}
	}
	if (count == 2) {
		fscanf(csvFile, "%d", &cd);
	}
	return cd;		
}

// pegando valor total e inserindo na arcore totalTree
void getTotalLines(totalNo *totalTree) {

	int line=1;
	int totalValue=0;
	char u;
	do {
		u = fgetc(csvFile);
		if (u == EOF) break;
		totalValue = getValueTotal();
		cout << "TOTAL = " << totalValue << "   linha: " << line << endl;
		//insertTotalTree(totalTree, totalValue, line);
		while (u != '\n') {
			u = fgetc(csvFile);
			if (u == EOF) break;	
			if (u == '\n') {
				line++;
				break;
			}
		}

	} while(u!=EOF);
	fclose(csvFile);
}

// pegando os valores de CD e inserindo na arvore cdTree
void getCdLines(cdNo *cdTree) {

	int line=1;
	int cdValue=0;
	char u;
	do {
		u = fgetc(csvFile);
		if (u == EOF) break;
		cdValue = getCdValue();
		//cout << "CD = " << cdValue << "   linha: " << line << endl;
		insertCdTree(cdTree, cdValue, line);
		while (u != '\n') {
			u = fgetc(csvFile);
			if (u == EOF) break;	
			if (u == '\n') {
				line++;
				break;
			}
		}

	} while(u!=EOF);
	fclose(csvFile);
}

// lendo arquivo csv e inserindo dados arvore de busca por estado(UF)
void getStateLines(ufNo *ufTree, char *STATE) {

	int line=1, count=0;
	int valueTotal=0;
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
					valueTotal = getValueTotal(); // essa função vai receber a linha toda e verificar
					 //qual é o valor depois do ultimo ";" (o decimo) que corresponde ao valor da variavel total 
					insertUfNo(ufTree, valueTotal, line);
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
	line=1;
	fclose(csvFile);
}
// recebe o estado para ser usado na busca
char *Uf() {
	
	char *state = (char *) malloc(2*sizeof(char));
	cout << "Digite o estado que deseja consultar\n";
	cin >> state;
	return state; 
}

// mostra o conteúdo da árvore UF
void showUfTree(ufNo *ufTree) {

	if (ufTree != NULL) {
		showUfTree(ufTree->left);
		cout << "Total: "<< ufTree->total << "   linha: "<< ufTree->line << endl;
		showUfTree(ufTree->right);
	}
}

// mostra o conteúdo da árvore CD
void showCdTree(cdNo *cdTree) {

	if (cdTree != NULL) {
		showCdTree(cdTree->left);
		cout << "CD: "<< cdTree->cd << "   linha: "<< cdTree->line << endl;
		showCdTree(cdTree->right);
	}
}

// menu principal
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
void Options (totalNo *totalTree, cdNo *cdTree, ufNo *ufTree, int Option) {
	
	int choose=0;
	char *uf;
	
	switch (Option) {
		
		case 1:
			cdTree->left = NULL;
			cdTree->right = NULL;
			getCdLines(cdTree);
			totalTree->left = NULL;
			totalTree->right = NULL;
			//getTotalLines(totalTree);
			break;

		case 2:
			choose = subMenu();
			subOptions(totalTree, cdTree, choose);
			break;

		case 4:
			uf = Uf();
			getStateLines(ufTree, uf);
			showUfTree(ufTree);
			freeUfTree(ufTree);
			break;

		case 5: 
			cout << "\nThank you for using the program.\n";			
			break;

		default: 
			cout << "\nYou can't do this!\nPlease choose another option.\n";
	}
}

//opcões de ordenamento da opção 2 do menu principal
void subOptions (totalNo *totalTree, cdNo *cdTree, int subOption) {

	switch (subOption) {
		case 1:
			break;
			
		case 2:
			showCdTree(cdTree);
			break;
			
		case 3:
			
			break;
	}
}






