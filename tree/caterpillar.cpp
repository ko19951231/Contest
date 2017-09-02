#include<cstdio>
#include<cstdlib>

int main()
{
    freopen("input12.txt", "w", stdout);
    puts("50000 1 49");
    srand(1231);
    for(int i=1;i<10000;i++) printf("%d %d\n", i, i+1);
    for(int i=10001;i<=50000;i++) printf("%d %d\n", i, 1+rand()%10000);
}