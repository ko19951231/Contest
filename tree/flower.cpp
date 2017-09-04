#include<cstdio>

int main()
{
    freopen("input16.txt", "w", stdout);
    puts("50000 2 2");
    //for(int i=2;i<=50000;i++) printf("%d 1\n", i);
    for(int i=2;i<=50000;i++){
        if(i%3==0) printf("%d %d\n", i, i-1);
        else printf("%d 1\n", i);
    }
}