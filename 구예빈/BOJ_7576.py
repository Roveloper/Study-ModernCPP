# BOJ_7576
# 모든 토마토가 익는 최소 날짜 구하고 싶어. 결과는 0, -1, 자연수
# 토마토는 상하좌우에 익은 토마토가 있을 때 익어.
# 그렇다면 익은 토마토를 중심으로 인접한 토마토로 이동해야하니까
# DFS보다는 BFS가 적합하겠네.
# 아니다 굳이 BFS를 쓸 필요 없이
# 인접한 익지 않은 토마토만 익게 만들어부면 되잖아.
"""
모든 토마토가 익은 상태인지 확인한다.
익었으면 0을 출력한다.

1. 익은 토마토를 찾는다.
2. 익은 토마토를 찾으면 인접한 모든 토마토를 익힌다. > 현재 그래프에 저장한다.
1) 어제 그래프에서 익은 토마토 기준으로 현재그래프의 인접한 모든 익지 않은 토마토를 익힌다.

3. 마지막 토마토를 방문할 때(오늘 모든 토마토 스캔한 후)
모든 토마토가 익은 경우 날짜를 출력하고 종료한다.
전날 그래프와 오늘 그래프가 같은 경우 -1을 출력하고 종료한다.

4. 그렇지 않으면 날짜에 하루가 더해지고
'전날 그래프'에 현재 그래프를 저장한 후
다음날 또 처음부터 토마토를 스캔한다.
"""
import copy


def make_ripen(x, y, graph):
    for i in range(4):
        nx = x + dx[i]
        ny = y + dy[i]
        # if ~(0 <= nx < n) or ~(0 <= ny < m):
        if nx < 0 or nx >= n or ny < 0 or ny >= m:
            continue
        # 어제 그래프에서 익은 토마토 기준으로
        # 현재 그래프의 인접한 모든 익지 않은 토마토를 익힌다.
        if graph[nx][ny] == 0:
            today_graph[nx][ny] = 1
    return today_graph

# 입력
m, n = map(int, input().split())
# 입력 받은 모든 토마토 상태 그래프
graph = [list(map(int, input().split())) for _ in range(n)]
# 모든 토마토가 익었을 때의 그래프
finish_graph = copy.deepcopy(graph)
for i in range(n):
    for j in range(m):
        if finish_graph[i][j] == 0:
            finish_graph[i][j] = 1
# 전날 토마토 상태를 저장해두는 그래프
yesterday_graph = [[2] * m for _ in range(n)]
# 토마토가 모두 다 익거나, 더 이상 상태 변화가 없을 때까지
# 루프문을 돌려준다.
today_graph = copy.deepcopy(graph)
# 첫날에도 토마토가 익기 때문에 날짜에 1을 더해준다.
day = 1
# 상하좌우 스캔을 위한 변수
dx = [-1, 1, 0, 0]
dy = [0, 0, -1, 1]
while True:
    # 모든 토마토가 익은 상태인지 확인한다.
    if today_graph == finish_graph:
        # 익었으면 0을 출력하고 스캔을 종료한다.
        print(0)
        break
    # 1. 익은 토마토를 찾는다.
    for i in range(n):
        for j in range(m):
            # 2. 익은 토마토를 찾으면 인접한 모든 토마토를 익힌다.
            if day == 1:
                if graph[i][j] == 1:
                    today_graph = make_ripen(i, j, graph)
            else:
                if yesterday_graph[i][j] == 1:
                    today_graph = make_ripen(i, j, yesterday_graph)
    # 3. 오늘 모든 토마토를 스캔한 후
    # 1) 모든 토마토가 익은 경우
    if today_graph == finish_graph:
        # 날짜를 출력하고 스캔을 종료한다.
        print(day)
        break
    # 2) 전날  그래프와 오늘 그래프가 같은 경우
    if today_graph == yesterday_graph:
        # -1을 출력하고 종료한다.
        print(-1)
        break
    # 4. 계속 바뀌는 상황일 때
    day += 1
    yesterday_graph = copy.deepcopy(today_graph)




