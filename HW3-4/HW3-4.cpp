#include<iostream>
#include<vector>
#include<algorithm>
#include<fstream>
using namespace std;

fstream fin;
fstream fout;
string filename;

class Graph
{
    private:
        int V,E;
        vector<pair<int,pair<int,int>>> edges;
    public:
        Graph(int v,int e){V=v; E=e;}
        void addedge(int,int,int);
        int kruskal();
    friend class set;
};

class set
{
    private:
        int *parent,*rank;
    public:
        set(int);
        int find(int);
        void connect(int,int);
    friend class Graph;
};

void Graph::addedge(int x,int y,int w)
{
    edges.push_back({w,{x,y}});
}

int Graph::kruskal()
{
    int result=0;
    sort(edges.begin(),edges.end());
    set s(V);

    vector<pair<int,pair<int,int>>> ::iterator ptr;
    for(ptr=edges.begin();ptr<edges.end();ptr++)
    {
        int v1 = ptr->second.first;
        int v2 = ptr->second.second;

        int set1 = s.find(v1);
        int set2 = s.find(v2);

        if(set1!=set2)
        {
            result += ptr->first;
            s.connect(v1,v2);
        }
    }
    return result;
}

set::set(int n)
{
    parent = new int[n+1];
    rank = new int[n+1];
    for(int i=0;i<=n;i++)
    {
        parent[i] = i;
        rank[i] = 0;
    }
}

int set::find(int n)
{
    if(n!=parent[n])
        parent[n] = find(parent[n]);
    return parent[n];
}

void set::connect(int x,int y)
{
    x = find(x);
    y = find(y);

    if(rank[x]>rank[y])
        parent[y] = x;
    else
        parent[x] = y;
    if(rank[x]==rank[y])
        rank[y]++;
}

int main()
{
    cout<<"filename: ";
    cin>>filename;
    fin.open(filename,ios::in);

    int v,e;
    fin>>v>>e;
    Graph G(v,e);
    
    int x,y,w;
    for(int i=0;i<e;i++)
    {
        fin>>x>>y>>w;
        G.addedge(x,y,w);
    }
    int result = G.kruskal();
    cout<<result;

    fout.open("output_4.txt",ios::out);
    fout<<result<<endl;

    fin.close();
    fout.close();
    system("pause");
    return 0;
}