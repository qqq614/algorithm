//question : https://codingcompetitions.withgoogle.com/codejam/round/00000000004362d7/00000000007c0f00
#define _CRT_SECURE_NO_DEPRECATE
#define ll long long 
#include<iostream>
#include<algorithm>
#include<string>
#include<vector>




using namespace std;
int test_num;

int N;
ll K;

void test_case(int tc) {
	cin >> N >> K;
	vector<ll> a(N);
	for (int i = 0; i < N; i++) {
		cin >> a[i];
	}
	sort(a.begin(), a.end());
	ll best1 = 0;
	vector<ll> best2;
	best2.push_back(a[0] - 1);
	best2.push_back(K - a.back());
	for (int i = 0; i < N-1; i++) {
		best1 = max(best1, a[i+1]-a[i]-1);
		best2.push_back((ll)((a[i + 1] - a[i]) / 2));
	}
	sort(best2.begin(), best2.end());
	ll ans = max(best2[N] + best2[N-1], best1);
	double rst = (ans) / ((double)K);
	cout << "Case #" << tc + 1 << ": " << rst << endl;
}

int main() {
	freopen("sample_input.txt", "r", stdin);

	cin >> test_num;
	for (int tc = 0; tc < test_num; tc++) {
		test_case(tc);
	}
	return 0;
}



