#include<cstdio>
#include<cstdlib>

int main()
{
    freopen("input20.txt", "w", stdout);
    int seed=20;
    srand(seed);
    puts("50000 1 40");
    for(int i=2;i<=50000;i++){
        int rnd=1+rand()%(i-1);
        printf("%d %d\n", rnd, i);
    }
}