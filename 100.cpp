#include <cstdio>
#include <algorithm>

int compute(int n) {
	int c = 1;
	while(n != 1) {
		if(n % 2 == 1) {
			n = n * 3 + 1;
		} else {
			n = n / 2;
		}
		c++;
	}
	return c;
}

int main() {
	int in1, in2, result;

	while(scanf("%d", &in1) != EOF) {
		int tmp1, tmp2;
		scanf("%d", &in2);
		if(in2 < in1) {
			tmp1 = in2;
			tmp2 = in1;
		} else {
			tmp1 = in1;
			tmp2 = in2;
		}
		result = 0;
		for(int i = tmp1; i <= tmp2; i++) {
			int tmp = compute(i);
			if(tmp > result) result = tmp;
		}
		printf("%d %d %d\n", in1, in2, result);
	}

	return 0;
}

