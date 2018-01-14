# E - Party
## 题目描述
$N$ 个人参加一个 Party，如果两个人互相认识的，则在他们之间连接一条边，这 $N$ 个人构成的图是联通的。
每次操作：选择一个人 $p$，使得 $p$ 认识的人全部互相认识。问至少执行几次操作可以使这 $N$ 个人互相认识，并输出任一满足条件的操作次数最少的操作列表。
数据范围： $1\leqslant N\leqslant 22$


## 题解
记 $f(p)$ 为 $p$ 认识的人的集合，设 $dp(S)$ 表示使得 $S$ 中的人全部互相认识且执行的操作最少的选人集合。
那么接下来选择 $S-dp(S)$ 中的一个人 $p$ 可使得 $S+f(p)$ 中的人全部都互相认识（因为此前 $p$ 已经认识了 $S$ 中的所有人），
使用刷表法就可以解决问题了，最少执行的操作次数为 $|dp(S_n)|$，其中 $S_n$ 为所有这 $N$ 个人的集合。
而操作列表就是普通的输出转移路径的问题了。
时间复杂度为 $O(N^{2}2^N)$。

其实由于每次操作相当于将选择的人的所有认识的人合并到他所属的团中，也就是集合的合并的操作，因此操作的执行顺序其实是无关紧要的，
所以直接使用 DFS 搜索就好了。复杂度为 $O(N\times 2^N)$

