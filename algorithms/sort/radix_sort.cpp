/* radix_sort of N strings with O(N*M) */

#include<iostream>

using namespace std;
#define MAX_N 100000
#define MAX_LEN 100
char line[MAX_N][MAX_LEN];
int N;
int maxlen;
char output[MAX_N][MAX_LEN];

void countsort(int idx) {
	int count[28] = {0};
	for (int i = 0; i < N; i++) {
		if (line[i][idx]<'a' || line[i][idx]>'z')
			count[1]++;
		else
			count[line[i][idx] - 'a' + 2]++;
	}
	for (int i = 1; i < 27; i++)
		count[i] += count[i - 1];
	for (int i = 0; i < N; i++) {
		int pos;
		if (line[i][idx]<'a' || line[i][idx]>'z')
			pos = count[0];
		else
			pos = count[line[i][idx] - 'a' + 1];
		for (int j = 0; j < maxlen; j++)
			output[pos][j] = line[i][j];
		if (line[i][idx]<'a' || line[i][idx]>'z')
			count[0]++;
		else
			count[line[i][idx] - 'a' + 1]++;
	}
	for (int i = 0; i < N; i++)
		for (int j = 0; j < maxlen; j++)
			line[i][j] = output[i][j];
	
}

void radixsort() {
	int idx;
	for (idx = maxlen-1; idx >=0; idx--) {
		countsort(idx);
	}

}
void printlines() {
	for (int i = 0; i < N; i++) {
		printf("%s\n", line[i]);
	}
}

int main() {
	freopen("input.txt", "r", stdin);
	scanf("%d", &N);	
	for (int i = 0; i < N;i++)
		scanf("%s", line[i]);
	maxlen = 0;
	for (int i = 0; i < N; i++) {
		int idx = 0;
		while (line[i][idx] != 0)
			idx++;
		if (idx > maxlen)
			maxlen = idx;
	}
	radixsort();
	printlines();

	return 0;
}