# BOJ_2869
import math
# 입력
up, down, height = map(int, input().split())

# 걸리는 일자 구하기
day_up = up - down
height -= up
day = math.ceil(height / day_up) + 1
print(day)
