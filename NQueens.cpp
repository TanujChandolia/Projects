#include<bits/stdc++.h>
using namespace std;
bool printed = false;
int totalSolutins = 0;
void printGrid(vector<vector<int>> &queensGrid){
   printed = true;
   totalSolutins ++;
   int N = queensGrid.size();
   for(int i = 0; i < N; i++){
      for(int j = 0; j < N; j++){
         if(queensGrid[i][j])
            cout<<"Q ";
         else
            cout<<". ";
      }

      cout<<"\n";
   }
   cout<<"\n";
}
bool cantPlace(vector<pair<int,int>> queens, int row, int i){
   if(row == 0)
      return false;

   for(int j = 0; j < row; j++){
      if(queens[j].second == i){
         //cout<<"same col: "<<row<<","<<i<<"\n";
         return true;
      }
      float x = queens[j].first*(1.00);
      float y = queens[j].second*(1.00);

      if(abs(row-x)/(abs(y-i)*(1.00)) == 1){
         //cout<<"Same diagonal: "<<row<<","<<i<<"\n";
         return true;
      }
   }

   return false;
}
bool recQueens(vector<vector<int>> &queensGrid,vector<pair<int,int>> queens, int N, int row){
      if(row == N) return true;

      for(int i = 0 ; i < N; i++){
         if(cantPlace(queens,row,i)){
            continue;
         }
         //cout<<"Pushed: "<<row<<","<<i<<"\n";
         queens.push_back({row,i});
         queensGrid[row][i] = 1;
         if(recQueens(queensGrid, queens, N, row+1) == true)
            printGrid(queensGrid);
         queens.pop_back();
         queensGrid[row][i] = 0;
      }
      return false;
}
void NQueens(int N){
   vector<vector<int>> queensGrid(N,vector<int>(N,0));
   vector<pair<int,int>> queens;
   recQueens(queensGrid,queens,N,0);
   if(!printed)
      cout<<"No possible board\n";
   cout<<"Total Solutions: "<<totalSolutins<<"\n";
}
int main(){
   int N; cin >> N;
   NQueens(N);
}
