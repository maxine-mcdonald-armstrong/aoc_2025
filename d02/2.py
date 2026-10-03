def is_repeat(x: int):
    s = str(x)
    success = False
    for l in range(1, len(s)):
        if s == s[:l] * (len(s) // l):
            success = True
    return success

with open("in.txt", "r") as file:
    line = file.readline()
    ranges = [[int(b) for b in a.split("-")] for a in line.split(",")]
    ans = 0
    for l, r in ranges:
        for i in range(l, r+1):
            if is_repeat(i):
                ans += i
    print(ans)

