/* UESTC 2017 Summer Training #32 Div.2. Problem B, by Abreto<m@abreto.net>. */
#include <bits/stdc++.h>

using namespace std;

struct node
{
    int func_name;
    node *prev, *next;
    char deleted;
    node(void):func_name(0),prev(NULL),next(NULL),deleted(0){}
    node(int f, node *p, node *n):func_name(f),prev(p),next(n),deleted(0){}
};
struct func
{
    int name;
    char w[16];
    node *head, *rear;
    func(void):name(0),head(NULL),rear(NULL){w[0]=0;}
};

#define MAXN    100000
func funs[MAXN+128];
node vir[MAXN+128]; int used_vir;
int N;
unordered_map<string, int> name2id;
char H[16];

char vis[MAXN+128];
void swim(int f)
{
    int extended = 0;
    node *p = NULL;
    vis[f] = 1;
    for(p = funs[f].rear;p != NULL;p = p->prev)
    {
        if(vis[p->func_name]) p->deleted = 1;
        else swim(p->func_name);
    }
}
void print(int f)
{
    node *p = NULL;
    printf(" %s", funs[f].w);
    for(p = funs[f].head;p != NULL;p = p->next)
        if(!(p->deleted)) print(p->func_name);
}
int call(int h)
{
    node *cur = NULL;
    for(cur = funs[h].rear;cur != NULL;cur = cur->prev)
    {
        if(vis[cur->func_name]) cur->deleted = 1;
        else swim(cur->func_name);
    }
    printf("%s", funs[h].w);
    for(cur = funs[h].head;cur != NULL;cur = cur->next)
        if(!(cur->deleted)) print(cur->func_name);
    puts("");
}

int main(void)
{
    int i = 0;
    char com[8], val[16];
    scanf("%d", &N); getchar();
    for(i = 0;i < N;++i)
    {
        int nwith = 0;
        scanf("%s %s", com, val);
        if(strcmp(com, "def")) exit(EXIT_FAILURE); /* com must be 'def' */
        name2id[string(val)] = i;
        funs[i].head = funs[i].rear = NULL;
        while(scanf("%s %s", com, val) && 'w' == com[0])
        {
            if(0 == nwith)
            {
                funs[i].head = &(vir[used_vir]);
                vir[used_vir] = node(name2id[string(val)], NULL, NULL);
                used_vir++;
            } else {
                vir[used_vir-1].next = &(vir[used_vir]);
                vir[used_vir] = node(name2id[string(val)], &(vir[used_vir-1]), NULL);
                used_vir++;
            }
            ++nwith;
        }
        if(nwith) funs[i].rear = &(vir[used_vir-1]);
        if('=' != com[0]) while(1); /* com must be '=' */
        strcpy(funs[i].w, val);
    }
    scanf("%s", H);
    call(name2id[string(H)]);
    return 0;
}
