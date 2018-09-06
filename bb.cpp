#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

#define N 10
#define INF INT_MAX

int mat [N][N]= {{0,1,1,3,6,4,8,8,12,10},
                {1,0,3,3,7,3,7,8,14,10},
                {1,1,0,3,8,5,8,10,13,10},
                {3,3,3,0,6,2,4,5,11,12},
                {6,7,8,6,0,3,6,5,6,8},
                {4,3,5,2,3,0,5,4,9,5},
                {8,7,8,4,6,5,0,2,5,7},
                {8,8,10,5,5,4,2,0,4,5},
                {12,14,13,11,6,9,5,4,0,3},
                {10,10,10,12,8,5,7,5,3,0}};
int somepl[N][N]={0};
int sample[N][N];
int nn_path[N]={0};
int ff_dist[N][N];



void print(int graph[N][N])
{
    char c;
     for(int row=-1;row<N;row++)
    {
        for(int col=-1;col<N;col++)
        {
            if(row==-1&&col>=0)
            {
                c=(char)col+97;
                cout<<c<<'\t';
            }
            else if(row>-1&&col>-1)
            {
                cout<<graph[row][col]<<'\t';
            }
            else if(col==-1 && row>=0)
            {
                 c=(char)row+97;
                cout<<c<<'\t';
            }
            else
            {
                cout<<"\t";
            }
        }


       cout<<'\n';
     }
}

void someplaces(int mat[N][N],int point)
{
    cout<<point;
    for(int i=0;i<N;i++)
    {

           somepl[i][point]=mat[i][point];

    }
}

void copy(int graph[N][N])
{   //memset(sample,-1,sizeof(sample));
    for(int i=0;i<N;i++)
    {
        for(int j=0;j<N;j++)
        {
            sample[i][j]=graph[i][j];
        }
    }
}
int nn_visited[N]={0};

int tr=0;
int nn_next(int current,int sample[N][N])
{   nn_visited[0]=1;
    int min=9999;

    int p;
    int index;
if(tr==0)
{
    p=1;
}
else
{
    return 0;
}
    for(int t=p;t<N;t++)
    {
        if(sample[current][t]<min&&sample[current][t]!=0 && nn_visited[t]==0)
        {
            min=sample[current][t];
            index=t;
        }
    }
    nn_visited[index]=true;
    return index;
}
void display(int sample[N][N],int current,int index)
{
    for(int row=0;row<N;row++)
    {
        for(int col=0;col<N;col++)
        {   if(row==current&&col==index)
                {cout<<" {";}
            cout<<sample[row][col]<<' ';
            if(row==current&&col==index)
            {cout<<"} ";}
        }

       cout<<'\n';
     }
    // cout<<"head to row -->"<<index+1;
    cout<<'\n'<<endl;
}
void timetaken(int cost)
{
    float hrs,mins;
    cout<<"considering average town speed of delivery boy to be 25km/hr \n";
    hrs= (float)cost/25;
    //cout<< hrs;
    mins= hrs*60;
    cout<<" It would take the delivery man "<<hrs<<" hours or "<<mins<<" mins to cover the destinations \n";

}

void nearest_neighbour(int mat[N][N],int total)
{
    int nn_cost=0;
    int current=0;
    int index;
    int start=0;
    int count=0;
    nn_path[count]=current;

    while(count!=total)
    {  // cout<<"cost "<<nn_cost<<endl;
     if(count==total-1)
     { // cout<<"last\t: ";
      tr=1;
     }
         index=nn_next(current,sample);
        nn_path[++count]=index;
         nn_cost+=sample[current][index];
       // cout<<current<<index<<endl;
        //display(sample,current,index);
        sample[index][current]=0;
         current=index;
}
    nn_path[++count]=current;

    nn_cost+=mat[current][0];
    cout<<"Path :";
    for(int i=0;i<total;i++)
    {
        cout<<nn_path[i]<<"-->";
    }
    cout<<start<<"\n\n";
    cout<<"Cost ="<<nn_cost<<endl;
    timetaken(nn_cost);



}

int floydwar (int graph[][N],int start,int end)
{

    int  i, j, k;

    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            ff_dist[i][j] = graph[i][j];
        }
    }

    for (k = 0; k < N; k++)
    {

        for (i = 0; i < N; i++)
        {

            for (j = 0; j < N; j++)
            {

                if (ff_dist[i][k] + ff_dist[k][j] < ff_dist[i][j])
                    ff_dist[i][j] = ff_dist[i][k] + ff_dist[k][j];
            }
        }
    }


    return ff_dist[start][end];
}





struct Node
{
    vector<pair<int, int>> bb_path;
    int reducedmat[N][N];
    int cost;
    int vertex;
    int level;
};

Node* newnode(int parentmat[N][N], vector<pair<int, int>> const &bb_path,int level, int i, int j)
{
    Node* node = new Node;

    node->bb_path = bb_path;

    if (level != 0)
        node->bb_path.push_back(make_pair(i, j));

    memcpy(node->reducedmat, parentmat,sizeof (node->reducedmat));

    for (int k = 0; level != 0 && k < N; k++)
    {
        node->reducedmat[i][k] = INF;

        node->reducedmat[k][j] = INF;
    }

    node->reducedmat[j][0] = INF;

    node->level = level;

    node->vertex = j;

    return node;
}
int rowreduc(int reducedmat[N][N], int row[N])
{
    fill_n(row, N, INF);


    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
           {
                if (reducedmat[i][j] < row[i])
                    row[i] = reducedmat[i][j];
           }

    }
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (reducedmat[i][j] != INF && row[i] != INF)
                reducedmat[i][j] -= row[i];
        }
    }
}

int colreduc(int reducedmat[N][N], int col[N])
{

    fill_n(col, N, INF);


    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (reducedmat[i][j] < col[j])
                col[j] = reducedmat[i][j];
        }
    }

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (reducedmat[i][j] != INF && col[j] != INF)
                reducedmat[i][j] -= col[j];
        }
    }
}


int calculatecost(int reducedmat[N][N])
{
    int cost = 0;

    int row[N];
    rowreduc(reducedmat, row);

    int col[N];
    colreduc(reducedmat, col);

    for (int i = 0; i < N; i++)
    {
        if(row[i]!=INT_MAX)
            cost+=row[i];
        if(col[i]!=INT_MAX)
            cost+=col[i];
    }

    return cost;
}

void printbb_path(vector<pair<int, int>> const &list)
{int i;
    for (i = 0; i < list.size(); i++)
        {cout << list[i].first;
        if(i!=list.size()-1)
        {
            cout<<"-->";
        }
    }
    cout<<"\n\n";
}

struct comp {
    bool operator()(const Node* lhs, const Node* rhs) const
    {
        return lhs->cost > rhs->cost;
    }
};


int bb_tsp(int costmat[N][N])
{
    priority_queue<Node*, std::vector<Node*>, comp> pq;

    vector<pair<int, int>> v;

    Node* root = newnode(costmat, v, 0, -1, 0);

    root->cost = calculatecost(root->reducedmat);

    pq.push(root);

    while (!pq.empty())
    {
        Node* min = pq.top();

        pq.pop();

        int i = min->vertex;

        if (min->level == N - 1)
        {
            min->bb_path.push_back(make_pair(i, 0));

            printbb_path(min->bb_path);

            return min->cost;
        }
        for (int j = 0; j < N; j++)
        {
            if (min->reducedmat[i][j] != INF)
            {

                Node* child = newnode(min->reducedmat, min->bb_path,min->level + 1, i, j);

                child->cost = min->cost + min->reducedmat[i][j]+ calculatecost(child->reducedmat);

                pq.push(child);
            }
        }
        delete min;
    }
}


int main() {


    cout<<"\t\t\t\t Courier delivery \t\n\n";

    cout<<"\t\t MENU\n\n";

    cout<<" -- 1. Enter 1 to Tour complete city \n\n";

    cout<<" -- 2. Enter 2 to Enter Delivery Points \n\n";

    cout<<" -- 3. Enter 3 to Find minimum distance between two Points\n\n";

    cout<<" -- 4. Press any other key to exit\n\n";

    int choice;

    cin>>choice;

    cout<<"\t\t\t\tCity Map\t\n";

    print(mat);

    if(choice ==1)
    {
        copy(mat);

        cout<<"\nComplete tour means STarting from A and Ending at A\n";

        cout<<"\t\t\tNearest Neighbour Algorithm \n";

        clock_t start = clock();

        nearest_neighbour(mat,N);

        clock_t end = clock();

        double time = (double) (end-start) / CLOCKS_PER_SEC * 1000.0;

        cout<<"\nTime taken by Nearest Neighbour :"<<time<<endl;

        cout<<"\n\n \t\t\tBranch and bound \n\n";

        start = clock();

        int x=bb_tsp(mat);

        end = clock();

        time = (double) (end-start) / CLOCKS_PER_SEC * 1000.0;

        cout<<"Time taken by Branch & Bound : "<<time<<endl;
        cout<<"COST="<<x<<endl;
        cout<<'\n';

    }
    else if(choice==2)
    {
/* visit some cities*/
        cout<<"Enter the places u wish to visit\n\n\n";
        char places[N];
        cin>>places;
        int l=strlen(places);
        int place[l];
        for(int i=0;i<strlen(places);i++)
        {
            place[i]=int(places[i])-97;
        }

        for(int i=0;i<l;i++)
        {
        someplaces(mat,place[i]);
        }
        copy(somepl);
        cout<<"\t\t\tUsing nearest neighbour algo \n\n\n";
        nearest_neighbour(somepl,l);

//        cout<<"\t\t\t Using branch and bound approach\n\n\n";

        //cout<<"Time taken by Branch & Bound  "<<time<<endl;
        //cout<<"Cost====="<<bb_tsp(somepl);
        cout<<'\n';
    }
    else if(choice ==3)
    {

        cout<<"Enter Starting Point\n";

        char c ;

        cin>>c;

        cout<<"\nEnter Final Point";

        char d;

        cin>>d;

        int start,end;

        start=(int)c;

        end=(int)d;

        start=start-97;

        end=end-97;

        cout<<"Minimum distance between "<<c<<" and "<<d<<" is (Using Floyd Warshall):"<<floydwar(mat,start,end);

        return 0;

    }
    else if(choice ==4)
    {
        return 0;
    }

    return 0;


}