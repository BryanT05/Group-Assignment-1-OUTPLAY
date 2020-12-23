#include <stdio.h>
int ackerman(int m, int n)
{
	if(m==0)
	{
		return n+1;
	}
	
	if(m>0 && n== 0)
	{
		return ackerman(m-1, 1);
	}
	
	if(m > 0 && n > 0)
	{
		return ackerman(m-1, ackerman(m,n-1));
	}
}

int main()
{
	int n, m, result;
	scanf("%d %d", &m, &n);
	
	result = ackerman(m,n);
	
	printf("result: %d\n", result);
	return 0;
}
