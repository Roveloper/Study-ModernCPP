# BOJ_1463
# 입력
n = int(input())


calculate_list = []
def calculation_min(n):
    global calculate_list
    a = calculation_min(n // 3) + 1
    b = calculation_min(n // 2) + 1
    if  n % 2 == 0 and n % 3 == 0:

        return min(a, b) + 1
    elif n % 2 != 0 and n % 3 == 0:


    return min(a, b)
if
# count = 0
# minus_for_3 = 0
# if (n - 1) % 3 == 0:
#     n -= 1
#     count += 1
# while n > 1:
#     print(n, count)
#     if n % 2 != 0 and n % 3 != 0:
#         n -= 1
#         count += 1
#     elif n % 3 == 0:
#         n //= 3
#         count += 1
#     elif n % 2 == 0:
#         n //= 2
#         count += 1
#
# print(count)