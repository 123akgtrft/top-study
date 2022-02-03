int findMinFibonacciNumbers(int k){
    int n=0,i=0,j,sum=0,count=1;
    long long F[45];
    F[0]=1;
    F[1]=1;
    for(i=2;i<45;i++)
        F[i]=F[i-1]+F[i-2];
    while(F[n+1]<=k)
        n++;
    sum=F[n];
    if(sum==k)
        return 1;
    else{
        for(j=n;j>=0;){
            if(sum+F[j]>k)
            j--;
            else if(sum+F[j]<k){
                sum+=F[j];
                count++;
            }
            else{
                count++;
                break;
            }
        }
    }
    return count;
}
