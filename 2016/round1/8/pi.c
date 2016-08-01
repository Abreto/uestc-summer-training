/* UESTC 2016 Summer Training #8 Div.2. Problem I, by Abreto, 201607191652. */
#include <stdio.h>
#include <string.h>

char n[100024] = {0};

int print47(int n1, int n2)
{
  int i = 0;
  for(i = 0;i < n1;++i)
    printf("4");
  for(i = 0;i < n2;++i)
    printf("7");
}

void handle(void)
{
  int nd = strlen(n);
  if( 1 == nd%2 )
  {
    print47((nd+1)/2, (nd+1)/2);
    printf("\n");
  }
  else if( n[0] > '7' )
  {
    print47(nd/2+1, nd/2+1);
    printf("\n");
  }
  else
  {
    int all4 = nd/2, all7 = nd/2;
    int i = 0;
    char ansp1[100024] = {0};int nansp1 = 0;
    for(i = 0;i < nd;++i)
    {
      if( n[i] < '4' )
      {
        ansp1[nansp1] = '4';
        nansp1++;
        --all4;
        break;
      }
      {
      else if( '4' == n[i] )
        ansp1[nansp1] = '4';
        nansp1++;
        --all4;
      }
      else if ( '4' < n[i] && n[i] < '7' )
      {
        ansp1[nansp1] = '7';
        nansp1++;
        --all7;
        break;
      }
      else if( '7' == n[i] )
      {
        ansp1[nansp1] = '7';
        nansp1++;
        --all7;
      }
      else if( n[i] > '7' )
      {
        int j = 0;
        for(j = nansp1-1;j >= 0;--j)
          if( '4' == ansp1[j] )
            break;
        if( j < 0 )
        {
          nansp1 = 0;
          all4 = nd/2 + 1;
          all7 = nd/2 + 1;
          break;
        }
        else
        {
          ansp1[j] = '7';
          ++all4; --all7;
          all7 += nansp1 - j - 1;
          nansp1 = j+1;
          break;
        }
      }
    }

    if( nansp1 < nd )
    {
      for(i = 0;i < nansp1;++i)
        printf("%c", ansp1[i]);
      print47(all4, all7);
      printf("\n");
    }
    else
    {
      if( all4 == all7 )
      {
        for(i = 0;i < nd;++i)
          printf("%c", n[i]);
        printf("\n");
      }
      else
      {
        all4 = nd/2; all7 = n2/2;
        for(i = 0;i < nd;++i)
          if( '7' == n[i] )
          {
            all7--;
            printf("7");
          }
          else
          {
            printf("7");
            all7--;
            break;
          }
        print47(all4, all7);
      }
    }
  }
}

int main(void)
{
  scanf("%s", n);
  handle();
  return 0;
}
