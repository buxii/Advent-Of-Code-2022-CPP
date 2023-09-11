#include <iostream>
#include <fstream>
#include <string>

const int FILES = 99;
const int COLUM = 99;

const int EDGE = COLUM * 2 + (FILES - 2) * 2;

int matriu[FILES][COLUM];


bool te_visibilitat(int a, int b) {
	bool files = true, columnes = true;
	for (int i = 0; i < b; i++) {
		if (matriu[a][b] <= matriu[a][i]) {
			files = false;
			break;
		}
	}
	if (files) return true;
	else files = true;
	for (int i = b+1; i < COLUM; i++) {
		if (matriu[a][b] <= matriu[a][i]) {
			files = false;
			break;
		}
	}
	if (files) return true;
	for (int i = 0; i < a; i++) {
		if (matriu[a][b] <= matriu[i][b]) {
			columnes = false;
			break;
		}
	}
	if (columnes) return true;
	else columnes = true;
	for (int i = a+1; i < FILES; i++) {
		if (matriu[a][b] <= matriu[i][b]) {
			columnes = false;
			break;
		}
	}
	if (columnes) return true;
	
	return false;
}

int scenic_score(int a, int b) {	
	int up=0, down = 0, left = 0, right = 0;
	for (int i = b-1; i >= 0 ; i--) { //left
		int x = matriu[a][b], y = matriu[a][i];
		if (matriu[a][b] <= matriu[a][i]) {
			left++;
			break;
		}
		else left++;
	}
	
	for (int i = b + 1; i < COLUM; i++) { //right
		if (matriu[a][b] <= matriu[a][i]) {
			right++;
			break;
		}
		else right++;
	}

	for (int i = a - 1; i >= 0; i--) { //up
		if (matriu[a][b] <= matriu[i][b]) {
			up++;
			break;
		}
		else up++;
	}
	
	for (int i = a + 1; i < FILES; i++) { //down
		if (matriu[a][b] <= matriu[i][b]) {
			down++;
			break;
		}
		else down++;
	}	

	return up*down*left*right;
}

int process_data(char c) {
	int compt = 0, compt2 = 0, maxim = 0;
	for (int i = 1; i < FILES - 1; i++) {
		for (int j = 1; j < COLUM - 1; j++) {
			if(te_visibilitat(i, j)) compt++;
			maxim = std::max(maxim, scenic_score(i,j));
		}
	}
	if (c == 'a') return compt;
	else return maxim;
}

void llegir_fitxer(std::ifstream& f) {
	if (f.is_open()) {
		while (!f.eof()) {
			for (int i = 0; i < FILES; i++) {
				for (int j = 0; j < COLUM; j++) {
					f >> matriu[i][j];
				}
			}

		}
	}
	else {
		std::cerr << "FILE CAN'T BE OPENED" << std::endl;
	}
	f.close();
}

int solve_A(std::ifstream& f) {
	llegir_fitxer(f);
	int interior = process_data('a');
	return EDGE + interior;
}

int solve_B(std::ifstream& f) {
	int scenic_score = process_data('b');
	return scenic_score;
}

int main() {
	std::ifstream f("input.txt");
	std::cout << "A: " << solve_A(f) << std::endl;
	std::cout << "B: " << solve_B(f) << std::endl;
	return 0;
}