#include<iostream>
#include<deque>
#include<vector>
#include<fstream>
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
    friend class bfs;
};

class bfs
{
    private:
        node *adjlist[1000];
        int visit[1000];
        int total_vertex;
        int begin_num;
    public:
        void build();
        void bfs_search(int);
        void show();
        node* search_last(node*);
};

void bfs::build()
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

node* bfs::search_last(node* n)
{
    node *ptr;
    ptr = n;
    while(ptr->link!=NULL)
        ptr = ptr->link;
    return ptr;
}

void bfs::bfs_search(int n)
{
   node *ptr;
   deque<int> q;
   int num;
   q.push_back(n);
   visit[n] = 1;
   while(!q.empty())
   {
       num = q.front();
       cout<<num<<" ";
       result.push_back(num);
       q.pop_front();
       ptr = adjlist[num]->link;
       while(ptr!=NULL)
       {
           if(!visit[ptr->vertex])
           {
                q.push_back(ptr->vertex);
                visit[ptr->vertex] = 1;
           }            
           ptr = ptr->link;
       }
   }
   
}

void bfs::show()
{
    bfs_search(begin_num);
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
        bfs obj;
        obj.build();
        obj.show();
    }

    fout.open("output_3.txt",ios::out);
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