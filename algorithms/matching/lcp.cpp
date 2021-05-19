/* This app calculates the Longest Common Prefix of a given string in NlogN time
First it builds suffix array in sa within O(NlogN) using radixsort, and it generates LCP within O(N).
*/

#include<stdio.h>

#define MAX_N 100000

char str[MAX_N + 1];
int sa[MAX_N + 1];
int rank[MAX_N + 1];
int id[MAX_N + 1];
int lcp[MAX_N + 1];
int str_size;
struct tuple {
	int first;
	int second;
	tuple& operator=(const tuple a) {
		first = a.first;
		second = a.second;
		return *this;
	}
};
tuple tuples[MAX_N + 1];
tuple outputs[MAX_N + 1];
int firstoutputs[MAX_N + 1];
//int counts[MAX_N+1];
void firstcountsort() {
	int counts[26] = { 0, };
	for (int i = 0; i < str_size; i++)
		counts[str[sa[i]] - 'a']++;
	for (int i = 1; i < 26; i++)
		counts[i] += counts[i - 1];
	for (int i = 0; i < str_size; i++) {
		firstoutputs[counts[str[sa[i]] - 'a'] - 1] = sa[i];
		counts[str[sa[i]] - 'a']--;
	}
	for (int i = 0; i < str_size; i++)
		sa[i] = firstoutputs[i];
}
void counting_sort(int idx) {
	int counts[MAX_N + 1] = { 0, };
	if (idx == 0) {
		for (int i = 0; i < str_size; i++)
			counts[tuples[i].second + 1]++;
		for (int i = 1; i < str_size; i++)
			counts[i] += counts[i - 1];
		for (int i = 0; i < str_size; i++) {
			outputs[counts[tuples[i].second + 1] - 1] = tuples[i];
			counts[tuples[i].second + 1]--;
		}
		for (int i = 0; i < str_size; i++)
			tuples[i] = outputs[i];
	}
	else {
		for (int i = 0; i < str_size; i++)
			counts[tuples[i].first + 1]++;
		for (int i = 1; i < str_size; i++)
			counts[i] += counts[i - 1];
		/*for (int i = str_size-1; i >=1; i--)
			counts[i] = counts[i - 1];*/
			//counts[0] = 0;
		for (int i = 0; i < str_size; i++) {
			outputs[counts[tuples[i].first]] = tuples[i];
			counts[tuples[i].first]++;
		}
		for (int i = 0; i < str_size; i++)
			tuples[i] = outputs[i];
	}
}
void radixsort() { //2digit
	for (int i = 0; i < 2; i++) {
		counting_sort(i);
	}
}
int main() {
	freopen("input.txt", "r", stdin);
	scanf("%s", str);
	str_size = 0;
	while (str[str_size] != 0)
		str_size++;
	for (int i = 0; i < str_size; i++)
		sa[i] = i;
	//processing the remainder at the end is important
	firstcountsort();
	int idx1 = 0;
	id[0] = 0;
	//rank make
	for (int i = 0; i < str_size; i++)
		rank[sa[i]] = i;
	//id make
	for (int i = 1; i < str_size; i++) {
		if (str[sa[i]] != str[sa[i - 1]])
			idx1++;
		id[i] = idx1;
	}
	// tuple make
	for (int i = 0; i < str_size; i++) {
		tuples[i].first = id[i];
		if (sa[i] + 1 < str_size)
			tuples[i].second = id[rank[sa[i] + 1]];
		else
			tuples[i].second = -1;
	}
	for (int sz = 2; sz < str_size; sz *= 2) {
		radixsort();
		//rank_make
		for (int i = 0; i < str_size; i++)
			rank[sa[i]] = i;
		//id make
		int idx2 = 0;
		id[0] = 0;
		for (int i = 1; i < str_size; i++) {
			if (tuples[i].first != tuples[i - 1].first || tuples[i].second != tuples[i - 1].second)
				idx2++;
			id[i] = idx2;
		}
		//tuple_make
		for (int i = 0; i < str_size; i++) {
			tuples[i].first = id[i];
			if (sa[i] + sz < str_size)
				tuples[i].second = id[rank[sa[i] + sz]];
			else
				tuples[i].second = -1;
		}
	}
	for (int i = 0; i < str_size; i++) {
		for (int idx = sa[i]; idx < str_size; idx++)
			printf("%c", str[idx]);
		printf("\n");
	}
	int k = 0;
	for (int i = 0; i < str_size; i++, k ? k-- : 0)
	{
		if (rank[i] == 0) { k = 0; lcp[rank[i]] = k; continue; }
		int j = sa[rank[i] - 1];
		while (i + k < str_size && j + k < str_size && str[i + k] == str[j + k]) k++;
		lcp[rank[i]] = k;
	}
	int maxval = 0;
	for (int i = 0; i < str_size; i++)
		if (maxval < lcp[i])
			maxval = lcp[i];
	printf("biggest LCP: %d\n", maxval);
	return 0;
}