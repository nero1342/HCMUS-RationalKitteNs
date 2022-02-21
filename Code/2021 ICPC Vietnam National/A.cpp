#include <bits/stdc++.h>

using namespace std;

int main()
{
    cin.tie(NULL); ios_base::sync_with_stdio(false);
    int n; cin >> n;
    vector<vector<int>> indexes(n + 2);
    vector<int> res(n * n);
    for (int i = 0; i < n * n; ++i) {
        int x; cin >> x;
        indexes[x].push_back(i);
    }

    for (int box = 1; box <= n; ++box) {
        int mincol = 0, maxcol = 0;
        for (int i = 1; i <= n + 1; ++i) {
            if (indexes[i].empty()) continue;
            if (!mincol || indexes[i].size() < indexes[mincol].size())
                mincol = i;
        }
        for (int i = 1; i <= n + 1; ++i) {
            if (indexes[i].empty() || i == mincol) continue;
            if (!maxcol || indexes[i].size() > indexes[maxcol].size())
                maxcol = i;
        }
        if (maxcol && indexes[mincol].size() < n) {
            int amt = n - indexes[mincol].size();
            assert(amt >= 0);
            for (int j : indexes[mincol])
                res[j] = box;
            while (amt > 0) {
                res[indexes[maxcol].back()] = box;
                indexes[maxcol].pop_back();
                --amt;
            }
            indexes[mincol].clear();
        }
        else {
            assert(indexes[mincol].size() >= n);
            int amt = n;
            while (amt > 0) {
                res[indexes[mincol].back()] = box;
                indexes[mincol].pop_back();
                --amt;
            }
        }
    }
    cout << "YES\n";
    for (int i = 0; i < n * n; ++i) cout << res[i] << ' ';
    return 0;
}
