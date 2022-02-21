#include <bits/stdc++.h>

using namespace std;

int a[3][3];

struct State {
    int mask;
    int lock;
    int tme;
};
vector<State> steps;
int c;

void rotate_edge(int m1, int m2, int l1, int l2, int k)
{
    if (!k || k == c) return;
    steps.push_back({m1, l1, c - k});
    steps.push_back({m2, l1, k});
    steps.push_back({0, l2, c - k});
}

int main()
{
    cin >> c;
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j) cin >> a[i][j];

    if (a[0][0] != 0) steps.push_back({0, 1, c - a[0][0]});
    if (a[0][2] != 0) steps.push_back({0, 3, c - a[0][2]});
    if (a[2][0] != 0) steps.push_back({0, 7, c - a[2][0]});
    if (a[2][2] != 0) steps.push_back({0, 9, c - a[2][2]});

    a[0][0] = a[0][2] = a[2][0] = a[2][2] = 0;

    const int PINA = 1;
    const int PINB = 2;
    const int PINC = 4;
    const int PIND = 8;
    rotate_edge(PINC, PINA + PINC, 7, 1, c - a[0][1]);
    rotate_edge(PINA, PINA + PINC, 1, 7, c - a[2][1]);
    rotate_edge(PINB, PINA + PINB, 3, 1, c - a[1][0]);
    rotate_edge(PINA, PINA + PINB, 1, 3, c - a[1][2]);

    if (a[1][1] != 0) {
        steps.push_back({PINA, 1, c - a[1][1]});
        steps.push_back({0, 1, a[1][1]});
        rotate_edge(PINC, PINA + PINC, 7, 1, a[1][1]);
        rotate_edge(PINB, PINA + PINB, 3, 1, a[1][1]);
    }

    cout << "YES\n";
    cout << steps.size() << '\n';
    for (auto step : steps) {
        cout << !!(step.mask & PINA) << ' ';
        cout << !!(step.mask & PINB) << ' ';
        cout << !!(step.mask & PINC) << ' ';
        cout << !!(step.mask & PIND) << ' ';
        cout << step.lock << ' ' << step.tme << '\n';
    }
    return 0;
}
