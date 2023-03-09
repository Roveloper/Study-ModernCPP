# BOJ_11726_DP
import time

n = int(input())
start = time.time()
dp = [0] * 1001
dp[1] = 1
dp[2] = 2
for x in range(3, 1001):
    dp[x] = dp[x-1] + dp[x-2]

print(dp[n] % 10007, end=' ')
# print(dp[n] % 10007)
end = time.time()
print('-> running time:', round(end - start, 4), '초')