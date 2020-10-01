#pragma GCC optimize("Ofast")
#include "bits/stdc++.h"
#define rep(i,j,n) for(int i=(j);i<=((int)n);++i)
#define rev(i,n,j) for(int i=(n);i>=((int)j);--i)
typedef long long int ll;
#define int long long int
const ll INFL=0x3f3f3f3f3f3f3f3fLL;
const int INF=0x3f3f3f3f;
const int mod=1000000007;
#define endl "\n"
#define mem(a,val) memset(a,val,sizeof(a))
#define all(c) (c).begin(),(c).end()
#define tr(container, it) for(__typeof(container.begin()) it = container.begin(); it != container.end(); it++)
#define present(container, element) (container.find(element) != container.end())
#define pb push_back
#define FAST ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define readmat(a, n, m) int a[n + 5][m + 5] = {}; rep(i, 1, n) {rep(j, 1, m) cin >> a[i][j];}
#define printmat(a, n, m) rep (i, 1, n) {rep (j, 1, m) cout << a[i][j] << " "; cout << endl;} cout << endl;
#define printarr(a, n) rep(i, 0, n) cout << a[i] << " "; cout << endl;
typedef std::map< int,int> mii;
typedef std::vector< int > vi;
typedef std::vector< vi > vvi;
typedef std::pair< int,int > ii;
using namespace std;
#define cerr cout
#define error(args...) { string _s = #args; replace(_s.begin(), _s.end(), ',', ' '); stringstream _ss(_s); istream_iterator<string> _it(_ss); err(_it, args); }
void err(istream_iterator<string> it) {}
template<typename T, typename... Args>
void err(istream_iterator<string> it, T a, Args... args) {
    cout << *it << " = " << a << endl;
    err(++it, args...);}
const int N = 1e6+5, M = N;
vector <int>g[N];
int a[50];
int n;

void bubbleSort()
{
    int b[50];
    for(int i = 0; i <n; ++i) 
    {
        b[i]=a[i];
    }
    for(int i = 0; i <n; ++i) 
    {
        for(int j = 0; j <n-i-1; ++j) 
        {
            if (b[j]>b[j+1])
                swap(b[j],b[j+1]);
        }
    }

    printarr(b,n-1);
}

void selectionSort()
{
    int b[50];
    for(int i = 0; i <n; ++i) 
    {
        b[i]=a[i];
    }

    for(int i = 0; i <n; ++i) 
    {
        int mx=b[0];
        int p=0;
        for(int j = 0; j <n-i; ++j) 
        {
            if (b[j]>mx)
            {
                mx=b[j];
                p=j;
            }
        }
        swap(b[n-i-1],b[p]);
    }

    printarr(b,n-1);
}

void insertionSort()
{
    int b[50];
    for(int i = 0; i <n; ++i) 
    {
        b[i]=a[i];
    }

    for(int i = 0; i <n; ++i) 
    {
        for (int j=i-1;j>=0;j--)
        {
            if (b[j]>b[j+1])
                swap(b[j],b[j+1]);
        }
    }

    printarr(b,n-1);
}


void mergeSortHelper(int l,int r,int b[])
{
    if (l>=r)
        return;
    int mid=(l+r)/2;
    mergeSortHelper(l,mid,b);
    mergeSortHelper(mid+1,r,b);

    int k[r-l+2];
    int i=l;
    int j=mid+1;
    int p=0;
    while(i<=mid and j<=r) 
    {
        if (b[i]<b[j])
        {
            k[p]=b[i];
            i++;
            p++;
        }
        else
        {
            k[p]=b[j];
            j++;
            p++;
        }
    }

    while(i<=mid) 
    {
        k[p]=b[i];
        i++;
        p++;
    }

    while(j<=r) 
    {
        k[p]=b[j];
        j++;
        p++;
    }

    int pos=l;
    for(int i = 0; i <r-l+1; ++i) 
    {
        b[pos]=k[i];
        pos++;
    }

}

void mergeSort()
{
    int b[50];
    for(int i = 0; i <n; ++i) 
    {
        b[i]=a[i];
    }

    mergeSortHelper(0,n-1,b);
    printarr(b,n-1);

}

int partition(int l,int r,int b[])
{
    int i=l-1;
    int j=l;
    int val=b[r];
    while(j<r) 
    {
        if (b[j]>val)
        {
            j++;
        }
        else 
        {
            i++;
            swap(b[i],b[j]);
            j++;
        }
    }
    return i+1;
}


void quickSortHelper(int l,int r,int b[])
{
    if (l>=r)
        return;
    int p=partition(l,r,b);
    swap(b[p],b[r]);
    quickSortHelper(l,p-1,b);
    quickSortHelper(p+1,r,b);

}

void quickSort()
{
    int b[50];
    for(int i = 0; i <n; ++i) 
    {
        b[i]=a[i];
    }

    quickSortHelper(0,n-1,b);
    printarr(b,n-1);
}


void buildHeap(int b[],int x)
{
    while(x>0) 
    {
        int p=(x-1)/2;
        if (b[x]>b[p])
        {
            swap(b[x],b[p]);
            x=p;
            p=(x-1)/2;
        }
        else
            break;
    }

}


void downHeapify(int b[],int sz,int x)
{
    if (x>sz)
        return;
    int l=2*x+1;
    int r=2*x+2;
    int largest=x;
    if (l<sz and b[l]>b[largest])
        largest=l;
    if (r<sz and b[r]>b[largest])
        largest=r;

    if (largest!=x)
    {
        swap(b[largest],b[x]);
        downHeapify(b,sz,largest);
    }


}

void heapSort()
{
    int b[50];
    for(int i = 0; i <n; ++i) 
    {
        b[i]=a[i];
    }

    for(int i = 1; i <n; ++i) 
    {
        buildHeap(b,i);
    }

    for(int i = n-1; i >=0 ; --i) 
    {
        swap(b[0],b[i]);
        downHeapify(b,i,0);
    }

    printarr(b,n-1);

}




void solve()
{
    cin>>n;
    for(int i = 0; i <n; ++i) 
    {
        cin>>a[i];
    }

    bubbleSort();
    selectionSort();
    insertionSort();
    mergeSort();
    quickSort();
    heapSort();
  

}



signed main()
{
  FAST;
#ifdef LOCAL
    freopen("C:\\Users\\hp\\Documents\\input.txt", "r", stdin);
    freopen("C:\\Users\\hp\\Documents\\output.txt", "w", stdout);
    std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
    start = std::chrono::high_resolution_clock::now();
#endif

solve();

#ifdef LOCAL
    end = std::chrono::high_resolution_clock::now();
    ll elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
    cout<<endl;
    cout << "\nElapsed Time: " << elapsed_time << "ms\n";
#endif

return 0;

}

// vector string set map first second continue break return upper_bound lower_bound length void sort
// stack queue pop size erase empty insert
// #Hala BBCF

