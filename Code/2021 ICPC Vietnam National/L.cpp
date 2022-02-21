#include <bits/stdc++.h>

using namespace std;

const int MAXA = 1e7;

int lp[MAXA + 2];

void sieve()
{
    for (int i = 2; i <= MAXA; ++i)
        if (!lp[i]) {
            lp[i] = i;
            for (long long j = 1LL * i * i; j <= MAXA; j += i)
                if (!lp[j]) lp[j] = i;
        }
}

int reduce(int x)
{
    int y = 1;
    while (x > 1) {
        int fact = lp[x];
        int cnt = 0;
        while (x % fact == 0) x /= fact, ++cnt;
        y *= fact;
    }
    return y;
}

int main()
{
    sieve();
    int n; cin >> n;
    map<int, int> cnt;
    for (int i = 0; i < n; ++i) {
        int x; cin >> x;
        ++cnt[reduce(x)];
    }

    long long res = 0;
    for (auto p : cnt)
        res += 1LL * p.second * (p.second - 1) / 2;
    cout << res;
    return 0;
}
