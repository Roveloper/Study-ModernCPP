# BOJ_10871
# 입력
n, x = map(int, input().split())
nums = list(map(int, input().split()))
for num in nums:
    if num < x:
        print(num, end=" ")
