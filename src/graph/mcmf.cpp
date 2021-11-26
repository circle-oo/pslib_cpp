#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int INF = 1e9;
const int MN = 805;

int dst[MN], inQ[MN], capacity[MN][MN], pa[MN];
vector<pair<int, int>> adj[MN];

bool SPFA(int s, int t) {
    fill(dst, dst+MN, INF);
    fill(inQ, inQ+MN, 0);
    bool ok = false;
    
    dst[s] = 0;
    queue<int> q; q.push(s); inQ[s] = 1;
    while (!q.empty()) {
        int u = q.front(); q.pop(); inQ[u] = 0;
        if (u == t) ok = true;
        for (auto [v, c]: adj[u]) {
            if (dst[u] + c >= dst[v] || capacity[u][v] <= 0) continue;
            dst[v] = dst[u] + c;
            pa[v] = u;
            
            if (!inQ[v]) {
                q.push(v); inQ[v] = 1;
            }
        }
    }
    return ok;
}

pair<int, int> MCMF(int s, int t) { //returns {total flow, total cost}
    int ret1 = 0, ret2 = 0;
    while (SPFA(s, t)) {
        int cap = 1e9;
        for (int pos = t; pos != s; pos = pa[pos]) {
            cap = min(cap, capacity[pa[pos]][pos]);
        }
        ret1 += cap;
        ret2 += dst[t] * cap;
        for (int pos = t; pos != s; pos = pa[pos]) {
            capacity[pa[pos]][pos] -= cap;
            capacity[pos][pa[pos]] += cap;
        }
    }
    return {ret1, ret2};
}