#with open("sample.txt", "r") as f:
with open("in.txt", "r") as f:
    lines = f.readlines()
    lists = []
    for i in range(4):
        for j, x in enumerate(map(int, lines[i].split())):
            if (i == 0):
                lists.append([x])
            else:
                lists[j].append(x)
    ans = 0
    for i, c in enumerate(lines[4].split()):
        if c == '+':
            ans += sum(lists[i])
        else:
            k = 1
            for x in lists[i]:
                k *= x
            ans += k
    print(ans)

