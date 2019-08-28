```c++
void ST(int n) {
    for (int i = 1; i <= n; i++)
        dp[i][0] = A[i];
    for (int j = 1; (1 << j) <= n; j++) {
        for (int i = 1; i + (1 << j) - 1 <= n; i++) {
            dp[i][j] = max(dp[i][j - 1], dp[i + (1 << (j - 1))][j - 1]);
        }
    }
}
int RMQ(int l, int r) {
    int k = 0;
    while ((1 << (k + 1)) <= r - l + 1) k++;
    return max(dp[l][k], dp[r - (1 << k) + 1][k]);
}
```