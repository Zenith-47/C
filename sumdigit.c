#include<stdio.h>
int main()
{
    int num=1234,sum = 0;
    int i;
    while(num>0)
    {
    sum+=num%10;
    num=num/10;
    }
    printf("sum of digits = %d\n",sum);
    return 0; 
}