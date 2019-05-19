#include <stdio.h>
#define DEBUG
int main()
{
	int i;
	int sum=0;
	for(i=0;i<10;i++)
	{
		sum+=i;
	}
#ifdef DEBUG
	printf("sum=%d\n",sum);
#endif
	return 0;
}
