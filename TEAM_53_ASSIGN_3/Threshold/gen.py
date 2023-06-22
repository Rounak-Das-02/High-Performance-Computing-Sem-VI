import sys
import random
n = 8192
sys.stdout = open(f'{n}.txt', 'w')
for i in range(n):
    for j in range(n):
        print(random.randint(0, 300), end = " ")
    print()
