#include <bits/stdc++.h>

using namespace std;

const int N = 52;

int solve(vector<char> a)
{
    int res = 26 * 4;
    for (int i = 0; i < 26; ++i) {
        int cur = 0;
        for (char ch : a) {
            int c = ch - 'A';
            cur += min(abs(i - c), 26 - abs(i - c));
        }
        res = min(res, cur);
    }
    return res;
}

char tab[N][N];
bool sel[N][N];

int main()
{
    int n, m; cin >> n >> m;
    for (int i = 0; i < n; ++i) cin >> tab[i];

    int res = 0;

    for (int i = 0; i <= n / 2; ++i)
        for (int j = 0; j <= m / 2; ++j) {
            vector<char> chars;
            chars.push_back(tab[i][j]);
            sel[i][j] = true;
            if (!sel[n - i - 1][j]) {
                sel[n - i - 1][j] = true;
                chars.push_back(tab[n - i - 1][j]);
            }
            if (!sel[i][m - 1 - j]) {
                sel[i][m - 1 - j] = true;
                chars.push_back(tab[i][m - 1 - j]);
            }
            if (!sel[n - i - 1][m - 1 - j]) {
                sel[n - i - 1][m - 1 - j] = true;
                chars.push_back(tab[n - i - 1][m - 1 - j]);
            }
            res += solve(chars);
        }
    cout << res;
    return 0;
}
