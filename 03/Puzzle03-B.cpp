#include <iostream>
#include <string>
#include <fstream>
#include <vector>


void llegir_fitxer_i_omplir_vector(std::vector<std::vector<std::string>>& vector_objectes) {
	std::fstream f("puzzle03-B.txt");
	int it = 0;
	bool final = false;
	std::string str;
	std::vector<std::string> temp;

	if (f.is_open()) {
		getline(f, str);
		while (!f.eof() or !final) {
			if (it == 3) {
				vector_objectes.push_back(temp);
				temp.clear();
				it = 0;
				if (f.eof()) final = true;
			}
			else {
				temp.push_back(str);
				it++;
			}
			if(it!=3) getline(f, str);
		}
	}
	else {
		std::cerr << "ERROR AL OBRIR EL FITXER" << std::endl;
	}

	f.close();
}


void caracters_comuns(char &igual, std::string s1, std::string s2, std::string s3) {
	std::string str[3] = { s1,s2,s3 };
	bool primari[52];
	memset(primari, true, sizeof(primari));

	for (int i = 0; i < 3; i++) {
		bool secundari[52] = { false };
		for (int j = 0; str[i][j]; j++) {
			if (str[i][j] >= 'a' and str[i][j] <= 'z') {
				if (primari[str[i][j] - 'a'])
					secundari[str[i][j] - 'a'] = true;
			}
			else {
				if (primari[str[i][j] - 'A' + 26])
					secundari[str[i][j] - 'A' + 26] = true;
			}		
		}
		memcpy(primari, secundari, sizeof(secundari));
	}

	for (int i = 0; i < 52; i++) {
		if (primari[i]) {
			if (i < 26)  igual = char(i + 'a');
			else igual = char(i + 'A' - 26);
		}
	}

}

void trobar_caracters_comuns(const std::vector<std::vector<std::string>> complet, std::vector<char>& caracters) {
	for (const auto& it : complet) {
		char igual=' '; //Nomes n'hi ha un, no cal cap llibreria
		caracters_comuns(igual, it[0], it[1], it[2]);
		if (igual != ' ') caracters.push_back(igual);
	}
}

int suma(const std::vector<char> vec) {
	int suma = 0;

	for (auto it : vec) {
		if (it >= 'a' and it <= 'z') {
			suma += it - 'a' + 1;
		}
		else suma += it - 'A' + 1 + 26;
	}

	return suma;
}

int main() {

	std::vector<std::vector<std::string>> vector_objectes;
	llegir_fitxer_i_omplir_vector(vector_objectes);
	std::vector<char> caracters_iguals;
	trobar_caracters_comuns(vector_objectes, caracters_iguals);
	std::cout << "RESULTAT 2: " << suma(caracters_iguals) << std::endl;

	return 0;
}