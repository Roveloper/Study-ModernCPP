# BOJ_2667
# dfs 구현
def dfs(x, y):
    global count
    if 0 > x or x >= len(graph) or 0 > y or y >= len(graph[0]):
        return False
    # 각 이동별로 dfs
    if graph[x][y] == 1:
        count += 1
        graph[x][y] = 0
        for i in range(4):
            nx = x + dx[i]
            ny = y + dy[i]
            # house_count[-1] += 1
            # 그래프 내부의 점이면
            dfs(nx, ny)
        return True # 상하좌우 다 뻗으면 단지수를 하나 추가한다.
    return False


# 메인
n = int(input())
graph = [list(map(int, input())) for _ in range(n)]
# 각 단지내 집의 수를 저장한 리스트
house_count = []
# 이동 좌표 - 상하좌우
dx = [-1, 1, 0, 0]
dy = [0, 0, -1, 1]
count = 0
# DFS 돌리기 - 모든 정점을 방문해야 한다.
for i in range(n):
    for j in range(n):
        if dfs(i, j):
            house_count.append(count)
            # print(house_count)
            count = 0

# 총 단지수와 각 단지내 집의 수 오름차순 출력
print(len(house_count))
house_count.sort()
for house in house_count:
    print(house)


# from collections import deque
#
# dx = [0, 0, 1, -1]
# dy = [1, -1, 0, 0]
#
#
# def bfs(graph, a, b):
#     n = len(graph)
#     queue = deque()
#     queue.append((a, b))
#     graph[a][b] = 0
#     count = 1
#
#     while queue:
#         x, y = queue.popleft()
#         for i in range(4):
#             nx = x + dx[i]
#             ny = y + dy[i]
#             if nx < 0 or nx >= n or ny < 0 or ny >= n:
#                 continue
#             if graph[nx][ny] == 1:
#                 graph[nx][ny] = 0
#                 queue.append((nx, ny))
#                 count += 1
#     return count
#
#
# n = int(input())
# graph = []
# for i in range(n):
#     graph.append(list(map(int, input())))
#
# cnt = []
# for i in range(n):
#     for j in range(n):
#         if graph[i][j] == 1:
#             cnt.append(bfs(graph, i, j))
#
# cnt.sort()
# print(len(cnt))
# for i in range(len(cnt)):
#     print(cnt[i])