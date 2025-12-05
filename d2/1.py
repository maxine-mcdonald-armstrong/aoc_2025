def is_repeat(x: int):
    s = str(x)
    if len(s) % 2 != 0:
        return False
    return s[:len(s)//2] == s[len(s)//2:]

with open("in.txt", "r") as file:
    line = file.readline()
    ranges = [[int(b) for b in a.split("-")] for a in line.split(",")]
    ans = 0
    for l, r in ranges:
        for i in range(l, r+1):
            if is_repeat(i):
                ans += i
    print(ans)

