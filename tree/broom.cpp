#include<cstdio>
#include<cstdlib>

int main()
{
    freopen("input14.txt", "w", stdout);
    puts("50000 1 49");
    for(int i=2;i<=50000;i++){
        if(i>10000&&i<=30000) printf("%d 1\n", i);
        else if(i>30000) printf("%d 10000\n", i);
        else printf("%d %d\n", i, i-1);
    }
}