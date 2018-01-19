#include <queue>
#include <vector>
#include <cassert>
#include <cstring>
#include <algorithm>


/**
 * 最小费用最大流算法 MCMF
 *
 * 构造函数：
 *   * `MCMF(int maxn)`:
 *     >  maxn 表示最大节点个数
 *     > 使用这个构造函数，则每次计算最大流时，需要先调用  init(int source, int converge, int n) 的方法初始化
 *     > 这么设计的原因是可以重复利用 MCMF 实例的变量，对于每次最大流计算
 *   * `MCMF(int source, int converge, int n)`:
 *     > source 表示源点
 *     > converge 表示汇点
 *     > n 表示网络流中的节点总数
 *     > 使用这个构造函数，则在第一次使用时，不需要调用 init 初始化，但以后要是想重复使用的话，就需要调用 init 初始化
 *
 * 对外函数：
 *   * `addEdge(int from, int to, int cap, int cost)`:`void`: 加边
 *   * `init(int source, int converge, int n)`:`void`: 初始化网络流变量
 *   * `mincostMaxflow()`:`int`: 返回最大流
 *   * `mincut()`:`vector<pair<int, int>>`: 返回最小割（不需要先执行 maxflow()）
 * 对外成员（请在跑完最大流时再使用）：
 *   * `edges`:`vector<Edge>`: 图中的边集
 *   * `G`: `vector<int>*`: 图中的邻接表
 *   * `dist`: `int*`: 满流后，到源点的步长
 */
class MCMF {
    typedef int* pInt;
public:
    explicit MCMF(int maxn) {
        this->s = this->t = this->n = -1;
        this->maxn = maxn;
        this->current_size = sizeof(int) * maxn;
        this->inq = new int[maxn];
        this->dist = new int[maxn];
        this->path = new int[maxn];
        this->G = new std::vector<int>[maxn];
        done = false;
        memset(this->inq, 0, current_size);
    }

public:
    static const int INF = 0x3f3f3f3f;

    struct Edge {
        int from, to, cap, flow, cost;
        explicit Edge(int from=0, int to=0, int cap=0, int flow=0, int cost=0):
                from(from), to(to), cap(cap), flow(flow), cost(cost) {}
    };


    /**
     * 加边（会加反向弧）
     * @param from      起始点
     * @param to        目的地
     * @param cap       边容量
     */
    void addEdge(int from, int to, int cap, int cost) {
        int size = edges.size();
        edges.emplace_back(from, to, cap, 0, cost);
        edges.emplace_back(to, from, 0, 0, -cost);
        G[from].emplace_back(size);
        G[to].emplace_back(size+1);
    }


    /**
     * 初始化
     * @param source    源点
     * @param converge  汇点
     * @param n         网络流中的节点个数
     */
    void init(int source, int converge, int n) {
        assert(maxn >= n);
        this->s = source;
        this->t = converge;
        this->n = n;
        this->current_size = sizeof(int) * n;
        for(int i=0; i < n; ++i) G[i].clear();
        edges.clear();
        done = false;
    }
protected:
    bool done;
    int n, s, t, maxn, mincost_cached, maxflow_cached;
    size_t current_size;
    std::queue<int> Q;
    pInt path, inq;

public:
    std::vector<Edge> edges;
    std::vector<int>* G;
    pInt dist;

protected:
    bool SPFA() {
        memset(dist, 0x3f, current_size);
        for(dist[s]=0, inq[s]=1, Q.push(s); !Q.empty();) {
            int o = Q.front(); Q.pop();
            for(int i: G[o]) {
                Edge& e = edges[i];
                if( e.cap > e.flow && dist[e.to] > dist[o]+e.cost ) {
                    dist[e.to] = dist[o] + e.cost;
                    path[e.to] = i;
                    if( inq[e.to] ) continue;
                    inq[e.to] = 1;
                    Q.push(e.to);
                }
            }
            inq[o] = 0;
        }
        return dist[t] < INF;
    }


public:
    /**
     * 最小费用最大流
     * @return
     */
    std::pair<int, int> mincostMaxflow() {
        if( done ) return std::make_pair(mincost_cached, maxflow_cached);

        mincost_cached = maxflow_cached = 0;
        while( SPFA() ) {
            int mif = INF;
            for(int o=t; o != s;) {
                Edge& e = edges[path[o]];
                mif = std::min(mif, e.cap-e.flow);
                o = e.from;
            }
            for(int o=t; o != s;) {
                int i = path[o];
                edges[i].flow += mif;
                edges[i^1].flow -= mif;
                o = edges[i].from;
            }
            maxflow_cached += mif;
            mincost_cached += mif * dist[t];
        }

        done = true;
        return std::make_pair(mincost_cached, maxflow_cached);
    }


    /**
     * 最小割
     * @return
     */
    std::vector<std::pair<int, int>> mincut() {
        if( !done ) mincostMaxflow();
        std::vector<std::pair<int, int>> cuts;
        for(Edge& e: edges) {
            if( e.cap > 0 && dist[e.from] < INF && dist[e.to] == INF )
                cuts.emplace_back(e.from, e.to);
        }
        return cuts;
    }
};