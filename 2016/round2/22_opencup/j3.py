# UESTC Summer Training Petrozavodsk Summer-2015. Moscow Subregional 2010.
# Problem J, by Abreto.

from decimal import *

line = raw_input();

nums = line.split(' ');

x = float(nums[0]);
y = float(nums[1]);

getcontext().prec = 1024;

print Decimal(x) / Decimal(y)
