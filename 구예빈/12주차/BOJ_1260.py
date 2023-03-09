# BOJ_1260
from collections import deque
import sys
read = sys.stdin.readline

# dfs 구현
def bfs(v):
    q = deque()
    q.append(v)
    visit_list[v] = 1
    while q:
        v = q.popleft()
        print(v, end=" ")
        for i in range(1, n + 1):
            if visit_list[i] == 0 and graph[v][i] == 1:
                q.append(i)
                visit_list[i] = 1

# DFS 구현
def dfs(v):
    visit_list2[v] = 1
    print(v, end=" ")
    for i in range(1, n + 1):
        if visit_list2[i] == 0 and graph[v][i] == 1:
            dfs(i)


# 메인 코드
# 정점의 갯수 n, 간선의 갯수 m, 시작점 v
n, m, v = map(int, read().split())
graph = [[0] * (n + 1) for _ in range(n + 1)]
visit_list = [0] * (n + 1)
visit_list2 = [0] * (n + 1)
for _ in range(m):
    a, b = map(int, read().split())
    graph[a][b] = graph[b][a] = 1

dfs(v)
print()
bfs(v)

