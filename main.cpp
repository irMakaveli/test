#include<iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <limits.h>
#include<array>
#define V 16
using namespace std;
struct nodes{
    float weight;
    float traffic;
};
class shortestPath
{
    friend vector<int> findPath(shortestPath a,int origin, int dest, bool visited[V], vector<int>path);

    int dest;
    int origin;
    nodes graph[V][V];
    nodes sptree[V][V];
    bool costPriority;
    public:
    shortestPath();
    shortestPath(nodes [V][V]);
    void createSPT();
    void setDestination(int);
    int getDestination();
    void setorigin(int);
    int getorigin();
    void settrafic(int,int , float);
    float gettrafic(int,int);
    void setweight(int,int , float);
    float getweight(int,int);
    void setPriority(string);
    bool getPriority();
};
vector<int> findPath(shortestPath a,int origin, int dest, bool visited[V], vector<int>path)
{
    if(!visited[origin])
    {
     path.push_back(origin);
     visited[origin]=true;
     }  
    if(a.sptree[origin][dest].weight!= 0)
    {
        path.push_back(dest);
        for (size_t i = 0; i < V; i++)
        {
            visited[i]=true;
        }
        return path;
    }
    for(int i = 0; i<V; i++)
    {
        if(a.sptree[origin][i].weight != 0 && !visited[i])
        {
            return findPath(a,i,dest,visited,path);
        }
    }
     
    path.pop_back();
    return findPath(a,path.back(),dest, visited , path);
}
void showPath(vector<int>path)
{
    for(int i = 0; i<path.size(); i++)
    {
       cout<<path[i];
       if(i<path.size()-1)
       cout<<"->";
    }
    cout<<endl;
}
void shortestPath::setorigin(int o)
{
    this->origin = o;
} 
int shortestPath::getorigin()
{
    return origin;
}
void shortestPath::setDestination(int d)
{
    this->dest = d;
} 
int shortestPath::getDestination()
{
    return dest;
}
void shortestPath::setPriority(string s)
{
    if(s=="time")
    {
        costPriority=false;
    }
    else{
        costPriority=true;
    }
}
bool shortestPath::getPriority()
{
    return this->costPriority;
}
shortestPath::shortestPath()
{

}
void shortestPath::setweight(int i,int j, float k)
{
    if( k > 0)
    {
        graph[i][j].weight=k;
    }
}
float shortestPath::getweight(int i,int j)
{
    return  graph[i][j].weight;
}
float shortestPath::gettrafic(int i,int j)
{
    return graph[i][j].traffic;
}
void shortestPath::settrafic(int i,int j, float k)
{
    if(k==1||k==2||k==3)
    {
        graph[i][j].traffic = k;
    }
    else
    {
        cout<<"invalid number"<<endl;
    }
}
shortestPath::shortestPath(nodes a[V][V])
{
    costPriority=false;
    for (size_t i = 0; i < V; i++)
    {
        for (size_t j = 0; j < V; j++)
        {
            graph[i][j].traffic = a[i][j].traffic;
            graph[i][j].weight = a[i][j].weight;
        }
    }
}
void shortestPath::createSPT()
{
    bool spt[V];
    float deg[V]; 
    float cost[V]; 
    vector<int>visited;  
    visited.push_back(getorigin());
    for (size_t i = 0; i < V; i++)
    {
        spt[i] =false;
        deg[i]= INT_MAX;
        cost[i]= INT_MAX;
        for(int j = 0; j < V; j++)
        {
            sptree[i][j].traffic = 0;
            sptree[i][j].weight = 0;
        }
       // cout<<endl;
    }
    deg[getorigin()] = 0;
    cost[getorigin()]=0;
    spt[getorigin()]=true;
    int row,column ;
   float min = INT_MAX ;
   float  mincost=INT_MAX;
    while ( visited.size()<V)
    {    
        for(int i = 0 ;i < visited.size() ; i++)
        {
            for(int j =0 ;j < V ; j++)
            {
                if(getweight(visited[i],j)!= 0 && spt[j] == false)
                {
                    if(!getPriority())
                    {
                        if(min > deg[visited[i]] + getweight(visited[i],j) )
                        {
                            min = deg[visited[i]]+graph[visited[i] ][j].weight;
                            row = visited[i];
                            column = j ;
                            mincost = cost[visited[i]] + getweight(visited[i],j)*gettrafic(visited[i],j);
                        }
                    }
                    else
                    {
                        if(mincost> cost[visited[i]] +getweight(visited[i],j)*gettrafic(visited[i],j))
                        {
                            min = deg[visited[i]]+graph[visited[i] ][j].weight;
                            row = visited[i];
                            column = j ;
                            mincost = cost[visited[i]] + getweight(visited[i],j)*gettrafic(visited[i],j);
                        }
                    }
                }        
            }        
        }
        deg[column]=min;
        spt[column]=true;
        cost[column]=mincost;
        visited.push_back(column);
        sptree[row][column].weight= min;
        sptree[row][column].traffic= mincost;
        min=INT_MAX,mincost=INT_MAX;
    }
    for (size_t i = 0; i < V; i++)
    {
        for(int j =0 ; j <V ;j++)
        {
            cout<<sptree[i][j].weight<<"  ";
        }
        cout<<endl;
    }
    
}
int getcommands()
{
    cout
    <<"1 -> change Priority"<<endl
    <<"2 -> choose destination"<<endl
    <<"3 -> show path"<<endl
    <<"4 -> exit"<<endl
    <<"5 -> set traffic"<<endl
    <<"6 -> set weight"<<endl;
    int c;
    cin>>c;
    return c;
}
int main()
{
    nodes graph[V][V];
    shortestPath a(graph);
    a.setorigin(0);
    a.setDestination(4);
    bool v[V];
    vector<int >path;
    int cmnd= getcommands();
    string c;
    while(cmnd != 4)
    {
        if(cmnd==1)
        {
            cout<<"choose priority"<<endl;
            cout<<"-> cost"<<endl;
            cout<<"-> time "<<endl;
            cin>>c;
            a.setPriority(c);
        }
        if(cmnd==2)
        {
            cout<<"enter destination"<<endl;
            int c;
            cin>>c;
            a.setDestination(c);
        }
        if(cmnd==3)
        {
            
            a.createSPT();
            path = findPath(a,a.getorigin(),a.getDestination(),v,path);
            showPath(path);
            path.clear();
            for (size_t i = 0; i < V; i++)
            {
                v[i]=false;
            }
        }
        if(cmnd ==5)
        {
            float A;
            int b,c;
            cout<<"enter row"<<endl;
            cin>>b;
            cout<<"enter column"<<endl;
            cin>>c;
            cout<<"enter traffic value"<<endl;
            a.settrafic(b,c,A);
            cout<<"done"<<endl;
        }
        if(cmnd ==6)
        {
            float A;
            int b,c;
            cout<<"enter row"<<endl;
            cin>>b;
            cout<<"enter column"<<endl;
            cin>>c;
            cout<<"enter weight "<<endl;
            a.setweight(b,c,A);
            cout<<"done"<<endl;
        }
        cmnd= getcommands();
    }
    return 0;
}