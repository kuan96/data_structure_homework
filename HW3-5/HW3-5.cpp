#include<iostream>
#include<fstream>

using namespace std;

fstream fin;
fstream fout;
string filename;

class node
{
    int data;
    int weight;
    node* link;
    friend class dijkstra;
};

class dijkstra
{
    node **ptr;
    int n;
    int *result;
    int *visit;
    public:
        dijkstra(int);
        void build();
        node* search_last(node*);
        void count_path();
        void show();
        int find_min();
        int check();
};

dijkstra::dijkstra(int n)
{
    this->n = n;
    result = new int[n+1];
    visit = new int[n+1];
    ptr = new node*[n+1];
    node *newnode;
    for(int i=0;i<n+1;i++)
    {
        newnode = new node;
        newnode->data = i;
        newnode->weight = 0;
        newnode->link = NULL;
        ptr[i] = newnode;
    }
    for(int i=1;i<n+1;i++)
    {
        result[i] = 10000;
        visit[i] = 0;
    }
}

void dijkstra::build()
{
    int first,second,w;
    node *newnode,*lastnode;
    for(int i=1;i<n;i++)
    {
        fin>>first>>second>>w;
        newnode = new node;
        newnode->data = first;
        newnode->weight = w;
        newnode->link = NULL;
        lastnode = new node;
        lastnode = search_last(ptr[second]);
        lastnode->link = newnode;

        newnode = new node;
        newnode->data = second;
        newnode->weight = w;
        newnode->link = NULL;
        lastnode = new node;
        lastnode = search_last(ptr[first]);
        lastnode->link = newnode;        
    }
}

node* dijkstra::search_last(node *n)
{
    node *p=n;
    while(p->link!=NULL)
        p = p->link;
    return p;
}

void dijkstra::count_path()
{
    int index;
    fin>>index;
    visit[index] = 1;
    node *current = ptr[index];
    while(current!=NULL)
    {
        result[current->data] = current->weight;
        current = current->link;
    }
    while(check())
    {
        int index = find_min();
        visit[index] = 1;
        node *p = ptr[index]->link;
        while(p!=NULL)
        {
            int w = result[index]+p->weight;
            if(w<result[p->data])
                result[p->data] = w;
            p = p->link;
        }
    }
}

int dijkstra::find_min()
{
    int min = 10000;
    int index=1;
    for(int i=1;i<n+1;i++)
    {
        if(result[i]<min && visit[i]==0)
        {
            min = result[i];
            index = i;
        }
    }
    return index;
}

int dijkstra::check()
{
    for(int i=1;i<n+1;i++)
    {
        if(visit[i]!=1) return 1;//keep going
    }
    return 0;
}

void dijkstra::show()
{
    for(int i=1;i<n+1;i++)
    {
        fout<<i<<" "<<result[i];
        fout<<endl;
    }
}

int main()
{
    cout<<"filename: ";
    cin>>filename;
    fin.open(filename,ios::in);
    fout.open("output_5.txt",ios::out);

    int v_num;
    fin>>v_num;
    dijkstra obj(v_num);
    obj.build();
    obj.count_path();
    obj.show();

    fin.close();
    fout.close();
    system("pause");
    return 0;
}