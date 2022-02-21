#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main()
{
    int n, k; cin >> n >> k;
    vector<int> a(n);
    for (int& x : a) cin >> x;
    sort(a.begin(), a.end());
    int smin = 0, smax = 0;
    for (int i = 0; i < k; ++i) {
        if (a[i] >= 2) smin += a[i];
        if (a[n - 1 - i] >= 2) smax += a[n - 1 - i];
    }
    if (smin < 2) smin = 0;
    if (smax < 2) smax = 0;
    cout << smin << ' ' << smax;
    return 0;
}
