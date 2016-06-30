#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std;

//arquivo que recebe o csv
FILE *csvFile;

// arvore de busca para CD
typedef struct cdSearch {
	
	int line;
	int cd;
	struct cdSearch *left;
  struct cdSearch *right;
}cdNo;

void showCdTree(cdNo *cdTree);
void insertCdTree(cdNo *cdTree, int cdValue, int lineNumber);
void freeCdTree(cdNo *&cdTree);
int getCdValue();
void getCdLines(cdNo *cdTree);

int main() {
	
	csvFile = fopen ("teste.csv", "r");
	cdNo *cdTree = (cdNo *) malloc(sizeof(cdNo));
	cdTree->left = NULL;
	cdTree->right = NULL;	

	getCdLines(cdTree);
	showCdTree(cdTree);
	freeCdTree(cdTree);
	return 0;
}

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

// libera cada nó da árvore CD
void freeCdTree(cdNo *&cdTree) {
    if(cdTree != NULL) {
        freeCdTree(cdTree->left);
        freeCdTree(cdTree->right);
        free(cdTree);
        cdTree = NULL;
    }
}

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

// mostra o conteúdo da árvore CD
void showCdTree(cdNo *cdTree) {

	if (cdTree != NULL) {
		showCdTree(cdTree->left);
		cout << "CD: "<< cdTree->cd << "   linha: "<< cdTree->line << endl;
		showCdTree(cdTree->right);
	}
}











