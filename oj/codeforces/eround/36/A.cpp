#include <bits/stdc++.h>
using namespace std;


typedef long long LL;
const int INF = 0x3f3f3f3f;
const LL  LNF = 0x3f3f3f3f3f3f3f3fLL;
const int MAXN = 100 + 10;


int N, K, A[MAXN];
int main() {
    scanf("%d%d", &N, &K);
    for(int i=1; i <= N; ++i) scanf("%d", A+i);

    sort(A+1, A+N+1);
    for(int i=N; i >= 1; --i) {
        if( K%A[i] == 0 ) {
            printf("%d\n", K/A[i]);
            break;
        }
    }

    return 0;
}

