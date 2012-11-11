#include <iostream>
#include <set>
#include <cstdlib>
#include <algorithm>

using namespace std;

int main() {
	int count;
	bool jolly;
	while(cin >> count) {
		if(count == 1) {
			cin >> count;
			cin.ignore(100, '\n');
			cout << "Jolly" << endl;
			continue;
		}
		set<int> numbers;
		int last;
		for(int i = 0; i < count; i++) {
			int tmp;
			cin >> tmp;
			if(i > 0) {
				numbers.insert(abs(last - tmp));
			}
			last = tmp;
		}
		cin.ignore(100, '\n');
		jolly = numbers.size() == count - 1 && 
                        numbers.find(1) != numbers.end() &&
                        numbers.find(count - 1) != numbers.end();
		if(jolly) {
			cout << "Jolly" << endl;
		} else {
			cout << "Not jolly" << endl;
		}
	}
	return 0;
}

