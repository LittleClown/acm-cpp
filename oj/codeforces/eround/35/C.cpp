#include <bits/stdc++.h>
using namespace std;


typedef long long LL;
const int INF = 0x3f3f3f3f;
const LL  LNF = 0x3f3f3f3f3f3f3f3fLL;


int x, y, z;


inline void _swap(int& x, int& y) { int t = x; x = y; y = t; }

inline bool solve() {
    if( x > y ) _swap(x, y);
    if( x > z ) _swap(x, z);
    if( y > z ) _swap(y, z);

    if( x == 1 ) return true;
    if( x == 2 ) {
        if( y == 2 ) return true;
        if( y == 4 && z == 4 ) return true;
    }
    if( x == 3 ) {
        return y == 3 && z == 3;
    }
    return false;
}


int main() {
    scanf("%d%d%d", &x, &y, &z);

    if( solve() ) printf("YES\n");
    else printf("NO\n");


    return 0;
}

