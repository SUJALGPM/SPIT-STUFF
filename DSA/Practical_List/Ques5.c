// 5. Evaluation of Postfix expression using Stack.

#include<stdio.h>
#include <math.h>
#include<malloc.h>
#include<string.h>
#include<stdlib.h> 
#include<ctype.h>

struct stack{
    int size;
    int *arr;
    int top;
}s1;

void init(int len)
{
    s1.size=len;
    s1.arr=(int *)malloc(sizeof(int)*s1.size);
    s1.top=-1;
}


int isEmpty()
{
    return s1.top==-1;
}
 
void push(int item)
{
    if(s1.top==s1.size-1)
    {
        printf("Stack overflow\n");
    }
    else
    {
        s1.arr[++s1.top]=item;
    }
}

int pop ()
{
    if(isEmpty())
    {
        return -1;
    }
    else
    {
        return s1.arr[s1.top--];
    }
}
int peak()
{
    if(isEmpty())
    {
        return -1;
    }
    return s1.arr[s1.top];
}

int evaluate(char *s)
{
    int i;
    for(i=0;i<strlen(s);i++)
    {
        if(isdigit(s[i]))
        {
            int m =s[i]-'0';
            push(m);
        }
        else
        {
            int n1=pop();
            int n2=pop();
            int ans;
            switch(s[i])
            {
                case '+':
                ans = n2+n1;
                break;
                
                case '-':
                ans= n2-n1;
                break;
                
                case '/':
                ans = n2/n1;
                break;
                
                case '*':
                ans = n2*n1;
                break;
                
                case '^':
                ans = pow(n2,n1);
                break;
                
                default:
                printf("unsupported operator");
                return -1;
            }
            push(ans);
        }
        
        
    }
    return peak();
    
}

int main()
{
    char s[100];
    printf("enter the postfix expression");
    scanf("%s",s);
    int len=strlen(s);
    init(len);
    int result = evaluate(s);
    printf("Result: %d",result);
    return 0;
}