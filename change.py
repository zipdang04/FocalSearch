line = [0 if x == 0 else 16 - x for x in list(map(int, input().split()))][::-1]
print(*line)