#include <bits/stdc++.h>

using namespace std;

const int MOD = 1e9 + 7;

void add(int& a, int b) { a += b; if (a >= MOD) a -= MOD; }
int mul(int a, int b) { return 1LL * a * b % MOD; }

struct Matrix {
    vector<int> a;
    Matrix() {}
    Matrix(int n, int m) { resize(n, m); }
    int r, c;
    void resize(int n, int m) { a.resize(n * m); r = n, c = m; }
    int& operator()(int i, int j) { return a[i * c + j]; }
    int operator()(int i, int j) const { return a[i * c + j]; }
    void print()
    {
        for (int i = 0; i < r; ++i)
            for (int j = 0; j < c; ++j)
                cerr << this->operator()(i, j) << " \n"[j + 1 == c];
    }
};

Matrix identity(int n)
{
    Matrix a(n, n);
    for (int i = 0; i < n; ++i) a(i, i) = 1;
    return a;
}

Matrix operator*(const Matrix& a, const Matrix& b)
{
    Matrix c(a.r, b.c);
    for (int i = 0; i < a.r; ++i)
        for (int j = 0; j < b.c; ++j)
            for (int k = 0; k < a.c; ++k)
                add(c(i, j), mul(a(i, k), b(k, j)));
    return c;
}

//Matrix operator^(Matrix base, long long expo)
//{
//    Matrix t = identity(base.r);
//    while (expo > 0) {
//        if (expo & 1) t = t * base;
//        base = base * base;
//        expo >>= 1;
//    }
//    return t;
//}

const int LN = 45;

Matrix a;
Matrix pw[LN];

Matrix calpw(long long expo)
{
    Matrix t = identity(a.r);
    for (int i = 0; i < LN; ++i)
        if ((expo >> i) & 1) t = t * pw[i];
    return t;
}

void recur(int i, int r, int mL, int mR)
{
    if (i == r) {
        ++a(mL, mR);
        return;
    }
    // skip
    recur(i + 1, r, mL, mR);
    // place hor
    recur(i + 1, r, mL ^ (1 << i), mR ^ (1 << i));
    // place ver
    if (i + 2 <= r)
        recur(i + 2, r, mL, mR | (1 << i) | (1 << (i + 1)));
}

void init(int r)
{
    a.resize(1 << r, 1 << r);
    recur(0, r, (1 << r) - 1, 0);
}

int main()
{
    int r; long long n; int k; cin >> r >> n >> k;
    init(r);
//    a.print();

    map<long long, int> msk;
    msk[n] = 0;
    for (int i = 0; i < k; ++i) {
        int x; long long y; cin >> x >> y;
        msk[y] |= 1 << (x - 1);
    }

    pw[0] = a;
    for (int i = 1; i < LN; ++i) pw[i] = pw[i - 1] * pw[i - 1];

    Matrix f(1, 1 << r);
    f(0, (1 << r) - 1) = 1;
    long long lasty = 0;

    for (auto pr : msk) {
        long long y = pr.first, mask = pr.second;
        long long d = y - lasty;
        Matrix trans = calpw(d);
        f = f * trans;
//        f.print();
        for (int i = (1 << r) - 1; i >= 0; --i)
            if ((i & mask) == mask) f(0, i) = f(0, i - mask);
            else f(0, i) = 0;
//        f.print(); cerr << '\n';
        lasty = y;
    }
    cout << f(0, (1 << r) - 1);
    return 0;
}

