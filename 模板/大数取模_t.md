```c++
 int mod(char str[],int c)
{
    int number[100];
    for(int i=0;i<strlen(str);i++)
     number[i]=str[i]-'0';
    int sum=0;
    for(int i=0;i<strlen(str);i++)
    {
        sum=((long long)sum*10+number[i])%c;
    }
    return sum;
}
```