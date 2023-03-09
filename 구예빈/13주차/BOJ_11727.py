# BOJ_11727
n = int(input())
dp = [0] * (1001)
dp[1] = 1
dp[2] = 3
for x in range(3, 1001):
    # dp[x-2]에는 2개를 곱한다.
    dp[x] = dp[x - 1] + dp[x - 2] * 2

print(dp[n] % 10007)