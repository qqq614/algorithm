//question : https://codingcompetitions.withgoogle.com/codejam/round/000000000043585d/00000000007543d8

#define _CRT_SECURE_NO_DEPRECATE
#include<iostream>
#include<algorithm>
#include<vector>
#include<string>

#define MAX_P 499
#define LIMIT 50000
#define ll long long

using namespace std;
int M;
ll max_val;

vector<int> P_i;
vector<ll> N_i;
vector<ll> taken;

bool check(ll product) {
    ll sum = 0;
    for (ll i = 0; i < N_i.size(); i++) {
        sum += P_i[i] * (N_i[i] - taken[i]);
    }
    if (sum == product) {
        return true;
    }
    else {
        return false;
    }
}
ll myPow(int x, unsigned int p)
{
    if (p == 0) return 1;
    if (p == 1) return x;

    ll tmp = myPow(x, p / 2);
    if (p % 2 == 0) return tmp * tmp;
    else return x * tmp * tmp;
}

void dfs(int idx, ll product) {
    if (idx == M) {
        if (check(product)&&product>max_val) {
            max_val = product;
        }
        return;
    }
    for (int num = 0; num <= N_i[idx]; num++) {
        int next_product = product * myPow(P_i[idx], num);
        if (next_product > LIMIT) {
            break;
        }
        taken.push_back(num);
        dfs(idx + 1, next_product);
        taken.pop_back();
    }
    return;
}



void test_case(int tc) {
    //initialize
    max_val = 0;
    P_i.clear();
    N_i.clear();
    taken.clear();

    cin >> M;
    for (int i = 0; i < M; i++) {
        int p_i;
        ll n_i;
        cin >> p_i >> n_i;
        P_i.push_back(p_i);
        N_i.push_back(n_i);
    }
    dfs(0, 1);

    cout << "Case #" << tc + 1 << ": " << max_val<< endl;
}


int main() {
    freopen("sample_input.txt", "r", stdin);
    int T;
    cin >> T;
    for (int tc = 0; tc < T; tc++) {
        test_case(tc);
    }
    return 0;
}