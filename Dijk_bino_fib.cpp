//////////////////--------------Title of project 9---------------////////////////
//----van Emde Boas tree with application to Dijkstra and compare wrt Fibonacci and Binomial./////////////
////This part of the Code is Implementation of Fibonacci and Binomial with Dijkstra//////

////Team Members : AMit Kumar & J Nalini Vidyulatha////


/////////////////////////----------SOURCE CODE----------///////////////////


#include <iostream>
#include <stdio.h>
#include <ctime>
#include <cstdlib>
#include <bits/stdc++.h>

using namespace std;

///Enumerating the data////////////
////////Fibonacci & Binomial/////// 
enum HeapType {BINOMIAL, FIBONACCI};

//////// Graph defining the verices & Edges//////
class Bino_Fib_Graph
{
    private:
        int V;// number of vertices
        list< pair<int, int> > *adj;//adjacent 
    public:
        Bino_Fib_Graph(int V);//graph with the vertices
        void add_fbEdge(int u, int v, int w);// to add the edge to the graph
        void shortest_fbPath(int s, int heap_type);// to find the shortest path
};


/////Defining the Heap Data Structure/////
class Heap
{
    public:
        virtual pair<int, int> heaptop() = 0;
        virtual pair<int, int> heap_pop() = 0;
        virtual void push(pair<int, int>) = 0;
        virtual int Num_operations() = 0;
    private:
        int h_op;//heap operations to know for Fibonacci & Binomial
};
//////////////////////////////////Fibonacci//////////////////////
/////////////////For Fibonacci/////////////////

////Defining the Node for Fibonacci heap///////
struct fib_Node
{
    pair<int,int> fib_data;
    int fib_degree;
    fib_Node *fib_child, *fib_sibling, *fib_parent;

    explicit fib_Node(pair<int, int>);
};

/////////Fibonacci heap construction////////////////

class Fibo_Heap: public Heap
{
    public:
        Fibo_Heap();
        pair<int, int> heaptop();//top of the heap
        pair<int, int> heap_pop();//pop operations

        void push(pair<int, int>);//push operations
        int Num_operations();//number of operations
        void print_Tree(fib_Node *h);//for printing the tree
        void print_Heap();//for printing the heap

    protected:
        pair<int, int> extract_Min();
	list<fib_Node*> removeMin_Tree_Return_FHeap(fib_Node *tree,fib_Node*& n);
        fib_Node* mergeFibo_Trees(fib_Node *bvar1, fib_Node *bvar2);
        list<fib_Node*> unionFibo_Heap(list<fib_Node*> lvar1,fib_Node*,list<fib_Node*> lvar2,fib_Node*);

        void insert_Tree_Heap(fib_Node *tree);        
        void adjust();
        void insert(pair<int,int> key);
        fib_Node* getMin();///from get min function

    private:
        int h_op;//heap operations
        list<fib_Node*> heap;
        fib_Node *minNode;
};



/////////////////////////////////Binomial//////////////////////

//////Defining the structure for the Node of The Binomial Heap///////

struct Bino_Node
{
    pair<int,int> bino_data;//Data for the binomial
    int bino_degree;//degree of the binomial
    Bino_Node *bino_child, *bino_sibling, *bino_parent;//children,sibling& parent

    explicit Bino_Node(pair<int, int>);
};

/////
class Bino_Heap: public Heap
{
    public:
        Bino_Heap();
        pair<int, int> heaptop();//top of the heap
        pair<int, int> heap_pop();//pop operations

        void push(pair<int, int>);//push operations
        int Num_operations();//number of operations
        void print_Tree(Bino_Node *h);//for printing the tree
        void print_Heap();//for printing the heap

    protected:
        pair<int, int> extract_Min();
        void insert_Tree_Heap(Bino_Node *tree);
        list<Bino_Node*> removeMin_Tree_Return_BHeap(Bino_Node *tree);
        Bino_Node* mergeBino_Trees(Bino_Node *bvar1, Bino_Node *bvar2);
        list<Bino_Node*> unionBino_Heap(list<Bino_Node*> lvar1,list<Bino_Node*> lvar2);
        void adjust();
        void insert(pair<int,int> key);
        Bino_Node* getMin();
    private:
        int h_op;//heap operations
        list<Bino_Node*> heap;
};


//////////////////////////////////Graph///////////////////

# define INF 0x3f3f3f3f
////Construction of the graph//////

Bino_Fib_Graph::Bino_Fib_Graph(int V)
{
    this->V = V;
    adj = new list<pair<int, int> > [V];
}

/////////--------Adding the edges to the graph--------//////

void Bino_Fib_Graph::add_fbEdge(int u, int v, int w)
{
    adj[u].push_back(make_pair(v, w));
////added on change to take the variables
    adj[v].push_back(make_pair(u, w));
}

///////------Finding the shortest path for both the Fibonacci and Binomial-----///////

void Bino_Fib_Graph::shortest_fbPath(int src, int heap_type)
{
    Heap *heap;

    switch(heap_type)
    {
        
        case BINOMIAL: heap = new Bino_Heap(); break;
        case FIBONACCI: heap = new Fibo_Heap(); break;
    }


//BINOMIAL: heap = new Bino_Heap(); 
    vector<int> distance(V, INF);

    (*heap).push(make_pair(0, src));

    distance[src] = 0;

  //changing while loop
	// while (!(*heap).empty()) 
  while ((*heap).heaptop() != make_pair(-1, -1))
    {
        int u = (*heap).heaptop().second;
        (*heap).heap_pop();

        list< pair<int, int> >::iterator i;
        for (i = adj[u].begin(); i != adj[u].end(); ++i)
        {
            int v = (*i).first;
            int weight = (*i).second;

            if (distance[v] > distance[u] + weight)
            {
                distance[v] = distance[u] + weight;
                (*heap).push(make_pair(distance[v], v));
            }
        }
    }

    printf("Vertex Distance from Source\n");
    for (int i = 0; i < V; ++i)
        printf("%d \t\t %d\n", i, distance[i]);

    printf("Number of Operations performed : %d \n", (*heap).Num_operations());
    return;
}


////////////////Binomial Heap////////////////////


Bino_Heap::Bino_Heap()
{
        h_op = 0;//heap operations
}

int Bino_Heap::Num_operations()
{
    return h_op;//heap operations
}

///for inserting the binomial node///////

void Bino_Heap::push(pair<int, int> Bino_Node)
{
    insert(Bino_Node);
    return;
}

pair<int, int> Bino_Heap::heaptop()
{
    if(heap.size() == 0)
        return make_pair(-1, -1);

    return getMin()->bino_data;
}

///////--------------------////////////
pair<int, int> Bino_Heap::heap_pop()
{
    if(heap.size() == 0)
        return make_pair(-1, -1);

    pair<int, int> Bino_Node = extract_Min();

    return Bino_Node;
}

/////////for extracting the minimum///////

pair<int, int> Bino_Heap::extract_Min()
{
    if(heap.size() == 0)
        return make_pair(-1, -1);
    list<Bino_Node*> new_heap,lovar;
    Bino_Node *temp_var;
    temp_var = getMin();
    list<Bino_Node*>::iterator iter;
    iter = heap.begin();
    while (iter != heap.end())
    {
        if (*iter != temp_var)
        {
            new_heap.push_back(*iter);
        }
        iter++;
    }

    h_op++;//heap operations
    lovar=removeMin_Tree_Return_BHeap(temp_var);
    heap = unionBino_Heap(new_heap,lovar);
    adjust();
    return temp_var->bino_data;
}

Bino_Node::Bino_Node(pair<int,int> key)
{
    this->bino_data = key;
    this->bino_degree = 0;
    this->bino_child = this->bino_parent = this->bino_sibling = NULL;
}
void Bino_Heap::insert(pair<int,int> key)
{
    Bino_Node *temp_var = new Bino_Node(key);
    insert_Tree_Heap(temp_var);
}

////////////////swaping the two binomial nodes/////////////////////

void swap(Bino_Node *bvar1,Bino_Node *bvar2)
{
    Bino_Node *a;
    a=bvar1;
    bvar1=bvar2;
    bvar2=a;
}

/////////////////////////merging the two binomial nodes//////////////////////

Bino_Node* Bino_Heap::mergeBino_Trees(Bino_Node *bvar1, Bino_Node *bvar2)
{
    if ((bvar1->bino_data).first > (bvar2->bino_data).first)
    {
        swap(bvar1, bvar2);
        h_op++;//heap operations
    }

    bvar2->bino_parent = bvar1;
    bvar2->bino_sibling = bvar1->bino_child;
    bvar1->bino_child = bvar2;
    bvar1->bino_degree++;

    return bvar1;
}

list<Bino_Node*> Bino_Heap::unionBino_Heap(list<Bino_Node*> lvar1,
                               list<Bino_Node*> lvar2)
{
    list<Bino_Node*> _new;
    list<Bino_Node*>::iterator iter = lvar1.begin();
    list<Bino_Node*>::iterator oter = lvar2.begin();
    while (iter!=lvar1.end() && oter!=lvar2.end())
    {
        if((*iter)->bino_degree <= (*oter)->bino_degree)
        {
            _new.push_back(*iter);
            iter++;
        }
        else
        {
            _new.push_back(*oter);
            oter++;
        }
    }
    while (iter != lvar1.end())
    {
        _new.push_back(*iter);
        iter++;
    }
    while (oter!=lvar2.end())
    {
        _new.push_back(*oter);
        oter++;
    }
    h_op++;//heap operations
    return _new;
}

void Bino_Heap::adjust()
{
    if (heap.size() <= 1)
        return;
    list<Bino_Node*> new_heap;
    list<Bino_Node*>::iterator iter1,iter2,iter3;
    iter1 = iter2 = iter3 = heap.begin();

    if (heap.size() == 2)
    {
        iter2 = iter1;
        iter2++;
        iter3 = heap.end();
    }
    else
    {
        iter2++;
        iter3=iter2;
        iter3++;
    }
    while (iter1 != heap.end())
    {
        if (iter2 == heap.end())
            iter1++;
        else if ((*iter1)->bino_degree < (*iter2)->bino_degree)
        {
            iter1++;
            iter2++;
            if(iter3!=heap.end())
                iter3++;
        }
        else if (iter3!=heap.end() &&
                (*iter1)->bino_degree == (*iter2)->bino_degree &&
                (*iter1)->bino_degree == (*iter3)->bino_degree)
        {
            iter1++;
            iter2++;
            iter3++;
        }
        else if ((*iter1)->bino_degree == (*iter2)->bino_degree)
        {
            *iter1 = mergeBino_Trees(*iter1,*iter2);
            iter2 = heap.erase(iter2);
            if(iter3 != heap.end())
                iter3++;
        }
    }
    h_op++;//heap operations
    return;
}

void Bino_Heap::insert_Tree_Heap(Bino_Node *tree)
{
    list<Bino_Node*> temp_var;
    temp_var.push_back(tree);
    heap = unionBino_Heap(heap,temp_var);
    adjust();
    return;
}

list<Bino_Node*> Bino_Heap::removeMin_Tree_Return_BHeap(Bino_Node *tree)
{
    list<Bino_Node*> temp_varheap;
    Bino_Node *temp_var = tree->bino_child;
    Bino_Node *lovar;
    h_op++;//heap operations
    while (temp_var)
    {
        lovar = temp_var;
        temp_var = temp_var->bino_sibling;
        lovar->bino_sibling = NULL;
        temp_varheap.push_front(lovar);
    }
    return temp_varheap;
}

Bino_Node* Bino_Heap::getMin()
{
    if (heap.size() == 0)
        return NULL;
    list<Bino_Node*>::iterator iter = heap.begin();
    Bino_Node *temp_var = *iter;
    h_op++;//heap operations
    while (iter != heap.end())
    {
        if (((*iter)->bino_data).first < (temp_var->bino_data).first)
            temp_var = *iter;
        iter++;
    }
    return temp_var;
}

//////////////////////printing the tree///////////////

void Bino_Heap::print_Tree(Bino_Node *h)
{
    while (h)
    {
        print_Tree(h->bino_child);
        h = h->bino_sibling;
    }
}

void Bino_Heap::print_Heap()
{
    list<Bino_Node*> ::iterator iter;
    iter = heap.begin();
    while (iter != heap.end())
    {
        print_Tree(*iter);
        iter++;
    }
}
///////////////////////////////////////////////////////
/////////////////Fibonacci///////////////////////////
////////////////////////////Fibonacci///////////////////////////////////

Fibo_Heap::Fibo_Heap()
{
        h_op = 0;//heap operations
        minNode = NULL;
}

int Fibo_Heap::Num_operations()
{
    return h_op;//heap operations
}

void Fibo_Heap::push(pair<int, int> fib_Node)////////////////push operations////////////
{
    insert(fib_Node);
    return;
}

pair<int, int> Fibo_Heap::heaptop()//////top of the heap///////////
{
    if(heap.size() == 0)
        return make_pair(-1, -1);

    return getMin()->fib_data;
}

//////////////////////////fibo pop////////////////////

pair<int, int> Fibo_Heap::heap_pop()
{
    if(heap.size() == 0)
        return make_pair(-1, -1);

    pair<int, int> fib_Node = extract_Min();

    return fib_Node;
}

fib_Node::fib_Node(pair<int,int> key)
{
    this->fib_data = key;
    this->fib_degree = 0;
    this->fib_child = this->fib_parent = this->fib_sibling = NULL;
}


void Fibo_Heap::insert(pair<int,int> key)
{
    fib_Node *temp_var = new fib_Node(key);
    insert_Tree_Heap(temp_var);
}

list<fib_Node*> Fibo_Heap::removeMin_Tree_Return_FHeap(fib_Node *tree,fib_Node*& min_lovar)
{
    list<fib_Node*> temp_varheap;
    fib_Node *temp_var = tree->fib_child;
    fib_Node *lovar;
    h_op++;//heap operations
    while (temp_var)
    {
        if(((temp_var)->fib_data).first < (min_lovar->fib_data).first)
                min_lovar = temp_var;
        lovar = temp_var;
        temp_var = temp_var->fib_sibling;
        lovar->fib_sibling = NULL;
        temp_varheap.push_front(lovar);
    }
    return temp_varheap;
}

///////////////////////extracting the minimum from fibonacci////////////////////

pair<int, int> Fibo_Heap::extract_Min()
{
    if(heap.size() == 0)
        return make_pair(-1, -1);
    list<fib_Node*> new_heap,lovar;
    fib_Node *temp_var;
    temp_var = getMin();
    list<fib_Node*>::iterator iter;
    iter = heap.begin();
    fib_Node *min_newheap = new fib_Node(make_pair(INT_MAX,-1));
    fib_Node *min_lovar = new fib_Node(make_pair(INT_MAX,-1));
    while (iter != heap.end())
    {
        if (*iter != temp_var)
        {
            new_heap.push_back(*iter);
            if(((*iter)->fib_data).first < (min_newheap->fib_data).first)
                min_newheap = (*iter);
        }
        iter++;
    }
    h_op++;//heap operations
    lovar=removeMin_Tree_Return_FHeap(temp_var,min_lovar);
    heap = unionFibo_Heap(new_heap,min_newheap,lovar,min_lovar);
    adjust();
    return temp_var->fib_data;
}
///////////////swapping the two nodes/////////////////

void swap(fib_Node *bvar1,fib_Node *bvar2)
{
    fib_Node *a;
    a=bvar1;
    bvar1=bvar2;
    bvar2=a;
}

/////////////////////////////merging the two nodes/////////////////

fib_Node* Fibo_Heap::mergeFibo_Trees(fib_Node *bvar1, fib_Node *bvar2)
{
    if ((bvar1->fib_data).first > (bvar2->fib_data).first)
    {
        swap(bvar1, bvar2);
        h_op++;//heap operations
    }

    bvar2->fib_parent = bvar1;
    bvar2->fib_sibling = bvar1->fib_child;
    bvar1->fib_child = bvar2;
    bvar1->fib_degree++;

    return bvar1;
}

list<fib_Node*> Fibo_Heap::unionFibo_Heap(list<fib_Node*> lvar1,fib_Node *minimum1, list<fib_Node*> lvar2, fib_Node *min2)
{
    copy(lvar1.rbegin(), lvar1.rend(), front_inserter(lvar2));
    if(minimum1==NULL)
        minNode = min2;
    else if(min2==NULL)
        minNode = minimum1;
    else
    {
        if((minimum1->fib_data).first < (min2->fib_data).first)
            minNode = minimum1;
        else
            minNode = min2;
    }
    return lvar2;
}

void Fibo_Heap::adjust()
{
    if (heap.size() <= 1)
        return;
    list<fib_Node*>::iterator iter;
    iter = heap.begin();
    map<int,fib_Node*>m;
    while(iter!=heap.end())
    {
        while(m[(*iter)->fib_degree]!=NULL)
        {
            int deg = (*iter)->fib_degree;
            *iter = mergeFibo_Trees(*iter,m[(*iter)->fib_degree]);
            list<fib_Node*>::iterator iter_temp;
            iter_temp = heap.begin();
            while((*iter_temp)!=m[deg])
                iter_temp++;
            iter_temp=heap.erase(iter_temp);
            m[deg]=NULL;
        }
        m[(*iter)->fib_degree]=(*iter);
        iter++;
    }
    h_op++;//heap operations
    return;
}

//////////////////////////inserting fibo node////////////////

void Fibo_Heap::insert_Tree_Heap(fib_Node *tree)
{
    list<fib_Node*> temp_var;
    temp_var.push_back(tree);
    heap = unionFibo_Heap(heap,minNode,temp_var,tree);
    return;
}

fib_Node* Fibo_Heap::getMin()
{
    if (heap.size() == 0)
        return NULL;
    return minNode;
}
void Fibo_Heap::print_Tree(fib_Node *h)
{
    while (h)
    {
        print_Tree(h->fib_child);
        h = h->fib_sibling;
    }
}

void Fibo_Heap::print_Heap()
{
    list<fib_Node*> ::iterator iter;
    iter = heap.begin();
    while (iter != heap.end())
    {
        print_Tree(*iter);
        iter++;
    }
}


/////////////////////////////Main///////////////////////////

int main()
{
    char Random;
    int V, start, stop, source, n, edges, rangeStart, rangeEnd;
	int num_dist;
    float avg_deg;

 int len,num=0;
    int Nvert=0,Svert=0;
    int i=0, u=0, w=0,temp=0;

  FILE *fptr;
	if ((fptr = fopen("input.txt","r")) == NULL)
	{
       printf("Error! opening file");

       // Program exits if the file pointer returns NULL.
       exit(1);
   	}
		
	fscanf(fptr,"%d", &V);
	printf("Number of Vertices=%d\n", V);
	 Bino_Fib_Graph g(V);
	fscanf(fptr,"%d", &source);
	//cout << "Enter the source vertex : ";
printf("source vertex =%d\n",source);

fscanf(fptr,"%d", &num_dist);

printf("The number of connections=%d\n",num_dist);

printf("Vertex No., Adj Vertex, Path distance\n");

	for (int j = 0; j < num_dist; j++)
            {
                int i,u, w;
	fscanf(fptr,"%d %d %d", &i, &u, &w);
              //  cin >>i>> u >> w;
                assert(u < V && w >= 0);
                g.add_fbEdge(i, u, w);


printf("%d %d %d\n",i,u,w);
            }
	

////////------finding the shortest paths of Fibonacci & Binomial-------------------/////
  
    cout << "-----Dijkstra BINOMIAL-----" << endl;
    start = clock();
	g.shortest_fbPath(source, BINOMIAL);
	stop = clock();
    cout << "Execution time using Dijkstra Binomial : " << (stop-start)/double(CLOCKS_PER_SEC)*1000 << endl;

    cout << "-----Dijkstra FIBONACCI -----" << endl;
    start = clock();
	g.shortest_fbPath(source, FIBONACCI);
	stop = clock();
    cout << "Execution time using Fibonacci : " << (stop-start)/double(CLOCKS_PER_SEC)*1000 << endl;

    return 0;
}
