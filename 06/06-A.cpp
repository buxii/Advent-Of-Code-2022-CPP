#include <iostream>
#include <fstream>
#include <string>
#include <vector>

bool solve_A(std::vector<char> vec, int i) {
	return vec[i] != vec[i - 1] and vec[i] != vec[i - 2] and vec[i] != vec[i - 3] and vec[i - 1] != vec[i - 2] and vec[i - 1] != vec[i - 3] and vec[i-2] != vec[i - 3];
}

int resultat() {
	std::fstream f("input.txt");
	std::vector<char> char_array;
	bool trobat = false;
	int compt = 1; //perque el resultat s'ha de donar amb numero normal, no index!
	if (f.is_open()) {
		while (!f.eof() and not trobat) {
			char c;
			c = f.get();
			char_array.push_back(c);
			if (char_array.size() > 3) 
				trobat=solve_A(char_array,char_array.size()-1);
			if (!trobat) compt++;
		} 
	}
	else std::cerr << "ERROR AL OBRIR EL FITXER" << std::endl;
	f.close();
	return compt;
}

int main() {
	std::cout << "RESULTAT 1: " << resultat() << std::endl;
	return 0;
}