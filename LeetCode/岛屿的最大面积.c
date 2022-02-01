int dair[4][2]={{1,0},{-1,0},{0,1},{0,-1}};
    int dfs(int**grid,int x,int y,int m,int n){
        grid[x][y]=0;
        int sum=1;
        for(int i=0;i<4;i++){
            int mx=x+dair[i][0],my=y+dair[i][1],w=0;
            if(mx>=0&&mx<m&&my>=0&&my<n&&grid[mx][my]==1){
                w=dfs(grid,mx,my,m,n);
            }
            sum+=w;
        }
        return sum;
    }
    int maxAreaOfIsland(int** grid, int gridSize, int* gridColSize){
        int max=0,i,j,m=gridSize,n=*gridColSize;
        for(i=0;i<m;i++){
            for(j=0;j<n;j++){
                if(grid[i][j]==1){
                    int w=dfs(grid,i,j,m,n);
                    if(w>max)
                        max=w;
                }
            }
        }
        return max;
    }
