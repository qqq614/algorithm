//question : https://codingcompetitions.withgoogle.com/codejam/round/000000000043580a/00000000006d1284
#include <iostream>
#include<algorithm>
#define MAX_N 55
using namespace std;

int temp[MAX_N];
int arr[MAX_N];
int arr_sz;
int T, N, Q;
int val;
int correct;
int judge;
int pseudo_arr[55];
bool check_ans(){
    bool first_rst=true, second_rst=true;
    for(int i=0;i<N;i++){
        if(arr[i]!=pseudo_arr[i]){
            first_rst=false;
            break;
        }
    }
    for(int i=0;i<N;i++){
        if(arr[N-1-i]!=pseudo_arr[i]){
            second_rst=false;
            break;
        }
    }
    return first_rst||second_rst;
}
void pseudo_gen(){
    arr_sz=0;
    for(int i=0;i<N;i++){
        pseudo_arr[arr_sz++]=i;
    }
    random_shuffle(pseudo_arr,pseudo_arr+N);
}

int pseudo_ask(int first, int second, int third){
    
    int ans_arr[3];
    int ans_cnt=0;
    for(int i=0;i<N;i++){
        if(pseudo_arr[i]==first||pseudo_arr[i]==second||pseudo_arr[i]==third){
            ans_arr[ans_cnt++]=pseudo_arr[i];
        }
    }
    return ans_arr[1];
}


struct Node{
    int pos;
    int num;
    Node(int pos1, int num1){
        pos=pos1;
        num=num1;
    }
};

pair<Node,Node> calculate(int left, int right){
    int mid1_pos=int((right-left)/3+left);
    int mid2_pos=int(2*(right-left)/3+left);
    return pair<Node,Node>(Node(mid1_pos,arr[mid1_pos]), Node(mid2_pos,arr[mid2_pos]));
};


int ask(int first, int second, int third){
    cout<<first+1<<" "<<second+1<<" "<<third+1<<endl;
    cout<<flush;
    cin>>val;
    return val-1;
}
void move(int num, int pos){
    for(int i=arr_sz-1;i>=pos;i--){
        arr[i+1]=arr[i];
    }
    arr[pos]=num;
    arr_sz++;
}
bool solve(){
    arr_sz=3;
    val=ask(0,1,2);//0 1 2
    arr[1]=val;
    int idx=0;
    for(int i=0;i<3;i++){
        if(i!=val){
            arr[idx]=i;
            idx+=2;
        }
    }
    for(int i=3;i<N;i++){
        int left=0;
        int right=arr_sz-1;
        int loop_cnt=0;
        while(loop_cnt<=2*N){
            //base
            if(right==left){
                move(i,right);//right자리에 i넣고 나머지 우측으로 한칸 이동
                break;
            }
            if(right==left+1){
                if(right==arr_sz-1){
                    val=ask(arr[left],arr[right],i);
                    if(val==i){
                        move(i, right);
                    }else{
                        move(i, right+1);
                    }
                }else if(left==0){
                    val=ask(arr[left],arr[right],i);
                    if(val==i){
                        move(i, right);
                    }else{
                        move(i, left);
                    }
                }else{
                    move(i, right);
                }
                break;
            }
            pair<Node, Node> mid=calculate(left, right);
            val=ask(mid.first.num,mid.second.num,i);
            if(val==mid.first.num){
                right=mid.first.pos;
            }else if(val==mid.second.num){
                left=mid.second.pos;
            }else{
                left=mid.first.pos;
                right=mid.second.pos;
            }
            loop_cnt++;
        }
    }
    for(int i=0;i<N;i++){
        cout<<arr[i]+1<<" ";
    }
    cin>>judge;
    return judge;
    // if(check_ans()){
    //     correct++;
    // }
}

int main()
{
    cin>>T>>N>>Q;
    // T=100;
    // N=50;  
    // Q=5000;
    // correct=0;
    for(int tc=0;tc<T;tc++){
        // pseudo_gen();
        bool correct=solve();
        if(correct!=1){
            exit(0);
        }
    }
    // cout<<"TC : "<<T<<", correct : "<<correct<<endl;
    return 0;

}


#include <bits/stdc++.h>
using namespace std;

int N, Q;

int ask(int a, int b, int c){
	cout << (a+1) << ' ' << (b+1) << ' ' << (c+1) << '\n';
	cout << flush;
	int res;
	cin >> res;
	if(res == -1) exit(0);
	return (res-1);
}

void solve(){
	vector<int> ord = {0, 1};
	for(int j = 2; j < N; j++){
		int s = 0;
		int e = (int)ord.size()+1;
		while(s + 1 < e){
			int m1 = (s + s + e) / 3;
			int m2 = (s + e + e) / 3;
			if(m1 == 0) m1++;
			while(m2 <= m1) m2++;
			if(m2 == (int)ord.size()+1) m2--;
			while(m1 >= m2) m1--;
			int res = ask(j, ord[m1-1], ord[m2-1]);
			if(res == j){
				s = max(s, m1);
				e = min(e, m2);
			} else if(res == ord[m1-1]){
				e = min(e, m1);
			} else if(res == ord[m2-1]){
				s = max(s, m2);
			}
		}
		ord.insert(ord.begin() + s, j);
	}
	for(int i = 0; i < N; i++){
		cout << (ord[i]+1) << " \n"[i == (N-1)];
	}
	cout << flush;
	int verdict;
	cin >> verdict;
	if(verdict == -1) exit(0);
}

int main(){
	ios_base::sync_with_stdio(false), cin.tie(nullptr);
	int T;
	cin >> T >> N >> Q;
	while(T--) solve();
}