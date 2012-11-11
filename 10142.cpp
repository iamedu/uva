#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <algorithm>
#include <utility>

using namespace std;

class Ballot {
public:
	list<int> votes;	
	int get_vote() { return votes.front(); }
	void delete_vote() { votes.pop_front(); }
	void push_vote(int index) { votes.push_back(index); } 
};

int main() {
	int cases;
	cin >> cases;
	cin.ignore(100, '\n');
	cin.ignore(100, '\n');

	while(cases--) {
		int candidates;
		int min_votes = 0;
		cin >> candidates;
		cin.ignore(100, '\n');
		vector<string> names(candidates + 1);
		vector<int> votes(candidates + 1);
		list<Ballot *> ballots;

		fill(votes.begin(), votes.end(), 0);


		for(int i = 1; i <= candidates; i++) {
			char name[256];
			cin.getline(name, 256);
			names[i] = name;
		}
		while(cin.peek() != '\n' && !cin.eof()) {
			min_votes++;
			Ballot *b = new Ballot();
			for(int i = 0; i < candidates; i++) {
				int tmp;
				cin >> tmp;
				b->push_vote(tmp);
			}
			cin.ignore(100, '\n');
			ballots.push_back(b);
			votes[b->get_vote()]++;
		}
		cin.ignore(100, '\n');

		min_votes /= 2;

		while(true) {
			vector<int> mins;
			vector<int> deleted;
			int min = 1001;
			bool found = false;

			//check if have same votes
			bool same_votes = true;
			int vote_count = 0;

			for(vector<int>::iterator it = votes.begin() + 1; it != votes.end(); it++) {
				int pos = it - votes.begin();
				if(*it > min_votes) {
					cout << names[pos] << endl;
					found = true;
					same_votes = false;
					break;
				}

				if(*it > 0) {
					if(vote_count == 0) vote_count = *it;
					if(*it != vote_count) same_votes = false;
				}

				if(*it == 0 && !binary_search(deleted.begin(), deleted.end(), pos)) {
					deleted.push_back(pos);
				}

				if(*it > 0 && *it < min) {
					mins.clear();
					mins.push_back(pos);
					min = *it;
				} else if(*it == min) {
					mins.push_back(pos);
				}
			}

			if(same_votes) {
				for(vector<int>::iterator it = votes.begin() + 1; it != votes.end(); it++) {
					int pos = it - votes.begin();
					if(*it > 0) cout << names[pos] << endl;
				}
				break;
			}

			if(found) break;
			else {
				for(vector<int>::iterator it = mins.begin(); it != mins.end(); it++) {
					votes[*it] = 0;
					deleted.push_back(*it);
				}
				sort(deleted.begin(), deleted.end());
				for(list<Ballot *>::iterator it = ballots.begin(); it != ballots.end(); it++) {
					Ballot *b = *it;
					if(binary_search(deleted.begin(), deleted.end(), b->get_vote())) {
						while(binary_search(deleted.begin(), deleted.end(), b->get_vote())) {
							b->delete_vote();
						}
						votes[b->get_vote()]++;
					}
				}
			}
		}

		if(cases > 0) cout << endl;

	}

	return 0;
}


