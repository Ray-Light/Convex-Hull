#include<iostream>
#include<vector>
#include "convexhull.h"

using namespace std;

int main() {
	vector<pair<int, int> >v;

    // v.push_back(make_pair());
    v.push_back(make_pair(1, -1));
    // v.push_back(make_pair(1, 0));
    v.push_back(make_pair(2, -6));
    // v.push_back(make_pair(2, 0));
    // v.push_back(make_pair(2, 2));
    // v.push_back(make_pair(3, 2));
    // v.push_back(make_pair(3, 5));
    // v.push_back(make_pair(4, 0));
    // v.push_back(make_pair(4, -6));
    v.push_back(make_pair(4, -7));
    // v.push_back(make_pair(4, 2));
    // v.push_back(make_pair(4, 6));
    // v.push_back(make_pair(6, 0));
    // v.push_back(make_pair(7, 0));
    // v.push_back(make_pair(8, 0));
    // v.push_back(make_pair(8, 3));
    v.push_back(make_pair(8, -6));

    // v.push_back(make_pair(9, 0));
    // v.push_back(make_pair(9, 1));
    v.push_back(make_pair(9, -5));


    // v.push_back(make_pair(-3, 1));
    // v.push_back(make_pair(-2, 3));
    // v.push_back(make_pair(-1, 5));
    // v.push_back(make_pair(1, 5));
    // v.push_back(make_pair(2, 3));
    // v.push_back(make_pair(3, 1));
    // v.push_back(make_pair(0,0));











	// v.push_back(make_pair(-7, 1));
 //    v.push_back(make_pair(-6, 7));
 //    v.push_back(make_pair(-5, 0));
    // v.push_back(make_pair(-4, 0));
    // v.push_back(make_pair(-3, 3));
    // v.push_back(make_pair(-2, -2));
    // v.push_back(make_pair(-1, -4));
    // v.push_back(make_pair(0, 0));
    // v.push_back(make_pair(1, 1));
    // v.push_back(make_pair(2, 3));
    // v.push_back(make_pair(3, -5));
    // v.push_back(make_pair(-2, -5));
    // v.push_back(make_pair(-3, -6));


	KirkPatrickSeidel ks(v);
	ks.kps();

	return 0;
}