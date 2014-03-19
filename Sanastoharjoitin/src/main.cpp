#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "colors.h"

using namespace std;

struct muutos {
	char tyyppi, mista, mihin;

	muutos(char a, char b, char c) :tyyppi(a), mista(b), mihin(c) {}
};

vector<muutos> levenshtein(const string &s1, const string &s2) {
	int *dyn = new int[(s1.size() + 1)*(s2.size() + 1)];
	int offset = s1.size() + 1;

	// Alustetaan taulukko
	for (int i = 0; i <= s1.size(); i++) {
		dyn[i] = i;
	}
	for (int i = 0; i <= s2.size(); i++) {
		dyn[offset*i] = i;
	}

	// Muodostetaan Levenshteinin taulukko
	for (int i = 1; i <= s1.size(); i++) {
		for (int j = 1; j <= s2.size(); j++) {
			dyn[offset*j + i] = min(min(
				dyn[offset*j + i - 1] + 1,
				dyn[(offset) *(j - 1) + i] + 1),
				dyn[(offset) *(j - 1) + i - 1] + (s1[i - 1] != s2[j - 1]));
		}
	}

	// Etsitään lyhin reitti taulukon läpi
	int i = s1.size();
	int j = s2.size();
	vector<muutos> vastaus;
	while (i > 0 || j > 0) {
		int nykyinen = dyn[offset*j + i];
		int poisto = (i >= 1) ? dyn[offset*j + i - 1] : -2;
		int lisays = (j >= 1) ? dyn[offset*(j - 1) + i] : -2;
		int sama = (i >= 1 && j >= 1) ? dyn[offset*(j - 1) + i - 1] : -2;

		if (sama + 1 == nykyinen) {
			// Merkin muutos
			vastaus.push_back(muutos(1, s1[i - 1], s2[j - 1]));
			i--;
			j--;
		} else if (lisays+1==nykyinen) {
			// Lisäys
			vastaus.push_back(muutos(2, 0, s2[j - 1]));
			j--;
		} else if (poisto + 1 == nykyinen) {
			// Poisto
			vastaus.push_back(muutos(3, s1[i - 1], 0));
			i--;
		}else if (sama == nykyinen) {
			// Ei muutosta
			vastaus.push_back(muutos(0, s1[i - 1], s1[i - 1]));
			i--;
			j--;
		} else {
			// Miten ihmeessä tänne päädyttiin?
		}
	}

	// Vastaus muodostettiin käänteisessä järjestyksessä -> korjataan asia
	reverse(vastaus.begin(), vastaus.end());

	// Vapautetaan hieman muistia
	delete[] dyn;

	return vastaus;
}

void tulostaAluperainen(const vector<muutos> &muutokset) {
	for (const muutos &muutos : muutokset) {
		switch (muutos.tyyppi) {
		case 0:
			// Sama merkki
			cout << b_black << f_white << muutos.mista;
			break;
		case 1:
			// Merkin muutos
			cout << b_yellow << f_black << muutos.mista;
			break;
		case 2:
			// Lisäys
			cout << b_black << " ";
			break;
		case 3:
			// Poisto
			cout << b_red << f_black << muutos.mista;
			break;
		}
	}
	// Palautetaan värit kohdalleen
	cout << b_black << f_white;

}
void tulostaMuutettu(const vector<muutos> &muutokset) {
	for (const muutos &muutos : muutokset) {
		switch (muutos.tyyppi) {
		case 0:
			// Sama merkki
			cout << b_black << f_white << muutos.mihin;
			break;
		case 1:
			// Merkin muutos
			cout << b_yellow<<f_black << muutos.mihin;
			break;
		case 2:
			// Lisäys
			cout << b_green << f_black << muutos.mihin;
			break;
		case 3:
			// Poisto
			cout <<b_black<< " ";
			break;
		}
	}
	// Palautetaan värit kohdalleen
	cout << b_black << f_white;
}

int main() {
	string a, b;
	while (1) {
		cin >> a >> b;
		vector<muutos> muutokset = levenshtein(a, b);
		tulostaAluperainen(muutokset);
		cout << endl;
		tulostaMuutettu(muutokset);
		cout << endl;
	}
}