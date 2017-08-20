/* Osipovsky Cup 2014 (partially SYSU-Aug-2014 contest). Problem A, by Abreto<m@abreto.net>. */
#include <bits/stdc++.h>

using namespace std;

int n_string;   /* 0 is null str. */
int string_length[1024];
char string_store[1024][128];

struct html_tag;
struct html_tag
{
    int name;
    int id;
    vector<int> classes;
    int rep;
    html_tag *child, *sibling;
    html_tag(void)
    {
        name = id = 0;
        rep = 1;
        classes.clear();
        child = sibling = NULL;
    }
};
void add_child(html_tag *par, html_tag *ch)
{
    html_tag *p = par->child;
    if(NULL == p) par->child = ch;
    else
    {
        while(p->sibling) p = p->sibling;
        p->sibling = ch;
    }
}

void render(html_tag *root)
{
    if(NULL == root) return;
    for(int i = 0;i < root->rep;++i)
    {
        if(root->name)
        {
            printf("<%s", string_store[root->name]);
            if(root->id) printf(" id=\"%s\"", string_store[root->id]);
            if(root->classes.size())
            {
                printf(" class=\"%s", string_store[root->classes[0]]);
                for(int i = 1;i < root->classes.size();++i)
                    printf(" %s", string_store[root->classes[i]]);
                putchar('"');
            }
            putchar('>');
        }
        render(root->child);
        if(root->name)
        {
            printf("</%s>", string_store[root->name]);
        }
    }
    render(root->sibling);
}

int n_tags; /* 0 is document root */
html_tag tags[1024];

int slen;
char src[1024];

#define VALIDNAME(c)    ((((c)>='A')&&((c)<='Z'))||(((c)>='a')&&((c)<='z'))||(((c)>='0')&&((c)<='9')))
#define VALIDIGIT(c)    (((c)>='0')&&((c)<='9'))
void proc(void)
{
    int i = 0, j = 0, k = 0;
    html_tag *par = &(tags[0]);
    stack<html_tag*> pars;
    for(i = 0;i < slen;++i)
    {
        if('(' == src[i])
        {
            pars.push(par);
        } else if (')' == src[i]) {
            par = pars.top();
            pars.pop();
        } else {    /* proccess one tag */
            html_tag *cur = &(tags[++n_tags]);
            cur->name = ++n_string;
            for(j = i;j < slen && VALIDNAME(src[j]);++j)
                string_store[cur->name][string_length[cur->name]++] = src[j];
            while(j < slen && src[j] != '>' && src[j] != ')')
            {
                if('.' == src[j])
                {
                    int newstring = ++n_string;
                    for(k = j+1;k < slen && VALIDNAME(src[k]);++k)
                        string_store[newstring][string_length[newstring]++] = src[k];
                    cur->classes.push_back(newstring);
                    j = k;
                } else if ('#' == src[j]) {
                    int newstring = ++n_string;
                    for(k = j+1;k < slen && VALIDNAME(src[k]);++k)
                        string_store[newstring][string_length[newstring]++] = src[k];
                    cur->id = newstring;
                    j = k;
                } else if ('*' == src[j]) {
                    int rpts = 0;
                    for(k = j+1;k < slen && VALIDIGIT(src[k]);++k)
                    {
                        rpts *= 10;
                        rpts += (src[k] - '0');
                    }
                    cur->rep = rpts;
                    j = k;
                }
            }
            add_child(par, cur);
            par = cur;
            if(j < slen && src[j] == '>') i = j;
            else i = j - 1;
        }
    }
}

int main(void)
{
    scanf("%s", src);
    slen = strlen(src);
    proc();
    render(&(tags[0]));
    puts("");
    return 0;
}
