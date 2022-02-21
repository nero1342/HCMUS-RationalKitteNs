#include <iostream>
#include <vector>

using namespace std;

const int N = 505;
int a[N][N], best[N][N], p[N], ra[N], L[N], sa[N], tempRA[N];
int n, m;
vector<int> e[N];

void radix_sort(int c) {
    // cerr << "Radix " << c << '\n';
    for (int i = 0; i < n; ++i) e[i].clear();
    for (int i = 0; i < m; ++i) {
        L[i] = 0; 
        e[a[i][c]].push_back(i);
    }
    for (int i = 0; i < m; ++i) L[ra[i]]++;
    int p = 0;
    for (int i = 0; i < m; ++i) {
        int x = L[i];
        L[i] = p; 
        p += x;
    }
    for (int i = 0; i < n; ++i) {
        for (int r : e[i]) {
            int &x = L[ra[r]];
            sa[x++] = r; 
        }
    }
    tempRA[sa[0]] = 0;
    for (int i = 1, r = 0; i < m; ++i) {
        if ((ra[sa[i - 1]] != ra[sa[i]]) || (a[sa[i - 1]][c] != a[sa[i]][c])) ++r;
        tempRA[sa[i]] = r; 
    }
    for (int i = 0; i < m; ++i) ra[i] = tempRA[i];
}

bool checkMax() {
    for (int j = 0; j < m; ++j) {
        for (int k = 0; k < n; ++k) {
            int c = p[k], r = sa[j];
            if (best[j][k] != n - a[r][c]) return best[j][k] < n - a[r][c];
        }
    }
    return false;
}

int main() {
    
    ios::sync_with_stdio(false); cin.tie(NULL);
    cin >> m >> n;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) { cin >> a[i][j]; a[i][j] = n - a[i][j]; }
    }
    for (int i = 0; i < m; ++i) {
        // cerr << "At " << i << '\n';
        for (int j = 0; j < n; ++j) { p[a[i][j]] = j; }
        for (int j = 0; j < m; ++j) ra[j] = 0;
        for (int j = 0; j < n; ++j) {
            int c = p[j];
            radix_sort(c);
            if (ra[sa[m - 1]] == m - 1) break;
        }
        if (checkMax()) {
            for (int j = 0; j < m; ++j) {
                for (int k = 0; k < n; ++k) {
                    int c = p[k], r = sa[j];
                    best[j][k] = n - a[r][c];
                }
            }
        }
    }
    // cout << "Time: " << (clock() - stime) / CLOCKS_PER_SEC * 1000 << "ms\n";
    // for (int i = 0; i < m; ++i) {
    //     for (int j = 0; j < n; ++j) cout << best[i][j] << " \n"[j + 1 == n];
    // }
    int q;
    cin >> q;
    while (q--) {
        int x, y;
        cin >> x >> y;
        cout << best[x - 1][y - 1] << '\n';
    }
}