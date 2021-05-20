//https://codingcompetitions.withgoogle.com/codejam/round/0000000000435baf/00000000007ae694#problem 
#define _CRT_SECURE_NO_DEPRECATE
#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
#include<math.h>
#define ll long long
#define BIL 1000000000LL
#define DEG360 43200000000000LL

using namespace std;


ll A, B, C;


bool solved;

vector<vector<ll>> sets;//a_h, a_m, a_s
vector<ll> set;
vector<ll> abc;
bool taken[3];

void make_sets() {
    if (set.size() == 3) {
        sets.push_back(set);
        return;
    }
    for (int i = 0; i < 3; i++) {
        if (!taken[i]) {
            taken[i] = true;
            set.push_back(abc[i]);
            make_sets();
            set.pop_back();
            taken[i] = false;
        }
    }
}

void test_case(int tc) {
    //initialize
    solved = false;
    sets.clear();
    set.clear();
    cin >> A >> B >> C;
    abc = { A,B,C };
    for (int i = 0; i < 3; i++) {
        taken[i] = false;
    }
    make_sets();

    ll t = 0;

    for (int i = 0; i < sets.size(); i++) {
        ll a_h = sets[i][0];
        ll a_m = sets[i][1];
        ll a_s = sets[i][2];
        ll mh_dff = a_m - a_h;
        //make diff clockwise positive from a_h to a_m
        if (mh_dff < 0) {
            mh_dff += DEG360;
        }
        //12*t-(t+mh_diff)=h*DEG360 => solve for t
        for (int h = 0; h < 12; h++) {
            ll temp_t = h * DEG360 + mh_dff;
            temp_t /= 11;
            ll test_a_h = temp_t;
            ll test_a_m = (12 * temp_t) % (DEG360);
            ll test_a_s = (720 * temp_t) % (DEG360);
            if (((a_h - a_m) - (test_a_h - test_a_m)) % (DEG360) != 0) continue;
            if (((a_h - a_s) - (test_a_h - test_a_s)) % (DEG360) != 0) continue;
            solved = true;
            t = temp_t;
            break;
        }
        if(solved) break;
    }
    t %= DEG360;
    ll hour = t / ((3600) * BIL);
    t %= ((3600) * BIL);
    ll min = t / ((60) * BIL);
    t %= ((60) * BIL);
    ll sec = t / BIL;
    ll nano = t % BIL;

    cout << "Case #" << tc + 1 << ": " << hour << " " << min << " " << sec << " " << nano << endl;
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
