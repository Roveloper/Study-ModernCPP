# BOJ_18111
# 입력
n, m, b = map(int, input().split())
blocks = []
min_height, now_min = 100, 100
max_height, now_max = 0, 0
for i in range(n):
    block = list(map(int, input().split()))
    now_min = min(block)
    now_max = max(block)
    if now_min < min_height:
        min_height = now_min
    if now_max > max_height:
        max_height = now_max
    blocks.append(block)
# print('height range: ', min_height, max_height)

# 각 높이에 맞게 블록을 추가해야하면 -1, 가져와야하면 +1 해준값
sum = 0
# 시간이 가장 적게 들 때 시간과 그 때의 높이
min_time = 256 * 2 * 500 * 500
min_time_height = 100
for height in range(min_height, max_height + 1):
    sum = 0
    time = 0
    for i in range(n):
        for j in range(m):
            # print(i, j, ':', blocks[i][j], time)
            gap = blocks[i][j] - height
            if gap < 0:
                time += 1 * abs(gap)
            elif gap > 0:
                time += 2 * abs(gap)
            sum += gap
    # print(height, min_time, sum)
    if sum + b < 0:
        continue
    if time <= min_time:
        min_time = time
        # if min_time_height <= height:
        min_time_height = height

print(min_time, min_time_height)
