# [CF1197D](https://codeforces.com/contest/1197/problem/D)
## 题解
\(m\)最大是10，所以可以设定状态dp[i][j]为第\(i\)个数位于j状态时的最大连续和，
设一组数有\(m\)个，每组的第一个数会减去\(k\)，所以有如下状态转移方程
\(dp[i][j]=
\begin{cases}
max(0,dp[i-1][m])+a[i]-k &j=1\\
dp[i-1][j-1]&j!=1
\end{cases}
\)
# [HDU_7(待补题)](http://acm.hdu.edu.cn/showproblem.php?pid=6652)