#include <bits/stdc++.h>
using namespace std;


typedef long long LL;
const int INF = 0x3f3f3f3f;
const LL  LNF = 0x3f3f3f3f3f3f3f3fLL;
const int MAXN = 200000 + 10;


int N, pos, lft, rht;


int leftThenRight(int N, int pos, int lft, int rht) {
    int steps = 0;
    if( lft > 1 ) steps += abs(lft-pos) + 1, pos = lft;
    if( rht < N ) steps += abs(rht-pos) + 1;
    return steps;
}


int rightThenLeft(int N, int pos, int lft, int rht) {
    int steps = 0;
    if( rht < N ) steps += abs(rht-pos) + 1, pos = rht;
    if( lft > 1 ) steps += abs(lft-pos) + 1;
    return steps;
}


int main() {
    scanf("%d%d%d%d", &N, &pos, &lft, &rht);

    int ans = min(leftThenRight(N, pos, lft, rht), rightThenLeft(N, pos, lft, rht));
    printf("%d\n", ans);


    return 0;
}

