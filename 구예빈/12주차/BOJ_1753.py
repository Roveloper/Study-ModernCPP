# BOJ_1753
# 입력
v, e = map(int, input().split())
start = int(input())
# 가중치 그래프를 입력받는다.
graph = [[0] * (v + 1) for _ in range(v + 1)]
for _ in range(e):
    a, b, c = map(int, input().split())
    graph[a][b] = c
# start 점에서 각 점까지 최단 겅로를 저장해준다.
min_paths = [-1 for _ in range(v + 1)]
min_paths[start] = 0


# start에서 v점으로 가는 경로의 수를 구한다.
def find_min_path(v):
    # 한번도 계산한 적 없다면 재귀로 계산한다.
    if min_paths[v] == -1:
        min_path = 20000 * 10
        for i in range(1, v + 1):
            if graph[i][v] != 0:
                if find_min_path(i) == 'INF':
                    continue
                min_path = min(graph[i][v] + find_min_path(i), min_path)
        if min_path == 20000 * 10:
            return 'INF'
        return min_path
    return min_paths[v]


for vertex in range(1, v + 1):
    print(find_min_path(vertex))
