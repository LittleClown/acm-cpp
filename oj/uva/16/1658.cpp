#include <cstdio>
#include <lemon-clown/algorithm/netflow/mcmf.hpp>


const int MAXN = 2000 + 10;


int main() {
    int N, M;
    MCMF mcmf(MAXN);

    while( scanf("%d%d", &N, &M) == 2 ) {
        const int source = 1;
        const int converge = N+N;

        mcmf.init(source, converge, N+N+1);
        for(int i=2; i < N; ++i)
            mcmf.addEdge(i, i+N, 1, 0);
        mcmf.addEdge(1, 1+N, 2, 0);
        mcmf.addEdge(N, N+N, 2, 0);

        for(int i=0; i < M; ++i) {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            mcmf.addEdge(u+N, v, 1, w);
        }

        std::pair<int, int> ans = mcmf.mincostMaxflow();
        printf("%d\n", ans.first);
    }

    return 0;
}
