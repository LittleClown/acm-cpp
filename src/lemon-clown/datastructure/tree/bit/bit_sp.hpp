#include <cstring>


/**
 * BIT_SP   单点更新的树状数组
 * @tparam T
 */
template<class T> class BIT_SP {
public:
    static int lowbit(int x) { return x&-x; }

    explicit BIT_SP(int maxn) {
        this->maxn = maxn + 1;
        this->sumv = new T[this->maxn];
    }

    void init(int n) {
        this->n = n+1;
        memset(sumv, 0, sizeof(int)*this->n);
    }

    void add(int x, T v) {
        for(; x <= n; x+=lowbit(x)) sumv[x] += v;
    }

    T sum(int x) {
        T ans = 0;
        for(; x > 0; x-=lowbit(x)) ans += sumv[x];
        return ans;
    }

    T sum(int x, int y) {
        if( x > y ) return 0;
        return sum(y) - sum(x-1);
    }
protected:
    int maxn, n;
    T* sumv;
};