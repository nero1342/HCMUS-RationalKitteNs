#include <bits/stdc++.h>

using namespace std;

const int N = 50 + 2;

int n;
bool adj[N][N];
bool used[N][N];
vector<int> mems[N];
int cpn[N];
int k;
vector<vector<int>> tours;
vector<pair<int, int>> added;

void join(int p, int q)
{
    if (p == q) return;
    mems[p].insert(mems[p].end(), mems[q].begin(), mems[q].end());
    for (int x : mems[q]) cpn[x] = p;
    mems[q].clear();
}

int pre[N];

vector<int> get_path(int s, int t)
{
    fill(pre + 1, pre + 1 + n, -1);
    queue<int> q;
    q.push(s);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v = 1; v <= n; ++v)
            if ((adj[u][v] || adj[v][u]) && v != s && pre[v] == -1) {
                pre[v] = u;
                q.push(v);
            }
    }

    assert(pre[t] != -1);
    vector<int> path;
    while (t != -1) {
        path.push_back(t);
        t = pre[t];
    }
    return path;
}

void try_saturate()
{
    for (int i = 1; i <= n; ++i)
        for (int j = i + 1; j <= n; ++j)
            if (!used[i][j] && !adj[i][j] && cpn[i] == cpn[j]) {
                tours.push_back(get_path(i, j));
                used[i][j] = true;
                added.push_back({i, j});
                if (--k == 0) return;
            }
}

int main()
{
    cin.tie(NULL); ios_base::sync_with_stdio(false);
    int m; cin >> n >> m >> k;

    if (k > n * (n - 1) / 2 - (n - 1)) {
        cout << "NO\n";
        return 0;
    }

    iota(cpn + 1, cpn + 1 + n, 1);
    for (int i = 1; i <= n; ++i) mems[i].push_back(i);

    while (m--) {
        int u, v; cin >> u >> v;
        if (cpn[u] != cpn[v]) {
            join(cpn[u], cpn[v]);
            adj[u][v] = adj[v][u] = true;
        }
        else {
            if (k > 0) {
                tours.push_back(get_path(u, v));
                --k;
            }
            if (u > v) swap(u, v);
            used[u][v] = true;
        }
    }


    while (k > 0) {
        try_saturate();
        if (k == 0) break;

        int c1 = 1;
        for (int i = 1; i <= n; ++i)
            if (mems[i].size() > mems[c1].size())
                c1 = i;

        int c2 = c1;
        for (int i = 1; i <= n; ++i)
            if (i != c1 && (c2 == c1 || mems[i].size() > mems[c2].size()))
                c2 = i;

        int u = mems[c1].front(), v = mems[c2].front();
        adj[u][v] = adj[v][u] = true;
        added.push_back({u, v});
        join(c1, c2);
    }

    cout << "YES\n";
    cout << added.size() << '\n';
    for (auto edge : added)
        cout << edge.first << ' ' << edge.second << '\n';

    for (auto path : tours) {
        cout << path.size() << ' ';
        for (int u : path) cout << u << ' ';
        cout << '\n';
    }
    return 0;
}
