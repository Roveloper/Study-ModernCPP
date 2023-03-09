# BOJ_1697
from collections import deque


def bfs():
    q = deque()
    q.append(me)
    while q:
        x = q.popleft()
        if x == sister:
            return(pos_time[x])
        for nx in (x - 1, x + 1, x * 2):
            if 0 <= nx <= max and not pos_time[nx]:
                pos_time[nx] = pos_time[x] + 1
                q.append(nx)


# 입력
me, sister = map(int, input().split())
max = 10 ** 5 # 시간 초과 안 나오도록 수를 제한해준다.
pos_time = [0] * (max + 1) # 각 위치별로 걸리는 시간을 보여준다.
print(bfs())