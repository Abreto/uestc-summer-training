# UESTC Summer Training Petrozavodsk Summer-2015. Moscow Subregional 2010.
# Problem J, by Abreto.

def getexp(nstr):
    i = 0;
    while nstr[i] == '0' or nstr[i] == '.':
        i += 1;
    return i-1;

line = raw_input();

nums = line.split(' ');

x = float(nums[0]);
y = float(nums[1]);

expx = getexp(nums[0]);
expy = getexp(nums[1]);

for i in range(expx):
    x *= 10;
for i in range(expy):
    y *= 10;

#print x,y;

n = x / y;
n = float(str(n));
if expx > 0 and expy > expx:
    expy = expy - expx;
    expx = 0;
elif expy > 0 and expy < expx:
    expx = expx - expy;
    expy = 0;
for i in range(expx):
    n /= 10;
    #print n;
while expy > 0:
    n *= 10;
    expy -= 1;
    if n == int(n):
        break;

#print int(n);
zeros = ['0'] * expy;
ans = str(int(n));
for x in zeros:
    ans += x;
print ans;
