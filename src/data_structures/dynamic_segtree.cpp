#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int MN = 4040404;
int N = 1e5;

struct Node {
    int l, r;
    ll v;
};

struct DynamicSegTree {
    vector<Node> tree;

    void init() {
        tree.push_back({-1, -1, 0});
    }

    void update(int n, int nl, int nr, int i, ll v) {
        if (nl == nr) {
            tree[n].v = v;
            return;
        }
        int m = (nl + nr) >> 1;
        if (i <= m) {
            if (tree[n].l == -1) {
                tree[n].l = tree.size();
                tree.push_back({-1, -1, 0});
            }
            update(tree[n].l, nl, m, i, v);
        } else {
            if (tree[n].r == -1) {
                tree[n].r = tree.size();
                tree.push_back({-1, -1, 0});
            }
            update(tree[n].r, m+1, nr, i, v);
        }
        ll a = (tree[n].l != -1 ? tree[tree[n].l].v : 0);
        ll b = (tree[n].r != -1 ? tree[tree[n].r].v : 0);
        tree[n].v = a+b;
    }

    ll query(int n, int nl, int nr, int l, int r) {
        if (n == -1) return 0;
        if (r < nl || nr < l) return 0;
        if (l <= nl && nr <= r) return tree[n].v;
        int m = (nl + nr) >> 1;
        return query(tree[n].l, nl, m, l, r) + query(tree[n].r, m+1, nr, l, r);
    }

    void update(int i, ll v) {
        update(0, 1, N, i, v);
    }

    ll query(int l, int r) {
        return query(0, 1, N, l, r);
    }
};