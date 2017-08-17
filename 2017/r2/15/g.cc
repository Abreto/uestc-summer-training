/* UESTC 2017 Summer Training #32 Div.2. Problem A, by Abreto<m@abreto.net>. */
#include <bits/stdc++.h>

using namespace std;

#define MAXN    888
int nnum;
int nums[MAXN*MAXN];
int sub(int start, int end, int size) {  
    int mid = (start + end) / 2;  
    int pivot = nums[mid];  
    int i = start - 1, j = end + 1;  
    for (int k = start; k < j; k++) {  
        if (nums[k] < pivot) {  
            i++;  
            int tmp = nums[i];  
            nums[i] = nums[k];  
            nums[k] = tmp;  
        }  
        else if (nums[k] > pivot) {  
            j--;  
            int tmp = nums[j];  
            nums[j] = nums[k];  
            nums[k] = tmp;  
            k--;  
        }  
    }  
    if (i - start + 1 >= size) {  
        return sub(start, i, size);  
    }  
    else if (j - start >= size) {  
        return nums[j - 1];  
    }  
    else {  
        return sub(j, end, size - (j - start));  
    }  
}
int median(void) {  
    return sub(0, nnum-1, (nnum + 1) / 2);
}

int n;
int mat[MAXN][MAXN];

int main(void)
{
    int i = 0, j = 0;
    int q = 0;
    scanf("%d%d", &n, &q);
    for(i = 0;i < n;++i)
        for(j = 0;j < n;++j)
            scanf("%d", &(mat[i][j]));
    while(q--)
    {
        int x1, y1, x2, y2;
        nnum = 0;
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
        for(i = x1-1;i < x2;i++)
            for(j = y1-1;j < y2;j++)
                nums[nnum++] = mat[i][j];
        random_shuffle(nums, nums+nnum);
        printf("%d\n", median());
    }
    return 0;
}
