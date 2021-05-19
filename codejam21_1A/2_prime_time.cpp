//question : https://codingcompetitions.withgoogle.com/codejam/round/000000000043585d/00000000007543d8
// not finished fail on first test case
#define _CRT_SECURE_NO_DEPRECATE
#include<iostream>
#include<algorithm>
#include<math.h>
#include<vector>
#include<string>

#define MAX_P 499
#define ll long long

using namespace std;
int M;
ll max_val;

ll N_i[MAX_P+10];
vector<ll> primes;
vector<ll> P_i;

ll max(ll a, ll b) {
    if (a > b) {
        return a;
    }
    else {
        return b;
    }
}


void fill_primes() {
    for (int i = 2; i <= MAX_P; i++) {
        bool is_prime = true;
        for (int j = 2; j <= sqrt(i); j++) {
            if (i % j == 0) {
                is_prime = false;
                break;
            }
        }
        if (is_prime) {
            primes.push_back(i);
        }
    }
}
void factorize(ll num, ll* factorized) {
    
    for (int i = 0; i < primes.size(); i++) {
        while (true) {
            if (num % primes[i] != 0) {
                break;
            }
            num /= primes[i];
            factorized[primes[i]]++;
        }
    }
}

bool checksum(ll expected, ll* factorized) {
    ll sum = 0;
    for (int i = 0; i < primes.size(); i++) {
        if (factorized[primes[i]] > N_i[primes[i]]) {
            return false;
        }
        sum += primes[i] * factorized[primes[i]];
    }
    return sum == expected;
}


void test_case(int tc) {
    cin >> M;

    //initialize 
    P_i.clear();
    for (int i = 0; i < MAX_P + 1; i++) {
        N_i[i] = 0;
    }
    max_val = 0;
    for (int i = 0; i < M; i++) {
        ll p_i;
        ll n_i;
        cin >> p_i >> n_i;
        P_i.push_back(p_i);
        N_i[p_i] = n_i;
    }
    ll total_sum = 0;
    for (int i = 0; i < P_i.size(); i++) {
        total_sum += P_i[i] * N_i[P_i[i]];
    }
    for (ll num = max(2, total_sum - 499 * 60); num <= total_sum; num++) {
        ll factorized[MAX_P + 10] = { 0 };
        factorize(num, factorized);
        // second group product value(num) + second group factorized_sum = total sum
        if (checksum(total_sum - num, factorized)) {
            max_val = num;
        }
    }


    cout << "Case #" << tc + 1 << ": " << max_val << endl;
}

    
int main() {
    fill_primes();
    freopen("sample_input.txt", "r", stdin);
    int T;
    cin >> T;
    for (int tc = 0; tc < T; tc++) {
        test_case(tc);
    }
    return 0;
}
