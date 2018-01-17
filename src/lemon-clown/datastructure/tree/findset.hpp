#include <cassert>
#include <cstring>
#include <algorithm>


/**
 * 并查集
 */
class FindSet {
    typedef int* pInt;
public:
    explicit FindSet(int maxn) {
        this->maxn = maxn+1;
        this->current_size = sizeof(int) * (this->maxn);
        this->f = new int[this->maxn];
        this->cnt = new int[this->maxn];
    }

public:
    void init(int n) {
        assert(maxn > n);
        this->current_size = sizeof(int) * (n+1);
        memset(f, 0, current_size);
        for(int i=1; i <= n; ++i) cnt[i] = 1;
    }


    /**
     * 获取 x 的根节点
     * @param x
     * @return
     */
    int getRoot(int x) {
        return f[x]? f[x]=getRoot(f[x]): x;
    }

    /**
     * 合并两棵树
     * @param x
     * @param y
     */
    void merge(int x, int y) {
        x = getRoot(x);
        y = getRoot(y);
        if( x == y ) return;
        if( cnt[x] > cnt[y] ) std::swap(x, y);
        f[x] = y;
        cnt[y] += cnt[x];
    }


    /**
     * 添加新节点
     * @param x
     */
    void addNode(int x) {
        assert(maxn > x);
        f[x] = 0;
        cnt[x] = 1;
    }
protected:
    int maxn;
    size_t current_size;

public:
    pInt f, cnt;
};
