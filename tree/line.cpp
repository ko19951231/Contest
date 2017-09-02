#include<cstdio>

int main()
{
    freopen("input07.txt", "w", stdout);
    puts("50000 1 49");
    for(int i=1;i<20000;i++) printf("%d %d\n", i, i+1);
    for(int i=20001;i<50000;i++) printf("%d %d\n", i, i+1);
    puts("1 50000");
}