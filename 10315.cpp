#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

//Ranks
const int HIGH_CARD       = 100;
const int PAIR            = 200;
const int TWO_PAIRS       = 300;
const int THREE_OF_A_KIND = 400;
const int STRAIGHT        = 500;
const int FLUSH           = 600;
const int FULL_HOUSE      = 700;
const int FOUR_OF_A_KIND  = 800;
const int STRAIGHT_FLUSH  = 900;

const string values = "23456789TJQKA";
const string suits  = "CDHS";

//Rank card
int rank_card(char value) {
	int v_value = values.find(value);
	return v_value;
}

class PokerHand {
public:
	vector<int> cards;
	map<char, vector<int> > suit_groups;
	map<char, vector<int> > value_groups;

	PokerHand() {
		make_heap(cards.begin(), cards.end());
	}

	void add_card(char value, char suit) {
		int ranked = rank_card(value);
		if(suit_groups.find(suit) == suit_groups.end()) {
			vector<int> cards;
			suit_groups[suit] = cards;
			make_heap(cards.begin(), cards.end());
		}
		if(value_groups.find(value) == value_groups.end()) {
			vector<int> cards;
			value_groups[value] = cards;
			make_heap(cards.begin(), cards.end());
		}

		cards.push_back(ranked);
		suit_groups[suit].push_back(ranked);
		value_groups[value].push_back(ranked);

		push_heap(cards.begin(), cards.end());
		push_heap(suit_groups[suit].begin(), suit_groups[suit].end());
		push_heap(value_groups[value].begin(), value_groups[value].end());
	}

	int rank(vector<int> &results, vector<int> &remaining) {
		int r;
		results.clear();
		if((r = checkStraightFlush()) != -1) {
			results.clear();
			return r;
		} else if((r = checkFourOfAKind()) != -1) {
			results.clear();
			return r;
		} else if((r = checkFullHouse()) != -1) {
			results.clear();
			return r;
		} else if((r = checkFlush(results)) != -1) {
			return r;
		} else if((r = checkStraight()) != -1) {
			results.clear();
			return r;
		} else if((r = checkThreeOfAKind()) != -1) {
			results.clear();
			return r;
		} else if((r = checkPairs(results, remaining)) != -1) {
			return r;
		} else {
			results.clear();
			remaining.clear();
			return checkHighCard(results);
		}
	}

	int checkFullHouse() {
		map<char, vector<int> >::iterator it = value_groups.begin();
		char threeKey = -1;
		char twoKey   = -1;

		for(it = value_groups.begin(); it != value_groups.end(); it++) {
			if((*it).second.size() == 3) {
				threeKey = (*it).first;
			}
			if((*it).second.size() == 2) {
				twoKey = (*it).first;
			}
		}

		if(threeKey != -1 && twoKey != -1) {
			return FULL_HOUSE + values.find(threeKey);
		}

		return -1;

	}

	int checkHighCard(vector<int> &results) {
		results.resize(cards.size());
		copy(cards.begin(), cards.end(), results.begin());
		return HIGH_CARD;
	}

	int checkPairs(vector<int> &results, vector<int> &remaining) {
		results.clear();
		int oneKey = -1;
		map<char, vector<int> >::iterator it;
		for(it = value_groups.begin(); it != value_groups.end(); it++) {
			if((*it).second.size() == 2) {
				results.push_back(values.find((*it).first));
			} else {
				remaining.push_back(values.find((*it).first));
			}
		}

		make_heap(results.begin(), results.end());
		make_heap(remaining.begin(), remaining.end());

		switch(results.size()) {
			case 0:
				return -1;
				break;
			case 1:
				return PAIR;
				break;
			case 2:
				return TWO_PAIRS;
				break;
		}

		return -1;
	}

	int checkThreeOfAKind() {
		map<char, vector<int> >::iterator it;
		for(it = value_groups.begin(); it != value_groups.end(); it++) {
			if((*it).second.size() == 3) {
				return THREE_OF_A_KIND + values.find((*it).first);
			}
		}
		return -1;
	}

	int checkFlush(vector<int> &results) {
		map<char, vector<int> >::iterator it = suit_groups.begin();

		results.resize(cards.size());

		if((*it).second.size() == 5) {
			copy(cards.begin(), cards.end(), results.begin());
			return FLUSH;
		}
		
		return -1;
	}

	int checkStraight() {
		sort_heap(cards.begin(), cards.end());
		for(int i = 1; i < cards.size(); i++) {
			if(cards[i] - cards[i - 1] != 1) {
				make_heap(cards.begin(), cards.end());
				return -1;
			}
		}
		return STRAIGHT + cards.back();
	}

	int checkFourOfAKind() {
		map<char, vector<int> >::iterator it = value_groups.begin();

		for(it = value_groups.begin(); it != value_groups.end(); it++) {
			if((*it).second.size() == 4) {
				return FOUR_OF_A_KIND + values.find((*it).first);
			}
		}

		return -1;

	}

	int checkStraightFlush() {
		map<char, vector<int> >::iterator it = suit_groups.begin();

		if((*it).second.size() == 5) {
			vector<int> s = (*it).second;
			sort_heap(s.begin(), s.end());

			for(int i = 1; i < s.size(); i++) {
				if(s[i] - s[i - 1] != 1) {
					make_heap(s.begin(), s.end());
					return -1;
				}
			}

			int value = STRAIGHT_FLUSH + s.back();


			return value;
		}

		return -1;
	}

};

int compare(PokerHand *hand1, PokerHand *hand2) {
	vector<int> results1;
	vector<int> results2;

	vector<int> remaining1;
	vector<int> remaining2;
	
	int rank1 = hand1->rank(results1, remaining1);
	int rank2 = hand2->rank(results2, remaining2);

	if(rank1 > rank2) {
		return -1;
	} else if(rank1 < rank2) {
		return 1;
	} else {
		while(results1.size() > 0 && results2.size() > 0) {
			pop_heap(results1.begin(), results1.end());
			int compare1 = results1.back();
			results1.pop_back();
			pop_heap(results2.begin(), results2.end());
			int compare2 = results2.back();
			results2.pop_back();

			if(compare1 > compare2) return -1;
			if(compare1 < compare2) return 1;
		}

		while(remaining1.size() > 0 && remaining2.size() > 0) {
			pop_heap(remaining1.begin(), remaining1.end());
			int compare1 = remaining1.back();
			remaining1.pop_back();
			pop_heap(remaining2.begin(), remaining2.end());
			int compare2 = remaining2.back();
			remaining2.pop_back();

			if(compare1 > compare2) return -1;
			if(compare1 < compare2) return 1;
		}

	

		return 0;
	}

	return 0;
}

int main() {
	while(cin.peek() != '\n' && !cin.eof()) {
		char value;
		char suit;

		PokerHand *hand1 = new PokerHand();
		PokerHand *hand2 = new PokerHand();

		for(int i = 0; i < 5; i++) {
			cin >> value;
			cin >> suit;
			hand1->add_card(value, suit);
		}

		for(int i = 0; i < 5; i++) {
			cin >> value;
			cin >> suit;
			hand2->add_card(value, suit);
		}

		cin.ignore(100, '\n');

		int c = compare(hand1, hand2);

		switch(c) {
			case -1:
				cout << "Black wins." << endl;
			break;
			case 1:
				cout << "White wins." << endl;
			break;
			case 0:
				cout << "Tie." << endl;
			break;
			default:
				cout << "Got " << c << endl;
			break;
		}

		delete hand1;
		delete hand2;
	}
	
	return 0;
}

