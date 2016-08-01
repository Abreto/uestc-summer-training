# UESTC 2016 Summer Training #17 Div.2. Problem A, by Abreto, 20160728.

def C(n, k):    ## select k elements in n.
    ans = 1;
    for x in range(n, n-k, -1):
        ans *= x;
    for x in range(1, k+1, 1):
        ans /= x;
    return ans;

rocks = raw_input();
k = int(raw_input());
count = {};

for r in rocks:
    if not count.has_key(r):
        count[r] = 1;
    else:
        count[r] += 1;

nrocks = {};
for r in count:
    if not nrocks.has_key(count[r]):
        nrocks[count[r]] = 1;
    else:
        nrocks[count[r]] += 1;

nrockslist = [];
for x in nrocks:
    nrockslist.append(x);
nrockslist.sort();
nrockslist.reverse();

colorgrabbed = 0;
lsize = 0;
nsets = 1;
for i in nrockslist:
    if colorgrabbed < k:
        maybe = colorgrabbed + nrocks[i];
        if maybe <= k:
            lsize += i*nrocks[i];
            colorgrabbed += nrocks[i];
        else:
            lsize += i * (k - colorgrabbed);
            nsets = C(nrocks[i], k-colorgrabbed);
            colorgrabbed = k;


print lsize, nsets;
