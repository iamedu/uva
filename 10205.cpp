#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> shuffle(const vector<int> &deck, const vector<int> &moves) {
	vector<int> result(deck.size());
	fill(result.begin(), result.end(), 0);
	for(int i = 1; i < 53; i++) {
		result[i] = deck[moves[i]];
	}
	return result;
}

int main() {
	int n;
	cin >> n;
	
	while(n--) {
		int count;
		vector<vector<int> > shuffles;
		vector<string> suits;
		suits.push_back("Clubs");
		suits.push_back("Diamonds");
		suits.push_back("Hearts");
		suits.push_back("Spades");

		vector<string> cards;
		cards.push_back("2");
		cards.push_back("3");
		cards.push_back("4");
		cards.push_back("5");
		cards.push_back("6");
		cards.push_back("7");
		cards.push_back("8");
		cards.push_back("9");
		cards.push_back("10");
		cards.push_back("Jack");
		cards.push_back("Queen");
		cards.push_back("King");
		cards.push_back("Ace");

		vector<int> deck(53);

		cin >> count;

		shuffles.resize(count + 1);

		for(int i = 1; i <= count; i++) {
			shuffles[i].resize(53);
			for(int j = 1; j < 53; j++) {
				cin >> shuffles[i][j];
			}
		}

		cin.ignore(100, '\n');

		for(int i = 1; i < 53; i++) deck[i] = i;
		
		while(cin.peek() != '\n' && !cin.eof()) {
			int shuffle_idx;
			cin >> shuffle_idx;
			cin.ignore(100, '\n');
			deck = shuffle(deck, shuffles[shuffle_idx]);
		}

		for(int i = 1; i < 53; i++) {
			int idx = deck[i] - 1;
			string card = cards[idx % 13];
			string suit = suits[idx / 13];
			cout << card << " of " << suit << endl;
		}

		if(n) cout << endl;

	}

	return 0;
}

