# BOJ_7662
from collections import deque
def dual_priority_q(q, command, n):
    if command == 'I':
        q.append(n)
    elif command == 'D':
        if len(q) == 0:
            return
        if n == 1:
            # 최댓값 삭제
            max_num = max(q)
            q.remove(max_num)
        elif n == -1:
            # 최솟값 삭제
            min_num = min(q)
            q.remove(min_num)
    return


# 입력
t = int(input())
for _ in range(t):
    k = int(input())
    q = deque()
    for _ in range(k):
        command, n = map(str, input().split())
        n = int(n)
        dual_priority_q(q, command, n)
    if len(q) == 0:
        print('EMPTY')
    else:
        # print(q)
        print(max(q), min(q))
