// 并查集

#include <cstdio>
#include <lemon-clown/datastructure/tree/findset.hpp>

const int MAXN = 200000 + 10;


FindSet fs(MAXN);
int sum[MAXN], id[MAXN];


void merge(int u, int v) {
    u = fs.getRoot(u);
    v = fs.getRoot(v);
    if( u == v ) return;
    int w = sum[u] + sum[v];
    fs.merge(u, v);
    sum[fs.getRoot(u)] = w;
}


int main() {
    int N, M, op, u, v=-1, ru, rv=-1, w;

    while( scanf("%d%d", &N, &M) == 2 ) {
        fs.init(N);
        for(int i=1; i <= N; ++i) sum[i] = id[i] = i;

        int minId = N+1;
        for(int i=0; i < M; ++i) {
            scanf("%d%d", &op, &u);
            ru = fs.getRoot(id[u]);
            if( op != 3 ) {
                scanf("%d", &v);
                rv = fs.getRoot(id[v]);
            }

            switch( op ) {
                case 1: merge(ru, rv); break;
                case 2:
                    if( ru != rv ) {
                        sum[ru] -= u;
                        --fs.cnt[ru];
                        id[u] = minId++;
                        sum[id[u]] = u;
                        fs.addNode(id[u]);
                        merge(id[u], rv);
                    }
                    break;
                case 3:
                    printf("%d %d\n", fs.cnt[ru], sum[ru]);
                    break;
            }
        }
    }

    return 0;
}
