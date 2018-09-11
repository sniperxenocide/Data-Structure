#include<stdio.h>
#include<stdlib.h>
#define NULL_VALUE -999999
#define INFINITY 999999


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


//******************Graph class starts here**************************
class Graph
{
	int nVertices, nEdges ;
	bool directed ;
	int ** matrix ; //adjacency matrix to store the graph
	//define other variables required for bfs such as color, parent, and dist
	//you must use pointers and dynamic allocation
	int *dist;
	int *color;
	int *parent;

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
};


Graph::Graph(bool dir)
{
	nVertices = 0 ;
	nEdges = 0 ;
	matrix = 0 ;
	directed = dir ; //set direction of the graph
	//define other variables to be initialized
}

void Graph::setnVertices(int n)
{
	this->nVertices = n ;

	//allocate space for the matrix
    matrix = new int*[nVertices];
    for(int i=0;i<nVertices;i++)
    {
        matrix[i] = new int[nVertices];
        for(int j=0;j<nVertices;j++)
            matrix[i][j] = 0; //initialize the matrix cells to 0
    }
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
    //write your code here
    if(u<0 || u>=nVertices || v<0 || v>=nVertices) return;
    matrix[u][v] = 1;
    if(!directed) matrix[v][u] = 1;
    nEdges++;
}

void Graph::removeEdge(int u, int v)
{
    matrix[u][v]=0;
    if(!directed) matrix[v][u] = 0;
    nEdges--;
    //write this function
}

bool Graph::isEdge(int u, int v)
{
    if(matrix[u][v]==1) return true;
    return false;
    //returns true if (u,v) is an edge, otherwise should return false
}

int Graph::getDegree(int u)
{
    int i,cnt=0;
    for(i=0;i<nVertices;i++) {if(matrix[u][i]==1) cnt++;}
    return cnt;
    //returns the degree of vertex u
}

void Graph::printAdjVertices(int u)
{
    int i;
    for(i=0;i<nVertices;i++)
    {
        if(matrix[u][i]==1) printf("%d ",i);
    }
    printf("\n");
    //prints all adjacent vertices of a vertex u
}

bool Graph::hasCommonAdjacent(int u, int v)
{
    for(int i=0;i<nVertices;i++)
    {
        if(matrix[u][i]==1 && matrix[v][i]==1) return true;
    }
    return false;
    //returns true if vertices u and v have common adjacent vertices

}

void Graph::bfs(int source)
{
    //write this function
    for(int i=0;i<nVertices;i++)
    {
        dist[i]=INFINITY;
        color[i]=0;
        parent[i]=NULL_VALUE;
    }
    Queue Q;
    color[source]=1;
    dist[source]=0;
    parent[source]=NULL_VALUE;
    Q.enqueue(source);
    while(Q.empty()==false)
    {
        int u=Q.dequeue();
        for(int i=0;i<nVertices;i++)
        {
            if(matrix[u][i]==1 && color[i]==0)
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
        for(int j=0; j<nVertices;j++)
        {
            if(matrix[i][j]==1)
                printf(" %d", j);
        }
        printf("\n");
    }
}

Graph::~Graph()
{
    if(matrix)
    {
        for(int i=0;i<nVertices;i++)
        {
            delete[] matrix[i];
        }
        delete[] matrix;
        matrix=0;
    }
    if(dist) delete[] dist;
    dist=0;
    if(color) delete[] color;
    color=0;
    if(parent) delete[] parent;
    parent=0;
    //write your destructor here
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
    return 0;
}
