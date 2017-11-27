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

circle CircleWithTwoBoundaryPoints(vector<point> points, int k, point b0, point b1){
    circle next;
    circle prev(midpoint(b0,b1),b1);
    for(int i = 0; i < k; i++){
        if(!prev.outside(points[i])) next = prev;
        else next = circle(b0,b1,points[i]);
        prev = next;
    }
    return next;
}

circle CircleWithSingleBoundaryPoint(vector<point> points, int j, point b){
    circle next;
    circle prev(midpoint(points[0],b),b);
    for(int i = 1; i < j; i++){
        if(!prev.outside(points[i])) next = prev;
        else next = CircleWithTwoBoundaryPoints(points, i, b, points[i]);
        prev = next;
    }
    return next;
}
int main (){    //g++ -I ~/leda/incl -c incr.cpp  //g++ -L ~/leda incr.o -lleda -lX11 -lm
    
    int n; //nuber of points      
    cin >> n;
    vector<point> points(n);
    int i = 0, j = 0, k = 0;
    float x,y;
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
    circle c = circle(midpoint(points[1], points[0]),points[0]);
    circle cnext;
    for(i=2;i<n;i++){
        if(!c.outside(points[i])) cnext = c;
        else cnext = CircleWithSingleBoundaryPoint(points , i, points[i]);
        //cout << next.radius() << endl;
    	c = cnext;
    }
    circle minCircle = c;
    end = clock();
    msecs = ((double) (end - start)) * 1000 / CLOCKS_PER_SEC;
    cout << minCircle.center().xcoord()<<", "<< minCircle.center().ycoord() << endl << minCircle.radius() << endl; //Report MinCircle
    //cout << msecs << endl; //Report time
    return 0;
}
