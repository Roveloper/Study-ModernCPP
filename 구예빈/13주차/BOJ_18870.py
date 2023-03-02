# BOJ_18870
import sys
input = sys.stdin.readline
# 입력
n = int(input())
nums = list(map(int, input().split()))
set_nums = list(set(nums))
# print(set_nums)
sort_nums = sorted(set_nums)
# print(sort_nums)
new_nums = [[0] for _ in range(n)]


def binary_search(target, data):
    start = 0
    end = len(data) - 1
    while start <= end:
        mid = (start + end) // 2
        if data[mid] == target:
            return mid
        elif data[mid] < target:
            start = mid + 1
        else:
            end = mid - 1
    return



# 각 갯수 세서 좌표 압축 만들기
count = 0
for i in range(len(nums)):
    # start_idx = sort_nums.index(nums[i])
    # 이분탐색으로 하자
    end_idx = binary_search(nums[i], sort_nums)
    # new_nums[i] = end_idx
    print(end_idx, end=' ')


# # 압축된 좌표들 출력
# new_strings = list(map(str, new_nums))
# print(' '.join(new_strings))

