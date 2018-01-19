#include <cstdio>
#include <cstring>
#include <lemon-clown/datastructure/tree/bit/bit_sp.hpp>


const int MAXN = 5e4 + 10;


int T_T, N, u, v;
char cmd[10];
BIT_SP<int> bit(MAXN);


int main() {
    scanf("%d", &T_T);
    for(int kase=1; kase <= T_T; ++kase) {
        scanf("%d", &N);
        bit.init(N);

        for(int i=1; i <= N; ++i) {
            scanf("%d", &u);
            bit.add(i, u);
        }

        printf("Case %d:\n", kase);
        while( true ){
            scanf("%s", cmd);
            if( cmd[0] == 'E' ) break;
            scanf("%d%d", &u, &v);
            switch( cmd[0] ) {
                case 'Q': printf("%d\n", bit.sum(u, v)); break;
                case 'A': bit.add(u, v); break;
                case 'S': bit.add(u, -v); break;
            }
        }
    }

    return 0;
}
