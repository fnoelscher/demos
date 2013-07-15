/*
  reddit challenge:
  http://www.reddit.com/r/dailyprogrammer/comments/1hvh6u/070813_challenge_132_easy_greatest_common_divisor/
 */

#include <stdio.h>

long set[] = { 65535 , 4294967295 };

long greatestCommonDivisorLoop(long a, long b);
long greatestCommonDivisorEuclidRecursive(long a, long b);

int main(int argc, char **argv)
{

  long first = greatestCommonDivisorLoop(set[0], set[1]);
  long second = greatestCommonDivisorEuclidRecursive(set[0], set[1]);
  printf("loop version: The greatest common divisor is %ld\n", first);
  printf("euclid recursive version: The greatest common divisor is %ld\n", second);
  
  return 0;
}


// iterate backwards, starting at the smallest of the 2 numbers in the set
// 1st try
long greatestCommonDivisorLoop(long a, long b)
{
  long i;
  if(a <= b)
    i = a;
  else
    i = b;
  
  for(i; i > 0; i--)
    {
      if(! (a % i) &&
	 ! (b % i) )
	{
	  break;
	}
    }
  return i;
}

// recursive euclid algorithm
long greatestCommonDivisorEuclidRecursive(long a, long b)
{
  if(b == 0)
    return a;
  else
    return greatestCommonDivisorEuclidRecursive(b, a % b);
}
