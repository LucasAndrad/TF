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

int menu () {
	int opt=0;
	cout << "\n\nEscolha uma opção:\n";
	cout << "1 - Buscar por municipio\n";
	cout << "2 - Buscar por CD's\n";
	cout << "3 - Buscar por Total\n";
	cout << "0 - Para sair do programa\n\n";
	cin >> opt;
	return opt;
}

void Options (info *list, int Option) {
	
	switch (Option) {
		case 0: 
			cout << "\nThank you for using the program\n";			
			break;

		default: 
			cout << "\nYou can't do this!\nPlease choose another option.\n";
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
