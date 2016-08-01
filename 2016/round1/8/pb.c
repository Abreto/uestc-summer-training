/* UESTC 2016 Summer Training #8 Div.2. Problem B, by Abreto, 201607191226. */
#include <stdio.h>

#define GUARANTEE(x) ( ((x)<0)?0:(x) )

int main(void)
{
  int cal = 0;
  int fat = 0, car = 0, pro = 0;

  while(1)
  {
    scanf("%d %d %d %d", &cal, &fat, &car, &pro);

    if( (0 == cal) && (0 == fat) && (0 == car) && (0 == pro) )
      break;
    else
    {
      double maxfat = (double)fat + 0.5, minfat = GUARANTEE((double)fat - 0.5);
      double maxcar = (double)car + 0.5, mincar = GUARANTEE((double)car - 0.5);
      double maxpro = (double)pro + 0.5, minpro = GUARANTEE((double)pro - 0.5);
      double maxcal = maxfat*(double)9 + (maxcar+maxpro)*(double)4;
      double mincal = minfat*(double)9 + (mincar+minpro)*(double)4;
      int maxcalrounded = (int)(maxcal+0.5);
      int mincalrounded = (int)(mincal+0.5);

      if(  mincal <= (double)cal && (double)cal < maxcal )
        printf("yes\n");
      else
        printf("no\n");
    }
  }

  return 0;
}
