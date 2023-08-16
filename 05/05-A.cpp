#include <iostream>
#include <vector>
#include <fstream>
#include <string>


void solve(std::vector<std::vector<char>>& vec) {
	std::ifstream f("input.txt");
	int i = 0;
	if (f.is_open()) {
		while (!f.eof()) {
			if (i < 9) {
				std::string str;
				f >> str;
				vec.push_back({});
				for (int j = 0; j < str.size(); j++) {
					vec.back().push_back(str[j]);
				}
				i++;
			}
			else {
				std::string s1, s2, s3;
				int numero_a_moure, origen, desti;
				f >> s1 >> numero_a_moure >> s2 >> origen >> s3 >> desti;
				for (int j = 0; j < numero_a_moure; j++) {
					char a_moure = vec[origen-1].back();
					vec[origen-1].pop_back();
					vec[desti-1].push_back(a_moure);
				}
			}
		}
	}
	else std::cerr << "ERROR AL OBRIR EL FITXER" << std::endl;
}

int main() {
	std::vector<std::vector<char>> caixes;
	solve(caixes);
	for (const auto& inner_vector : caixes) 
		std::cout << inner_vector.back() << std::endl;
	
	return 0;
}