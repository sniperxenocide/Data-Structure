#include<stdio.h>
#include<stdlib.h>
#define NULL_VALUE -999999
#define INFINITY 999999
#define WHITE 1
#define GREY 2
#define BLACK 3

class Queue
{
    int queueInitSize ;
    int queueMaxSize;
    int * data;
    int length;
    int front;
    int rear;
public:
    Queue();
    ~Queue();
    void enqueue(int item); //insert item in the queue
    int dequeue(); //returns the item according to FIFO
    bool empty(); //return true if Queue is empty
};

Queue::Queue()
{
    queueInitSize = 2 ;
    queueMaxSize = queueInitSize;
    data = new int[queueMaxSize] ; //allocate initial memory
    length = 0 ;
    front = 0;
    rear = 0;
}


void Queue::enqueue(int item)
{
	if (length == queueMaxSize)
	{
		int * tempData ;
		//allocate new memory space for tempList
		queueMaxSize = 2 * queueMaxSize ;
		tempData = new int[queueMaxSize] ;
		int i, j;
		j = 0;
		for( i = rear; i < length ; i++ )
		{
			tempData[j++] = data[i] ; //copy items from rear
		}
		for( i = 0; i < rear ; i++ )
		{
			tempData[j++] = data[i] ; //copy items before rear
		}
		rear = 0 ;
		front = length ;
		delete[] data ; //free the memory allocated before
		data = tempData ; //make list to point to new memory
	}

	data[front] = item ; //store new item
	front = (front + 1) % queueMaxSize ;
	length++ ;
}


bool Queue::empty()
{
	if(length == 0) return true ;
	else return false ;
}


int Queue::dequeue()
{
	if(length == 0) return NULL_VALUE ;
	int item = data[rear] ;
	rear = (rear + 1) % queueMaxSize ;
	length-- ;
	return item ;
}


Queue::~Queue()
{
    if(data) delete[] data; //deallocate memory
    data = 0; //set to NULL
}

//****************Queue class ends here************************

//****************Dynamic ArrayList class based************************
class ArrayList
{
	int * list;
	int length ;
	int listMaxSize ;
	int listInitSize ;
public:
	ArrayList() ;
	~ArrayList() ;
	int searchItem(int item) ;
    void insertItem(int item) ;
	void removeItem(int item) ;
	void removeItemAt(int item);
	int getItem(int position) ;
	int getLength();
	bool empty();
	void printList();
} ;


ArrayList::ArrayList()
{
	listInitSize = 2 ;
	listMaxSize = listInitSize ;
	list = new int[listMaxSize] ;
	length = 0 ;
}

void ArrayList::insertItem(int newitem)
{
	int * tempList ;
	if (length == listMaxSize)
	{
		//allocate new memory space for tempList
		listMaxSize = 2 * listMaxSize ;
		tempList = new int[listMaxSize] ;
		int i;
        for( i = 0; i < length ; i++ )
        {
            tempList[i] = list[i] ; //copy all items from list to tempList
        }
        delete[] list ; //free the memory allocated before
        list = tempList ; //make list to point to new memory
	};

	list[length] = newitem ; //store new item
	length++ ;
}

int ArrayList::searchItem(int item)
{
	int i = 0;
	for (i = 0; i < length; i++)
	{
		if( list[i] == item ) return i;
	}
	return NULL_VALUE;
}

void ArrayList::removeItemAt(int position) //do not preserve order of items
{
	if ( position < 0 || position >= length ) return ; //nothing to remove
	list[position] = list[length-1] ;
	length-- ;
}


void ArrayList::removeItem(int item)
{
	int position;
	position = searchItem(item) ;
	if ( position == NULL_VALUE ) return ; //nothing to remove
	removeItemAt(position) ;
}


int ArrayList::getItem(int position)
{
	if(position < 0 || position >= length) return NULL_VALUE ;
	return list[position] ;
}

int ArrayList::getLength()
{
	return length ;
}

bool ArrayList::empty()
{
    if(length==0)return true;
    else return false;
}

void ArrayList::printList()
{
    int i;
    for(i=0;i<length;i++)
        printf("%d ", list[i]);
    printf("Current size: %d, current length: %d\n", listMaxSize, length);
}

ArrayList::~ArrayList()
{
    if(list) delete [] list;
    list = 0 ;
}

//******************ArrayList class ends here*************************

//******************Graph class starts here**************************
class Graph
{
	int nVertices, nEdges ;
	bool directed ;
	ArrayList  * adjList ;
	int *color;
	int *dist;
	int *parent;
	//define other variables required for bfs such as color, parent, and dist
	//you must use pointers and dynamic allocation

public:
	Graph(bool dir = false);
	~Graph();
	void setnVertices(int n);
	void addEdge(int u, int v);
	void removeEdge(int u, int v);
	bool isEdge(int u, int v);
    int getDegree(int u);
    void printAdjVertices(int u);
    bool hasCommonAdjacent(int u, int v);
    int getDist(int u, int v);
    void printGraph();
	void bfs(int source); //will run bfs in the graph
	void dfs(int source); //will run dfs in the graph
};


Graph::Graph(bool dir)
{
	nVertices = 0 ;
	nEdges = 0 ;
	adjList = 0 ;
	directed = dir ; //set direction of the graph
	//define other variables to be initialized

}

void Graph::setnVertices(int n)
{
	this->nVertices = n ;
	if(adjList!=0) delete[] adjList ; //delete previous list
	adjList = new ArrayList[nVertices] ;
	dist=new int[nVertices];
    color=new int[nVertices];
    parent= new int[nVertices];
    for(int i=0;i<nVertices;i++)
    {
        dist[i]=INFINITY;
        color[i]=0;
        parent[i]=NULL_VALUE;
    }
}

void Graph::addEdge(int u, int v)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) return; //vertex out of range
    this->nEdges++ ;
	adjList[u].insertItem(v) ;
	if(!directed) adjList[v].insertItem(u) ;
}

void Graph::removeEdge(int u, int v)
{
    adjList[u].removeItem(v);
    if(!directed) adjList[v].removeItem(u);
    this->nEdges--;
    //write this function
}

bool Graph::isEdge(int u, int v)
{
    if(adjList[u].searchItem(v)!=NULL_VALUE) return true;
    return false;
    //returns true if (u,v) is an edge, otherwise should return false
}

int Graph::getDegree(int u)
{
    return adjList[u].getLength();
    //returns the degree of vertex u
}

void Graph::printAdjVertices(int u)
{
    for(int i=0;i<nVertices;i++)
    {
        if(adjList[u].getItem(i)) printf("%d ",adjList[u].getItem(i));
    }
    printf("\n");
    //prints all adjacent vertices of a vertex u
}

bool Graph::hasCommonAdjacent(int u, int v)
{
    for(int i=0;i<nVertices;i++)
    {
        if(adjList[u].searchItem(i)!=NULL_VALUE && adjList[u].searchItem(i)!=NULL_VALUE) return true;
    }
    return false;
    //returns true if vertices u and v have common adjacent vertices

}

void Graph::bfs(int source)
{
    for(int i=0; i<nVertices; i++)
    {
        //color[i] = WHITE ;
        //parent[i] = -1 ;
        //dist[i] = INFINITY ;
        dist[i]=INFINITY;
        color[i]=0;
        parent[i]=NULL_VALUE;
    }
    //Queue q ;
    //color[source] = GREY;
    //dist[source] = 0 ;
    Queue Q;
    color[source]=1;
    dist[source]=0;
    parent[source]=NULL_VALUE;
    Q.enqueue(source);
    while( !Q.empty() )
    {
        //complete this part
        int u=Q.dequeue();
        for(int i=0;i<nVertices;i++)
        {
            if(adjList[u].searchItem(i)!=NULL_VALUE && color[i]==0)
            {
                Q.enqueue(i);
                color[i]=1;
                dist[i]=dist[u]+1;
                parent[i]=u;
            }
        }

    }
}

int Graph::getDist(int u, int v)
{
    bfs(u);
    return dist[v];
    //returns the shortest path distance from u to v
    //must call bfs using u as the source vertex, then use distance array to find the distance
}

void Graph::printGraph()
{
    printf("\nNumber of vertices: %d, Number of edges: %d\n", nVertices, nEdges);
    for(int i=0;i<nVertices;i++)
    {
        printf("%d:", i);
        for(int j=0; j<adjList[i].getLength();j++)
        {
            printf(" %d", adjList[i].getItem(j));
        }
        printf("\n");
    }
}

Graph::~Graph()
{
    //write your destructor here
    if(color) delete[] color;
    color=0;
    if(parent) delete[] parent;
    parent=0;
    if(dist) delete[] dist;
    dist=0;
    if(adjList)
    {
        delete[] adjList;
        adjList=0;
    }
}


//**********************Graph class ends here******************************


//******main function to test your code*************************
int main(void)
{
    int n;
    Graph g;
    printf("Enter number of vertices: ");
    scanf("%d", &n);
    g.setnVertices(n);

    while(1)
    {
        printf("1. Add edge. 2.BFS. 3.REMOVE EDGE 4.isEDGE\n");
        printf("5. Print Graph 6.getDistance\n");
        printf("7.getDegree. 8.printAdjecentV. 9.hasCommonAdj. 10.EXIT\n");

        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            g.addEdge(u, v);
        }
        else if(ch==2)
        {
            int s;
            printf("source:");
            scanf("%d",&s);
            g.bfs(s);
        }
        else if(ch==3)
        {
            int u,v;
            printf("u:");
            scanf("%d",&u);
            printf("v:");
            scanf("%d",&v);
            g.removeEdge(u,v);

        }
        else if(ch==4)
        {
            int u,v;
            printf("u:");
            scanf("%d",&u);
            printf("v:");
            scanf("%d",&v);
            if(g.isEdge(u,v)) printf("Yes\n");
            else printf("No\n");
        }
        else if(ch==5)
        {
            g.printGraph();
        }
        else if(ch==6)
        {
            int u,v;
            printf("u:");
            scanf("%d",&u);
            printf("v:");
            scanf("%d",&v);
            printf("distance: %d\n",g.getDist(u,v));
        }
        else if(ch==7)
        {
            int u;
            printf("u:");
            scanf("%d",&u);
            printf("Degree: %d\n",g.getDegree(u));
        }
        else if(ch==8)
        {
            int u;
            printf("u:");
            scanf("%d",&u);
            g.printAdjVertices(u);
        }
        else if(ch==9)
        {
            int u,v;
            printf("u:");
            scanf("%d",&u);
            printf("v:");
            scanf("%d",&v);
            if(g.hasCommonAdjacent(u,v)) printf("Yes\n");
            else printf("No\n");
        }
        else if(ch==10) break;
    }

}
