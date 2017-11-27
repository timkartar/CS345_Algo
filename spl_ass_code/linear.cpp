#include <iostream>
#include <ctime>
#include <LEDA/geo/point.h>
#include <LEDA/geo/circle.h>

using namespace std;
using namespace leda;

circle minRadiusCircle(point a, point b, point c){
    circle minRadiusCircle;
    if(orientation(a,b,c) != 0){
        circle temp(a,b,c);
        minRadiusCircle = temp;
    }
    circle temp0(midpoint(a,b),b);
    if(!temp0.outside(c) && temp0.radius() < minRadiusCircle.radius()){
        minRadiusCircle = temp0;
    }
    circle temp1(midpoint(a,c),c);
    if(!temp1.outside(b) && temp1.radius() < minRadiusCircle.radius()){
        minRadiusCircle = temp1;
    }
    circle temp2(midpoint(c,b),b);
    if(!temp2.outside(a) && temp2.radius() < minRadiusCircle.radius()){
        minRadiusCircle = temp2;
    }
    return minRadiusCircle;
}

circle CircleWithTwoBoundaryPoints(point Points[], int k, point b0, point b1){
    circle next;
    circle prev(midpoint(b0,b1),b1);
    for(int i = 1; i <= k; i++){
        if(!prev.outside(Points[i-1])) next = prev;
        else next = minRadiusCircle(b0,b1,Points[i-1]);
        //else{
            //circle temp(b0,b1,Points[i-1]);
            //next = temp;
        //}
        prev = next;
    }
    return next;
}

circle CircleWithSingleBoundaryPoint(point Points[], int j, point b){
    circle next;
    circle prev(midpoint(Points[0],b),b);
    for(int i = 2; i <= j; i++){
        if(!prev.outside(Points[i-1])) next = prev;
        else next = CircleWithTwoBoundaryPoints(Points, i-1, b, Points[i-1]);
        prev = next;
    }
    return next;
}

int main(){
    int N;
    clock_t begin,end;
    cin >> N;
    point Points[N];
    for(int i = 0; i < N; i++){
        double X,Y;
        cin >> X >> Y;
        point temp(X,Y);
        Points[i] = temp;
    }

    begin = clock();
    circle next;
    circle prev(midpoint(Points[0],Points[1]), Points[1]);
    for(int i = 3; i <= N; i++){
        if(!prev.outside(Points[i-1])) next = prev;
        else next = CircleWithSingleBoundaryPoint(Points , i-1, Points[i-1]);
        //cout << next.radius() << endl;
        prev = next;
    }
    end = clock();

    cout << N << '\t' << ((float)(end-begin)/CLOCKS_PER_SEC) << endl;
    cout << next.center() << endl;
    cout << next.radius() << endl;

    return 0;
}
