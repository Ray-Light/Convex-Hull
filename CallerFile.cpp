#include<iostream>
#include<vector>
#include "convexhull.h"

using namespace std;

int main() {
	vector<pair<int, int> >v;

	v.push_back(make_pair(-7, 1));
    v.push_back(make_pair(-6, 7));
    v.push_back(make_pair(-5, 0));
    v.push_back(make_pair(-4, 0));
    v.push_back(make_pair(-3, 3));
    v.push_back(make_pair(-2, -2));
    v.push_back(make_pair(-1, -4));
    v.push_back(make_pair(0, 0));
    v.push_back(make_pair(1, 1));
    v.push_back(make_pair(2, 3));
    v.push_back(make_pair(3, -5));

	KirkPatrickSeidel ks(v);
	ks.kps();
	
	return 0;
}