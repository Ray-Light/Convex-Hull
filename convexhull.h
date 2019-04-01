#include "UtilFunction.h"

class GrahamScan
{
public:

	vector<pair<int,int> > points;
	int n;

	GrahamScan(vector<pair<int,int> > p)
	{
		for(int i=0;i<p.size();i++)
		{
			points.push_back(make_pair(p[i].first,p[i].second));
		}
		n=points.size();
	}

	void convexHull() 
	{ 
	   // Find the bottommost point 
	   int ymin = points[0].second, min = 0; 
	   for (int i = 1; i < n; i++) 
	   { 
	     int y = points[i].second; 
	  
	     // Pick the bottom-most or chose the left 
	     // most point in case of tie 
	     if ((y < ymin) || (ymin == y && points[i].first < points[min].first)) 
	        ymin = points[i].second, min = i; 
	   } 
	  
	   // Place the bottom-most point at first position 
	   swap(points[0], points[min]); 
	  
	   // Sort n-1 points with respect to the first point. 
	   // A point p1 comes before p2 in sorted ouput if p2 
	   // has larger polar angle (in counterclockwise 
	   // direction) than p1 
	   p0 = points[0]; 
	   qsort(&points[1], n-1, sizeof(pair<int,int>), compare); 
	  
	   // If two or more points make same angle with p0, 
	   // Remove all but the one that is farthest from p0 
	   // Remember that, in above sorting, our criteria was 
	   // to keep the farthest point at the end when more than 
	   // one points have same angle. 
	   int m = 1; // Initialize size of modified array 
	   for (int i=1; i<n; i++) 
	   { 
	       // Keep removing i while angle of i and i+1 is same 
	       // with respect to p0 
	       while (i < n-1 && orientation(p0, points[i], points[i+1]) == 0) 
	          i++; 
	  
	  
	       points[m] = points[i]; 
	       m++;  // Update size of modified array 
	   } 
	  
	   // If modified array of points has less than 3 points, 
	   // convex hull is not possible 
	   if (m < 3) 
			return; 
	  
	   // Create an empty stack and push first three points 
	   // to it. 
	   stack<pair<int,int> > S; 
	   S.push(points[0]); 
	   S.push(points[1]); 
	   S.push(points[2]); 
	  
	   // Process remaining n-3 points 
	   for (int i = 3; i < m; i++) 
	   { 
	      // Keep removing top while the angle formed by 
	      // points next-to-top, top, and points[i] makes 
	      // a non-left turn 
	      while (orientation(nextToTop(S), S.top(), points[i]) != 2) 
	         S.pop(); 
	      S.push(points[i]); 
	   } 
	  
	   // Now stack has the output points, print contents of stack
	   pair<int, int>store_pt = S.top();
	   pair<int, int>temp_pt = S.top();
	   vector<string>v;
	   string final_str = "";
	   string temp_str = to_string(temp_pt.first) + " " + to_string(temp_pt.second) + " ";
	   S.pop(); 
	   while (!S.empty()) 
	   { 
	       pair<int,int> p = S.top();
	       temp_str += to_string(p.first) + " " + to_string(p.second) + " 1\n";
	       final_str += temp_str;
	       cout << "(" << p.first << ", " << p.second <<")" << endl;
	       temp_str = to_string(p.first) + " " + to_string(p.second) + " ";
	       S.pop(); 
	   }
	   final_str += temp_str + to_string(store_pt.first) + " " + to_string(store_pt.second) + " 1\n";
	   ofstream myfile;
	   myfile.open("testpoints.txt");
	   myfile << final_str;
	   myfile.close();
	}
	~GrahamScan(){};
};

class JarvisMarch
{
public:

	vector<pair<int,int> > points;
	int n;

	JarvisMarch(vector<pair<int,int> > p)
	{
		for(int i=0;i<p.size();i++)
		{
			points.push_back(make_pair(p[i].first,p[i].second));			
		}
		n=points.size();
	}

	void convexHull() 
	{ 
	    // There must be at least 3 points 
	    if (n < 3) 
	    	return; 
	  
	    // Initialize Result 
	    vector<pair<int,int> > hull; 
	  
	    // Find the leftmost point 
	    int l = 0; 
	    for (int i = 1; i < n; i++) 
	        if (points[i].first < points[l].first) 
	            l = i; 
	  
	    // Start from leftmost point, keep moving counterclockwise 
	    // until reach the start point again.  This loop runs O(h) 
	    // times where h is number of points in result or output.

	    vector<string>str;
	    string temp_str = to_string(points[l].first) + " " + to_string(points[l].second) + " "; 
	    int p = l, q; 
	    do
	    { 
	        // Add current point to result 
	        hull.push_back(points[p]); 
	  
	        // Search for a point 'q' such that orientation(p, x, 
	        // q) is counterclockwise for all points 'x'. The idea 
	        // is to keep track of last visited most counterclock- 
	        // wise point in q. If any point 'i' is more counterclock- 
	        // wise than q, then update q. 
	        q = (p+1)%n; 
	        for (int i = 0; i < n; i++) 
	        { 
	           // If i is more counterclockwise than current q, then 
	           // update q 
	           if (orientation(points[p], points[i], points[q]) == 2) 
	               q = i; 
	        } 
	  
	        // Now q is the most counterclockwise with respect to p 
	        // Set p as q for next iteration, so that q is added to 
	        // result 'hull' 
	        p = q;
	        temp_str +=  to_string(points[p].first) + " " + to_string(points[p].second) + " 1";
	        str.push_back(temp_str);
	        temp_str = to_string(points[p].first) + " " + to_string(points[p].second) + " ";
	  
	    } while (p != l);  // While we don't come to first point 
		
		ofstream myfile;
		myfile.open("testpoints.txt");
		temp_str = "";
	    for(int x = 0; x < str.size(); x++) {
	    	temp_str += str[x] + "\n";
	    }
	    myfile << temp_str;
	    myfile.close();

	    // Print Result 
	    for (int i = 0; i < hull.size(); i++) 
	        cout << "(" << hull[i].first << ", "<< hull[i].second << ")\n"; 
	} 
	~JarvisMarch(){};	
};

class KirkPatrickSeidel
{
	public:

	vector<pair<int,int>> points;

	KirkPatrickSeidel(vector<pair<int,int>> v)
	{
		for(int i=0;i<v.size();i++)
		{
			points.push_back(v[i]);
		}
	}

	pair<pair<int,int>, pair<int, int> > upperBridge(vector<pair<int,int>>s,pair<int,int>l)
	{
		vector<pair<int,int> > cand;
	    int n = s.size();
	    sort(s.begin(),s.end());
	    if(n==2)
	    {
	        sort(s.begin(),s.end());
	        return make_pair(s[0],s[1]);
	    }
	    vector<pair<pair<int,int>,pair<int,int>>> pairs;
	    vector<double> k;
	    vector< pair< double, pair< pair< int, int >,pair< int,int > > > > slope_pair;
	    bool flag=true;
	    for(int i=0;i<=n-2;i+=2)
	    {
	        if(s[i].first<s[i+1].first)
	            pairs.push_back(make_pair(s[i],s[i+1]));
	        else
	            pairs.push_back(make_pair(s[i+1],s[i]));
	        if(i==n-2)
	            flag=false;
	    }
	    if(flag)
	        cand.push_back(s[n-1]);
	    for(int i=0;i<pairs.size();i++)
	    {
	        if(pairs[i].first.first==pairs[i].second.first)
	        {
	            if(pairs[i].first.second>pairs[i].second.second)
	                cand.push_back(pairs[i].first);
	            else
	                cand.push_back(pairs[i].second);
	        }
	        else
	        {
	            double temp=slope(pairs[i]);
	            k.push_back(temp);
	            slope_pair.push_back(make_pair(temp,pairs[i]));
	        }        
	    }
	    sort(k.begin(),k.end());
	    double midslope;
	    if(k.size()%2==0)
	    {
	        midslope=(k[k.size()/2]+k[(k.size()/2)-1])/2;
	    }
	    else
	        midslope=k[k.size()/2];

	    vector<pair<pair<int,int>,pair<int,int>>> small,equal,large;
	    for(int i=0;i<slope_pair.size();i++)
	    {
	        if(slope_pair[i].first<midslope)
	        {
	            small.push_back(slope_pair[i].second);
	        }
	        else if(slope_pair[i].first==midslope)
	        {
	            equal.push_back(slope_pair[i].second);
	        } 
	        else
	        {
	            large.push_back(slope_pair[i].second);
	        }
	    }

	    int maxval=INT_MIN;
	    for(int i=0;i<n;i++)
	    {
	        if((s[i].second-(midslope*s[i].first))>maxval)
	            maxval=s[i].second-(midslope*s[i].first);

	    }
	    vector<pair<int,int>> maxset;
	    pair<int,int> pmax=make_pair(INT_MIN,INT_MIN);
	    pair<int,int> pmin=make_pair(INT_MAX,INT_MAX);
	    for(int i=0;i<n;i++)
	    {
	        if(maxval==(s[i].second-(midslope*s[i].first)))
	        {
	            maxset.push_back(s[i]);
	            if(pmax.first<s[i].first)
	            {
	                pmax.first=s[i].first;
	                pmax.second=s[i].second;
	            }
	            if(pmin.first>s[i].first)
	            {
	                pmin.first=s[i].first;
	                pmin.second=s[i].second;
	            }
	        }
	    }
	    if(pmin.first<=l.first && pmax.first>l.first)
	    {
	        return make_pair(pmin,pmax);
	    }
	    if(pmax.first<=l.first)
	    {
	        for(int i=0;i<small.size();i++)
	        {
	            cand.push_back(small[i].first);
	            cand.push_back(small[i].second);
	        }
	        for(int i=0;i<large.size();i++)
	        {
	            cand.push_back(large[i].second);
	        }
	        for(int i=0;i<equal.size();i++)
	        {
	            cand.push_back(equal[i].second);
	        }
	    }
	    if(pmin.first>l.first)
	    {
	        for(int i=0;i<large.size();i++)
	        {
	            cand.push_back(large[i].first);
	            cand.push_back(large[i].second);
	        }
	        for(int i=0;i<small.size();i++)
	        {
	            cand.push_back(small[i].first);
	        }
	        for(int i=0;i<equal.size();i++)
	        {
	            cand.push_back(equal[i].first);
	        }
	    }
	    return upperBridge(cand,l);
	}

	Node* upperhull(pair<int,int> pmin, pair<int,int> pmax,vector<pair<int, int>> v)
	{
		int n = v.size();
		sort(v.begin(), v.end());
	    if(pmin.first == pmax.first && pmin.second == pmax.second)
	    {
	        Node* head=(Node *)malloc(sizeof(Node));
	        head->p.first=pmin.first;
	        head->p.second=pmin.second;
	        head->prev=NULL;
	        head->next=NULL;
	        return head;
	    }
	    pair<int,int> x_med;
		if(n%2==0)
			x_med= v[n/2];
		else
			x_med= v[n/2];
	    vector<pair<int, int> >tleft, tright;
	    for(int i = 0;i < n; i++)
	    {
	        //FATAL : ADDED EQUAL CONDITION
	        if(v[i].first <= x_med.first)
	        {
	            tleft.push_back(v[i]);
	        }
	        else
	        {
	            tright.push_back(v[i]);
	        }
	    }
	    pair<pair<int, int>, pair<int, int> > plpr;
	    plpr = upperBridge(v, x_med);
	    pair<int,int> pl=plpr.first;
	    pair<int,int> pr=plpr.second;
	    vector<pair<int,int>> ntleft,ntright;
	    ntleft.push_back(pl);
	    ntleft.push_back(pmin);
	    ntright.push_back(pr);
	    ntright.push_back(pmax);

	    for(int i=0;i<tleft.size();i++)
	    {
	        if(isLeft(pmin,pl,tleft[i])>0 && tleft[i].first > pmin.first && tleft[i].first < pl.first)
	        {
	            ntleft.push_back(tleft[i]);
	        }        
	    }
	    for(int i=0;i<tright.size();i++)
	    {
	        if(isLeft(pr,pmax,tright[i])>0 && tright[i].first > pr.first && tright[i].first < pmax.first)
	        {
	            ntright.push_back(tright[i]);
	        }        
	    }
	    Node* left=upperhull(pmin,pl,ntleft);
	    Node* right=upperhull(pr,pmax,ntright);

	    if(left == NULL) {
	        left = right;
	        return left;
	    }

	    Node* temp=left;
	    while(temp->next)
	    {
	        temp=temp->next;
	    }
	    temp->next=right;
	    
	    return left;
	}

	pair<pair<int,int>, pair<int, int> > lowerBridge(vector<pair<int,int>>s,pair<int,int>l)
	{
	    vector<pair<int,int> > cand;
	    sort(s.begin(),s.end());
	    int n = s.size();
	    if(n==2)
	    {
	        sort(s.begin(),s.end());
	        return make_pair(s[1],s[0]);
	    }
	    vector<pair<pair<int,int>,pair<int,int>>> pairs;
	    vector<double> k;
	    vector< pair< double, pair< pair< int, int >,pair< int,int > > > > slope_pair;
	    bool flag=true;
	    for(int i=0;i<=n-2;i+=2)
	    {
	        if(s[i].first<s[i+1].first)
	            pairs.push_back(make_pair(s[i+1],s[i]));
	        else
	            pairs.push_back(make_pair(s[i+1],s[i]));
	        if(i==n-2)
	            flag=false;
	    }
	    if(flag)
	        cand.push_back(s[n-1]);
	    for(int i=0;i<pairs.size();i++)
	    {
	        if(pairs[i].first.first==pairs[i].second.first)
	        {
	            if(pairs[i].first.second<pairs[i].second.second)
	                cand.push_back(pairs[i].first);
	            else
	                cand.push_back(pairs[i].second);
	        }
	        else
	        {
	            double temp=slope(pairs[i]);
	            k.push_back(temp);
	            slope_pair.push_back(make_pair(temp,pairs[i]));
	        }        
	    }
	    sort(k.begin(),k.end());
	    double midslope;
	    if(k.size()%2==0)
	    {
	        midslope=(k[k.size()/2]+k[(k.size()/2)-1])/2;
	    }
	    else
	        midslope=k[k.size()/2];

	    vector<pair<pair<int,int>,pair<int,int>>> small,equal,large;
	    for(int i=0;i<slope_pair.size();i++)
	    {
	        if(slope_pair[i].first<midslope)
	        {
	            small.push_back(slope_pair[i].second);
	        }
	        else if(slope_pair[i].first==midslope)
	        {
	            equal.push_back(slope_pair[i].second);
	        } 
	        else
	        {
	            large.push_back(slope_pair[i].second);
	        }
	    }

	    int minval=INT_MAX;
	    for(int i=0;i<n;i++)
	    {
	        if((s[i].second-(midslope*s[i].first))< minval)
	            minval=s[i].second-(midslope*s[i].first);

	    }
	    vector<pair<int,int>> minset;
	    pair<int,int> pmax=make_pair(INT_MIN,INT_MIN);
	    pair<int,int> pmin=make_pair(INT_MAX,INT_MAX);
	    for(int i=0;i<n;i++)
	    {
	        if(minval==(s[i].second-(midslope*s[i].first)))
	        {
	            minset.push_back(s[i]);
	            if(pmax.first<s[i].first)
	            {
	                pmax.first=s[i].first;
	                pmax.second=s[i].second;
	            }
	            if(pmin.first>s[i].first)
	            {
	                pmin.first=s[i].first;
	                pmin.second=s[i].second;
	            }
	        }
	    }
	    if(pmin.first<l.first && pmax.first>=l.first)
	    {
	        return make_pair(pmax,pmin);
	    }
	    if(pmin.first>l.first)
	    {
	        for(int i=0;i<small.size();i++)
	        {
	            cand.push_back(small[i].first);
	            cand.push_back(small[i].second);
	        }
	        for(int i=0;i<large.size();i++)
	        {
	            cand.push_back(large[i].second);
	        }
	        for(int i=0;i<equal.size();i++)
	        {
	            cand.push_back(equal[i].second);
	        }
	    }
	    if(pmax.first<=l.first)
	    {
	        for(int i=0;i<large.size();i++)
	        {
	            cand.push_back(large[i].first);
	            cand.push_back(large[i].second);
	        }
	        for(int i=0;i<small.size();i++)
	        {
	            cand.push_back(small[i].first);
	        }
	        for(int i=0;i<equal.size();i++)
	        {
	            cand.push_back(equal[i].first);
	        }
	    }
	    return lowerBridge(cand,l);
	}

	Node* lowerhull(pair<int,int> pmin, pair<int,int> pmax,vector<pair<int, int>> v)
	{
	    int n = v.size();
	    sort(v.begin(), v.end());
	    if(pmin.first == pmax.first && pmin.second == pmax.second)
	    {
	        Node* head=(Node *)malloc(sizeof(Node));
	        head->p.first=pmin.first;
	        head->p.second=pmin.second;
	        head->prev=NULL;
	        head->next=NULL;
	        return head;
	    }
	    pair<int,int> x_med;
	    if(n%2==0)
	        x_med= make_pair((v[n/2-1].first+v[n/2].first)/2,(v[n/2-1].second+v[n/2].second)/2);
	    else
	        x_med = v[n/2];
	    vector<pair<int, int> >tleft, tright;
	    for(int i = 0;i < n; i++)
	    {
	        //FATAL : ADDED EQUAL CONDITION
	        if(v[i].first <= x_med.first)
	        {
	            tleft.push_back(v[i]);
	        }
	        else
	        {
	            tright.push_back(v[i]);
	        }
	    }
	    pair<pair<int, int>, pair<int, int> > prpl;
	    prpl = lowerBridge(v, x_med);
	    pair<int,int> pr=prpl.first;
	    pair<int,int> pl=prpl.second;
	    // cout<<pr.first<<" "<<pr.second<<endl;
	    // cout<<pl.first<<" "<<pl.second<<endl;
	    vector<pair<int,int>> ntleft,ntright;

	    // cout<<tleft.size()<<" "<<tright.size()<<endl;

	    ntleft.push_back(pl);
	    ntleft.push_back(pmin);
	    ntright.push_back(pr);
	    ntright.push_back(pmax);

	    for(int i=0;i<tleft.size();i++)
	    {
	        if(isLeft(pl,pmin,tleft[i])>0 && tleft[i].first > pmin.first && tleft[i].first < pl.first)
	        {
	            ntleft.push_back(tleft[i]);
	        }        
	    }
	    for(int i=0;i<tright.size();i++)
	    {
	        if(isLeft(pr,pmax,tright[i])<0 && tright[i].first > pr.first && tright[i].first < pmax.first)
	        {
	            ntright.push_back(tright[i]);
	        }        
	    }
	    Node* left=lowerhull(pmax,pr,ntright);
	    Node* right=lowerhull(pl,pmin,ntleft);
	    if(left == NULL) {
	        left = right;
	        return left;
	    }

	    Node* temp=left;
	    while(temp->next)
	    {
	        temp=temp->next;
	    }
	    temp->next=right;
	    
	    return left;
	}

	void kps()
	{
		sort(points.begin(),points.end(),comparepointsuh);
	    pair<int,int> pumin=points[0];

	    sort(points.begin(),points.end(),comparepointslh);    
	    pair<int,int> pumax=points[points.size()-1];

	    sort(points.begin(),points.end(),comparepointsuh);
	    
	    vector<pair<int,int>> T;
	    T.push_back(pumin);
	    T.push_back(pumax);
	    
	    vector<pair<int,int>> sol;
	    pair<int,int> pfirst=points[0];
	    sol.push_back(points[0]);
	    for(int i=1;i<points.size();i++)
	    {
	        int countstep=0;
	        if(pfirst.first==points[i].first)
	        {
	            countstep++;
	        }//temp->next->p.first+" "+temp->next->p.first
	        else
	        {
	            sol.push_back(points[i-countstep]);
	            pfirst=points[i];
	        }
	    }
	    for(int i=0;i<sol.size();i++)
	    {
	        if(sol[i].first>pumin.first && sol[i].first<pumax.first)
	        {
	            T.push_back(sol[i]);
	        }
	    }
	    // Node* temp = upperhull(pumin,pumax,T);
	    // Node* temp1=temp;
	    ofstream fileout;
	    fileout.open("testpoints.txt");
	    // while(temp->next)
	    // {
	    // 	fileout<< to_string(temp->p.first)<<" "<<to_string(temp->p.second)<<" "<<to_string(temp->next->p.first)<<" "<<to_string(temp->next->p.second)<<" 1\n";
	    //     temp=temp->next;
	    // }
	    
	    // fileout<<to_string(temp->p.first)<<" "<<to_string(temp->p.second)<<" ";

	    sort(points.begin(),points.end(),comparepointslh);
	    pair<int,int> plmin=points[0];
	    sort(points.begin(),points.end(),comparepointsuh);    
	    pair<int,int> plmax=points[points.size()-1];
	    sort(points.begin(),points.end(),comparepointslh);

	    T.clear();
	    T.push_back(plmin);
	    T.push_back(plmax);
	    sol.clear();
	    pfirst=points[0];
	    sol.push_back(points[0]);
	    for(int i=1;i<points.size();i++)
	    {
	        int countstep=0;
	        if(pfirst.first==points[i].first)
	        {
	            countstep++;
	        }
	        else
	        {
	            sol.push_back(points[i-countstep]);
	            pfirst=points[i];
	        }
	    }
	    for(int i=0;i<sol.size();i++)
	    {
	        if(sol[i].first>plmin.first && sol[i].first<plmax.first)
	        {
	            T.push_back(sol[i]);
	        }
	    }

	    Node* temp = lowerhull(plmax,plmin,T);
	    map<pair<int, int>, int>m;
	    cout<<"LH : \n";
	    while(temp)
	    {
	    	cout<<temp->p.first<<" "<<temp->p.second<<"\n";
	        m[temp->p] = 0;
	        temp=temp->next;
	    }
	    cout<<"LH ends : \n\n";
	    auto it = m.rbegin();
	    auto it1 = m.rbegin();
	    fileout<<to_string(it->first.first) <<" "<< to_string(it->first.second)<<" "<<" 1\n";
	    fileout << to_string(it->first.first) <<" "<< to_string(it->first.second)<<" ";

	    cout<<it->first.first<<" "<<it->first.second<<endl;
	    it++;
	    for (; it != m.rend(); it++ )
	    {
	    	cout<<it->first.first<<" "<<it->first.second<<endl;
	        fileout << to_string(it->first.first)  // string (key)
	                  << " "
	                  << to_string(it->first.second)
	                  <<" 1\n";   // string's value 
	                 
	        fileout << to_string(it->first.first)  // string (key)
	                  << " "
	                  << to_string(it->first.second)
	                  <<" ";

	    }
	    // fileout<<to_string(temp1->p.first)<<" "<<to_string(temp1->p.second)<<" 1\n";
	    fileout.close();
	}

	~KirkPatrickSeidel(){}
	
};
