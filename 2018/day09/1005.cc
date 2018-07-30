#include <cstdio>
#include <vector>

using namespace std;

int mat[2048][2048];
vector<int> l[2048];

int main(void)
{
    int n = 2000;
    int block_per_line = 42;
    int num_in_block = n / block_per_line;
    int ncnt = 0;
    for(int i = 0;i < n;i++)
    {
        int offset = i / num_in_block;
        int line_of_block = i - offset * num_in_block;
        /* first block of line */
        if(offset < num_in_block)
        {
            l[i].push_back(offset);
            mat[i][offset] = 1;
            ncnt++;
        }
        for(int j = 1;j*num_in_block < n;j++)
        {
            int base = j * num_in_block;
            int right = (offset * (j-1) + line_of_block) % num_in_block;
            mat[i][base+right] = 1;
            l[i].push_back(right);
            ncnt++;
        }
    }
    printf("Number of 1s: %d\n", ncnt);
    for(int i = 0;i < n;i++)
    {
        for(auto off : l[i])
            printf("%d ", off);
        puts("");
    }
    printf("%d\n", n);
    for(int i = 0;i < n;i++)
    {
        for(int j = 0;j < n;j++)
            printf("%d", mat[i][j]);
        puts("");
    }
    return 0;
}