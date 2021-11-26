#include <bits/stdc++.h>

using namespace std;

using ll = long long;
const int ST = 1<<20;

struct SegTree {
    ll seg[ST*2];

    void init() {
        for (int i = 0; i < ST*2; i++)
            seg[i] = 0;
    }

    void update(int i, ll v) {
        seg[i+=ST] = v;
        for (i /= 2; i > 0; i /= 2) seg[i] = seg[i*2] + seg[i*2+1];
    }

    ll query(int l, int r) {
        ll ret = 0;
        for (l += ST, r += ST+1; l < r; l /= 2, r /= 2) {
            if (l & 1) ret += seg[l++];
            if (r & 1) ret += seg[--r];
        }
        return ret;
    }
};