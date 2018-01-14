#include <bits/stdc++.h>
using namespace std;


typedef long long LL;
const int INF = 0x3f3f3f3f;
const LL  LNF = 0x3f3f3f3f3f3f3f3fLL;


const int MAXN = 200 + 10;
int N, A, B;

int main() {
    scanf("%d%d%d", &N, &A, &B);
    int x = 0;
    for(; ; ++x) {
        bool flag = false;
        for(int a=1; a < N; ++a) {
            if( a*x <= A && (N-a)*x <= B ) {
                flag = true;
                break;
            }
        }
        if( !flag ) break;
    }

    printf("%d\n", x-1);

    return 0;
}

