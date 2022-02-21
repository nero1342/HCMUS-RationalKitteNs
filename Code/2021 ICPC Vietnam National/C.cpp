#include <bits/stdc++.h>

using namespace std;

template<typename T>
inline T sqr(T x) { return x * x; }

struct Point {
    long long x, y;
    Point operator-(Point q) { return {x - q.x, y - q.y}; }
    long long operator%(Point q) { return x*q.y - y*q.x; }
};

long long dist(Point A, Point B)
{
    return sqr(A.x - B.x) + sqr(A.y - B.y);
}

long long area(Point A, Point B, Point C)
{
    return (B - A) % (C - A);
}

const int N = 102;

Point a[N];
int f1[N], f2[N][N];
vector<array<int, 3>> idxs[N * N * N];

int main()
{
    int n; cin >> n;
    for (int i = 0; i < n; ++i) {
        int x, y; cin >> x >> y;
        a[i] = {x, y};
    }

    map<array<long long, 3>, int> cnt;
    for (int i = 0; i < n; ++i)
        for (int j = i + 1; j < n; ++j)
            for (int k = j + 1; k < n; ++k) {
                if (area(a[i], a[j], a[k]) == 0) continue;
                array<long long, 3> d = {dist(a[i], a[j]), dist(a[j], a[k]), dist(a[i], a[k])};
                sort(d.begin(), d.end());
                if (cnt.find(d) == cnt.end())
                    cnt.insert({d, cnt.size()});
                idxs[cnt[d]].push_back({i, j, k});
            }

    long long res = 0;
    for (auto pr : cnt) {
        auto d = pr.first;
        int id = pr.second;

        long long cur = 1LL * idxs[id].size() * (idxs[id].size() - 1);
        for (auto tri : idxs[id]) {
            for (auto p : tri) {
                cur -= f1[p] * 2;
                ++f1[p];
            }
            cur += f2[tri[0]][tri[1]] * 2;
            ++f2[tri[0]][tri[1]];

            cur += f2[tri[0]][tri[2]] * 2;
            ++f2[tri[0]][tri[2]];

            cur += f2[tri[1]][tri[2]] * 2;
            ++f2[tri[1]][tri[2]];
        }

        for (auto tri : idxs[id]) {
            for (auto p : tri) f1[p] = 0;
            f2[tri[0]][tri[1]] = 0;
            f2[tri[0]][tri[2]] = 0;
            f2[tri[1]][tri[2]] = 0;
        }

        if (d[0] == d[1] || d[1] == d[2] || d[0] == d[2]) cur *= 2;
        res += cur;
    }
    cout << res;
    return 0;
}
