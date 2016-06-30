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
#include <string.h>

using namespace std;

//arquivo que recebe o csv
FILE *csvFile;
FILE *arq;

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
	struct totalSearch *left;
  struct totalSearch *right;
}totalNo;

// arvore de busca para MUNICIPIO
typedef struct citySearch {

	int line;
	char city[30];
	struct citySearch *left;
	struct citySearch *right;
}cityNo;	

// funções
void insertUfNo(ufNo *ufTree, int totalValue, int lineNumber);
void freeUfTree(ufNo *&ufTree);
int getValueTotal();
void getStateLines(ufNo *ufTree, char *STATE);
char *Uf();
void showUfTree(ufNo *ufTree);
int menu();
int subMenu();
void Options (cityNo *cityTree, totalNo *totalTree, cdNo *cdTree, ufNo *ufTree, int Option);
void subOptions (cityNo *cityTree, totalNo *totalTree, cdNo *cdTree, int subOption);

void insertCityTree(cityNo *cityTree, char *CITYH, int lineNumber);
void showCityTree(cityNo *cityTree);
char *getCity();

void showAllData(int lineH);
void showCdTree(cdNo *cdTree);
void insertCdTree(cdNo *cdTree, int cdValue, int lineNumber);
void freeCdTree(cdNo *&cdTree);
void freeTotalTree(totalNo *&totalTree);
int getCdValue();

int getNewTotalValue();
void insertTotalTree(totalNo *totalTree, int totalValue, int lineNumber);
void getCdLines(totalNo *totalTree, cdNo *cdTree);

void showTotalTree(totalNo *totalTree);

// main começa aqui
int main() {

	int option=0;
	option = menu();
	cdNo *cdTree = (cdNo *) malloc(sizeof(cdNo));
	totalNo *totalTree = (totalNo *) malloc(sizeof(totalNo));
	cityNo *cityTree = (cityNo *) malloc(sizeof(cityNo));

	while (option!=5) {
		csvFile = fopen ("dados.csv", "r");
		ufNo *ufTree = (ufNo *) malloc(sizeof(ufNo));
		Options(cityTree, totalTree, cdTree, ufTree, option);
		option = 0;
		option = menu();		
	}
	//freeCityTree(cityTree);
	freeCdTree(cdTree);
	freeTotalTree(totalTree);
	
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
		
		if (current != NULL) {
			freeCdTree(current);
			freeCdTree(behind);
			freeCdTree(helperCdTree);
		}
  }
  return ;
	
}

// insere valor Municipio na cityTree
void insertCityTree(cityNo *cityTree, char *CITYH, int lineNumber) {

	cityNo *helperCityTree = (cityNo *) malloc(sizeof(cityNo));
	
	strcpy(helperCityTree->city, CITYH);
	helperCityTree->line = lineNumber;
	helperCityTree->left = NULL;
	helperCityTree->right = NULL;
	
	if (cityTree == NULL) {
		cityTree = helperCityTree;
	}
	
	else {
		cityNo *current = cityTree;
		cityNo *behind = NULL;
		while (current != NULL) {
			behind = current;
			
			if ((strcmp(CITYH, current->city)) > 0) {
				current = current->right;
			}
			else {
				current = current->left;
			}
		}
		if ((strcmp(CITYH, behind->city)) > 0) {
			behind->right = helperCityTree;
		}
		else {
			behind->left = helperCityTree;
		}
		if (current != NULL) {
			// free
		}
	}
}

// insere valor TOTAL na totalTree
void insertTotalTree(totalNo *totalTree, int totalValue, int lineNumber) {
	
	totalNo *helperTotalTree = (totalNo *) malloc(sizeof(totalNo));
	
	helperTotalTree->total = totalValue;
	helperTotalTree->line = lineNumber;
  helperTotalTree->left = NULL;
  helperTotalTree->right = NULL;

	if (totalTree == NULL) {
			totalTree = helperTotalTree;
	}

	else {
		totalNo *current =totalTree;
		totalNo *behind = NULL;
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
			behind->right = helperTotalTree;
		}
		else {
			behind->left = helperTotalTree;
		}
		if (current != NULL) {
			freeTotalTree(current);
			freeTotalTree(behind);
			freeTotalTree(helperTotalTree);
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

// libera cada nó da árvore TOTAL
void freeTotalTree(totalNo *&totalTree) {

	if(totalTree != NULL) {
		freeTotalTree(totalTree->left);
		freeTotalTree(totalTree->right);
		free(totalTree);
		totalTree = NULL;
	} 
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

// recebe o valor total depois depois do getCdValue
int getNewTotalValue() {

	char w;
	int total=0, count=2;
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
	int cd=0, count=2;
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

// recebe o valor de MUNICIPIO da linha atual
char *getCity() {

	char w;
	char *c = (char *) malloc(sizeof(char)*30);
	int i=0, count=0;
	while (count != 1) {
		w = fgetc(csvFile);
		if (w == ';') {
			count++;
		}
	}
	if (count == 1) {
		w = fgetc(csvFile);
		while (w != ';') {
			c[i] = w;
			i++;
			w = fgetc(csvFile);
			if (w == ';') break;
		}
	}
	
	return c;
}
// pegando os valores de CD e inserindo na arvore cdTree
void getCdLines(cityNo *cityTree, totalNo *totalTree, cdNo *cdTree) {

	int line=1, totalValue=0;
	int cdValue=0;
	char u;
	char *city = (char *) malloc(sizeof(char)*30);
	do {
		u = fgetc(csvFile);
		if (u == EOF) break;
		
		strcpy(city, getCity());
		cdValue = getCdValue();
		totalValue = getNewTotalValue();
		
		insertCityTree(cityTree, city, line);
		insertTotalTree(totalTree, totalValue, line);
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
		//cout << "Total: "<< ufTree->total << "   linha: "<< ufTree->line << endl;
		showAllData(ufTree->line);
		showUfTree(ufTree->right);
	}
}

// mostra o conteúdo da árvore MUNICIPIO
void showCityTree(cityNo *cityTree) {

	if (cityTree != NULL) {
		showCityTree(cityTree->left);
		//cout << "MUNICIPIO: "<< cityTree->city << "   linha: "<< cityTree->line << endl;
		showAllData(cityTree->line);
		showCityTree(cityTree->right);
	}
}

// mostra o conteúdo da árvore CD
void showCdTree(cdNo *cdTree) {

	if (cdTree != NULL) {
		showCdTree(cdTree->left);
		//cout << "CD: "<< cdTree->cd << "   linha: "<< cdTree->line << endl;
		showAllData(cdTree->line);
		showCdTree(cdTree->right);
	}
}

// mostra o conteúdo da árvore TOTAL
void showTotalTree(totalNo *totalTree) {
	
	if (totalTree != NULL) {
		showTotalTree(totalTree->left);
		//cout << "TOTAL: " << totalTree->total << "   linha: " << totalTree->line << endl;
		showAllData(totalTree->line);
		showTotalTree(totalTree->right); 
	}
}

// mostrando todos os dados de uma linha
void showAllData(int lineH) {
	
	arq = fopen("dados.csv", "r");
	char f[100];
	if (lineH < 10000 && lineH != 0) {
		int i=0;
		while (i<lineH) {
		i++;
		fgets(f, sizeof(f), arq);
	
		}
		cout << f;
	}
	fclose(arq);
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
void Options (cityNo *cityTree, totalNo *totalTree, cdNo *cdTree, ufNo *ufTree, int Option) {
	
	int choose=0;
	char *uf;
	
	switch (Option) {
		
		case 1:
			cityTree->left = NULL;
			cityTree->right = NULL;
			cdTree->left = NULL;
			cdTree->right = NULL;
			totalTree->left = NULL;
			totalTree->right = NULL;
			getCdLines(cityTree, totalTree, cdTree);
			break;

		case 2:
			choose = subMenu();
			subOptions(cityTree, totalTree, cdTree, choose);
			break;

		case 3:
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
void subOptions (cityNo *cityTree, totalNo *totalTree, cdNo *cdTree, int subOption) {

	switch (subOption) {
		case 1:
			showCityTree(cityTree);
			break;
			
		case 2:
			showCdTree(cdTree);
			break;
			
		case 3:
			showTotalTree(totalTree);
			break;
	}
}






