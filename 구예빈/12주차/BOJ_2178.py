# BOJ_2178
from collections import deque

# 최단거리 문제를 풀 때는 BFS로 푼다.
def bfs(graph):
    # (0,0) 에서 출발
    q = deque([(0, 0)])
    # 각 점에서의 최단거리를 나타낸다.
    visited = [[0] * m for _ in range(n)]
    dx = [0, 0, -1, 1]
    dy = [-1, 1, 0, 0]
    visited[0][0] = 1
    graph[0][0] = 0
    while q:
        # print(q)
        x, y = q.popleft()
        for i in range(4):
            nx = x + dx[i]
            ny = y + dy[i]
            if 0 <= nx < len(graph) and 0 <= ny < len(graph[0]):
                if graph[nx][ny] == 1 and not visited[nx][ny]:
                    visited[nx][ny] = visited[x][y] + 1
                    q.append((nx, ny))
    answer = -1
    # 도착점에 이뤘을 때 0이 아니므로
    if visited[-1][-1]:
        # print(visited)
        return visited[-1][-1]
    return answer


# 입력
n, m = map(int, input().split())
graph = [list(map(int, input())) for _ in range(n)]
print(bfs(graph))

# # DFS로 푼다.
# def dfs(cur_x, cur_y, visited, move_count):
#     visited[cur_x][cur_y] = True
#     for i in range(4):
#         next_x = cur_x + dx[i]
#         next_y = cur_y + dy[i]
#         if next_x <= -1 or next_x >=n or next_y <= -1 or next_y >= m:
#             continue
#         if not visited[next_x][next_y] and graph[next_x][next_y] == 1:
#             if next_x == n - 1 and next_y == m - 1:
#                 return move_count
#             move_count = dfs(next_x, next_y, visited, move_count + 1)
#             min_move[next_x][next_y] = move_count
#     return move_count
#
# # 메인문
# move_count = 0
# answer = dfs(0, 0, visited, move_count)
# print(min_move)
# print(answer)
