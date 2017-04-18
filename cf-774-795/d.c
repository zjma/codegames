#include<stdio.h>

#define rng(i,begin,end) for (int i=begin;i<end;++i)


int v2c[100001];
int a[100000];
int b[100000];

int main()
{
    int n,l,r;
    scanf("%d", &n);
    scanf("%d", &l);
    scanf("%d", &r);
    --l;--r;
    rng(i,0,n){
        scanf("%lld", &a[i]);
    }
    rng(i,0,n){
        scanf("%lld", &b[i]);
    }
    int ans=1;
    rng(i,0,l){
        ans=ans&&a[i]==b[i];
    }
    rng(i,r+1,n){
        ans=ans&&a[i]==b[i];
    }
    rng(i,l,r+1){
        v2c[a[i]]++;
        v2c[b[i]]--;
    }
    rng(i,0,100001){
        ans=ans&&v2c[i]==0;
    }
    if (ans)
        printf("TRUTH\n");
    else
        printf("LIE");
    return 0;
}
