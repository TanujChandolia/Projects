#include<bits/stdc++.h>
using namespace std;
bool solFound = false;
int totalCombinations = 0;
vector<unordered_set<int>> block(10);

void printGrid(vector<vector<int>> &sudokuGrid){

   for(int i = 0; i < 9; i++){
      if(i == 0 || i == 3 || i == 6){
         cout<<"-------------------------\n";
      }
      for(int j = 0; j < 9; j++){
         if(j == 0||j == 3 || j == 6){
            cout<<"| ";
         }
         cout<<sudokuGrid[i][j]<<" ";
         if(j == 8)
            cout<<"|";
      }
      cout<<"\n";
   }
   cout<<"-------------------------\n\n";
}

void fillBlocks(vector<vector<int>> &sudokuGrid){

   for(int start = 0; start < 9; start += 3){
      for(int i = start; i < start+3; i++){

         for(int j = 0; j < 3; j++)
            if(sudokuGrid[i][j])
               block[start + 1].insert(sudokuGrid[i][j]);

         for(int j = 3; j < 6; j++)
            if(sudokuGrid[i][j])
               block[start + 2].insert(sudokuGrid[i][j]);

         for(int j = 6; j < 9; j++)
            if(sudokuGrid[i][j])
               block[start + 3].insert(sudokuGrid[i][j]);

      }
   }

   /*for(int i = 1; i < 10; i++){
      cout<<i<<": ";
      for(auto x:block[i])
         cout<<x<<" ";
      cout<<"\n";
   }*/
}

int findBlock(int x, int y){
   if(y < 3){
      if(x < 3) return 1;
      if(x < 6) return 4;
      if(x < 9) return 7;
   }
   if(y < 6){
      if(x < 3) return 2;
      if(x < 6) return 5;
      if(x < 9) return 8;
   }
   if(y < 9){
      if(x < 3) return 3;
      if(x < 6) return 6;
      if(x < 9) return 9;
   }
   return -1;
}

bool cantPlace(vector<vector<int>> &sudokuGrid, int i , int x, int y, int num){
   if(block[num].find(i) != block[num].end())
      return true;

   for(int j = 0; j < 9; j++){
      if(sudokuGrid[x][j] == i && j != y)
         return true;
      if(sudokuGrid[j][y] == i && j != x)
         return true;
   }
   return false;
}

bool recSudoku(vector<vector<int>> &sudokuGrid, int x, int y){
   if(x == 9) return true;

   int num = findBlock(x,y);
   if(sudokuGrid[x][y] != 0){
      if(y + 1 == 9)
         return recSudoku(sudokuGrid,x+1,0);
      else
         return recSudoku(sudokuGrid,x,y+1);
   }
   else{
      for(int i = 1; i <= 9; i++){
         totalCombinations++;
         if(cantPlace(sudokuGrid,i,x,y,num))
            continue;
         sudokuGrid[x][y] = i;
         block[num].insert(i);
         //printGrid(sudokuGrid);
         if(y + 1 == 9){
            if(recSudoku(sudokuGrid,x+1,0))
               return true;
         }
         else{
            if(recSudoku(sudokuGrid,x,y+1))
               return true;
         }

         block[num].erase(i);
         sudokuGrid[x][y] = 0;
      }
   }

   return false;
}

void solveSudoku(vector<vector<int>> &sudokuGrid){
   fillBlocks(sudokuGrid);
   if(recSudoku(sudokuGrid,0,0)){
      solFound = true;
      cout<<"After total Combinations = "<<totalCombinations<<"\n";
      cout<<"The Answer Grid is:\n";
      printGrid(sudokuGrid);
   }
   if(!solFound)
      cout<<"Solution is not possible for this configuration.\n";
}

int main(){
   vector<vector<int>> sudokuGrid = {{ 3, 0, 0  ,   0, 0, 0  ,  0, 0, 0 },
                                     { 5, 2, 9  ,   1, 3, 4  ,  7, 6, 8 },
                                     { 4, 8, 7  ,   6, 2, 9  ,  5, 3, 1 },

                                     { 2, 6, 3  ,   4, 1, 5  ,  9, 8, 7 },
                                     { 9, 7, 4  ,   8, 6, 3  ,  1, 2, 5 },
                                     { 8, 5, 1  ,   7, 9, 2  ,  6, 4, 3 },

                                     { 1, 3, 8  ,   9, 4, 7  ,  2, 5, 6 },
                                     { 6, 9, 2  ,   3, 5, 1  ,  8, 7, 4 },
                                     { 7, 4, 5  ,   2, 8, 6  ,  3, 1, 9 },
                                  };
   printGrid(sudokuGrid);
   solveSudoku(sudokuGrid);
}
/*
3 0 0 0 0 0 0 0 0
5 2 9 1 3 4 7 6 8
4 8 7 6 2 9 5 3 1

2 6 3 4 1 5 9 8 7
9 7 4 8 6 3 1 2 5
8 5 1 7 9 2 6 4 3

1 3 8 9 4 7 2 5 6
6 9 2 3 5 1 8 7 4
7 4 5 2 8 6 3 1 9
*/
