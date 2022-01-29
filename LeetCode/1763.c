

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
 typedef struct
 {
     int x;
     int y;
 }pair;
 int dair[4][2]={{0,1},{0,-1},{1,0},{-1,0}};
int** highestPeak(int** isWater, int isWaterSize, int* isWaterColSize, int* returnSize, int** returnColumnSizes){
    int m=isWaterSize,n=isWaterColSize[0],i,j,head=0,tail=0;
    *returnSize=m;
    *returnColumnSizes=(int*)malloc(sizeof(int)*m);
    int**res=(int**)malloc(sizeof(int*)*m);
    for(i=0;i<isWaterSize;i++){
        (*returnColumnSizes)[i]=n;
        res[i]=(int*)malloc(sizeof(int)*n);
        for(j=0;j<n;j++){
            res[i][j]=-1;
        }
    }
    pair*queue=(pair*)malloc(sizeof(pair)*m*n);
    for(i=0;i<m;i++){
        for(j=0;j<n;j++){
            if(isWater[i][j]){
                res[i][j]=0;
                queue[tail].x=i;
                queue[tail].y=j;
                tail++;
            }
        }
    }
    while(head!=tail){
        int px=queue[head].x,py=queue[head].y;
        for(i=0;i<4;i++){
            int x=px+dair[i][0],y=py+dair[i][1];
            if(x>=0&&x<m&&y>=0&&y<n&&res[x][y]==-1){
                res[x][y]=res[px][py]+1;
                queue[tail].x=x;
                queue[tail].y=y;
                tail++;
            }
        }head++;
    }
    free(queue);
    return res;
}
