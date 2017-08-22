/* UESTC 2017 Summer Training #33 Div.2. Problem C, by Abreto<m@abreto.net>. */
#include <bits/stdc++.h>

using namespace std;

int m,  /* rows */
    n;  /* cols */
char world[32][32];
int own_force[32];
int dispatch_force[32];
int support_force[32];
set<int> adj[32];
int saruman_force;
set<int> app_countries;
int n_human_countries;
int countries_alive;
int ruined[32];

void clear(void)
{
    int i = 0;
    for(i = 0;i < 26;++i)
    {
        support_force[i] = ruined[i] = 0;
        adj[i].clear();
    }
    app_countries.clear();
    n_human_countries = 0;
}

int one_attack(void)
{
    int i = 0;
    int selected_attack_country = -1;
    int minimal_force = 1000000000;
    /* select who to attack */
    for(i = 0;i < n_human_countries;++i)
        if(0 == ruined[i] && own_force[i]+support_force[i] < minimal_force)
        {
            selected_attack_country = i;
            minimal_force = own_force[i] + support_force[i];
        }
    if(minimal_force >= saruman_force) return 0;
    else
    {
        ruined[selected_attack_country] = 1;
        for(auto adjc:adj[selected_attack_country])
        {
            own_force[adjc] -= dispatch_force[adjc];
            support_force[adjc] -= dispatch_force[selected_attack_country];
        }
        return 1;
    }
}

void proc(void)
{
    int i = 0, j = 0;
    for(i = 0;i < m;++i)
    {
        scanf("%s", world[i]);
        for(j = 0;j < n;++j)
            world[i][j] -= 'A';
    }
    for(i = 0;i < m;++i)
        for(j = 0;j < n;++j)
        {
            app_countries.insert(world[i][j]);
            if((j+1 < n) && (world[i][j] != world[i][j+1]))
            {
                adj[world[i][j]].insert(world[i][j+1]);
                adj[world[i][j+1]].insert(world[i][j]);
            }
            if((i+1 < m) && (world[i][j] != world[i+1][j]))
            {
                adj[world[i][j]].insert(world[i+1][j]);
                adj[world[i+1][j]].insert(world[i][j]);
            }
        }
    countries_alive = n_human_countries = app_countries.size();
    for(i = 0;i < n_human_countries;++i)
    {
        scanf("%d", own_force+i);
        dispatch_force[i] = own_force[i] / (adj[i].size() + 1);
        for(auto adjc:adj[i])
            support_force[adjc] += dispatch_force[i];
    }
    scanf("%d", &saruman_force);
    while(countries_alive)
    {
        int status = one_attack();
        if(0 == status)
        {
            puts("Human");
            return;
        }
        else countries_alive--;
    }
    puts("Saruman");
}

int main(void)
{
    int T = 0;
    scanf("%d", &T);
    while(T--)
    {
        scanf("%d %d", &m, &n);
        clear();
        proc();
    }
    return 0;
}
