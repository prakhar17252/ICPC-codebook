from sys import stdin, stdout, setrecursionlimit

stdin = open('input.txt', 'r')
stdout = open('output.txt', 'w')

inp = int(stdin.readline())   # Similar to input()
stdout.write(str(inp))     # Use only with strings

setrecursionlimit(1000000)
