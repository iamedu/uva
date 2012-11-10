#include <iostream>

using namespace std;

int main() {
	char digits[10][7] = {
		{'-', '|', '|', ' ', '|', '|', '-'}, //0
		{' ', ' ', '|', ' ', ' ', '|', ' '}, //1
		{'-', ' ', '|', '-', '|', ' ', '-'}, //2
		{'-', ' ', '|', '-', ' ', '|', '-'}, //3
		{' ', '|', '|', '-', ' ', '|', ' '}, //4
		{'-', '|', ' ', '-', ' ', '|', '-'}, //5
		{'-', '|', ' ', '-', '|', '|', '-'}, //6
		{'-', ' ', '|', ' ', ' ', '|', ' '}, //7
		{'-', '|', '|', '-', '|', '|', '-'}, //8
		{'-', '|', '|', '-', ' ', '|', '-'}, //9
	};

	while(true) {
		string n;
		int s;
		int l;
		cin >> s >> n;
		if(s == 0 && n == "0") break;
		l = n.length();

		for(int j = 0; j < 7; j++) {
			if(j % 3 == 0) {
				for(int i = 0; i < l; i++) {
					cout << " ";
					for(int k = 0; k < s; k++) {
						cout << digits[n[i] - '0'][j];
					}
					cout << " ";
					if(i < l - 1) cout << " ";
				}
				cout << endl;
			} else {
				for(int k = 0; k < s; k++) {
					for(int i = 0; i < l; i++) {
						cout << digits[n[i] - '0'][j];
						for(int k = 0; k < s; k++) cout << " ";
						cout << digits[n[i] - '0'][j + 1];
						if(i < l - 1) cout << " ";
					}
					cout << endl;
				}
				j++;
			}
		}
		cout << endl;

	}	
	return 0;
}

