#include <cstdio>
#include <vector>

using namespace std;

int main() {
	int n;
	vector<double> students(1000);
	vector<double>::iterator s_it;

	while(true) {
		scanf("%d", &n);
		students.resize(n);
		double result = 0.0;
		double tmp;
		double lendSum = 0;
		double borrowSum = 0;
		double max;
		if(n == 0) break;
		for(int i = 0; i < n; i++) {
			scanf("%lf", &tmp);
			students[i] = tmp;
			result += tmp;
		}
		result /= n;
		for(s_it = students.begin(); s_it != students.end(); s_it++) {
			double sum = (int)((result - *s_it) * 100) / 100.0;
			if(*s_it < result) {
				borrowSum += sum;
			} else {
				lendSum -= sum;
			}
		}
		max = (borrowSum > lendSum)?borrowSum:lendSum;
		printf("$%.2lf\n", max);
	}

	return 0;
}

