#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int INF = 1e9;
const int MN = 505;
int N;
int capacity[MN][MN];
vector<int> adj[MN];
int dis[MN], pnt[MN];

bool bfs(int s, int t) {
    memset(dis, 0, sizeof(dis));
    memset(pnt, 0, sizeof(pnt));
    queue<int> q;
    q.push(s);
    dis[s] = 1;
    
    while (!q.empty()) {
        int x = q.front();
        q.pop();
        for (auto next: adj[x]) {
            if (capacity[x][next] > 0 && !dis[next]) {
                dis[next] = dis[x] + 1;
                q.push(next);
            }
        }
    }
    return dis[t] > 0;
}

int dfs(int x, int sink, int f) {
    if (x == sink) return f;
    for (int &i = pnt[x]; i < adj[x].size(); i++) {
        int next = adj[x][i];
        if (dis[next] == dis[x] + 1 && capacity[x][next] > 0) {
            int fl = dfs(next, sink, min(f, capacity[x][next]));
            if (fl > 0) {
                capacity[x][next] -= fl;
                capacity[next][x] += fl;
                return fl;
            }
        }
    }
    return 0;
}

int maxflow(int s, int t) {
    int flow = 0;
    while (bfs(s, t)) {
        int r;
        while ((r = dfs(s, t, INF))) flow += r;
    }
    return flow;
}