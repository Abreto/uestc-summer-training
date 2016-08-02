#!/bin/bash
node bgen > b.in
./b < b.in > b1.out
./b2 < b.in > b2.out
diff -s b1.out b2.out
