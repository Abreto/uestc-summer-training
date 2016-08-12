# UESTC Summer Training Petrozavodsk Summer-2015. Moscow Subregional 2010.
# Problem J, by Abreto.

line = raw_input();

nums = line.split(' ');

x = float(nums[0]);
y = float(nums[1]);

print x,y;

if x > 1:
    print int(x / y);
else:
    lx = len(nums[0]);
    if lx < 12:
        print int(x/y);
    else:
        print x;
