#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>

using namespace std;

int credit[10000];
int cust_x[5000];
int cust_y[5000];
int solution[2000][2000];

//Man. Distance for two locations
int dist(int cust1_x, int cust1_y, int cust2_x, int cust2_y){

    int delta_x = abs(cust1_x - cust2_x);
    int delta_y = abs(cust1_y - cust2_y);
    int sum = delta_x + delta_y;
    return sum;
}


int opt(int lastdayone, int lastdaytwo){
    
    if (solution[lastdayone][lastdaytwo] != 0){
      
        return solution[lastdayone][lastdaytwo];
    }
    
    solution[lastdayone][lastdaytwo] = 1000000000;
    
    // if we don't know the second to the last customer for day2
    if(lastdayone == (lastdaytwo-1)){
        for(int k = 0; k<lastdaytwo-1; k++){
            
        solution[lastdayone][lastdaytwo] =
       min((opt(lastdayone, k)+ 
         dist(cust_x[k],cust_y[k],cust_x[lastdaytwo], cust_y[lastdaytwo])+
         credit[lastdaytwo]),
         solution[lastdayone][lastdaytwo]);
            
    
    }
    }
    
    // we know last customer and second to the last customer for day2
    if(lastdayone < (lastdaytwo-1)){
        
       solution[lastdayone][lastdaytwo] = opt(lastdayone, lastdaytwo-1) + credit[lastdaytwo]
       +dist(cust_x[lastdaytwo],cust_y[lastdaytwo],cust_x[lastdaytwo-1], cust_y[lastdaytwo-1]);
         
    }
    
    
    // if we don't know the second to the last customer for day1
    if(lastdaytwo == (lastdayone-1)){
        for(int k = 0; k < lastdayone-1 ; k++){
            solution[lastdayone][lastdaytwo] =
                min((opt(k, lastdaytwo)+dist(cust_x[k],cust_y[k],cust_x[lastdayone], cust_y[lastdayone])),
                    solution[lastdayone][lastdaytwo]);
        }
    
    }
    // if we don't know the second to the last customer for day1
    if(lastdaytwo < (lastdayone-1)){
    
        solution[lastdayone][lastdaytwo] =
        opt(lastdayone-1 ,lastdaytwo) + dist(cust_x[lastdayone],cust_y[lastdayone],cust_x[lastdayone-1], cust_y[lastdayone-1]);
    }
  
    return solution[lastdayone][lastdaytwo];
}

int main()
{
    credit[0] = 0;
    cust_x[0] =0;
    cust_y[0] =0;
    int answer = 0;
    int num_customer;
    cin >> num_customer;
    credit[num_customer+1] = 0;
    cust_x[num_customer+1] = 0;
    cust_y[num_customer+1] = 0;
    
    for(int i = 1; i<= num_customer; i++){
        int x,y,c;
        cin >> x >> y >> c;
        credit[i] = c;
        cust_x[i] = x;
        cust_y[i] = y;
       
    }
    //basecase
    solution[1][0] = dist(cust_x[1],cust_y[1],cust_x[0], cust_y[0]);
    if(num_customer<3){
        solution[0][1] = dist(cust_x[1],cust_y[1],cust_x[0], cust_y[0]);
    }
    else{
    solution[0][1] = dist(cust_x[1],cust_y[1],cust_x[0], cust_y[0])+credit[1];
    }
    solution[0][0] = 0;
    
    int tempsol = 1000000000;
    int finalsolution = min(opt(0,num_customer)+dist(cust_x[num_customer],cust_y[num_customer],cust_x[0], cust_y[0]),opt(num_customer,0)+dist(cust_x[num_customer],cust_y[num_customer],0,0));
    for(int i = 1; i< num_customer; i++){
        int newsolution = min(opt(i,num_customer)+dist(cust_x[i],cust_y[i],cust_x[0], cust_y[0])+ dist(cust_x[num_customer],cust_y[num_customer],cust_x[0], cust_y[0]),opt(num_customer,i) + dist(cust_x[i],cust_y[i],cust_x[0], cust_y[0])+ dist(cust_x[num_customer],cust_y[num_customer],cust_x[0], cust_y[0]));
        
        finalsolution = min(newsolution, finalsolution);
    }
   

   cout<<finalsolution;
    return 0;
}
