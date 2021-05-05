//question : https://codingcompetitions.withgoogle.com/codejam/round/000000000043580a/00000000006d1155
#include<iostream>
#include<math.h>
#include<vector>
#include<fstream>
using namespace std;

int N=100;
int Q=10000;
double sigmoid(double x){
    return 1.0 / (1.0 + exp(-x));
}
double sigmoid_inverse(double x){
    return log(x/(1.0-x));
}

string raw_input[101];

int main(){
    freopen("./codejam2021_qual_round_5_cheating_detection/sample_input.txt", "r",stdin);
    int T, P;
    cin>>T>>P;
    for(int tc=0;tc<T;tc++){
        // vector<string> raw_input(N);
        for(int i=0;i<N;i++){
            cin>>raw_input[i];
        }
        // for(int i=0;i<N;i++)
        //     cout<<raw_input[i].size()<<endl;
        vector<double> pskills(N,0.0);
        vector<double> pdiff(Q,0.0);
        for(int i=0;i<N;i++){
            for(int j=0;j<Q;j++){
                int correct=int(raw_input[i][j]=='1');
                pskills[i]+=correct;
                pdiff[j]+=1-correct;
            }
        }
        for(int i=0;i<N;i++){
            pskills[i]=sigmoid_inverse(pskills[i]/(double)Q);
        }
        for(int i=0;i<Q;i++){
            pdiff[i]=sigmoid_inverse(pdiff[i]/(double)N);
        }
        vector<double> suspiciousness(N, 0.0);
        for(int i=0;i<N;i++){
            for(int j=0;j<Q;j++){
                double diff=pskills[i]-pdiff[j];
                if(sigmoid(diff)>0.75&&raw_input[i][j]=='0'){
                    suspiciousness[i]+=diff;
                }
            }
        }
        double max=0;
        int cheater_idx=-1;
        for(int i=0;i<N;i++){
            if(suspiciousness[i]>max){
                cheater_idx=i;
            }
        }

        cout << "Case #" << tc+1 << ": " << cheater_idx+1 << endl;


    }
    return 0;
}