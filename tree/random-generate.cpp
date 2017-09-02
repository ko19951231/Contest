#include<cstdio>
#include<cstdlib>

int main()
{
    freopen("input05.txt", "w", stdout);
    int seed=3333;
    srand(seed);
    puts("50000 23 23");
    for(int i=2;i<=50000;i++){
        int rnd=1+rand()%(i-1);
        printf("%d %d\n", rnd, i);
    }
}