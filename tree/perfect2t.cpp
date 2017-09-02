#include<cstdio>
#include<cstdlib>

int main()
{
    freopen("input15.txt", "w", stdout);
    puts("50000 1 49");
    for(int i=2;i<=50000;i++) printf("%d %d\n", i, i/2);
}