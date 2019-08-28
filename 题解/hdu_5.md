[TOC]
# [permutation 1(DFS)](http://acm.hdu.edu.cn/showproblem.php?pid=6628)
## 题意
给定一个数$n$,求出$p_2-p_1,p_3-p_2,...,p_n-p_{n-1}$中字典序第$k$小的排列，$1\leq p_i\leq n$
## 题解
第一位定为一个较大的值，枚举差[1-n,n-1]，然后控制数列最大值-最小值<=n-1，最后输出的时候所有值减去最小值。