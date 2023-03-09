# BOJ_3052
# 입력
nums = []
for _ in range(10):
    nums.append(int(input()))


# 나머지 구하기
rests = []
for num in nums:
    rests.append(num % 42)
rest = set(rests)
print(len(rest))