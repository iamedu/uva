#include <iostream>
#include <string>
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

int decrypt(const string s, map<string, char> &decrypted, const pkey &old_key, pkey &key) {
	if(s.length() == 0) {
		copy(old_key.begin(), old_key.end(), key.begin());
		return 0;
	}

	int pos = s.find(" ");
	if(pos == -1) pos = s.size();

	string word = s.substr(0, pos);
	string next = (pos + 1 < s.length())?s.substr(pos + 1):"";

	if(decrypted.find(word) != decrypted.end()) {
		return decrypt(next, decrypted, old_key, key);
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
			if(old_key[word_char] == 0 || possible_key[word_char] == possible_char) {
				possible_key[word_char] = possible_char;
			}
			else break;
		}
		if(i == word.size()) {
			decrypted[word] = 1;
			if(decrypt(next, decrypted, possible_key, key) == 0) {
				return 0;
			}
			decrypted.erase(decrypted.find(word));
		}
	}

	if(classes.find(sig) == classes.end()) {
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
		map<string, char> decrypted;
		pkey key(128);
		fill(key.begin(), key.end(), 0);
		cin.getline(tmp, 182, '\n');
		string s = tmp;
		if(decrypt(s, decrypted, nkey, key) == -1) {
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

