# BOJ_18870_dictionary
import sys
input = sys.stdin.readline
n = int(input())
nums = list(map(int, input().split()))
# 중복 제거
set_nums = list(set(nums))
# 오름차순 정렬
sort_nums = sorted(set_nums)
print(sort_nums)
dic_nums = {sort_nums[i]: i for i in range(len(sort_nums))}
print(dic_nums)
for num in nums:
    print(dic_nums[num], end=' ')

