#include <iostream>
#include <string>
#include <queue>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <sstream>

using namespace std;

typedef vector<int> signature;
typedef vector<char> pkey;

map<string, signature> sig_cache;
map< signature, vector< string > > classes;

class length_comparison {
public:
	bool operator() (const string &lhs, const string &rhs) {
		return lhs.size() < rhs.size();
	}
};

signature calc_signature(string s) {

	if(sig_cache.find(s) != sig_cache.end()) return sig_cache[s];

	vector<int> freqs(128);
	signature signature;
	fill(freqs.begin(), freqs.end(), 0);
	for(string::iterator i = s.begin(); i != s.end(); i++) {
		freqs[*i] += 1;
	}

	for(vector<int>::iterator i = freqs.begin(); i != freqs.end(); i++) {
		if(*i) signature.push_back(*i);
	}

	sort(signature.begin(), signature.end());

	sig_cache[s] = signature;

	return signature;
}

int decrypt(priority_queue<string, vector<string>, length_comparison> &s, vector<bool> used, map<string, char> &decrypted, const pkey &old_key, pkey &key) {
	if(s.size() == 0) {
		copy(old_key.begin(), old_key.end(), key.begin());
		return 0;
	}

	string word = s.top();
	s.pop();

	if(decrypted.find(word) != decrypted.end()) {
		return decrypt(s, used, decrypted, old_key, key);
	}


	signature sig = calc_signature(word);

	if(classes.find(sig) == classes.end()) {
		return -1;
	}

	vector<string> words = classes[sig];

	int i;
	for(vector<string>::iterator it = words.begin(); it != words.end(); it++) {
		string possibility = *it;
		pkey possible_key(128);
		copy(old_key.begin(), old_key.end(), possible_key.begin());
		for(i = 0; i < word.size(); i++) {
			char word_char = word[i];
			char possible_char = possibility[i];
			bool char_used = used[possible_char];
			if(old_key[word_char] == 0 && char_used) break;
			if(old_key[word_char] == 0 || possible_key[word_char] == possible_char) {
				possible_key[word_char] = possible_char;
			}
			else break;
		}
		if(i == word.size()) {
			decrypted[word] = 1;
			vector<bool> new_used(128);
			for(int j = 0; j < 128; j++) new_used[j] = false;
			for(int j = 1; j < 128; j++) {
				if(possible_key[j]) {
					new_used[possible_key[j]] = true;
				}
			}
			if(decrypt(s, new_used, decrypted, possible_key, key) == 0) {
				return 0;
			}
			decrypted.erase(decrypted.find(word));
		}
	}

	return -1;
}

int main() {
	int word_count = 0;
	pkey nkey(128);
	fill(nkey.begin(), nkey.end(), 0);

	cin >> word_count;
	cin.ignore(20, '\n');

	for(int i = 0; i < word_count; i++) {
		char tmp[82];
		string s;
		cin.getline(tmp, 82, '\n');
		s = tmp;
		signature sig = calc_signature(s);
		classes[sig].push_back(s);
	}

	while(cin.peek() != '\n' && !cin.eof()) {
		char tmp[182];
		vector<bool> used(128);
		map<string, char> decrypted;
		pkey key(128);
		fill(key.begin(), key.end(), 0);
		fill(used.begin(), used.end(), false);
		cin.getline(tmp, 182, '\n');
		string s = tmp;
		stringstream ss(s);
		priority_queue<string, vector<string>, length_comparison> pq;

		while(ss.peek() != '\n' && !ss.eof()) {
			string st;
			ss >> st;
			ss.ignore(100, ' ');
			pq.push(st);
		}

		if(decrypt(pq, used, decrypted, nkey, key) == -1) {
			fill(key.begin(), key.end(), '*');
		}
		key[' '] = ' ';
		for(string::iterator i = s.begin(); i != s.end(); i++) {
			cout << key[*i];
		}
		cout << endl;
	}
	return 0;
}

