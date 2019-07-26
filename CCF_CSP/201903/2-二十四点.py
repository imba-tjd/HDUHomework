def Do():
    s = input().replace('/','//').replace('x','*')
    r = eval(s)
    if r == 24:
        print('Yes')
    else:
        print('No')

n=int(input())
while n >0:
    Do()
    n = n -1
