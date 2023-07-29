#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

/*
1000
2000	//6000
3000

4000	//4000

5000	/11000
6000

7000
8000	/24000
9000

10000	/10000

R/ 24000!!
*/

std::vector <std::string> crear_vector_strings() {
	std::vector <std::string> vect;
	std::ifstream input_file("puzzle01.txt");
	std::string calories_linea;
	if (input_file.is_open()) {
		while (!input_file.eof()) {
			getline(input_file, calories_linea);
			vect.push_back(calories_linea);
		}
	}
	return vect;
}

auto passar_string_a_vector_de_vectors_de_int(std::vector<std::string> const& s) {
	std::vector <std::vector<int>> resultat;
	resultat.push_back({}); //creem un element al vector per assegurar-nos que comen�i b�
	for (auto const& it : s) {
		if (it.size() > 0) {
			resultat.back().push_back(std::stoi(it));
		}
		else {
			resultat.push_back({});
		}
	}
	return resultat;
}

std::vector <int> suma_vector_de_vectors_int(const std::vector <std::vector<int>>& a_sumar) {
	std::vector <int> sumat;
	for (const auto& vec : a_sumar) {
		int suma = 0;
		for (int num : vec) {
			suma += num;
		}
		sumat.push_back(suma);
	}
	return sumat;
}

int main() {
	std::vector<std::string> vector_strings = crear_vector_strings(); //posem el fitxer dins del vector de strings

	auto vector_int = passar_string_a_vector_de_vectors_de_int(vector_strings); //passem el vector de strings a un vector de vector d'ints

	std::vector<int> vector_sumat = suma_vector_de_vectors_int(vector_int);

	int maxim_calories_1 = 0;

	//Problema 1:

	for (auto it : vector_sumat) {
		if (it > maxim_calories_1) {
			maxim_calories_1 = it;
		}
	}

	std::cout << "RESULTAT 1: " << maxim_calories_1 << std::endl;

	//Problema 2:

	//ordenem el vector i el posem en reversa per poder agafar els 3 primers i que siguin els mes grans (mes f�cil que fer .size(), .size()-1, .size()-2.
	sort(vector_sumat.begin(), vector_sumat.end());
	reverse(vector_sumat.begin(), vector_sumat.end());

	int resultat_2 = vector_sumat[0] + vector_sumat[1] + vector_sumat[2];


	std::cout << "RESULTAT 2: " << resultat_2 << std::endl;

	return 0;
}
