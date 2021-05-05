//question : https://codingcompetitions.withgoogle.com/codejam/round/00000000004362d7/00000000007c0f01
#define _CRT_SECURE_NO_DEPRECATE
#define ll unsigned long long
#define MAX_DIGITS 19
#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<assert.h>

using namespace std;

int test_num;
//vector<int> MAX = { 1,2,3,4,5,6,7,8,9,1,0,1,1,1,2,1,3,1,4 };
ll MAX_LL = 1234567891011121314;

vector<ll> candidates2;


int find_digits(ll num) {
	int rst = 0;
	while (num) {
		num /= 10;
		rst++;
	}
	return rst;
}

ll concat(ll& num, const ll& num2add, int add_digits) {
	ll ans = num;
	while (add_digits--) {
		ans *= 10;
	}
	ans += num2add;
	return ans;
}


void fill_candidates2() {
	candidates2.clear();
	for (ll i = 1; i < 999999; i++) {
		ll candidate = i;
		int add = 1;
		int digits = find_digits(i);
		while (true) {
			ll addition = i+add++;
			int add_digits = find_digits(addition);
			digits += add_digits;
			if (digits > MAX_DIGITS) {
				break;
			}
			candidate=concat(candidate, addition, add_digits);
			if (candidate > MAX_LL) {
				break;
			}
			candidates2.push_back(candidate);
		}
	}
	sort(candidates2.begin(), candidates2.end());
}




ll find_minimum_binary_3comps(ll input) {
	int lo = -1;
	int hi = candidates2.size()-1;
	//assure that input<candidates[hi]
	while (lo + 1 < hi) {
		int mid = int((lo + hi) / 2);
		if (candidates2[mid]>input) {
			hi = mid;
		}
		else {
			lo = mid;
		}
	}
	return candidates2[hi];
}


ll find_minimum_binary(ll& input) {
	ll lo = 1;
	ll hi = 999999999;
	while (lo + 1 < hi) {
		ll mid = (ll)((lo + hi) / 2);
		ll f_mid = concat(mid, mid + 1, find_digits(mid + 1));
		if (f_mid>input) {//mid>input
			hi = mid;
		}
		else {
			lo = mid;
		}
	}
	ll rst = concat(hi, hi + 1, find_digits(hi + 1));
	return rst;
}

void test_case(int tc) {
	ll y;
	cin >> y;

	// 1. 3 parts(at most 6 digits) minimum
	ll min1 = find_minimum_binary_3comps(y);
	// 2. 2 parts minimum (binary search)
	ll min2 = find_minimum_binary(y);
	ll ans = min(min1, min2);
	cout << "Case #" << tc + 1 << ": " << ans << endl;
	
}

int main() {
	fill_candidates2();
	freopen("sample_input.txt", "r", stdin);
	cin >> test_num;
	for (int tc = 0; tc < test_num; tc++) {
		test_case(tc);
	}
}