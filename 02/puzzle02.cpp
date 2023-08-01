#include <iostream>
#include <string>
#include <fstream>
#include <unordered_map>

//ROCA: 1 punts --> A i X
//PAPER: 2 punts --> B i Y
//TISORES: 3 punts --> C i Z

//si guanyes tu, son 6 punts + lo que tiris: depen de si es roca(1), paper(2), tisores(3)
//si perds tu, son 0 punts + lo que tiris: depen de si es roca(1), paper(2), tisores(3)
//si empates, son 3 punts + lo que tiris: depen de si es roca(1), paper(2), tisores(3)

int resoldre1(char a, char b) {
	int resultat=0;
	if (a == 'A' and b == 'X' or a == 'B' and b == 'Y' or a == 'C' and b == 'Z') resultat += 3; //Empat
	else if ((b == 'X' and a == 'C') or (b == 'Y' and a == 'A') or (b == 'Z' and a == 'B')) resultat += 6; //Victoria
	//No cal cas derrota ja que es += 0!
	if (b == 'X') resultat += 1;
	else if (b == 'Y') resultat += 2;
	else if (b == 'Z') resultat += 3;

	return resultat;
}

int resoldre2(char a, char b, std::unordered_map<char,char>& movimentGuanyador, std::unordered_map<char, char>& movimentEmpat, std::unordered_map<char, char>& movimentPerdedor, std::unordered_map<char,int>& puntuacio) {
	int resultat = 0;
	
	if (b == 'X') resultat += puntuacio[movimentPerdedor[a]];
	else if (b == 'Y') resultat = 3 + puntuacio[movimentEmpat[a]];
	else resultat = 6 + puntuacio[movimentGuanyador[a]];
	
	return resultat;
}

int main() {
	std::ifstream f_in("puzzle02.txt");
	std::string str;
	int suma1 = 0, suma2 = 0;
	
	std::unordered_map<char, char> hash_guanyar = {{'A','Y'},{'B','Z'},{'C','X'}};
	std::unordered_map<char, char> hash_empatar = {{'A','X'},{'B','Y'},{'C','Z'} };
	std::unordered_map<char, char> hash_perdre = {{'A','Z'},{'B','X'},{'C','Y'} };
	std::unordered_map<char, int> hash_puntuacio = { {'X',1},{'Y',2},{'Z',3} };

	if (f_in.is_open()) {
		while (!f_in.eof()) {
			getline(f_in,str);
			suma1 += resoldre1(str[0], str[2]); 
			suma2 += resoldre2(str[0],str[2],hash_guanyar, hash_empatar, hash_perdre,hash_puntuacio);
		}
	}
	else {
		std::cerr << "ERROR OBRINT EL FITXER" << std::endl;
		return 1;
	}

	f_in.close();

	std::cout << "RESULTAT 1: " << suma1 << std::endl;
	std::cout << "RESULTAT 2: " << suma2 << std::endl;

	return 0;
}