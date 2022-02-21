#include <iostream>

using namespace std;

const int N = 1e6 + 100;
int dp[N];

void Solve() {
    string st;
    cin >> st;
    int n = st.size();
    dp[1] = st[0] - '0';
    for (int i = 2; i <= n; ++i) {
        dp[i] = dp[i - 1] + st[i - 1] - '0';
        if (i > 1 && (st[i - 2] != st[i - 1])) {
            dp[i] = min(dp[i], dp[i - 2]);
        } 
    }
    cout << dp[n] << '\n';
}
int main() {
    ios::sync_with_stdio(false); cin.tie(NULL);
    int test;
    cin >> test;
    while (test--) Solve();
}