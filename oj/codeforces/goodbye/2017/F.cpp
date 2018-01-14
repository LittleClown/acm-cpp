#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;

typedef long long LL;
const int INF = 1e9+10;
const LL  LNF = 0x3f3f3f3f3f3f3f3fLL;


const int MAXN = 300000 + 10;
int N, P[MAXN], R[MAXN], G[MAXN], B[MAXN], rev_idx[MAXN], r, g, b;
char color[10], colors[MAXN];


inline int connectBetweenTwoG(int x, int y) {
    int d = P[y] - P[x];
    if( x+1 == y ) return d;

    int lR = -1,
        rR = -1,
        lB = -1,
        rB = -1;

    for(int i=x+1; i < y; ++i) {
        switch( colors[i] ) {
            case 'R': if( lR > 0 ) rR = rev_idx[i]; else lR = rev_idx[i]; break;
            case 'B': if( lB > 0 ) rB = rev_idx[i]; else lB = rev_idx[i]; break;
        }
    }

    int dR = 0, dB = 0;
    rR = max(lR, rR);
    rB = max(lB, rB);

    if( lR > 0 ) {
        int mxr = max(P[R[lR]]-P[x], P[y]-P[R[rR]]);
        for(int i=lR+1; i <= rR; ++i) mxr = max(mxr, P[R[i]]-P[R[i-1]]);
        dR = d - mxr;
    }
    if( lB > 0 ) {
        int mxb = max(P[B[lB]]-P[x], P[y]-P[B[rB]]);
        for(int i=lB+1; i <= rB; ++i) mxb = max(mxb, P[B[i]]-P[B[i-1]]);
        dB = d - mxb;
    }

    int ans = d + dR + dB;
    if( lR > 0 && lB > 0 ) ans = min(ans, 2*d);
    return ans;
}

inline int connectLeftG(int x) {
    int lR = -1, lB = -1;
    for(int i=x-1; i > 0; --i) {
        switch( colors[i] ) {
            case 'R': lR = i; break;
            case 'B': lB = i; break;
        }
    }

    int ans = 0;
    if( lR > 0 ) ans += P[x] - P[lR];
    if( lB > 0 ) ans += P[x] - P[lB];
    return ans;
}

inline int connectRightG(int y) {
    int rR = -1, rB = -1;
    for(int i=y+1; i <= N; ++i) {
        switch( colors[i] ) {
            case 'R': rR = i; break;
            case 'B': rB = i; break;
        }
    }

    int ans = 0;
    if( rR > 0 ) ans += P[rR] - P[y];
    if( rB > 0 ) ans += P[rB] - P[y];
    return ans;
}


int main() {
    ios::sync_with_stdio(false);
    cin >> N;
    for(int i=1; i <= N; ++i) {
        cin >> P[i] >> color;
        colors[i] = color[0];
        switch( colors[i] ) {
            case 'R': R[++r] = i; rev_idx[i] = r; break;
            case 'G': G[++g] = i; rev_idx[i] = g; break;
            case 'B': B[++b] = i; rev_idx[i] = b; break;
        }
    }

    LL ans = 0;
    if( g == 0 ) {
        if( r > 1 ) ans += P[R[r]] - P[R[1]];
        if( b > 1 ) ans += P[B[b]] - P[B[1]];
    } else {
        ans += connectLeftG(G[1]);
        for(int i=2; i <= g; ++i) ans += connectBetweenTwoG(G[i-1], G[i]);
        ans += connectRightG(G[g]);
    }

    cout << ans << endl;
    return 0;
}
