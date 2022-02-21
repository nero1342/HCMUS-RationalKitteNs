#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int n; cin >> n;
    vector<long long> f(n + 1, 0);
    f[0] = 1;
    for (int i = 1; i <= n; ++i)
        for (int j = 0; j < i; ++j)
            f[i] += f[j];
    cout << f[n];
    return 0;
}
