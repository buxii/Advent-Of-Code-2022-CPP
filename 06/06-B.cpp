#include <iostream>
#include <fstream>
#include <string>
#include <set>

struct taula_hash {
	bool existeix;
	int posicio;
};

void llegir_fitxer(std::string& str) {
	std::fstream f("input.txt");
	if (f.is_open()) {
		f >> str;
	}
	else std::cerr << "ERROR AL OBRIR EL FITXER" << std::endl;
	f.close();
}


int main() {
	std::string str;
	llegir_fitxer(str);
	for (int i = 13; i < str.size(); i++) {
		std::set<char> llista_sense_repetits; //el set el que fa es ser com un vector pero que no pot contenir valors repetits!
		int compt = 14;
		for (int j = i; compt > 0; j--, compt--) { 
			llista_sense_repetits.insert(str[j]);
		}
		if (llista_sense_repetits.size() == 14) {
			std::cout << i + 1 << std::endl;
			break;
		}
	}

	return 0;
}