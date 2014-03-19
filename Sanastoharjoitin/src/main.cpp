#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "colors.h"

using namespace std;

struct change {
	char type, from, to;

	change(char a, char b, char c) :type(a), from(b), to(c) {}
};

vector<change> changes(const string &s1, const string &s2) {
	int *dyn = new int[(s1.size() + 1)*(s2.size() + 1)];
	int offset = s1.size() + 1;

	for (int i = 0; i <= s1.size(); i++) {
		dyn[i] = i;
	}
	for (int i = 0; i <= s2.size(); i++) {
		dyn[offset*i] = i;
	}

	for (int i = 1; i <= s1.size(); i++) {
		for (int j = 1; j <= s2.size(); j++) {
			dyn[offset*j + i] = min(min(
				dyn[offset*j + i - 1] + 1,
				dyn[(offset) *(j - 1) + i] + 1),
				dyn[(offset) *(j - 1) + i - 1] + (s1[i - 1] != s2[j - 1]));
		}
	}

	// Find the shortest path
	int i = s1.size();
	int j = s2.size();
	vector<change> res;
	while (i > 0 || j > 0) {
		int cur = dyn[offset*j + i];
		int del = (i >= 1) ? dyn[offset*j + i - 1] : -2;
		int ins = (j >= 1) ? dyn[offset*(j - 1) + i] : -2;
		int edit = (i >= 1 && j >= 1) ? dyn[offset*(j - 1) + i - 1] : -2;

		if (edit + 1 == cur) {
			// Change
			res.push_back(change(1, s1[i - 1], s2[j - 1]));
			i--;
			j--;
		} else if (ins+1==cur) {
			// Insering
			res.push_back(change(2, 0, s2[j - 1]));
			j--;
		} else if (del + 1 == cur) {
			// Deleting
			res.push_back(change(3, s1[i - 1], 0));
			i--;
		}else if (edit == cur) {
			// Same characters
			res.push_back(change(0, s1[i - 1], s1[i - 1]));
			i--;
			j--;
		} else {
			// ERROR!!!
		}
	}

	reverse(res.begin(), res.end());

	delete[] dyn;
	return res;
}

void printDiff(const vector<change> &changes) {
	// Original
	for (const change &c : changes) {
		switch (c.type) {
		case 0:
			// Keep this
			cout << b_black <<f_white<< c.from;
			break;
		case 1:
			// Change
			cout << b_yellow << f_black << c.from;
			break;
		case 2:
			// Insertion
			cout << b_black  << " ";
			break;
		case 3:
			// Deletion
			cout << b_red << f_black << c.from;
			break;
		default:
			break;
		}
	}
	cout << endl;

	// Changed
	for (const change &c : changes) {
		switch (c.type) {
		case 0:
			// Keep this
			cout << b_black << f_white << c.to;
			break;
		case 1:
			// Change
			cout << b_yellow<<f_black << c.to;
			break;
		case 2:
			// Insertion
			cout << b_green << f_black << c.to;
			break;
		case 3:
			// Deletion
			cout <<b_black<< " ";
			break;
		default:
			break;
		}
	}
	cout << endl;
	cout << b_black << f_white;
}

int main() {
	string a, b;
	while (1) {
		cin >> a >> b;
		vector<change> c = changes(a, b);
		printDiff(c);
	}
}