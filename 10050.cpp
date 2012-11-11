#include <iostream>
#include <set>

using namespace std;

int main() {
	int cases;

	cin >> cases;

	while(cases--) {
		int days, parties, count = 0;
		set<int> parameters;
		cin >> days >> parties;

		for(int i = 0; i < parties; i++) {
			int tmp;
			cin >> tmp;
			parameters.insert(tmp);
		}

		for(int i = 1, day = 1; i <= days; i++, day++) {
			//Handle Friday and Saturday
			if(day == 7) {
				day = 0;
				continue;
			}
			if(day == 6) continue;

			bool hartal = false;

			for(set<int>::iterator it = parameters.begin(); it != parameters.end(); it++) {
				if(!hartal) hartal = (i % (*it) == 0);
				else break;
			}

			if(hartal) count++;
		}

		cout << count << endl;

	}

	return 0;
}

