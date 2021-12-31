#include<iostream>
#include<fstream>
#include<string.h>
#include<vector>
using namespace std;

int dataset;
char s_input[100][1000];
int n1[100][1000];
int n2[100][1000];
int nodenum[100];
vector<int> myvector;

struct node
{
    int data;
    struct node *leftchild;
    struct node *rightchild;
};

class tree
{
    struct node *root=NULL,*ptr=NULL,*current = NULL,*prev = NULL;

public:
    void Insert();
    void preorder(struct node *);
    void inorder(struct node *);
    void postorder(struct node *);
    void show();
    int find_index(int,int[][1000],int,int);
};

int tree::find_index(int num,int arr[100][1000],int row,int col)
{
    for(int i=0;i<col;i++)
        if(arr[row][i] == num)
            return i;
    return -1;
}

void tree::Insert()
{
    for(int i=0;i<dataset;i++)
    {
        if(strcmp(s_input[i],"preorder-inorder")==0)
        {
            ptr = new node;
            ptr->data = n1[i][0];
            ptr->leftchild = ptr->rightchild = NULL;
            root = ptr;
            for(int j=1;j<nodenum[i];j++)
            {
                current = root;
                ptr = new node;
                ptr->data = n1[i][j];
                ptr->leftchild = ptr->rightchild = NULL;
                while(current!=NULL)
                {
                    if(find_index(ptr->data,n2,i,nodenum[i])<find_index(current->data,n2,i,nodenum[i]))
                    {
                        prev = current;
                        current = current->leftchild;
                    }
                    else
                    {
                        prev = current;
                        current = current->rightchild;
                    }
                }
                if(find_index(ptr->data,n2,i,nodenum[i])<find_index(prev->data,n2,i,nodenum[i]))
                    prev->leftchild = ptr;
                else
                    prev->rightchild = ptr;
            }
            postorder(root);
            cout<<endl;
            root = NULL;
        }
        else if(strcmp(s_input[i],"postorder-inorder")==0)
        {
            ptr = new node;
            ptr->data = n1[i][nodenum[i]-1];
            ptr->leftchild = ptr->rightchild = NULL;
            root = ptr;
            for(int j=nodenum[i]-2;j>=0;j--)
            {
                current = root;
                ptr = new node;
                ptr->data = n1[i][j];
                ptr->leftchild = ptr->rightchild = NULL;
                while(current!=NULL)
                {
                    if(find_index(ptr->data,n2,i,nodenum[i])<find_index(current->data,n2,i,nodenum[i]))
                    {
                        prev = current;
                        current = current->leftchild;
                    }
                    else
                    {
                        prev = current;
                        current = current->rightchild;
                    }
                }
                if(find_index(ptr->data,n2,i,nodenum[i])<find_index(prev->data,n2,i,nodenum[i]))
                    prev->leftchild = ptr;
                else
                    prev->rightchild = ptr;
            }
            preorder(root);
            cout<<endl;
            root = NULL;
        }
        else if(strcmp(s_input[i],"inorder-preorder")==0)
        {
            ptr = new node;
            ptr->data = n2[i][0];
            ptr->leftchild = ptr->rightchild = NULL;
            root = ptr;
            for(int j=1;j<nodenum[i];j++)
            {
                current = root;
                ptr = new node;
                ptr->data = n2[i][j];
                ptr->leftchild = ptr->rightchild = NULL;
                while(current!=NULL)
                {
                    if(find_index(ptr->data,n1,i,nodenum[i])<find_index(current->data,n1,i,nodenum[i]))
                    {
                        prev = current;
                        current = current->leftchild;
                    }
                    else
                    {
                        prev = current;
                        current = current->rightchild;
                    }
                }
                if(find_index(ptr->data,n1,i,nodenum[i])<find_index(prev->data,n1,i,nodenum[i]))
                    prev->leftchild = ptr;
                else
                    prev->rightchild = ptr;
            }
            postorder(root);
            cout<<endl;
            root = NULL;
        }
        else if(strcmp(s_input[i],"inorder-postorder")==0)
        {
            ptr = new node;
            ptr->data = n2[i][nodenum[i]-1];
            ptr->leftchild = ptr->rightchild = NULL;
            root = ptr;
            for(int j=nodenum[i]-2;j>=0;j--)
            {
                current = root;
                ptr = new node;
                ptr->data = n2[i][j];
                ptr->leftchild = ptr->rightchild = NULL;
                while(current!=NULL)
                {
                    if(find_index(ptr->data,n1,i,nodenum[i])<find_index(current->data,n1,i,nodenum[i]))
                    {
                        prev = current;
                        current = current->leftchild;
                    }
                    else
                    {
                        prev = current;
                        current = current->rightchild;
                    }
                }
                if(find_index(ptr->data,n1,i,nodenum[i])<find_index(prev->data,n1,i,nodenum[i]))
                    prev->leftchild = ptr;
                else
                    prev->rightchild = ptr;
            }
            preorder(root);
            cout<<endl;
            root = NULL;
        }
    }
}

void tree::preorder(struct node *n)
{
    if(n != NULL)
    {
        cout<<n->data<<" ";
        myvector.push_back(n->data);
        preorder(n->leftchild);
        preorder(n->rightchild);
    }
}

void tree::inorder(struct node *n)
{
    if(n != NULL)
    {
        inorder(n->leftchild);
        cout<<n->data<<" ";
        myvector.push_back(n->data);
        inorder(n->rightchild);
    }
}

void tree::postorder(struct node *n)
{
    if(n != NULL)
    {
        postorder(n->leftchild);
        postorder(n->rightchild);
        cout<<n->data<<" ";
        myvector.push_back(n->data);
    }
}

int main()
{
    string filename;
    cout<<"filename: ";
    cin>>filename;
    ifstream fin;
    fin.open(filename,ios::in);
        fin>>dataset;
        for(int i=0;i<dataset;i++)//input
        {
            fin>>s_input[i];
            fin>>nodenum[i];
            for(int j=0;j<nodenum[i];j++)
                fin>>n1[i][j];
            for(int j=0;j<nodenum[i];j++)
                fin>>n2[i][j];
        }
    fin.close();

    tree T;
    T.Insert();

    ofstream fout;
    fout.open("output_1.txt",ios::out);
        int count=0;
        for(int i=0;i<dataset;i++)
        {
            for(int j=0;j<nodenum[i];j++)
                fout<<myvector[count++]<<" ";
            fout<<endl;
        }
        fout.close();

    system("pause");
    return 0;
}
