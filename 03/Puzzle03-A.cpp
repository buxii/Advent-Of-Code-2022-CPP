#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <unordered_set>

/*
	1. DIVIDIR LINEAS PER LA MEITAT
	2. BUSCAR CARACTERS COMUNS EN LES DUES MEITATS (A i a no son iguals, A i A si!)
	3. ACONSEGUIR NUMERO VINCULAT A LES LLETRES COMUNES -> (a ->1, z->26, A->27, Z->52)
	4. SUMAR EL TOTAL
*/

void llegir_fitxer(std::vector<std::string>& vector_objectes) {
	std::fstream f("puzzle03.txt");

	if (f.is_open()) {
		while (!f.eof()) {
			std::string str;
			getline(f, str);
			vector_objectes.push_back(str);
		}
	}
	else {
		std::cerr << "ERROR AL OBRIR EL FITXER" << std::endl;
	}
	f.close();
}

void omplir_vector_meitat_linies(std::vector<std::string> vec_a_dividir, std::vector<std::vector<std::string>>& vec_meitat) {

	for (const auto& it : vec_a_dividir) {
		std::string str1, str2;
		for (size_t i = 0; i < it.size() / 2; i++) {
			str1 += it[i];
			str2 += it[it.size() / 2 + i];
		}
		std::vector<std::string> temp;
		temp.push_back(str1);
		temp.push_back(str2);
		vec_meitat.push_back(temp);
	}
}

void caracters_comuns(std::vector<char>& caracters, std::string s1, std::string s2) {
	std::unordered_set<char> temp;

	for (int i = 0; i < s1.size(); ++i) {
		for (int j = 0; j < s2.size(); ++j) {
			if (s1[i] == s2[j]) {
				temp.insert(s1[i]); //ho insertem a un unordered_set perque no agafa repetits!
			} 
		}
	}
	for (const auto& it : temp) {
		caracters.push_back(it);
	}
}

void trobar_caracters_comuns(const std::vector<std::vector<std::string>> complet, std::vector<char>& caracters) {
	for (const auto& it : complet) {
		caracters_comuns(caracters, it.front(), it.back());
	}
}

int suma(const std::vector<char> vec) {
	int suma = 0;
	/*
	LA MEVA SOLUCIO
	std::unordered_map<char, int> int_a_sumar = {
		{'a',1},{'b',2},{'c',3},{'d',4},{'e',5},{'f',6},{'g',7},{'h',8},{'i',9},{'j',10},{'k',11},
		{'l',12},{'m',13},{'n',14},{'o',15},{'p',16},{'q',17},{'r',18},{'s',19},{'t',20},{'u',21},
		{'v',22},{'w',23},{'x',24},{'y',25},{'z',26},{'A',27},{'B',28},{'C',29},{'D',30},{'E',31},
		{'F',32},{'G',33},{'H',34},{'I',35},{'J',36},{'K',37},{'L',38},{'M',39},{'N',40},{'O',41},
		{'P',42},{'Q',43},{'R',44},{'S',45},{'T',46},{'U',47},{'V',48},{'W',49},{'X',50},{'Y',51},
		{'Z',52}
	};

	for (const auto& it : vec) 
		suma += int_a_sumar[it];
	*/

	//SOLUCIO MILLOR(no ocupem tanta memoria):
	
	for (auto it : vec) {
		if (it >= 'a' and it <= 'z') {
			suma += it - 'a' + 1;
		}
		else suma += it - 'A' + 1 + 26; 
	}

	return suma;
}

int main() {
	
	std::vector<std::string> vector_objectes;
	llegir_fitxer(vector_objectes);
	std::vector<std::vector<std::string>> vector_meitat_linies;
	omplir_vector_meitat_linies(vector_objectes, vector_meitat_linies); 
	std::vector<char> caracters_iguals;
	trobar_caracters_comuns(vector_meitat_linies, caracters_iguals);
	std::cout << "RESULTAT 1: " << suma(caracters_iguals) << std::endl;

	return 0;
}