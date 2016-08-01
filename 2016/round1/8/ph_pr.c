#include <stdio.h>

int prime = 0;
int primes[1000000] = {2,0};
int base[1000000] = {1,0};
int nbase = 1;

int is_prime(int x)
{
  int i = 0;

  for(i = 2;i*i <= x;++i)
    if( 0 == (x%i) )
      return 0;
  return 1;
}

int main(void)
{
  for(prime = 2;prime < 1000000;++prime)
    if( is_prime(prime) )
    {
      int tprime = 0;
      tprime = base[nbase-1] * prime;
      primes[nbase-1] = prime;
      if( tprime < 0 )
        break;
      base[nbase++] = tprime;
    }

  printf("int bases[%d] = {%d", nbase, base[0]);
  for(prime = 1;prime < nbase;++prime)
    printf(", %d", base[prime]);
  printf("};\n");
  printf("int primes[%d] = {%d", nbase, primes[0]);
  for(prime = 1;prime < nbase;++prime)
    printf(", %d", primes[prime]);
  printf("};\n");

  return 0;
}
