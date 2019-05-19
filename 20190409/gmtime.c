#include <stdio.h>
#define MAX 100
#define max(a,b) ((a)>(b)?(a):(b)) //宏定义，执行-E 之后被替换
int main()
{
	 printf("MAX=%d\n",MAX);
	  printf("max(3,4)=%d\n",max(3,4));
	  return 0;
}
