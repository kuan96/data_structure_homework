#include<iostream>
#include<fstream>
#include<vector>
using namespace std;

vector<int> set;
vector<int> result;
fstream fin;
fstream fout;
string filename;

class node
{
    int vertex;
    node *link;
    friend class dfs;
};

class dfs
{
    private:
        node *adjlist[1000];
        int visit[1000];
        int total_vertex;
        int begin_num;
    public:
        void build();
        void dfs_search(int);
        void show();
        node* search_last(node*);
};

void dfs::build()
{
    int weight;
    node *newnode,*lastnode;
    fin>>total_vertex>>begin_num;
    set.push_back(total_vertex);
    for(int i=0;i<total_vertex;i++)//initialize
    {
        visit[i] = 0;//not visit yet
        adjlist[i] = new node;
        adjlist[i]->vertex = i;
        adjlist[i]->link = NULL;
    }
    for(int i=0;i<total_vertex;i++)
    {
        for(int j=0;j<total_vertex;j++)
        {
            fin>>weight;
            if(weight==1)
            {
                newnode = new node;
                newnode->vertex = j;
                newnode->link = NULL;
                lastnode = search_last(adjlist[i]);
                lastnode->link = newnode;
            }
        }
    }
}

node* dfs::search_last(node* n)
{
    node *ptr;
    ptr = n;
    while(ptr->link!=NULL)
        ptr = ptr->link;
    return ptr;
}

void dfs::dfs_search(int n)
{
    node *ptr;
    int nextnum;
    cout<<adjlist[n]->vertex<<" ";
    result.push_back(adjlist[n]->vertex);
    visit[n] = 1;//has been visited
    ptr = adjlist[n]->link;
    do
    {
        nextnum = ptr->vertex;
        if(!visit[nextnum])
            dfs_search(nextnum);
        else
            ptr = ptr->link;
    } while (ptr!=NULL);
    
}

void dfs::show()
{
    dfs_search(begin_num);
    cout<<endl;
}

int main()
{
    cout<<"filename: ";
    cin>>filename;
    fin.open(filename,ios::in);
    int dataset;
    fin>>dataset;
    for(int i=0;i<dataset;i++)
    {
        dfs obj;
        obj.build();
        obj.show();
    }

    fout.open("output_2.txt",ios::out);
    int count=0;
    for(int i=0;i<dataset;i++)
    {
        for(int j=0;j<set[i];j++)
            fout<<result[count++]<<" ";
        fout<<endl;          
    }

    fin.close();
    fout.close();
    system("pause");
    return 0;
}