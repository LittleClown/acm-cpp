#include <cstdio>
using namespace std;


typedef long long LL;
const int INF = 0x3f3f3f3f;
const LL  LNF = 0x3f3f3f3f3f3f3f3fLL;


const int MAXN = 200000 + 10;
int N, K, T, A[MAXN], B[MAXN], tot;

int main() {
    T = 1;
    B[0] = -1000;

    scanf("%d%d", &N, &K);
    for(int i=1; i <= K; ++i) {
        scanf("%d", A+i);
        B[++tot] = A[i];
        while( B[tot] == T ) --tot, ++T;
    }

    bool flag = true;
    for(int i=1; i < tot; ++i) if( B[i] < B[i+1] ) flag = false;
    if( flag ) {
        int t = K;
        for(int i=tot; i > 0; --i) {
            for(int a = B[i]-1; a >= T; --a)
                A[++t] = a;
            T = B[i] + 1;
        }
        for(int a=N; a >= T; --a) A[++t] = a;

        bool first = true;
        for(int i=1; i <= N; ++i) {
            if( first ) first = false;
            else printf(" ");
            printf("%d", A[i]);
        }
        printf("\n");
    } else printf("-1\n");

    return 0;
}

