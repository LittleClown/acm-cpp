#include <bits/stdc++.h>
using namespace std;


typedef long long LL;
const int INF = 0x3f3f3f3f;
const LL  LNF = 0x3f3f3f3f3f3f3f3fLL;
const int MAXN = 200000 + 10;


int cnt[10], bx[20], ax[20], bt, at;
LL a, b;


bool DFS(int t, bool flag) {
    if( t <= 0 ) return true;
    if( flag ) {
        for(int a=bx[t]; a >= 0; --a) {
            if( cnt[a] <= 0 ) continue;
            ax[t] = a;
            --cnt[a];
            if( DFS(t-1, a==bx[t]) ) return true;
            ++cnt[a];
        }
    } else {
        for(int a=9; a >= 0; --a) {
            if( cnt[a] <= 0 ) continue;
            ax[t] = a;
            --cnt[a];
            if( DFS(t-1, false) ) return true;
            ++cnt[a];
        }
    }
    return false;
}

int main() {
    cin >> a >> b;
    for(; a > 0; a/=10) ++cnt[a%10], ++at;
    for(; b > 0; b/=10) bx[++bt] = b%10;

    if( at < bt ) {
        for(int i=9; i >= 0; --i)
            while( cnt[i]-- ) putchar(i+'0');
        return 0;
    }

    if( at > bt ) return -1;

    DFS(bt, true);
    for(int i=at; i > 0; --i) putchar(ax[i]+'0');

    return 0;
}

