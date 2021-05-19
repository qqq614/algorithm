//https://codingcompetitions.withgoogle.com/codejam/round/0000000000435baf/00000000007ae694#problem
// test set 2 failed. 
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
struct AB {
    ll a;
    ll b;
    AB(ll a_, ll b_) {
        a = a_;
        b = b_;
    }
};
vector<ll> checksum;
vector<AB> sets;
void pushback(ll diff, ll diff2) {
    sets.push_back(AB(diff, diff2));
    if (diff < 0) {
        sets.push_back(AB(diff + DEG360, diff2));
    }
    if (diff2 < 0) {
        sets.push_back(AB(diff, diff2+DEG360));
    }
}

bool solved;
struct Time{
    ll hour;
    ll min;
    ll sec;
    ll nano;
    Time(ll hr, ll m, ll s, ll n) {
        hour = hr;
        min = m;
        sec = s;
        nano = n;
    };
};

Time convert_tick_to_time(ll tick) {
    tick %= (43200 * BIL);
    ll hour = tick / ((3600) * BIL);
    tick %= ((3600) * BIL);
    ll min = tick / ((60) * BIL);
    tick %= ((60) * BIL);
    ll sec = tick / BIL;
    ll nano = tick % BIL;
    return Time(hour, min, sec, nano);
}

 

bool reverse_check(ll tick) {
    Time time = convert_tick_to_time(tick);
    ll a_h = (3600 * BIL * time.hour) + (60 * BIL * time.min) + time.sec * BIL + time.nano;
    ll a_m = 12*((60 * BIL * time.min) + time.sec * BIL + time.nano);
    ll a_s = 720*(time.sec * BIL + time.nano);
    ll a = a_h - a_m;
    ll b = a_h - a_s;
    ll min_ = min(a_h, min(a_m, a_s));
    vector<ll> temp = { a_h - min_, a_m - min_, a_s - min_ };
    sort(temp.begin(), temp.end());
    for (int i = 0; i < temp.size(); i++) {
        if (temp[i] != checksum[i]) {
            return false;
        }
    }
    return true;
}

void test_case(int tc) {
    //initialize
    sets.clear();
    checksum.clear();
    cin >> A >> B >> C;
    ll min_ = min(A, min(B, C));
    checksum.push_back(A - min_);
    checksum.push_back(B - min_);
    checksum.push_back(C - min_);
    sort(checksum.begin(), checksum.end());
    solved = false;
    pushback(B - A, C - A);
    pushback(C - A, B - A);
    pushback(A - B, C - B);
    pushback(C - B, A - B);
    pushback(A - C, B - C);
    pushback(B - C, A - C);
    ll t=0;
    for (int i = 0; i < sets.size(); i++) {
        ll a = sets[i].a; 
        ll b = sets[i].b;
        for (ll h = 0; h < 12; h++) {
            for (ll m = 0; m < 60; m++) {
                ll temp_t=h* DEG360 + a;
                ll temp_t2 = (60 * h + m) * DEG360 + b;
                if (temp_t % 11 != 0 || temp_t2 % 719 !=0) continue;
                temp_t /= 11;
                temp_t2 /= 719;
                if (temp_t != temp_t2 || (temp_t + a) < 0 || (temp_t + a) > DEG360) continue;
                if (!reverse_check(temp_t)) continue;
                solved = true;
                t = temp_t; 
                //break;
            }
            //if (solved) break;
        }
        //if (solved) break;
    }
    Time solution = convert_tick_to_time(t);

    cout << "Case #" << tc + 1 << ": " << solution.hour << " " << solution.min << " " << solution.sec << " " << solution.nano << endl;
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
