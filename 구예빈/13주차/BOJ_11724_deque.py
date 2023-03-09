from collections import deque

# bfs
def bfs(start, visited):
    global graph
    q = deque(graph[start])
    visited[start] = True
    while q:
        node = q.popleft()
        if not visited[node]:
            visited[node] = True
            q.extend(graph[node])
    return


# 입력
n, m = map(int, input().split())
graph = [[] for _ in range(n + 1)]
visited = [False] * (n + 1)
for _ in range(m):
    a, b = map(int, input().split())
    graph[a].append(b)
    graph[b].append(a)


link_count = 0
for i in range(1, n + 1):
    # 해당 노드를 방문한 적이 없으면
    if not visited[i]: # 새로운 덩어리이면
        link_count += 1
        bfs(i, visited)
        # print(i, visited)
print(link_count)
