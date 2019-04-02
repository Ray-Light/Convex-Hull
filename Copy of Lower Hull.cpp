pair<pair<int,int>, pair<int, int> > lowerBridge(vector<pair<int,int>>s,pair<int,int>l)
	{
		cout<<"Hull iteration : "<<iterlh - 1<<endl;
	    vector<pair<int,int> > cand;
	    sort(s.begin(),s.end());
	    cout<<"Points in "<<iterlb++<<" are : \n";
		for (int i = 0; i < s.size(); ++i)
		{
			cout<<s[i].first<<" "<<s[i].second<<endl;
		}
		cout<<"End points \n";
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
	            pairs.push_back(make_pair(s[i],s[i + 1]));
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
	    // if(k.size()%2==0)
	    // {
	    //     midslope=(k[k.size()/2]+k[(k.size()/2)-1])/2;
	    // }
	    // else
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

	    double minval=INT_MAX;
	    for(int i=0;i<n;i++)
	    {
	        if(((double)s[i].second-(midslope*(double)s[i].first))< minval)
	            minval=(double)s[i].second-(midslope*(double)s[i].first);

	    }
	    vector<pair<int,int>> minset;
	    pair<int,int> pmax=make_pair(INT_MIN,INT_MIN);
	    pair<int,int> pmin=make_pair(INT_MAX,INT_MAX);
	    for(int i=0;i<n;i++)
	    {
	        if(minval==((double)s[i].second-(midslope*(double)s[i].first)))
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

	    /*if(pmax.first<=l.first)
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
	    }*/

	    /*MAJOR CHANGES HERE*/
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