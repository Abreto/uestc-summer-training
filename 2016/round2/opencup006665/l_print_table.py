# print
# +----------> j
# |
# |
# |
# |
# i
rows = [[1]]

# 0 for rightward, 1 for upward and so on
dir = [
    [0, +1],    # [di,dj]
    [-1, 0],
    [0, -1],
    [+1, 0]
]

curi = 0
curj = 0
curd = 0
maxni = 1
maxnj = 1

for i in range(2, 1000000001):
    nexti = curi + dir[curd][0]
    nextj = curj + dir[curd][1]
    if nexti >= 0 and nexti < maxni:
        if nextj >= len(rows[nexti]):
            rows[nexti].append(i)
            curi = nexti
            curj = nextj
            if nextj >= maxnj:
                maxnj += 1
                curd = 1
        elif nextj <= 0:
            rows[nexti].insert(0, i)
            curi = nexti
            curj = 0
            if len(rows[nexti]) > maxnj:
                maxnj += 1
                curd = 3
        else:
            if curd == 2:
                rows[nexti].insert(0,i)
                curj = 0
            elif curd == 0:
                rows[nexti].append(i)
                curj = nextj
            curi = nexti
    elif nexti < 0:
        newcol = [i]
        rows.insert(0, newcol)
        maxni = len(rows)
        curi = 0
        curj = 0
        if curd == 1:
            curd = 2
    elif nexti >= maxni:
        newcol = [i]
        rows.append(newcol)
        maxni = len(rows)
        curi = nexti
        curj = 0
        if curd == 3:
            curd = 0

output = "int table[%d][%d] = {"%(len(rows), maxnj)
output += "{%d"%(rows[0][0])
for j in range(1, len(rows[0])):
    output += ",%d"%(rows[0][j])
output += "}"
for i in range(1, len(rows)):
    output += ",{%d"%(rows[i][0])
    for j in range(1, len(rows[i])):
        output += ",%d"%(rows[i][j])
    output += "}"
output += "};"

print output
print "endi: %d" % curi
print "endj: %d" % curj
print "endd: %d" % (curd)
