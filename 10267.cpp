#include <iostream>
#include <string>
#include <stack>
#include <utility>
#include <algorithm>

using namespace std;

const int MAX = 260;

void fill(char bitmap[MAX][MAX], int M, int N, int X, int Y, char C) {
	char curr = bitmap[X][Y];
	bool visited[MAX][MAX];
	stack< pair<int, int> > pstack;

	pstack.push(make_pair(X, Y));

	for(int i = 0; i < MAX; i++) {
		for(int j = 0; j < MAX; j++) {
			visited[i][j] = false;
		}
	}

	while(!pstack.empty()) {
		pair<int, int> el = pstack.top();
		pstack.pop();
		int x, y;
		x = el.first;
		y = el.second;

		if(bitmap[x][y] == curr) {
			visited[x][y] = true;
			bitmap[x][y] = C;

			if(x > 1 && !visited[x-1][y]) {
				pstack.push(make_pair(x-1, y));
			}
			if(y > 1 && !visited[x][y-1]) {
				pstack.push(make_pair(x, y-1));
			}
			if(x < M && !visited[x+1][y]) {
				pstack.push(make_pair(x+1, y));
			}
			if(y < N && !visited[x][y+1]) {
				pstack.push(make_pair(x, y+1));
			}

		}

		

	}
	

}

int main() {
	char bitmap[MAX][MAX];
	char C;
	char c;
	int M, N;
	int X, Y;
	int X1, X2;
	int Y1, Y2;
	string name;

	while(cin >> c) {
		switch(c) {
			case 'X':
				return 0;
			case 'I':
				cin >> M >> N;
				for(int i = 1; i <= M; i++) {
					for(int j = 1; j <= N; j++) {
						bitmap[i][j] = 'O';
					}
				}
			break;
			case 'C':
				for(int i = 1; i <= M; i++) {
					for(int j = 1; j <= N; j++) {
						bitmap[i][j] = 'O';
					}
				}
			break;
			case 'L':
				cin >> X >> Y >> C;
				bitmap[X][Y] = C;
			break;
			case 'V':
				cin >> X >> Y1 >> Y2 >> C;
				if(Y2 < Y1) swap(Y2, Y1);
				for(int i = Y1; i <= Y2; i++) {
					bitmap[X][i] = C;
				}
			break;
			case 'H':
				cin >> X1 >> X2 >> Y >> C;
				if(X2 < X1) swap(X2, X1);
				for(int i = X1; i <= X2; i++) {
					bitmap[i][Y] = C;
				}
			break;
			case 'K':
				cin >> X1 >> Y1 >> X2 >> Y2 >> C;
				for(int i = X1; i <= X2; i++) {
					for(int j = Y1; j <= Y2; j++) {
						bitmap[i][j] = C;
					}
				}
			break;
			case 'F':
				cin >> X >> Y >> C;
				fill(bitmap, M, N, X, Y, C);
			break;
			case 'S':
				cin >> name;
				cout << name << endl;
				for(int i = 1; i <= N; i++) {
					for(int j = 1; j <= M; j++) {
						cout << bitmap[j][i];
					}
					cout << endl;
				}
			break;
			default:
				cin.ignore(10000, '\n');
			break;
		}
	}

	return 0;
}

