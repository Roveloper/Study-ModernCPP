from collections import deque


def bfs(x, y):
    queue.append((x, y))
    done.append((x, y))
    while queue:
        curr = queue.popleft()
        for i in range(4):
            nx = curr[0] + dx[i]
            ny = curr[1] + dy[i]
            if (0 <= nx < N) and (0 <= ny < N) and ((nx, ny) not in done):
                if colors[nx][ny] == colors[curr[0]][curr[1]]:
                    queue.append((nx, ny))
                    done.append((nx, ny))


N = int(input())
colors = [list(input()) for _ in range(N)]
dx = [1, -1, 0, 0]
dy = [0, 0, 1, -1]
# 정상인인 경우
queue = deque()
done = []
cnt_1 = 0
for i in range(N):
    for j in range(N):
        if (i, j) not in done:
            bfs(i, j)
            cnt_1 += 1

# 적록색맹인 경우
for i in range(N):
    for j in range(N):
        if colors[i][j] == 'G':
            colors[i][j] = 'R'

queue = deque()
done = []
cnt_2 = 0
for i in range(N):
    for j in range(N):
        if (i, j) not in done:
            bfs(i, j)
            cnt_2 += 1

print(cnt_1, cnt_2)