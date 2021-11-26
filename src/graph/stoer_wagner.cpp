#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int INF = 1e9;
const int MN = 505;

int N, M;

int w[MN][MN], dist[MN];
int vst[MN], inset[MN];

int mincutphase(int &s, int &t) {
    memset(dist, 0, sizeof(dist));
    memset(vst, 0, sizeof(vst));
    int mincut = 0;
    for (int i = 1; i <= N; i++) {
        int k = -1, mx = -1;
        for (int j = 1; j <= N; j++) {
            if (inset[j] || vst[j]) continue;
            if (dist[j] > mx) k = j, mx = dist[j];
        }
        if (k == -1) return mincut;
        s = t, t = k;
        mincut = mx, vst[k] = 1;
        for (int j = 1; j <= N; j++)
            if (!inset[j] && !vst[j]) dist[j] += w[k][j];
    }
    return mincut;
}

pair<int, pair<int, int>> globalmincut() { //{mincut, {s, t}}
    int mincut = 1e9 + 7, rs, rt;
    for (int i = 1; i < N; i++) {
        int s, t;
        int now = mincutphase(s, t);
        inset[t] = 1;
        if (mincut > now) {
            mincut = now;
            rs = s, rt = t;
        }
        for (int j = 1; j <= N; j++) {
            if (!inset[j]) {
                w[s][j] += w[t][j];
                w[j][s] += w[t][j];
            } 
        }
    }
    
    return {mincut, {rs, rt}};
}