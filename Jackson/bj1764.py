n, m = map(int, input().split())

uni = set()
result = []
for i in range(n + m):
    name = input()
    if name in uni:
        result.append(name)
        continue
    uni.add(name)
    
print(len(result))
result.sort()
for i in result:
  print(i)
