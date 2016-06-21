#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std;

struct LISTA {

	char uf[2];	
	char munucipio[30];

//	collouns of csv file. Dot not now what is all this abbreviation. 
//	"Total" is one of values for shearch in the Tree.
	int cd, epao, tpd, 
			lb, tsb, asb,
			apd, epo;
	int total;
	struct LISTA *next;
};

typedef struct LISTA info;

void subOptions(info *list, int subOption);

int menu() {
	int opt=0;
	cout << "\n\nEscolha uma opção:\n";
	cout << "1 - Importar dados\n";
	cout << "2 - Gerar relatório (ordenados por):\n";
	cout << "3 - Relatório de um Estado\n";
	cout << "5 - Consultadar dados de um Município\n";
	cout << "0 - Sair do sistema\n";
	cin >> opt;
	return opt;
}

int subMenu() {

	int opt=0;
	cout << "\n1 - Município\n";
	cout << "2 - CD\n";
	cout << "3 - Total\n";
	cin >> opt;
	return opt;
}

void Options (info *list, int Option) {
	
	int choose=0;
	
	switch (Option) {
		case 0: 
			cout << "\nThank you for using the program.\n";			
			break;
		
		case 1:
			break;

		case 2:
			choose = subMenu();
			subOptions(list, choose);
			break;

		default: 
			cout << "\nYou can't do this!\nPlease choose another option.\n";
	}
}

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

	while (option!=0) {
		Options(list, option);
		option = 0;
		option = menu();
	}
	
}
