int dair[4][2]={{0,1},{0,-1},{1,0},{-1,0}};
void dfs(int**grid,int x,int y,int m,int n,int*sum,int*sign){
    grid[x][y]=1;
    if(x==0||x==m-1||y==0||y==n-1){      
        *sign=1;
    }//刚开始的时候也要判断，因为可能只有单独一个0在边界上
    for(int i=0;i<4;i++){
        int mx=x+dair[i][0],my=y+dair[i][1];
        if(mx>=0&&mx<m&&my>=0&&my<n&&grid[mx][my]==0){
            if(mx==0||mx==m-1||my==0||my==n-1){      
                *sign=1;
            }
            dfs(grid,mx,my,m,n,sum,sign);
        }
    }
}
int closedIsland(int** grid, int gridSize, int* gridColSize){
    int i,j,sum=0,m=gridSize,n=gridColSize[0];
    for(i=0;i<m;i++){
        for(j=0;j<n;j++){
            int sign=0;
            if(grid[i][j]==0){
                dfs(grid,i,j,m,n,&sum,&sign);
                sum++;
                if(sign==1)
                    sum--;
            }                
        }
    }
    return sum;
}
