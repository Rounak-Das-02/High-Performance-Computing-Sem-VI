import sys
# import random
n = 1024
sys.stdout = open(f'seed_{n}.txt', 'w')
for i in range(n):
    for j in range(n):
        print(0, end = " ")
    print()
