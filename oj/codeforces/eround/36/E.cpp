#include <bits/stdc++.h>
using namespace std;


class SegmentTree {
public:
    struct Node {
        int setv, sum;
        Node *lson, *rson;

        Node(): lson(nullptr), rson(nullptr) {}
        Node(int sum, int setv=-1): lson(nullptr), rson(nullptr) {
            this->sum = sum;
            this->setv = setv;
        }

        void pushdown(int lft, int rht) {
            if( setv < 0 ) return;
            int mid = lft+rht >> 1;
            if( lson == nullptr ) lson = new Node();
            lson->setv = setv, lson->sum = setv? mid-lft+1: 0;
            if( rson == nullptr ) rson = new Node();
            rson->setv = setv, rson->sum = setv? rht-mid: 0;
            setv = -1;
        }

        void pushup(int lft, int rht) {
            sum = lson->sum + rson->sum;
            int total = rht - lft + 1;
            if( sum == 0 || sum == total ) setv = sum? 1: 0;
        }
    };

protected:
    Node* root;
    int N;

public:
    explicit SegmentTree(int N) {
        root = new Node(N, N);
        this->N = N;
    }

    void update(int lft, int rht, int v) {
        this->ul = lft;
        this->ur = rht;
        this->uv = v;
        update(root, 1, N);
    }

    int count() { return root->sum; }
private:
    int ul, ur, uv;
    void update(Node* o, int lft, int rht) {
        if( o->setv == uv ) return;
        if( ul <= lft && rht <= ur ) {
            o->setv = uv;
            o->sum = uv? (rht-lft+1): 0;
        } else {
            int mid = lft+rht >> 1;
            o->pushdown(lft, rht);
            if( ul <= mid ) update(o->lson, lft, mid);
            if( mid < ur ) update(o->rson, mid+1, rht);
            o->pushup(lft, rht);
        }
    }
};


int N, Q, u, v, w;

int main() {
    scanf("%d%d", &N, &Q);
    SegmentTree tree(N);
    for(int q=1; q <= Q; ++q) {
        scanf("%d%d%d", &u, &v, &w);
        tree.update(u, v, w-1);
        printf("%d\n", tree.count());
    }

    return 0;
}
