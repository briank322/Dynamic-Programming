#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>
#include <cstring>

int x_cor[500];
int y_cor[500];
int sol[7][200][200][200];
const int inf = 0x3f3f3f3f;
int num_points;

using namespace std;
bool isLeft(int i, int j, int k){

    if((x_cor[k] - x_cor[i])*(y_cor[j]- y_cor[i])- (y_cor[k] - y_cor[i])*(x_cor[j] - x_cor[i]) > 0){
        
        return true;
    }
    else{
        return false;
    }


}



        
int twicearea(int i, int j, int k){


    int sol = 0;
    sol = abs(x_cor[i]*y_cor[j]+ x_cor[j]*y_cor[k] + x_cor[k]*y_cor[i] - x_cor[j]*y_cor[i] - x_cor[k]*y_cor[j] - x_cor[i]*y_cor[k]);
    return sol;


}
        
        

int opt(int e,int i,int j,int k){
    
    //if computed
    if(sol[e][i][j][k] != -1){
        
        return sol[e][i][j][k];
        
        
    }
    
    
    else if((y_cor[i]<=y_cor[j])&&(y_cor[i]<=y_cor[k]) && isLeft(i,j,k)){
        int mintemp = inf;
        
    //call opt
        for(int l =0; l<num_points; l++){
            
           if(isLeft(k,l,j)
              &&y_cor[j]>=y_cor[i] 
              &&!isLeft(i,k,j) 
             ) 
           {
               mintemp =  min(mintemp, opt(e-1, i,k,l));
               
           }
        
        }
        mintemp = mintemp + twicearea(i,j,k);
        sol[e][i][j][k] = mintemp ;
        
        
        return mintemp;
        
        
    }
    else{
        return inf;
    }



}


int main()
{
    
    cin >> num_points;
    x_cor[num_points] = 0;
    y_cor[num_points] = 0;
    //inf for sol 4d array  
    memset(sol, -1, sizeof(sol));
    
    
    for(int i = 0; i< num_points; i++){
        int x,y;
        cin >> x >> y;
        x_cor[i] = x;
        y_cor[i] = y;
       
    }
    
    
    //base case
    for(int i = 0; i<num_points; i++){
        for(int j = 0; j<num_points; j++){
            for(int k = 0; k<num_points; k++){
            
                // i should be the lowest point
                
                if((y_cor[i]<=y_cor[j])&&(y_cor[i]<=y_cor[k]) && isLeft(i,j,k))
                {   //valid triangle
                    sol[3][i][j][k] = twicearea(i,j,k);
                }
                else{
                    
                    sol[3][i][j][k] = inf;
                }
            
            }
       }
    }
    //inf value for initialzing answer
    int answer = inf;
    //solution
    for(int i = 0; i<num_points; i++){
        for(int j = 0; j<num_points; j++){
            for(int k = 0; k<num_points; k++){
            
                answer = min(answer, opt(6,i,j,k));
            
            
            }
       }
    }
    
    cout<<fixed<<answer/2.0;
    
}

