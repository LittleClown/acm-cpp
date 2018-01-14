#include <bits/stdc++.h>
using namespace std;


typedef long long LL;
const int INF = 0x3f3f3f3f;
const LL  LNF = 0x3f3f3f3f3f3f3f3fLL;

const int MAXN = 200000 + 10;
int N, A[MAXN];


int main() {
    scanf("%d", &N);
    for(int i=0; i < N; ++i) scanf("%d", A+i);

    int min_num = A[0], min_num_pos = 0, cnt = 1;
    for(int i=1; i < N; ++i) {
        if( A[i] == min_num ) ++cnt;
        else if( A[i] < min_num ) {
            min_num_pos = i;
            min_num = A[i];
            cnt = 1;
        }
    }
    if( cnt > 1 ) {
        int ans = N, last = min_num_pos;
        for(int i=last+1; i < N; ++i) {
            if( A[i] != min_num ) continue;
            ans = min(ans, i-last);
            last = i;
        }
        printf("%d\n", ans);
    } else {
        int second_min_num_pos = min_num_pos == 0? 1: 0;
        int second_min_num = A[second_min_num_pos];
        int ans = N;
        for(int i=second_min_num_pos+1; i < N; ++i) {
            if( i == min_num_pos ) continue;
            if( A[i] < second_min_num ) {
                second_min_num = A[i];
                ans = abs(min_num_pos-i);
            } else if( A[i] == second_min_num ) {
                ans = min(ans, abs(min_num_pos-i));
            }
        }
        printf("%d\n", ans);
    }



    return 0;
}

