### Solved this on gfg : [link](https://practice.geeksforgeeks.org/problems/number-of-distinct-islands/1)

#### Approach - 1 (DFS + storing path of each island)
```
 ⭐✔️Approach - 1 (DFS + pathMaintain + Visited)
    
        1 1          1 1 
        1     <==>   1    (identical)
        1            1    
        
        1 1          1 1    (not identical, as 2nd one is the reflection, or rotated version of 1st one so, not identical)
        1     !=       1 
        1              1  
    
        explanation :- From above img, all we need to check is the curr island that we visited is identical to any prv islands previously visited or not,
                       for that we somehow need to store the prv islands shape in a data structure (set), and to do that we have 2 logics 
                            1) either store the moves of exploring and comming back from the island 
                                OR
    (Alternative Approach)  2) take the starting cell of each DFS as the base and store all the other islands coordinates by subtracting them from the base
                            as described in the vid by striver : (https://youtu.be/7zmgQSJghpo)
                            
                       lets follow the 1st approach and that we have to just make sure to backtrack ur way white comming back too, so that we do not fail at the below test case.
                        
          An imp edge case - 
            
            3 5              Correct Output :- 2 
            1 1 0 1 1         
            1 0 0 0 1       Output (without backtrack) : 1 (i.e paths -> SRDD, SRDD) 
            1 0 0 0 1       Output (with backtracking) : 2 (i.e paths -> SRBDDBB, SRDDBBB)
        
        
       
        ✅Time : - O(n*m) - DFS
        ✅Space : O(n*m) - visited, un_set
        
        
        
    
```
![App-1](https://user-images.githubusercontent.com/124666305/236748735-ae4e980b-d70e-449d-8004-48192a49b7b5.jpg)

### Code in C++ :- 
```cpp

#include <bits/stdc++.h>
using namespace std;

class Solution {
  private:
    bool isSafeToMove(vector<vector<int>> &grid, vector<vector<bool>> &visited, int row, int col){ // check if the new cell is in range of the grid or not
        
        int rowSize = grid.size();
        int colSize = grid[0].size();
        
        if( (row >= 0 && row < rowSize) && (col >= 0 && col < colSize) && (grid[row][col] == 1) && !visited[row][col])
            return true;
        return false;
        
    }
    
    void DFS(vector<vector<int>> &grid, vector<vector<bool>> &visited, int row, int col, string &currPath){
        
        visited[row][col] = true;
        
        // exploring all the neigh, of curr cells that are not yet visited, and white exploring them make sure to store the path
        // l, r, u, d
        vector<int> deltaRow = {0, 0, -1, +1};
        vector<int> deltaCol = {-1, +1, 0, 0};
        vector<char> currMove = {'L', 'R', 'U', 'D'};
        
        for(int i=0; i < 4; i++){
            int newRow = row + deltaRow[i];
            int newCol = col + deltaCol[i];
            
            // it is safe to move if the next cell is in range,  is a '1' cell (land), is not visited
            if(isSafeToMove(grid, visited, newRow, newCol)){ // if a neigh cell is not yet visited, then explore it 
            
                currPath += currMove[i]; // fetch move that we are going to move unvisited neigh cell
                DFS(grid, visited, newRow, newCol, currPath);
                currPath += 'B';
                //VIP :- now ones we returned from a cell, just add, 'B' (back) to avoid failing at the edge case at start
                
            }
        }
        
    }
    
  public:
    // main fun
    int countDistinctIslands(vector<vector<int>>& grid) {
        
        int rowSize = grid.size();
        int colSize = grid[0].size();
        
        // we need to maintain the visited cells, also we need to maintain the patter of path followed for each island
        vector<vector<bool>> visited(rowSize, vector<bool>(colSize, false));
        unordered_set<string> previousPathsSet;
        
        // apply DFS for all the unvisited land cells of the grid, maintain the 'distinctIslandCount' 
        int distinctIslands = 0;
        
        int index = 0;
        
        for(int row=0; row < rowSize; row++){
            for(int col=0; col < colSize; col++){
                
                if(!visited[row][col] && grid[row][col] == 1){ 
                    // S for start (so that our set doenst store empty string)
                    string currPath = "S"; // maitain the path followed white exploring for each island (for finding the distinct islands)
                    DFS(grid, visited, row, col, currPath); 
    
                    // ones a island is explored, check if a similar path has already been followed for some other island preveously, if yes then this is not a distinct island
                    if( previousPathsSet.find(currPath) == previousPathsSet.end() ){ //curr island is distinct, then store it into this set
                        previousPathsSet.insert(currPath);
                        distinctIslands++;
                    }
                }
            }
            
        }
        
        // // DEBUG
        // cout << "visited paths :- ";
        // for(string s:previousPathsSet){
        //     cout << "{ " << s << " }";  
        // }
        
        return distinctIslands;
    }
};

```
----------------------------------------------------------------------------------------------------------------

#### Approach - 2 (DFS + storing shapes of each island explored)

```⭐✔️Approach -2 (DFS + storing shapes + Visited)
    
        1 1          1 1 
        1     <==>   1    (identical)
        1            1    
        
        1 1          1 1    (not identical, as 2nd one is the reflection, or rotated version of 1st one so, not identical)
        1     !=       1 
        1              1  
    
        explanation :- From above img, all we need to check is the curr island that we visited is identical to any prv islands previously visited or not,
                       for that we somehow need to store the prv islands shape in a data structure (set), and to do that we have 2 logics 
                            1) either store the moves of exploring and comming back from the island 
                                OR
    (Alternative Approach)  2) take the starting cell of each DFS as the base and store all the other islands coordinates by subtracting them from the base
                            as described in the vid by striver : (https://youtu.be/7zmgQSJghpo)
                            
                       lets follow the 2nd approach and that we have to just make sure tostore shapes of each of the islands that we explore, and out of them then we can find the distinct ones
                        
          An imp edge case - 
            
            3 5              Correct Output :- 2 
            1 1 0 1 1         
            1 0 0 0 1       
            1 0 0 0 1       
        
        
       
        ✅Time : - O(n*m) - DFS
        ✅Space : O(n*m) - visited, set
        
           note : just like we can not store <pair> and vecto<pair> as teh key of un_map, but can do it with map
                  similarly for 'un_set' and 'set'
    
  
```
![App-2](https://user-images.githubusercontent.com/124666305/236749046-3f7a557c-b92b-40fc-8d4b-d1cb5f44ba5a.jpg)

```cpp

#include<set>
class Solution {
    
  private:
    bool isSafeToMove(vector<vector<int>> &grid, vector<vector<bool>> &visited, int row, int col){ // check if the new cell is in range of the grid or not
        
        int rowSize = grid.size();
        int colSize = grid[0].size();
        
        if( (row >= 0 && row < rowSize) && (col >= 0 && col < colSize) && (grid[row][col] == 1) && !visited[row][col])
            return true;
        return false;
        
    }
    
    void DFS(vector<vector<int>> &grid, vector<vector<bool>> &visited, vector<pair<int,int>> &currIslandShape, int baseRow, int baseCol, int row, int col){
        
        // whenever we reach a cell, make sure to sub it with the base cell and find the shape, and store it into 'currIslandShape'
        currIslandShape.push_back({row-baseRow, col-baseCol});
        visited[row][col] = true;
         
        // l, r, u, d
        vector<int> deltaRow = {0, 0, -1, +1};
        vector<int> deltaCol = {-1, +1, 0, 0};
        
        for(int i=0; i < 4; i++){
            
            int newRow = row + deltaRow[i];
            int newCol = col + deltaCol[i];
            
            // it is safe to move if the next cell is in range,  is a '1' cell (land), is not visited
            if(isSafeToMove(grid, visited, newRow, newCol)) // if a neigh cell is not yet visited, then explore it 
                DFS(grid, visited, currIslandShape, baseRow, baseCol, newRow, newCol);
        }
    }
    
  public:
    // main fun
    int countDistinctIslands(vector<vector<int>>& grid) {
        
        int rowSize = grid.size();
        int colSize = grid[0].size();
        
        // we need to maintain the visited cells, also we need to maintain the patter of path followed for each island
        vector<vector<bool>> visited(rowSize, vector<bool>(colSize, false));
        //unordered_set< vector<pair<int,int>> > exploredShapes; // stores the shapes of islands that have already been explored
        set<vector<pair<int,int>>> exploredShapes;
        
        // apply DFS for all the unvisited land cells of the grid
        for(int row=0; row < rowSize; row++){
            for(int col=0; col < colSize; col++){
                
                if(!visited[row][col] && grid[row][col] == 1){ 
                    
                    int baseRow = row;
                    int baseCol = col;
                    
                    vector<pair<int,int>> currIslandShape;
                    DFS(grid, visited, currIslandShape, baseRow, baseCol, row, col); 
                    
                    // ones an island is explored, just push its shape into the unorderedSet 'exploredShapes', ( there is no need to check if the curr shape is already present or not because a set never stores duplicates)
                    exploredShapes.insert(currIslandShape);
                }
            }
            
        }
        
        return exploredShapes.size();
    }
};

```
