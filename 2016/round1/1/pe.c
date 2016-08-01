/* UESTC 2016 Summer Training #1 Div.2.  Problem E. by Abreto, 201607111331. */
#include <stdio.h>
#include <string.h>

int main(void)
{
  int i = 0, j = 0;
  char user_password[128] = " ";
  char entered_password[128] = " ";
  int len_up = 0, len_ep = 0;
  int accepted = 0;

  scanf("%s\n", user_password);
  scanf("%s", entered_password);
  len_up = strlen(user_password);
  len_ep = strlen(entered_password);

  if( len_up == len_ep )
  {
    int n_mistakes = 0;
    for(i = 0;i < len_up;++i)
    {
      if( user_password[i] != entered_password[i] )
        n_mistakes ++;
      if( n_mistakes > 1 )
      {
        accepted = 0;
        goto print_result;
        break;
      }
    }

    if( (0 == n_mistakes) || ( (n_mistakes <= 1) && (len_up >= 8) ) )
    {
      accepted = 1;
      goto print_result;
    } else {
      accepted = 0;
      goto print_result;
    }
  }
  else if ( 1 == (len_up - len_ep) )
  {
    if ( len_up < 8 )
    {
      accepted = 0;
      goto print_result;
    }
    i = 0;
    while(1)
    {
      if( user_password[i] != entered_password[i] )
        break;
      ++i;
    }
    j = i;  /* j points to the entered_password */
    i++;
    for(;i<len_up;)
    {
      if( user_password[i] != entered_password[j] )
      {
        accepted = 0;
        goto print_result;
      }
      i++; ++j;
    }
    accepted = 1;
    goto print_result;
  }
  else
  {
    accepted = 0;
  }

print_result:
  if( accepted )
    printf("yes\n");
  else
    printf("no\n");
  return 0;
}
