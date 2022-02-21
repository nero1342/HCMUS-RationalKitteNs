#include <cstdio>
const int N = 105;
int a[N][N], b[N];

int main() {
    int n; scanf("%d", &n);
    if (n == 1) {
        printf("1\n1\n");
        return 0;
    }
    printf("%d\n", n * n - n + 1);

    --n;
    int index = 1;
    for (int i = 0; i <= n; ++i)
        b[i] = index++;
    for (int j = 0; j < n; ++j)
        for (int k = 0; k < n; ++k)
            a[j][k] = index++;

    for (int i = 0; i < n; ++i)
        for (int k = 0; k < n; ++k) {
            printf("%d", b[i]);
            for (int j = 0; j < n; ++j)
                printf(" %d", a[(i * j + k) % n][j]);
            printf("\n");
        }
    for (int j = 0; j < n; ++j) {
        printf("%d", b[n]);
        for (int k = 0; k < n; ++k)
            printf(" %d", a[k][j]);
        printf("\n");
    }
    for (int i = 0; i <= n; ++i)
        printf("%d%c", b[i], " \n"[i == n]);
}
