# BOJ_10026
# 빨 초 파 각각 덩어리로 보는 갯수와
# 빨 = 초, 파를 각각 덩어리로 보는 갯수를 구하고 싶다.
# 1. 빨 초 파 각각 덩어리로 보는 갯수
# 색을 저장하고 같은 색이 모두 나올 때까지 돌리기
# 파란색 덩어리수는 같고, 빨 = 초만 다르게 구현해주면 된다.
# 애초에 색약 있을 때는 그래프에서 G부분을 R로 모두 바꿔준다.
import sys
sys.setrecursionlimit(10**6)

# dfs
def dfs(x, y, graph):
    global pre_color
    if x < 0 or x >= n or y < 0 or y >= n:
        return False
    # print(x, y, ':', graph[x][y], pre_color)
    # 지정 범위 내에 현재 컬러를 저장해둔다.
    tmp_color = graph[x][y]
    if graph[x][y] == pre_color and visited[x][y] == False:
        # 지나간 자리는 블랙으로 색칠해준다.
        visited[x][y] = True
        for i in range(4):
            nx = x + dx[i]
            ny = y + dy[i]
            pre_color = tmp_color
            dfs(nx, ny, graph)
        return True
    return False


# 색을 판단해주는 함수
def add_color_chunk(x, y, graph):
    global red, green, blue
    if graph[x][y] == 'R':
        red += 1
        return
    elif graph[x][y] == 'G':
        green += 1
        return
    elif graph[x][y] == 'B':
        blue += 1
        return


# 입력
n = int(input())
graph_3color = [list(map(str, input())) for _ in range(n)]
# 각 칼라 구역의 갯수를 나타낸다.
red, green, blue = 0, 0, 0
# DFS에서 상하좌우 움직이기 위한 변수
dx = [-1, 1, 0, 0]
dy = [0, 0, -1, 1]
# 방문했는지 보여준다.
visited = [[False] * n for _ in range(n)]
# 색약 없는 사람
for i in range(n):
    for j in range(n):
        pre_color = graph_3color[i][j]
        if dfs(i, j, graph_3color):
            add_color_chunk(i, j, graph_3color)
# print(red, green, blue)
print(red + green + blue, end=" ")


# 색약이 보는 그래프 만들어주기
# 색약 있는 사람(녹색을 빨간색으로 본다고 가정한다.)
graph_2color = graph_3color
for i in range(n):
    for j in range(n):
        if graph_2color[i][j] == 'G':
            graph_2color[i][j] = 'R'


# 각 칼라 구역의 갯수를 다시 리셋해준다.
red, green, blue = 0, 0, 0
# 방문 기록도 다시 리셋해준다.
visited = [[False] * n for _ in range(n)]
# 색약 있는 사람
for i in range(n):
    for j in range(n):
        pre_color = graph_2color[i][j]
        if dfs(i, j, graph_2color):
            add_color_chunk(i, j, graph_2color)
# print(red, green, blue)
print(red + green + blue)


