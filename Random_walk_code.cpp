/*
 *
 * Random Walk Wallpaper
 *
 * Netpbm Format (ppm)
 *
 * 
 */
// Special thanks to Raziman TV .
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <deque>
#include <queue>
#include <stack>
#include <set>
#include <cstring>
#include <list>
#include <map>
#include <iomanip>
#include <algorithm>
#include <functional>
#include <utility>
#include <bitset>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cstdio>
using namespace std;
typedef long long          ll;
typedef unsigned long long ull;
typedef long double        ld;
typedef pair<int,int>      pii;
typedef pair<ll,ll>        pll;
typedef vector<int>        vi;
typedef vector<long long>  vll;
#define l(x)               (x << 1) + 1
#define r(x)               (x << 1) + 2
#define mid(l, r)          ((l + r) >> 1)
#define mp                 make_pair
#define pb                 push_back
#define all(a)             a.begin(),a.end()
#define sor(a)             sort(all(a));
#define pr(n)              printf("%d ",n)
#define s(n)               scanf("%d",&n)
#define debug(x)       {cerr <<#    x<<" = " <<x<<"\n"; }
#define debug2(x, y)       {cerr <<#x<<" = " <<x<<", "<<#y <<" = " <<y <<"\n";}
#define ss                 second
#define ff                 first
#define m0(x)              memset(x,0,sizeof(x))
#define snuke(c,itr)       for(__typeof((c).begin()) itr=(c).begin();itr!=(c).end();itr++)
const int mod=1e9+7;

const ll  mx_ll   = numeric_limits<ll> :: max();
const int mx_int  = numeric_limits<int> :: max();

const long double PI = (long double)(3.1415926535897932384626433832795);

inline bool ispow2(int x){return (x!=0 && (x&(x-1))==0);} //0 or 1

int msb(unsigned x){ union { double a; int b[2]; }; a = x; return (b[1] >> 20) - 1023; }

template<class T>
inline void cinarr(T a, int n){ for (int i=0;i<n;++i) cin >> a[i];}

inline ll powmod(ll a,ll b) {ll res = 1; while(b){if(b&1) res = (res*a)%mod;a = (a*a)%mod;b >>= 1;}return res;}

inline ll gcd(ll a,ll b){ll t;while(b){a=a%b;t=a;a=b;b=t;}return a;}
inline ll lcm(ll a,ll b){return a/gcd(a,b)*b;}

inline int next(){ int x; scanf("%d",&x); return x; }

const ll dim_x = 1920;
const ll dim_y = 1200;

struct nn
{
    int r , g , b;
    nn()
    {
        r = g = ( b = 0);
    }
};

nn node[dim_x+1][dim_y+1];

void print_node( nn a )
{
    cout << a.r << " " << a.g << " " << a.b << " ";
}

void print_grid()
{

    for(int i = 0; i < dim_x; i++)
    {
        for(int j = 0; j < dim_y; j++)
        {
            print_node(node[i][j]);
        }
        cout << "\n";
    }
}

bool white_node(nn x )
{
    if ( x.r == 255 && x.g == 255 && x.b == 255)
        return true;
    else
        return false;
}
bool black_node(nn x )
{
    if ( x.r == 0 && x.g == 0 && x.b == 0)
        return true;
    else
        return false;
}

bool check(int x ,int y )
{
    return ( x < dim_x && x >= 0  && y < dim_y && y >= 0 );
}

const int X=1920,Y=1080;
const double dropratio = pow(0.01,1./1000);
const int CMAX=1000,RMAX=100;

double c[X][Y],r[X][Y],g[X][Y],b[X][Y];
double mx=0;

int neigh[4][2]={{1,0},{0,1},{-1,0},{0,-1}};

inline void updatepos(int& x,int& y)
{
    if(x<0)x+=X;if(x>=X)x-=X;
    if(y<0)y+=Y;if(y>=Y)y-=Y;
}

inline void addcol(double col[X][Y],int x,int y,double val)
{
    for(int i=0;i<3;i++)
    {
        int xx=x+i;
        for(int j=0;j<3;j++)
        {
            int yy=y+j;
            updatepos(xx,yy);
            col[xx][yy]+=val;
            mx=max(mx,col[xx][yy]);
        }
    }
}

inline void work()
{
    int posx=(rand()%(X/10))*10,posy=(rand()%(Y/10))*10;
    double vval=4,val[3]={0,0,0};
    while(vval>0.01)
    {
        int dir=rand()%4;
        for(int i=0;i<10;i++)
        {
            addcol(c,posx,posy,vval);
            posx+=neigh[dir][0];posy+=neigh[dir][1];
            updatepos(posx,posy);
            vval*=dropratio;
        }
    }
}

int main()
{
    for(int i=0;i<500;i++)
    {
    work();
  }

  printf("P3\n");
  printf("%d %d\n",X,Y);
  printf("%d\n",CMAX);
  for(int y=0;y<Y;y++)
  {
    for(int x=0;x<X;x++)
    {
      double val[3];
      c[x][y]*=2/mx;
      if(c[x][y]<1)
      {
        val[0]=0;
        val[1]=c[x][y];
        val[2]=0;
      }
      else if(c[x][y]<2)
      {
        val[0]=c[x][y]-1;
        val[1]=1;
        val[2]=0;
      }
      else
      {
        val[0]=1;
        val[1]=1;
        val[2]=min(1.,c[x][y]-2);
      }
      printf("%d %d %d\n",(int)(val[0]*CMAX),(int)(val[1]*CMAX),(int)(val[2]*CMAX));
    }
  }
  return 0;
}

