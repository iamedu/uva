#include <cstring>
#include <iostream>

using namespace std;

const int MAX = 102;

int main() {
	char board[MAX][MAX];

	int n, m;
	int c = 0;
	
	while(true) {
		cin >> n >> m;
		if(n == 0 && m == 0) break;
		if(c != 0) cout << endl;
		cout << "Field #" << ++c << ":" << endl;
		for(int i = 1; i <= n; i++) {
			for(int j = 1; j <= m; j++) {
				board[i][j] = 0;
			}
		}
		for(int i = 1; i <= n; i++) {
			for(int j = 1; j <= m; j++) {
				char tmp;
				cin >> tmp;
				if(tmp == '*') {
					board[i][j] = tmp;
					int i0 = (i > 0)?i - 1:i;
					int j0 = (j > 0)?j - 1:j;
					int i1 = (i < n)?i + 1:i;
					int j1 = (j < m)?j + 1:j;
					for(int ii = i0; ii <= i1; ii++) {
						for(int jj = j0; jj <= j1; jj++) {
							if(board[ii][jj] != '*') {
								board[ii][jj]++;
							}
						}
					}
				}
			}
		}
		for(int i = 1; i <= n; i++) {
			for(int j = 1; j <= m; j++) {
				char tmp = board[i][j];
				if(tmp == '*') cout << '*';
				else cout << (int)tmp;
			}
			cout << endl;
		}
		
	}
	
	return 0;
}

