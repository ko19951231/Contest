#include<cstdio>

int main()
{
    freopen("input10.txt", "w", stdout);
    puts("50000 25 25");
    //for(int i=2;i<=50000;i++) printf("%d 1\n", i);
    for(int i=2;i<=50000;i++){
        if(i%30==1) printf("%d 1\n", i);
        else printf("%d %d\n", i, i-1);
    }
}