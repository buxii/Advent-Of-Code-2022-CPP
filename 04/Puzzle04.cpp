#include <iostream>
#include <fstream>

void solve(int& resultat1, int& resultat2) {
	std::ifstream f("input.txt");
	if (f.is_open()) {
		int e1, d1, e2, d2; //esquerra1,dreta1,etc.
		char c1, c2, c3; //c1=-;c2=,;c3=-;
		while (!f.eof()) {
			f >> e1 >> c1 >> d1 >> c2 >> e2 >> c3 >> d2;
			if ((e1 <= e2 and d1 >= d2) or (e2<=e1 and d2>=d1)) resultat1++;
			if ((e1 <= e2 and d1 >= e2) or (e2 <= e1 and d2 >= e1)) resultat2++;
		}
	}
	else 
		std::cerr << "ERROR AL OBRIR EL FITXER" << std::endl;
	f.close();

}

int main() {
	int resultatA = 0, resultatB = 0;
	solve(resultatA,resultatB);
	std::cout << "RESULTAT 1: " << resultatA << std::endl;
	std::cout << "RESULTAT 2: " << resultatB << std::endl;
	
	return 0;
}
