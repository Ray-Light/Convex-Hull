#include <bits/stdc++.h>
using namespace std;

//Doubly linked list of points
typedef struct node
{
	pair<int,int> p;
	struct node* next;
	struct node* prev;
}Node;

//Utility function to check whether a point lies to the left of a line joining a to b or not
//Function returns value:
//	>0 if the point lies to the left
//	=0 if the point lies on the line joining the two points a,b
//	<0 if the point lies to the right
int isLeft(pair<int,int> a, pair<int,int> b, pair<int,int> c){
     int t = ((b.first - a.first)*(c.second - a.second) - (b.second - a.second)*(c.first - a.first));
     return t;
}

//Utility function to find the slope between a pair of points
double slope(pair<pair<int,int>,pair<int,int>> pairs)
{
    double slopeline=((double)pairs.second.second-(double)pairs.first.second)/((double)pairs.second.first-(double)pairs.first.first);
    return slopeline;
}

//Utility function to sort the points by x-coordinate and in case of same x-coordinate
//sort by y-coordinate in deccreasing order
bool comparepointsuh(pair<int,int> a, pair<int,int> b)
{
    return (a.first<b.first) || (a.first==b.first && a.second>b.second);
}

//Utility function to sort the points by x-coordinate and in case of same x-coordinate
//sort by y-coordinate in increasing order
bool comparepointslh(pair<int,int> a, pair<int,int> b)
{
    return (a.first<b.first) || (a.first==b.first && a.second<b.second);
}

pair<int,int> p0;
// A utility function to find next to top in a stack
pair<int,int> nextToTop(stack<pair<int,int>> &S) 
{ 
    pair<int,int> p = S.top(); 
    S.pop(); 
    pair<int,int> res = S.top(); 
    S.push(p); 
    return res; 
}

// A utility function to swap two points 
void swap(pair<int,int> &p1, pair<int,int> &p2) 
{ 
    pair<int,int> temp = p1; 
    p1 = p2; 
    p2 = temp; 
}

// A utility function to return square of distance between p1 and p2 
int distSq(pair<int,int> p1, pair<int,int> p2) 
{ 
    return (p1.first - p2.first)*(p1.first - p2.first) + (p1.second - p2.second)*(p1.second - p2.second); 
} 

// To find orientation of ordered triplet (p, q, r). 
// The function returns following values 
// 0 --> p, q and r are colinear 
// 1 --> Clockwise 
// 2 --> Counterclockwise 
int orientation(pair<int,int> p, pair<int,int> q, pair<int,int> r) 
{ 
    int val = (q.second - p.second) * (r.first - q.first) - (q.first - p.first) * (r.second - q.second); 
    if (val == 0) 
    	return 0;  // colinear 
    return (val > 0)? 1: 2; // clock or counterclock wise 
}

// A function used by library function qsort() to sort an array of 
// points with respect to the first point 
int compare(const void *vp1, const void *vp2) 
{ 
   pair<int,int> *p1 = (pair<int,int> *)vp1; 
   pair<int,int> *p2 = (pair<int,int> *)vp2; 
  
   // Find orientation 
   int o = orientation(p0, *p1, *p2); 
   if (o==0) 
     return (distSq(p0, *p2) >= distSq(p0, *p1))? -1 : 1; 
    
   return (o == 2)? -1: 1; 
}
