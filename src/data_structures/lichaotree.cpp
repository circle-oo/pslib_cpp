#include<bits/stdc++.h>

using namespace std;

using ll = long long;

//this template for minimum query
//for maximum query: min -> max, h -> l, l -> h
const ll INF = 2e18;

struct Line {
    ll a, b;
    ll get(ll x) {
        return a*x + b;
    }
};

struct Node {
    int l, r;
    ll s, e;
    Line line;
};

struct LiChao {
    vector<Node> tree;

    void init(ll s=-2e9, ll e=2e9) { //consider overflow about a*x + b (check range of a, b)
        tree.push_back({-1, -1, s, e, {0, INF}});
    }

    void update(int n, Line v) {
        ll s = tree[n].s, e = tree[n].e;
        ll m = (s + e) >> 1;
        
        Line l = tree[n].line, h = v;
        if (l.get(s) > h.get(s)) swap(l, h);
        
        if (l.get(e) <= h.get(e)) {
            tree[n].line = l; return;
        }
        
        if (l.get(m) < h.get(m)) {
            tree[n].line = l;
            if (tree[n].r == -1) {
                tree[n].r = tree.size();
                tree.push_back({-1, -1, m+1, e, {0, INF}});
            }
            update(tree[n].r, h);
        } else {
            tree[n].line = h;
            if (tree[n].l == -1) {
                tree[n].l = tree.size();
                tree.push_back({-1, -1, s, m, {0, INF}});
            }
            update(tree[n].l, l);
        }
    }

    ll query(int n, ll x) {
        if (n == -1) return INF;
        ll s = tree[n].s, e = tree[n].e;
        ll m = (s + e) >> 1;
        if (x <= m) return min(tree[n].line.get(x), query(tree[n].l, x));
        else return min(tree[n].line.get(x), query(tree[n].r, x));
    }
};