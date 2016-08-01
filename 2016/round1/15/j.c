/* UESTC 2016 Summer Training #15 Div.2. Problem J, by Abreto, 20160727. */
#include <stdio.h>

typedef long long int ll;

ll x[4] = {0}; /* 0A, 1B, 2C, 3D */
ll y[4] = {0};
ll z[4] = {0};
ll vx[16] = {0};
ll vy[16] = {0};
ll vz[16] = {0};

ll len2(int i)
{
  return ( vx[i]*vx[i] + vy[i]*vy[i] + vz[i]*vz[i] );
}

void mkvector(int ans, int s, int e)
{
  vx[ans] = x[e] - x[s];
  vy[ans] = y[e] - y[s];
  vz[ans] = z[e] - z[s];
}

ll inner(int v1, int v2)
{
  return ( vx[v1] * vx[v2] + vy[v1] * vy[v2] + vz[v1] * vz[v2] );
}

void outter(int ans, int l, int r)
{
  vx[ans] = vy[l] * vz[r] - vy[r] * vz[l];
  vy[ans] = vx[r] * vz[l] - vx[l] * vz[r];
  vz[ans] = vx[l] * vy[r] - vx[r] * vy[l];
}


int main(void)
{
  int i = 0;

  for(i = 0;i < 4;++i)
    scanf("%lld %lld %lld", &(x[i]), &(y[i]), &(z[i]));
  mkvector(0, 0, 1);  /* vectorAB */
  mkvector(1, 2, 3);  /* vectorCD */

  /* if orthogonal */
  if( 0 != inner(0,1) )
  {
    printf("Invalid\n");
  }
  else
  {
    /* if in the same plane; */
    outter(2, 0, 1); /* normal vector:ABxCD */
    mkvector(3, 0, 2);  /* AC */
    mkvector(4, 0, 3);  /* AD */
    if( (0 != inner(2,3)) || (0 != inner(2,4)) )
    {
      printf("Invalid\n");
    }
    else
    {
      mkvector(5, 1, 2);  /*BC*/
      mkvector(6, 1, 3);  /*BD*/
      if( inner(0,5) >= 0 )  /* AB·BC */
      {
        if( len2(5) < len2(6) )
        {
          outter(7, 0, 5);  /*ABxBC*/
          outter(8, 0, 6);  /*ABxBD*/
          if( inner(7,8) < 0 )
            printf("Invalid\n");
          else
            printf("Valid\n");
        }
        else
          printf("Invalid\n");
      }
      else
      {
        printf("Invalid\n");
      }
    }
  }

  return 0;
}
