# BOJ_11724
# dfs
def dfs(start, visited):
    global graph
    # stack에 탐색할 노드를 추가한다.
    stack = []
    stack.append(start)
    while stack:
        node = stack.pop()
        # 방문한 노드이면 그 노드는 이미 체크했으므로 스킵한다.
        if visited[node]:
            continue
        # 한번도 방문하지 않았다면 더 탐색한다.
        else:
            visited[node] = True
            stack.extend(graph[node])
    return


# 입력
n, m = map(int, input().split())
graph = [[] for _ in range(n + 1)]
visited = [False] * (n + 1)
for _ in range(m):
    a, b = map(int, input().split())
    graph[a].append(b)
    graph[b].append(a)


# dfs를 이용하여 연결 덩어리들의 갯수를 구한다.
link_count = 0
for i in range(1, n + 1):
    # 해당 노드를 방문한 적이 없으면
    if not visited[i]: # 새로운 덩어리이면
        link_count += 1
        dfs(i, visited)
        # print(i, visited)
print(link_count)
