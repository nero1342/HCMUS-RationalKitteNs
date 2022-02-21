#include <iostream>
#include <vector>

using namespace std;

long long dp[17][150][150][3];
bool isPrime[150];

void init()
{
    for (int i = 2; i < 150; ++i) {
        isPrime[i] = true;
        for (int j = 2; j * j <= i; ++j)
            if (i % j == 0) isPrime[i] = false;
    }
}

int main()
{
    init();

    long long x;
    cin >> x;

    // for (int i = 1; i * 2 <= x; ++i) {
    //     int j = x - i * 2;
    //     int si = 0, sj = 0;
    //     int u = i, v = j;
    //     while (u) si += u % 10, u /= 10;
    //     while (v) sj += v % 10, v /= 10;
    //     if (isPrime[si] && isPrime[sj]) cerr << x - i * 2 << ' ' << i * 2 << ' ' << si << ' ' << sj << '\n';
    // }

    vector<int> a;
    while (x) {
        a.push_back(x % 10);
        x /= 10;
    }
    
    for (int i = 0; i < 10; ++i)
        for (int j = 0; j < 10; ++j)
            if ((i + j * 2) % 10 == a[0])
                dp[1][i][j][(i + j * 2) / 10] = 1;

    int n = a.size();
    for (int i = 1; i < n; ++i) {
        int dig = a[i];
        for (int j = 0; j <= 9 * i; ++j)
            for (int k = 0; k <= 9 * i; ++k)
                for (int carry = 0; carry < 3; ++carry)
                    if (dp[i][j][k][carry] > 0)
                        for (int dx = 0; dx < 10; ++dx)
                            for (int dy = 0; dy < 10; ++dy)
                                if ((dx + dy * 2 + carry) % 10 == dig) {
                                    int nc = (dx + dy * 2 + carry) / 10;
                                    dp[i + 1][j + dx][k + dy][nc] += dp[i][j][k][carry];
                                }
    }

    long long res = 0;
    for (int i = 1; i < 150; ++i)
        for (int j = 1; j < 150; ++j)
            if (isPrime[i] && isPrime[j]) {
                res += dp[n][i][j][0];
            }

    cout << res << '\n';
    return 0;
}
