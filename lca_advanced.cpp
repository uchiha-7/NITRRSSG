#include <bits/stdc++.h>
// vector string set map first second continue break return upper_bound lower_bound length 
#define FOR(i,j,n) for(int i=(j);i<=((int)n);++i)
#define N 1000005
#define INF 0x3f3f3f3f
#define MOD 1000000007
#define endl "\n"
#define mem(a,val) memset(a,val,sizeof(a))
#define all(c) (c).begin(),(c).end()
#define tr(container, it) for(__typeof(container.begin()) it = container.begin(); it != container.end(); it++)
#define present(container, element) (container.find(element) != container.end())
#define cpresent(c,x) (find(all(c),x) != (c).end())
#define pb push_back
#define debug(x) cout << ">>" << #x << " is " << x << "<<" << endl
typedef long long int ll;
#define int long long int
typedef std::map< int,int> mii;
typedef std::vector< int > vi;
typedef std::vector< vi > vvi;
typedef std::pair< int,int > ii;
using namespace std;
vector <int>g[N];
// The graph is a tree with root assumed to be 1
int timer=0;
// n is number of vertices of tree
int n;
int maxh; // 2^maxh stores maximum height of tree for binary lifting
int dp[N+5][20]; // dp[v][i] stores ancestor of v at a height of 2^i from it
int tin[N+5];
int tout[N+5];
int h[N+5];
int siz[N+5];
void dfs2(int u,int p)
{
	h[u]=1+h[p];
	int c=1;
	for(auto &i : g[u]) 
	{
		if (i==p)
			continue;
		dfs2(i,u);
		c+=siz[i];
	}
	siz[u]=c;
}

void dfs(int u,int p)
{
	dp[u][0]=p;
	for (int i=1;i<=maxh;i++)
	{
		dp[u][i]=dp[dp[u][i-1]][i-1];
	}
	tin[u]=++timer;
	for(auto &i : g[u]) 
	{
		if (i==p)
			continue;
		dfs(i,u);
	}
	tout[u]=++timer;
}

// utility function to check ancestor
// returns true if u is ancestor of v
bool is_ancestor(int u,int v)
{
	return (tin[u]<=tin[v] and tout[u]>=tout[v]);
}

int lca(int u,int v)
{
	if (is_ancestor(u,v))
		return u;
	if (is_ancestor(v,u))
		return v;
	// lift u in powers of two to get to vertex w which is ancestor of v
	for(int i = maxh; i >=0 ; --i) 
	{
		// we lift u only when new value of u is not the ancestor of v
		if (!(is_ancestor(dp[u][i],v)))
			u=dp[u][i];
	}
	// now lca is located at distance 2^0 from new value of u
	return (dp[u][0]);
}

int get_ancestor(int u,int c)
{
	// find ancestor of u at a distance c from it using binary lifting
	if (c<=0)
		return u;
	for(int i = maxh; i >=0 ; --i) 
	{
		// we lift u only when new value of u is not the ancestor of v
		if (!(c&(1<<i)))
			continue;
			u=dp[u][i];
	}
	return u;
}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
#ifndef ONLINE_JUDGE
    freopen("C:\\Users\\hp\\Documents\\input.txt", "r", stdin);
    freopen("C:\\Users\\hp\\Documents\\output.txt", "w", stdout);
#endif
    // n is already defined globally
cin>>n;
maxh=(int)(ceil(log2(n)));
for(int i = 1; i <n; ++i) 
{
	int u,v;
	cin>>u>>v;
	g[u].push_back(v);
	g[v].push_back(u);
}
dfs(1,1);
dfs2(1,1);
// for lca of x and y
// debug(siz[1]);
int m;
cin>>m;
while(m--) 
{
	int x,y;
	cin>>x>>y;
	if (x==y)
	{
		cout<<n<<endl;
		continue;
	}
	if (h[y]>h[x])
		swap(x,y);

	int l=lca(x,y);
	int d=h[x]+h[y]-2*h[l];
	if (d&1)
	{
		cout<<0<<endl;
		continue;
	}
	int mid=d/2;
	int t=get_ancestor(x,mid);
	if (t==l)
	{
		cout<<(n-(siz[get_ancestor(x,mid-1)]+siz[get_ancestor(y,mid-1)]))<<endl;
		continue;
	}
	cout<<((siz[get_ancestor(x,mid)]-siz[get_ancestor(x,mid-1)]))<<endl;
}

}

// #Hala BBCF