# BOJ_11726
from math import factorial
import time

# 입력
n = int(input())
# start = time.time()
# n을 1과 2의 합으로 구하는 경우의 수와 같다.
# 하지만 1과 2의 조합들을 더하는 순서 또한 고려해줘야한다
# 2로 나눈 값
two_mod = n // 2
count = 0

for i in range(two_mod + 1):
    one_num = n - (i * 2)
    total_num = one_num + i
    count += factorial(total_num) // (factorial(i) * factorial(one_num))
# print(count % 10007, end=' ')
print(count % 10007)
# end = time.time()
# print('-> running time:', round(end - start, 4), '초')