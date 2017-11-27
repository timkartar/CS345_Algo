# include<LEDA/geo/circle.h>
# include<LEDA/geo/point.h>
# include<iostream>
#include<vector>
#include <ctime>


using namespace std ;
using leda::circle ;
using leda::point ;

int main (){    //g++ -I ~/leda/incl -c brute.cpp  //g++ -L ~/leda brute.o -lleda -lX11 -lm
int n; //nuber of points      
cin >> n;
vector<point> points(n);
int i = 0, j = 0, k = 0;
double x,y;
for(i=0;i<n;i++){
    cin >> x;
    cin >> y;
    point p (x,y);
    points[i] = points[i] + p.to_vector();
    //cout << points[i];
}
clock_t start, end;
double msecs;
start = clock();

if(n == 1){
    cout << "only one point, required circle is of radius 0 centered at " << points[0];  
    return 0;
}
if(n == 2){
    cout << "only two points, required circle is  " << circle(center(points[0],points[1]),points[1]);
    cout << endl << "radius is " << points[0].distance(points[1])/2.0 << endl;
    return 0;
}
circle minCircle;
for(i = 0;i<n;i++){         //for all combinations of 2 points
    for(j=i+1;j<n;j++){
        circle c(center(points[i],points[j]),points[j]);
        for(k=0;k<n;k++){
            if(c.outside(points[k])){
                goto next;
            }
        }
        if(c.radius() <= minCircle.radius()) minCircle = c; //update minCircle
        next: continue;
    }
}

for(i = 0;i<n;i++){         //for all combinations of 3 points
    for(j=i+1;j<n;j++){
        for(k=j+1;k<n;k++){
            if(orientation(points[i],points[j],points[k]) == 0){  //Check if three points are co-linear
                continue;
            }
            circle c(points[i],points[j],points[k]);
            //cout << c.center().xcoord()<<", "<< c.center().ycoord() << endl << c.radius() << endl << c << endl;            
            for(int l=0;l<n;l++){
                if(c.outside(points[l])){
                    //cout << minCircle.center().xcoord()<<", "<< minCircle.center().ycoord() << endl << minCircle.radius() << endl << minCircle << endl;                    
                    goto next2;
                }
            }
        if(c.radius() <= minCircle.radius()) minCircle = c; //update minCircle
        if(minCircle.radius() < 0.00001) minCircle = c;        
        next2: continue;
        }
    }
}
end = clock();
msecs = ((double) (end - start)) * 1000 / CLOCKS_PER_SEC;
cout << minCircle.center().xcoord()<<", "<< minCircle.center().ycoord() << endl << minCircle.radius() << endl; //Report MinCircle
//cout << msecs << endl; //Report time
return 0;
}
