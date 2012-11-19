#include <string>
#include <map>
#include <vector>
#include <set>
#include <iostream>
#include <queue>
#include <sstream>
#include <algorithm>

using namespace std;

class length_comparison {
public:
	bool operator() (const string &lhs, const string &rhs) const {
		return lhs.size() < rhs.size();
	}
};

typedef priority_queue<string, vector<string>, length_comparison> lp_queue;
typedef vector<char> pkey;
typedef vector<int> signature;
typedef map<signature, set<string> > dictionary;

map<string, signature> sig_cache;

signature calc_signature(string word) {
	if(sig_cache.find(word) != sig_cache.end()) return sig_cache[word];

	vector<char> seen;
	vector<char>::iterator s_it;
	signature result;
	for(string::iterator it = word.begin(); it != word.end(); it++) {
		char c= *it;
		int pos;
		s_it = find(seen.begin(), seen.end(), c);
		if(s_it == seen.end()) {
			pos = seen.size();
			seen.push_back(c);
		} else {
			pos = s_it - seen.begin();
		}
		result.push_back(pos);
	}
	sig_cache[word] = result;

	return result;
}

string print_pkey(pkey key) {
	stringstream buff;
	string result;

	buff << "[";

	for(int i = 0; i < 128; i++) {
		if(key[i]) {
			buff << char(i) << "->" << key[i] << ",";
		}
	}

	buff << "]";

	buff >> result;

	return result;
}


pkey decrypt(lp_queue words, dictionary dict, pkey current, bool *result) {
	pkey key(128);

	if(words.size() == 0) {
		*result = true;
		copy(current.begin(), current.end(), key.begin());
		return key;
	}

	string word = words.top();
	signature sig = calc_signature(word);
	words.pop();

	if(dict.find(sig) == dict.end()) {
		fill(key.begin(), key.end(), '*');
		*result = false;
		return key;
	}

	set<string> possibilities = dict[sig];


	for(set<string>::iterator it = possibilities.begin(); it != possibilities.end(); it++) {
		set<char> used;
		string possibility = *it;
		bool correct = true;

		for(int i = 0; i < 128; i++) if(current[i] && current[i] != '*') used.insert(current[i]);
		copy(current.begin(), current.end(), key.begin());
		for(int i = 0; i < possibility.size(); i++) {
			char possibility_char = possibility[i];
			char encrypted_char   = word[i];
			char current_char     = key[encrypted_char];
			if(used.find(possibility_char) != used.end() && current_char != possibility_char) {
				correct = false;
				break;
			}
			if(current_char != 0 && current_char != possibility_char) {
				correct = false;
				break;
			}
			key[encrypted_char] = possibility_char;
			used.insert(possibility_char);
		}
		if(correct) {
			bool r;
			pkey nkey = decrypt(words, dict, key, &r);
			if(r) {
				*result = true;
				return nkey;
			}
		}
	}

	fill(key.begin(), key.end(), '*');
	*result = false;
	return key;
}

pkey decrypt(lp_queue words, dictionary dict) {
	pkey key(128);
	fill(key.begin(), key.end(), 0);
	bool result;
	pkey fkey = decrypt(words, dict, key, &result);
	fkey[' '] = ' ';
	return fkey;
}

int main() {
	int n;
	dictionary dict;
	cin >> n;

	while(n--) {
		string tmp;
		cin >> tmp;
		cin.ignore(100, '\n');
		signature sig = calc_signature(tmp);
		dict[sig].insert(tmp);
	}

	string line;

	while(getline(cin, line)) {
		stringstream ss(line);
		lp_queue strings;
		set<string> tmp_strings;
		string tmp;

		while(ss >> tmp) {
			tmp_strings.insert(tmp);
		}

		for(set<string>::iterator it = tmp_strings.begin(); it != tmp_strings.end(); it++) {
			strings.push(*it);
		}

		pkey key = decrypt(strings, dict);

		for(string::iterator it = line.begin(); it != line.end(); it++) {
			cout << key[*it];
		}

		cout << endl;
	}

	return 0;
}
