# include<LEDA/geo/circle.h>
# include<LEDA/geo/point.h>
# include<iostream>
#include<vector>
#include <ctime>

using namespace std ;
using leda::circle ;
using leda::point ;

vector<point> Shuffle(vector<point> v, int n)
{
	point temp;
	int ridx = n-1;

	for(int j=(n-1); j>1; j--)// one pass through array
	{
		ridx = rand()%(j+1);// index = 0 to j
		temp = v[ridx];// value will be moved to end element
		v[ridx] = v[j];// end element value in random spot
		v[j] = temp;// selected element moved to end. This value is final
	}
	return v;
}

circle SEC(vector<point> points,int n,vector<point> boundary,int b){

    circle sec;
    if (b == 3){
        sec = circle(boundary[0], boundary[1], boundary[2]);
    }
    else if (n == 1 && b == 0){
        sec = circle(points[0], 0.0000001);
    }
    else if (n == 0 && b == 2){
        sec = circle(center(boundary[0], boundary[1]),boundary[1]);
    }
    else if (n == 1 && b == 1){
        sec = circle(center(boundary[0], points[0]),points[0]);
    }
    else {
        sec = SEC(points, n-1, boundary, b);
        if (sec.outside(points[n-1])){
            boundary[b++] = points[n-1];
            sec = SEC(points, n-1, boundary, b);
        }
    }
    return sec;
}
int main (){    //g++ -I ~/leda/incl -c incr.cpp  //g++ -L ~/leda incr.o -lleda -lX11 -lm
    
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
    points = Shuffle(points,n);
    vector<point> boundary(3);
    circle minCircle = SEC(points,n,boundary,0);
    end = clock();
    msecs = ((double) (end - start)) * 1000 / CLOCKS_PER_SEC;
    cout << minCircle.center().xcoord()<<", "<< minCircle.center().ycoord() << endl << minCircle.radius() << endl; //Report MinCircle
    //cout << msecs << endl; //Report time
    return 0;
}
