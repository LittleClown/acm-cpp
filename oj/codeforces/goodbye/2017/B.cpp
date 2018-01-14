#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

typedef long long LL;
const int INF = 0x3f3f3f3f;
const LL  LNF = 0x3f3f3f3f3f3f3f3fLL;


int N, M, L, ord[200];
char maze[100][100];
char str[200];


int sx, sy;
const int nx[] = { -1, 0, 1, 0 };
const int ny[] = { 0, 1, 0, -1 };
int* od;

int xod[][4] = {
        { 0, 1, 2, 3 },
        { 0, 1, 3, 2 },
        { 0, 2, 1, 3 },
        { 0, 2, 3, 1 },
        { 0, 3, 1, 2 },
        { 0, 3, 2, 1 },
        { 1, 0, 2, 3 },
        { 1, 0, 3, 2 },
        { 1, 2, 0, 3 },
        { 1, 2, 3, 0 },
        { 1, 3, 0, 2 },
        { 1, 3, 2, 0 },
        { 2, 0, 1, 3 },
        { 2, 0, 3, 1 },
        { 2, 1, 0, 3 },
        { 2, 1, 3, 0 },
        { 2, 3, 0, 1 },
        { 2, 3, 1, 0 },
        { 3, 0, 1, 2 },
        { 3, 0, 2, 1 },
        { 3, 1, 0, 2 },
        { 3, 1, 2, 0 },
        { 3, 2, 0, 1 },
        { 3, 2, 1, 0 },
};


bool check() {
    int u = sx, v = sy;
    for(int i=0; i < L; ++i) {
        u += nx[od[ord[i]]];
        v += ny[od[ord[i]]];
        if( maze[u][v] == '#' ) return false;
        if( maze[u][v] == 'E' ) return true;
    }
    return false;
}



int main() {
    scanf("%d%d", &N, &M);
    for(int i=1; i <= N; ++i) {
        scanf("%s", str+1);
        for(int j=1; j <= M; ++j)
            maze[i][j] = str[j];
    }
    for(int i=1; i <= N; ++i) maze[i][0] = maze[i][M+1] = '#';
    for(int i=1; i <= M; ++i) maze[0][i] = maze[N+1][i] = '#';

    for(int i=1; i <= M; ++i)
        for(int j=1; j <= N; ++j)
            if( maze[i][j] == 'S' ) sx = i, sy = j;

    scanf("%s", str);
    L = strlen(str);
    for(int i=0; i < L; ++i) ord[i] = str[i] - '0';


    int ans = 0;
    for(int i=0; i < 24; ++i) {
        od = xod[i];
        if( check() ) ++ans;
    }

    printf("%d\n", ans);
    return 0;
}