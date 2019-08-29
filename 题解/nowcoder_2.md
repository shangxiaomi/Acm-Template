# [B BM线性递推](https://ac.nowcoder.com/acm/contest/882/B)
转移式为$$dp[i]=\sum_{j=i-k}^{i-1}{\frac{1}{k}dp[j]}$$
仅与后k项有关，使用BM线性递推。
注意无穷时答案为$\frac{2}{k+1}$,需要特判。
还有注意BM传入参数为n，不为n-1。（因为把a[0]推入了）