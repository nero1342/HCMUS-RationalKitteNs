#include <bits/stdc++.h>

using namespace std;

int main()
{
    cin.tie(NULL); ios_base::sync_with_stdio(false);
    int tests; cin >> tests;
    while (tests--) {
        int m, n; cin >> m >> n;
        vector<vector<int>> paths;
        while (n--) {
            int x, y; cin >> x >> y;
            if (x > 0 && y > 0) {
                paths.push_back({x - 1, y - 1, x - 1, y, x, y});
                paths.push_back({x - 1, y, x, y, x, y - 1});
                paths.push_back({x, y, x, y - 1, x - 1, y - 1});
            }
            else if (x > 0) {   // y == 0
                paths.push_back({x - 1, y + 1, x - 1, y, x, y});
                paths.push_back({x - 1, y, x, y, x, y + 1});
                paths.push_back({x, y, x, y + 1, x - 1, y + 1});
            }
            else if (y > 0) {
                paths.push_back({x + 1, y - 1, x + 1, y, x, y});
                paths.push_back({x + 1, y, x, y, x, y - 1});
                paths.push_back({x, y, x, y - 1, x + 1, y - 1});
            }
            else {  // x == 0 && y == 0
                paths.push_back({x + 1, y + 1, x + 1, y, x, y});
                paths.push_back({x + 1, y, x, y, x, y + 1});
                paths.push_back({x, y, x, y + 1, x + 1, y + 1});
            }
        }
        cout << paths.size() << '\n';
        for (auto path : paths) {
            cout << path.size() / 2 - 1 << ' ';
            for (int x : path) cout << x << ' ';
            cout << '\n';
        }
    }
    return 0;
}
