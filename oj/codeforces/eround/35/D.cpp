#include <bits/stdc++.h>
using namespace std;


typedef long long LL;
const int INF = 0x3f3f3f3f;
const LL  LNF = 0x3f3f3f3f3f3f3f3fLL;


const int MAXN = 1500 + 10;
int A[MAXN], N, M, u, v, ans;

const char ans_map[][10] = { "even", "odd" };

int main() {
    scanf("%d", &N);
    for(int i=1; i <= N; ++i) scanf("%d", A+i);

    ans = 0;
    for(int i=1; i <= N; ++i)
        for(int j=i+1; j <= N; ++j)
            if( A[i] > A[j] ) ans ^= 1;

    scanf("%d", &M);
    for(int kase=1; kase <= M; ++kase) {
        scanf("%d%d", &u, &v);
        int n = v - u + 1;
        ans ^= ((n*(n-1)) >> 1) & 1;
        printf("%s\n", ans_map[ans]);
    }

    return 0;
}

