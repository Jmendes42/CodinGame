horses = sorted([int(input()) for _ in range(int(input()))]) 
print(min(horses[i + 1] - horses[i] for i in range(len(horses) - 1)))
