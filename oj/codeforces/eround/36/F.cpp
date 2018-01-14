#include <bits/stdc++.h>
using namespace std;


typedef long long LL;
const int INF = 0x3f3f3f3f;
const LL  LNF = 0x3f3f3f3f3f3f3f3fLL;
const int MAXN = 1000000 + 10;

int N, A[MAXN], cnt[MAXN], ord[MAXN], f[MAXN];
vector<int> sons[MAXN];


inline int root(int x) { return f[x]? f[x]=root(f[x]): x; }
inline void merge(int u, int v) {
    int ru = root(u);
    int rv = root(v);
    if( ru == rv ) return;
    if( cnt[ru] > cnt[rv] ) {
        f[rv] = ru;
        cnt[ru] += cnt[rv];
    } else {
        f[ru] = rv;
        cnt[rv] += cnt[ru];
    }
}



LL merge(int o) {
    LL total = 0;
    int total_nodes = 1;
    cnt[o] = 1;
    for(int u: sons[o]) {
        u = root(u);
        if( cnt[u] > 0 ) {
            total += (LL) cnt[u] * total_nodes;
            total_nodes += cnt[u];
            merge(o, u);
        }
    }
    return total * (LL) A[o];
}


LL calc1() {
    LL ans = 0;
    memset(cnt, 0, sizeof cnt);
    memset(f, 0, sizeof f);
    for(int i=1; i <= N; ++i) {
        int o = ord[i];
        ans += merge(o);
    }
    return ans;
}


LL calc2() {
    LL ans = 0;
    memset(cnt, 0, sizeof cnt);
    memset(f, 0, sizeof f);
    for(int i=N; i > 0; --i) {
        int o = ord[i];
        ans += merge(o);
    }
    return ans;
}


inline int read() {
    int s = 0;
    char c = getchar();
    for(; c < '0' || c > '9'; c=getchar());
    for(; c >= '0' && c <='9'; c=getchar())
        s = s*10 + c-'0';
    return s;
}


int main() {
    N = read();
    for(int i=1; i <= N; ++i) A[i] = read();
    for(int i=1; i < N; ++i) {
        int u, v;
        scanf("%d%d", &u, &v);
        sons[u].push_back(v);
        sons[v].push_back(u);
    }

    for(int i=1; i <= N; ++i) ord[i] = i;
    sort(ord+1, ord+N+1, [](int a, int b) { return A[a] < A[b]; });
    LL total_max = calc1();
    LL total_min = calc2();

    cout << total_max - total_min << endl;
}

