#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <complex>
#include<bits/stdc++.h> 
using namespace std; 
#define V 4

class vEB
{
    unsigned long long int u;
    
    int *min, *max;
    vEB *summary;  
    vEB **arry;  
    
public:
    vEB(int);
    
    bool member(int);
    void insert(int);
    void Delete(int);
    int getMin();
    int getMax();
    int* predecessor(int);
    int* successor(int);
   
};

vEB::vEB(int u)
{
    this -> u = u;
    this -> min = NULL;
    this -> max = NULL;
    
    if (u == 2)
    {
        this -> summary = NULL;
        this -> arry = NULL;
    }
    
    else
    {
        int subSize = (int)sqrt(u);
        this -> summary = new vEB(subSize);
        this -> arry = new vEB*[subSize];
    }
}

bool vEB::member(int x)
{
    if (u == 2)
    {
        if (min == NULL) 
            return false;
        if (x == 0) 
            return ((*min) == 0);
        else if (x == 1) 
            return ((*max) == 1);
        return false;
    }
    else
    {
        if (min == NULL) 
            return false;
        if (x < (*min) || x > (*max)) 
            return false;
        else if (x == (*min) || (x == (*max))) 
            return true;
        else
        {
            int subSize = (int)sqrt(u);
            int h = x / subSize, l = x % subSize;
            if (arry[h] == NULL) 
                return false;
            else 
                return arry[h] -> member(l);
        }

    }
}

void vEB::insert(int x)
{
    if (u == 2)
    {
        if (x == 0)
        {
            if (min == NULL)
            {
                min = new int;
                max = new int;
                (*min) = (*max) = x;
            }
            else (*min) = x;
        }
        else if (x == 1)
        {
            if (max == NULL)
            {
                min = new int;
                max = new int;
                (*min) = (*max) = x;
            }
            else (*max) = x;
        }
    }
    else
    {
        if (min == NULL)
        {
            min = new int;
            max = new int;
            (*min) = (*max) = x;
        }
        else
        {
            if (x < (*min))
            {
                int currMin = (*min);
                (*min) = x;
                this -> insert(currMin);
            }
            else
            {
                int subSize = (int)sqrt(u);
                int h = x / subSize, l = x % subSize;
                if (arry[h] == NULL)
                {
                    arry[h] = new vEB(subSize);
                    arry[h] -> insert(l);
                    summary -> insert(h);
                }
                else 
                    arry[h] -> insert(l);
                
                if (x > (*max)) 
                    (*max) = x;
            }
        }
    }
}

void vEB::Delete(int x)
{
    if (u == 2)
    {
        if (x == 0)
        {
            if ((*max) == 0)
            {
                min = max = NULL;
            }
            else (*min) = 1;
        }
        else if (x == 1)
        {
            if ((*min) == 1)
            {
                min = max = NULL;
            }
            else 
                (*max) = 0;
        }
    }
    else
    {
        int subSize = (int)sqrt(u);
        int h = x / subSize, l = x % subSize;
        
        if (x == (*min))
        {
            if (x == (*max))
            {
                min = max = NULL;
            }
            else
            {
                int nextMinHi = summary -> getMin();
                int nextMinLo = arry[summary -> getMin()] -> getMin();
                int nextMin = nextMinHi * subSize + nextMinLo;
                //cout << "nextMin:-" << nextMin << "\n";
                this -> Delete(nextMin);
                (*min) = nextMin;
            }
        }
        else
        {
            arry[h] -> Delete(l);
            if (arry[h] -> min == NULL)
            {
                summary -> Delete(h);
                delete arry[h];
                arry[h] = NULL;
            }
            if (x == (*max))
            {
                if (summary -> min == NULL) 
                    (*max) = (*min);
                else
                {
                    int nextMaxHi = summary -> getMax();
                    int nextMaxLo = arry[summary -> getMax()] -> getMax();
                    (*max) = nextMaxHi * subSize + nextMaxLo;
                }
            }
        }
    }
}

int vEB::getMin()
{
    return (*min);
}

int vEB::getMax()
{
    return (*max);
}

int* vEB::predecessor(int x)
{
    if (u == 2)
    {
        if (x == 0) return NULL;
        else if (x == 1)
        {
            if (min == NULL) 
                return NULL;
            if ((*min) == 1) 
                return NULL;
            return min;
        }
        else return NULL;
    }
    else
    {
        if (min == NULL) 
            return NULL;
        if (x <= (*min)) 
            return NULL;
        if (x > (*max)) 
            return max;
        int subSize = (int)sqrt(u);
        int h = x / subSize;
        int l = x % subSize;
        if (arry[h] == NULL)
        {
            int* prev = summary -> predecessor(h);
            int* ret = new int;
            (*ret) = (*prev) * subSize + arry[(*prev)] -> getMax();
            return ret;
        }
        else
        {
            int *newLo, *newHi;
            newHi = new int;
            newLo = new int;
            (*newHi) = h;
            int minInCluster = arry[h] -> getMin();
            if (l > minInCluster) newLo = arry[h] -> predecessor(l);
            else
            {
                newHi = summary -> predecessor(h);
                (*newLo) = arry[(*newHi)] -> getMax();
            }
            int *ret = new int;
            (*ret) = (*newHi) * subSize + (*newLo);
            return ret;
        }
    }
}

int* vEB::successor(int x)
{
    if (u == 2)
    {
        if (x == 1) 
            return NULL;
        else if (x == 0)
        {
            if (max == NULL) 
                return NULL;
            if ((*max) == 0) 
                return NULL;
            return max;
        }
        else 
            return NULL;
    }
    else
    {
        if (min == NULL) 
            return NULL;
        if (x >= (*max)) 
            return NULL;
        if (x < (*min)) 
            return min;
        int subSize = (int)sqrt(u);
        int h = x / subSize;
        int l = x % subSize;
        if (arry[h] == NULL)
        {
            int* next = summary -> successor(h);
            int* ret = new int;
            (*ret) = (*next) * subSize + arry[(*next)] -> getMin();
            return ret;
        }
        else
        {
            int *newLo, *newHi;
            newHi = new int;
            newLo = new int;
            (*newHi) = h;
            int maxInCluster = arry[h] -> getMax();
            if (l < maxInCluster) newLo = arry[h] -> successor(l);
            else
            {
                newHi = summary -> successor(h);
                (*newLo) = arry[(*newHi)] -> getMin();
            }
            int *ret = new int;
            (*ret) = (*newHi) * subSize + (*newLo);
            return ret;
        }
    }
}

void addEdge(int graph[V][V],  int u, int v, int wt) 
{     
   graph[u][v]=wt;
   graph[v][u]=wt;      
} 
     

int main(int argc, char** argv) 
{ 
   // int V = 9; 
    //vector<iPair > adj[V]; 
    int start,stop;
    /*FILE *fptr;
    if ((fptr = fopen(argv[1],"r")) == NULL)
    {
       printf("Error! opening file");    
       exit(1);
    }
    fscanf(fptr,"%d", &V);*/
    printf("Number of Vertices=%d\n", V);
    int graph[V][V];
    memset(graph, 0, sizeof(graph[0][0]) * V * V);
    vEB *vEB = new class vEB(256);
    vector<int> wtadj[50]; 
    int src=0;//,num_dist;
   /* fscanf(fptr,"%d", &src);    
    printf("source vertex =%d\n",src);
    fscanf(fptr,"%d", &num_dist);
    printf("The number of connections=%d\n",num_dist); 
    for (int a = 0; a < num_dist; a++)
    {
        int u1,v1, w1;
        fscanf(fptr,"%d %d %d", &u1, &v1, &w1);              
        assert(v1 < V && w1 >= 0);
        graph[u1][v1]=w1;
        graph[v1][u1]=w1;
    }   
    fclose (fptr);*/
    addEdge(graph, 0, 1 ,2); 
   // vEB -> insert(4); 
    addEdge(graph,0, 2, 2); 
   // vEB -> insert(8);
    addEdge(graph,1, 2, 1);
    //vEB -> insert(8);
    addEdge(graph,1, 3, 1); 
    //vEB -> insert(11);
    addEdge(graph,2, 0, 1); 
    //vEB -> insert(7);
    addEdge(graph, 2, 3, 2);
    //vEB -> insert(2);
    addEdge(graph, 3, 3, 2); 
    
    int dist[V];     
    bool visited[V];
    cout << "-----Dijkstra vEB-----" << endl;
    start = clock();
        
     for (int i = 0; i < V; i++) 
        dist[i] = INT_MAX, visited[i] = false; 
        
     dist[src] = 0; 
     vEB -> insert(0); 
     wtadj[0].push_back(src);
     
     for (int count = 0; count < V-1; count++) 
     {
        bool flag=true;
        int temp=vEB -> getMin();
        int u;
        
        while(flag){
            //cout << "temp: " << temp << "\n";
            for(int a=0;a<wtadj[temp].size();a++){
                if (!visited[wtadj[temp][a]] )
                {
                    u=wtadj[temp][a];
                    //wtadj[temp][a]=-1;
                    flag=false;
                    break;
                }
            }
            //cout << "u: " << u << " " << vEB -> getMax() <<"\n";
            if(flag && temp != (vEB -> getMax())){
                temp=(*vEB -> successor(temp));
            }
            //cout << "After if" << "\n";
        }      
        visited[u] = true; 
          
         for (int v = 0; v < V; v++)  {
            
            if (!visited[v] && graph[u][v] && dist[u] != INT_MAX  && dist[u]+graph[u][v] < dist[v]){
                
                dist[v] = dist[u] + graph[u][v]; 
              //  cout << "v: " << v << " u: " << u << " dist[v]: " << dist[v] << "\n";
                vEB -> insert(dist[v]); 
                //cout << "End if" << "\n";
                wtadj[dist[v]].push_back(v);
                
            } 
                 
         }
     }

    printf("Vertex Distance from Source\n"); 
    for (int i = 0; i < V; ++i) 
        printf("%d \t\t %d\n", i, dist[i]); 

    stop = clock();
    cout << "Execution time using Dijkstra vEB : " << (stop-start)/double(CLOCKS_PER_SEC)*1000 << endl;
  
    return 0; 
} 