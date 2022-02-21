#include <bits/stdc++.h>

using namespace std;

const int N = 51;

const int X = 16;

long long dp[N][X][X][X][X][X];
int low[5], high[5], n, tags[N][5];

long long Go(int u, int x1, int x2, int x3, int x4, int x5) {
    int xx[] = {x1, x2, x3, x4, x5};
    for (int i = 0; i < 5; ++i) if (xx[i] > high[i]) return 0;
    if (dp[u][x1][x2][x3][x4][x5] != -1) return dp[u][x1][x2][x3][x4][x5];
    if (u == n) {
        for (int i = 0; i < 5; ++i) if (xx[i] < low[i]) return 0;
        return 1;
    }
    long long& res = dp[u][x1][x2][x3][x4][x5] = 0;
    res += Go(u + 1, x1, x2, x3, x4, x5);
    x1 += tags[u][0];
    x2 += tags[u][1];
    x3 += tags[u][2];
    x4 += tags[u][3];
    x5 += tags[u][4];
    res += Go(u + 1, x1, x2, x3, x4, x5);
    return res;
}

int main() {
    map<string, int> mp;
    mp["dp"] = 0;
    mp["graph"] = 1;
    mp["mathgeo"] = 2;
    mp["ds"] = 3;
    mp["adhoc"] = 4;
    cin >> n;
    memset(dp, -1, sizeof dp);
    for (int i = 0; i < n; ++i) {
        int k;
        cin >> k;
        while (k--) {
            string tag;
            cin >> tag;
            tags[i][mp[tag]] = 1;
        }
    }
    bool flag = true;
    for (int i = 0; i < 5; ++i) cin >> low[i] >> high[i];
    for (int i = 0; i < 5; ++i) if (low[i]) flag = false;
    cout << Go(0, 0, 0, 0, 0, 0) - flag << '\n';
}
