#include <bits/stdc++.h>

using namespace std;

using ll = long long;
const int ST = 1<<20;

struct LazySegTree {
    ll seg[ST*2], lazy[ST*2];

    void prop(int n, int nl, int nr) {
        seg[n] += lazy[n] * (nr-nl+1);
        if (n < ST) {
            lazy[n*2] += lazy[n];
            lazy[n*2+1] += lazy[n];
        }
        lazy[n] = 0;
    }

    void update(int n, int nl, int nr, int l, int r, ll v) {
        prop(n, nl, nr);
        if (nr < l || r < nl) return;
        if (l <= nl && nr <= r) {
            lazy[n] += v;
            prop(n, nl, nr);
            return;
        }

        int m = (nl + nr) / 2;
        update(n*2, nl, m, l, r, v);
        update(n*2+1, m+1, nr, l, r, v);
        seg[n] = seg[n*2] + seg[n*2+1];
    }

    ll query(int n, int nl, int nr, int l, int r) {
        prop(n, nl, nr);
        if (nr < l || r < nl) return 0;
        if (l <= nl && nr <= r) return seg[n];

        int m = (nl + nr) / 2;
        return query(n*2, nl, m, l, r) + query(n*2+1, m+1, nr, l, r);
    }
};