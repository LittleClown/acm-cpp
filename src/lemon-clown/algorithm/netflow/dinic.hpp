#include <queue>
#include <vector>
#include <cassert>
#include <cstring>
#include <algorithm>


/**
 * 最大流算法 Dinic
 *
 * 构造函数：
 *   * `Dinic(int maxn)`:
 *     >  maxn 表示最大节点个数
 *     > 使用这个构造函数，则每次计算最大流时，需要先调用  init(int source, int converge, int n) 的方法初始化
 *     > 这么设计的原因是可以重复利用 Dinic 实例的变量，对于每次最大流计算
 *   * `Dinic(int source, int converge, int n)`:
 *     > source 表示源点
 *     > converge 表示汇点
 *     > n 表示网络流中的节点总数
 *     > 使用这个构造函数，则在第一次使用时，不需要调用 init 初始化，但以后要是想重复使用的话，就需要调用 init 初始化
 *
 * 对外函数：
 *   * `addEdge(int from, int to, int cap)`:`void`: 加边
 *   * `init(int source, int converge, int n)`:`void`: 初始化网络流变量
 *   * `maxflow()`:`int`: 返回最大流
 *   * `mincut()`:`vector<pair<int, int>>`: 返回最小割（不需要先执行 maxflow()）
 * 对外成员（请在跑完最大流时再使用）：
 *   * `edges`:`vector<Edge>`: 图中的边集
 *   * `G`: `vector<int>*`: 图中的邻接表
 *   * `dist`: `int*`: 满流后，到源点的步长
 */
class Dinic {
    typedef int* pInt;
public:
    explicit Dinic(int maxn) {
        this->s = this->t = this->n = -1;
        this->maxn = maxn;
        this->current_size = sizeof(int) * maxn;
        this->cur = new int[maxn];
        this->dist = new int[maxn];
        this->G = new std::vector<int>[maxn];
        done = false;
    }

    explicit Dinic(int source, int converge, int n) {
        this->s = source;
        this->t = converge;
        this->n = n;
        this->maxn = n;
        this->current_size = sizeof(int) * n;
        this->cur = new int[n];
        this->dist = new int[n];
        G = new std::vector<int>[n];
        done = false;
    }
public:
    static const int INF = 0x3f3f3f3f;

    struct Edge {
        int from, to, cap, flow;
        explicit Edge(int from=0, int to=0, int cap=0, int flow=0):
                from(from), to(to), cap(cap), flow(flow) {}
    };


    /**
     * 加边（会加反向弧）
     * @param from      起始点
     * @param to        目的地
     * @param cap       边容量
     */
    void addEdge(int from, int to, int cap) {
        int size = edges.size();
        edges.emplace_back(from, to, cap, 0);
        edges.emplace_back(to, from, 0, 0);
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
    int n, s, t, maxn, maxflow_cached;
    size_t current_size;
    std::queue<int> Q;
    pInt cur;

public:
    std::vector<Edge> edges;
    std::vector<int>* G;
    pInt dist;

protected:
    bool BFS() {
        memset(dist, 0x3f, current_size);
        for(dist[s]=0, Q.push(s); !Q.empty();) {
            int o = Q.front(); Q.pop();
            for(int i: G[o]) {
                Edge& e = edges[i];
                if( dist[e.to] == INF && e.cap > e.flow ) {
                    dist[e.to] = dist[o] + 1;
                    Q.push(e.to);
                }
            }
        }
        return dist[t] != INF;
    }


    int DFS(int o, int minflow) {
        if( o == t || minflow == 0 ) return minflow;
        int flow = 0;
        for(int& i=cur[o]; i < G[o].size(); ++i) {
            Edge& e = edges[G[o][i]];
            if( dist[e.to] == dist[o]+1 ) {
                int f = DFS(e.to, std::min(minflow, e.cap-e.flow));
                if( f <= 0 ) continue;
                e.flow += f;
                edges[G[o][i]^1].flow -= f;
                flow += f;
                minflow -= f;
                if( minflow == 0 ) break;
            }
        }
        return flow;
    }

public:
    /**
     * 最大流
     * @return
     */
    int maxflow() {
        if( done ) return maxflow_cached;
        int ans = 0;
        while( BFS() ) {
            memset(cur, 0, current_size);
            ans += DFS(s, INF);
        }
        maxflow_cached = ans;
        done = true;
        return maxflow_cached;
    }


    /**
     * 最小割
     * @return
     */
    std::vector<std::pair<int, int>> mincut() {
        if( !done ) maxflow();
        std::vector<std::pair<int, int>> cuts;
        for(Edge& e: edges) {
            if( e.cap > 0 && dist[e.from] < INF && dist[e.to] == INF )
                cuts.emplace_back(e.from, e.to);
        }
        return cuts;
    }
};
