/* UESTC 2016 Summer Training #13 Div.2. Problem A, by Abreto, 20160725. */
#include <stdio.h>
#include <string.h>

#define MIN(a, b) (((a)<(b))?(a):(b))
#define YUELIMITION 3037000499

typedef long long int ll;
typedef struct _frac
{
  ll a;
  ll b;  /* a / b  */
}frac, *p_frac;

void yue_force(p_frac f)
{
  ll fact = MIN(f->a, f->b);
  while (fact > 1)
  {
    if( (0 == (f->a) % fact) && (0 == (f->b) % fact) )
    {
      f->a /= fact;
      f->b /= fact;
      fact = MIN(f->a, f->b);
    }
    else
      --fact;
  }
}

void yue(p_frac f)
{
  if( f->a >= YUELIMITION || f->b >= YUELIMITION )
    yue_force(f);
}

frac add(frac f1, frac f2)
{
  ll na = f1.a * f2.b + f2.a * f1.b;
  ll nb = f1.b * f2.b;
  frac nf = {na, nb};
  yue(&nf);
  return nf;
}

char rep[16] = {0};
frac res;

void handle_int(int s, int e)
{
  if( s <= e )
  {
    int digit = e - s + 1;
    int i = 0;
    frac toadd = {0,1};
    for(i = 0;i < digit;++i)
      toadd.a = toadd.a * 10 + (rep[s+i]-'0');
    res = add(res, toadd);
  }
}

void handle_fixed(int s, int e)
{
  if( s <= e )
  {
    int i = 0;
    int digit = e - s + 1;
    frac toadd = {0,1};
    for(i = 0;i < digit;++i)
    {
      toadd.a = toadd.a*10 + (rep[s+i]-'0');
      toadd.b *= 10;
    }
    res = add(res, toadd);
  }
}

void handle_loop(int poi, int s, int e)
{
  if( s <= e )
  {
    int i = 0;
    int digit = e - s + 1;
    frac toadd = {0,0};
    for(i = 0;i < digit;++i)
    {
      toadd.a = toadd.a * 10 + (rep[s+i]-'0');
      toadd.b = toadd.b * 10 + 9;
    }
    digit = s - poi - 2;
    for(i = 0;i < digit;++i)
      toadd.b *= 10;
    res = add(res, toadd);
  }
}

void handle()
{
  int i = 0, j = 0, k = 0;
  int len = strlen(rep);
  res.a = 0;
  res.b = 1;
  for(i = 0;i < len;i++)
    if( '.' == rep[i] )
      break;
  handle_int(0, i-1);
  for(j = i+1;j < len;++j)
    if('(' == rep[j])
      break;
  handle_fixed(i+1, j-1);
  for(k = j+1;k < len;++k)
    if( ')' == rep[k] )
      break;
  handle_loop(i, j+1, k-1);
}

int main(void)
{
  int i = 0, T = 0;

  scanf("%d", &T);
  for(i = 0;i < T;++i)
  {
    scanf("%s", rep);
    handle();
    yue_force(&res);
    printf("Case #%d: %lld/%lld\n", i+1, res.a, res.b);
  }

  return 0;
}
