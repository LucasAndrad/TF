#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std;

//arquivo que recebe o csv
FILE *csvFile;

// arvore de busca para TOTAL
typedef struct totalSearch {
	
	int line;
	int total;
	struct cdSearch *left;
  struct cdSearch *right;
}totalNo;

void getTotalLines(totalNo *totalTree);
int getValueTotal();

int main() {

	csvFile = fopen ("dados.csv", "r");
	totalNo *totalTree = (totalNo *) malloc(sizeof(totalNo));

	getTotalLines(totalTree);	
	
	return 0;
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

// pegando valor total e inserindo na arvore totalTree
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
