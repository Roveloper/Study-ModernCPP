from collections import deque


# bfs
def bfs():
    while queue:
        x, y = queue.popleft()
        for i in range(4):
            nx = x + dx[i]
            ny = y + dy[i]
            if 0 <= nx < n and 0 <= ny < m and graph[nx][ny] == 0:
                graph[nx][ny] = graph[x][y] + 1
                queue.append((nx, ny))


# 입력
m, n = map(int, input().split())
graph = [list(map(int, input().split())) for _ in range(n)]
# 익은 토마토가 있는 위치를 queue에 저장한다.
queue = deque()
for i in range(n):
    for j in range(m):
        if graph[i][j] == 1:
            queue.append((i, j))

dx = [-1, 1, 0, 0]
dy = [0, 0, -1, 1]
bfs()

day = 0
for i in range(n):
    for j in range(m):
        if graph[i][j] == 0:
            print(-1)
            exit(0)
    day = max(day, max(graph[i]))
print(day - 1)