#include<stdio.h>
int main()
{
    int n;
    int n1,n2;
    printf("enter the sign (+,-,*,/) = \n");
    scanf("%d",n);
    printf("enter two numbers = \n");
    scanf("%d %d",&n1, &n2);
    switch(n)
    {
        case '+':
        printf("%d + %d = %d\n",n1,n2,n1+n2);
        break;
        case '-':
        printf("%d-%d=%d\n",n1-n2);
        break;
        case '*':
        printf("%d*%d=%d\n",n1*n2);
        break;
        case '/':
        printf("%d/%d=%d\n",n1/n2);
        break;
        default:
        printf("INVALID");

    }
    return 0;
}