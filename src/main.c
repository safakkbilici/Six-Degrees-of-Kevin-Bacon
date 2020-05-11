#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<uchar.h>
char storage[190000][200];
int moviectrl[190000];
struct node{
	int vertex;
	char movie_actor[200];
	int visited;
	struct node* next;
	int ctrlMovie;
};

struct graph{
	int nVertex;
	struct node** adjList;
};
struct queue{
	int vertex;
	char movie_actor[200];
	int visited;
	struct queue* next;
};

typedef struct queue QUEUE;
typedef struct node NODE;
typedef struct graph GRAPH;
int numberOfVertex(FILE*);
NODE* createNode(int,char*);
GRAPH* createGraph(int);
GRAPH* addEdge(int,char*);
void printGraph(GRAPH*,int);
void enqueue(QUEUE**,int,char*);
QUEUE* dequeue(QUEUE**);
void BreadthFirstSearch(GRAPH**,char*,int,int*,int*);
int findMaxDistance(int,int*);
int* frequencyListOfKevinBaconNumbers(GRAPH*,int,int,int*);
void shortestDistance(GRAPH*,char*,int,int*,int*,char*);
void specificBreadthFirstSearch(GRAPH**,char*,char*,int,int*,int*);
int searchInformation(char*);
int main(int argc, char** argv){
	char filename[100];
	printf("Enter the file name: ");
  scanf("%s",filename);
	FILE* fp = fopen(filename,"r");
  if(fp == NULL){
    fprintf(stderr,"File Error!");
    exit(0);
  }
	printf("\n");

	int i;
	printf("It can take minutes, calculating...");
	int n = numberOfVertex(fp);
	printf("%d\n",n);
	int* parent = (int*)malloc(n*sizeof(int));
	for(i =0; i<n; i++){
		parent[i] = -1;
	}
	GRAPH* _graph = addEdge(n,filename);
	int* visited = (int*)calloc(n,sizeof(int));
	BreadthFirstSearch(&_graph,"Bacon, Kevin",n,visited,parent);
	int max = findMaxDistance(n,visited);
	int* frequency = (int*)calloc(max,sizeof(int));
	frequency = frequencyListOfKevinBaconNumbers(_graph,max,n,visited);
	printf("\n");
	char destination_actor[100];
	printf("----------------------------------------------------------------------------------------------------\n");
	printf("Actor name and surname must be given as: Surname, Name.\n");
	printf("Enter the actor's/actress's name to find connection map between Kevin Bacon: ");
	scanf(" %[^\n]s",destination_actor);
	printf("----------------------------------------------------------------------------------------------------");
	printf("\n");
	while(strcmp(destination_actor,"quit") != 0){
		shortestDistance(_graph,"Bacon, Kevin",n,visited,parent,destination_actor);
		printf("\n");
		printf("----------------------------------------------------------------------------------------------------\n");
		printf("To quit the program, type quit to actor's/actress's name.\n");
		printf("Actor name and surname must be given as: Surname, Name.\n");
 	 	printf("Enter the actor's/actress's name to find connection map between Kevin Bacon: ");
  	scanf(" %[^\n]s",destination_actor);
		printf("----------------------------------------------------------------------------------------------------");
  	printf("\n");
	}
	return 0;
}

NODE* createNode(int vertex, char* movie_actor){
	NODE* newNode = (NODE*)malloc(sizeof(NODE));
	newNode->vertex = vertex;
	strcpy(newNode->movie_actor,movie_actor);
	newNode->next = NULL;
	newNode->visited = 0;
	return newNode;
}

GRAPH* createGraph(int nVertices){
	int i;
	GRAPH* _graph = (GRAPH*)malloc(sizeof(GRAPH));
 	_graph->nVertex = nVertices;
	_graph->adjList = (NODE**)malloc(nVertices*sizeof(NODE*));
	for(i=0; i<nVertices; i++){
		_graph->adjList[i] = NULL;
	}
	return _graph;
}
GRAPH* addEdge(int nVertices,char filename[]){
	GRAPH* _graph = createGraph(nVertices);
	FILE * fp = fopen(filename,"r");
	NODE* newNode;
	char* ptr1;
	char* ptr2;
	char movie_buffer[100];
	char buffer[10000];
	int i=0;
	for(i=0; i<nVertices; i++){
		moviectrl[i] = -1;
	}
	i = 0;
	int j=0;
	while(fgets(buffer,10000,fp)){
		int ctrlMovie = 0;
		j=0;
		ptr1=strtok(buffer,"\n");
		ptr2=strtok(ptr1,"/");
		strcpy(movie_buffer,ptr2);
		while(strcmp(storage[j],movie_buffer)!=0 && j<nVertices){
			j++;
		}
		moviectrl[j] = 1;
		while(ptr2!=NULL){
			ptr2= strtok(NULL,"/");
			if(ptr2!=NULL){
				while(strcmp(storage[i],ptr2)!=0 && i<nVertices){
					i++;
				}
				moviectrl[i] = 0;
				newNode = createNode(i,ptr2);
				newNode->next = _graph->adjList[j];
				_graph->adjList[j] = newNode;
				if(ctrlMovie == 0){
					newNode->ctrlMovie = 1;
					ctrlMovie++;
				}
				else{
					newNode->ctrlMovie = 0;
				}
				newNode = createNode(j,movie_buffer);
				newNode->next = _graph->adjList[i];
				_graph->adjList[i] = newNode;
			}
			i=0;
		}
	}
	return _graph;
}

int numberOfVertex(FILE* fp){
	int nVertex=0;
	char* ptr1;
	char* ptr2;
	char buffer[10000];
	int i=0;
	int j=0;
	while(fgets(buffer,10000,fp)){
		ptr1=strtok(buffer,"\n");
		ptr2=strtok(ptr1,"/");
		while(ptr2!=NULL){
			while(i<nVertex && strcmp(storage[i],ptr2)!=0){
				i++;
			}
			if(i==nVertex){
				strcpy(storage[j],ptr2);
				j++;
				nVertex++;
			}
			ptr2=strtok(NULL,"/");
			i=0;
		}
	}
	return nVertex;
}
/*
int numberOfVertex(FILE* fp){
	int nVertex=0;
	char ch;
	char buffer[100];
	int i=0;
	int j = 0;
	int first = 0;
	while(!feof(fp)){
		//printf("%d\n",nVertex);
		fscanf(fp,"%c",&ch);
		if(ch!='/'){
			if(ch!='\n'){
				buffer[i] = ch;
				i++;
			}
		}
		if(ch=='/' || ch=='\n'){
			j=0;
			if(first==0){
				first++;
				strcpy(storage[0],buffer);
				nVertex++;
			}
			else{
				while(j<nVertex && strcmp(storage[j],buffer)!=0){
					j++;
				}
				if(j==nVertex){
					strcpy(storage[j],buffer);
					nVertex++;
				}
			}
			for(int k=0; k<100; k++){
			buffer[k] = '\0';
			}
			i=0;
		}
	}
	printf("\n");
	return nVertex-1;
}*/
void printGraph(GRAPH* _graph, int n){
  GRAPH* current = _graph;
	int i;
  for(i=0; i<n; i++){
    printf("(%s||%d) : ",storage[i],i);
    while(current->adjList[i]->next!=NULL){
      printf("(%s||%d) -> ",current->adjList[i]->movie_actor,current->adjList[i]->vertex);
      current->adjList[i] = current->adjList[i]->next;

    }
    printf("(%s||%d)\n",current->adjList[i]->movie_actor,current->adjList[i]->vertex);
  }
}


void enqueue(QUEUE** q, int vertex, char movie_actor[100]){
	QUEUE* newNode = (QUEUE*)malloc(sizeof(QUEUE));
	newNode->vertex = vertex;
	strcpy(newNode->movie_actor,movie_actor);
	if((*q)==NULL){
		newNode->next = NULL;
		(*q) = newNode;
	}
	else{
		newNode->next = *q;
		*q = newNode;
	}
}

QUEUE* dequeue(QUEUE** q){
	if(*q == NULL){
		return NULL;
	}
	else{
		int counter = 0;
		QUEUE* current = *q;
		QUEUE* before = current;
		while(current->next != NULL){
			counter++;
			before = current;
			current = current->next;
		}
		if(counter != 0){
			before->next = NULL;
			return current;
		}
		else if(counter == 0){
			*q = NULL;
			return current;
		}
	}
}

void BreadthFirstSearch(GRAPH** _graph, char actor[100], int n,int* visited,int* parent){
	for(int k=0; k<n; k++){
		visited[k] = -1;
	}
	QUEUE* q = (QUEUE*)malloc(sizeof(QUEUE));
	QUEUE* returned = (QUEUE*)malloc(sizeof(QUEUE));
	GRAPH* current = *_graph;
	q = NULL;
	int i=0,j=0;
	char actors_movies[100];
  strcpy(actors_movies,actor);
  while(strcmp(storage[i],actors_movies) != 0){
  	i++;
  }
	enqueue(&q,i,actors_movies);
	visited[i] = 0;
	returned = dequeue(&q);
	while(returned != NULL){
		while(strcmp(storage[j],returned->movie_actor) != 0){
			j++;
		}
		GRAPH* tmp = current;
		while(tmp->adjList[j] != NULL){
			if(visited[tmp->adjList[j]->vertex] == -1){
				enqueue(&q,tmp->adjList[j]->vertex,tmp->adjList[j]->movie_actor);
				visited[tmp->adjList[j]->vertex] =visited[returned->vertex]  + 1;
				parent[tmp->adjList[j]->vertex] = returned->vertex;;
			}
			tmp->adjList[j] = tmp->adjList[j]->next;
		}
		j=0;
		returned = dequeue(&q);
	}
}

int* frequencyListOfKevinBaconNumbers(GRAPH* _graph,int max,int n,int* visited){
	int i,j;
	GRAPH* current = _graph;
	int* frequency = (int*)calloc(max+1,sizeof(int));
	j = 0;
	for(i=0; i<n; i++){
		if(moviectrl[i] == 0){
		 frequency[visited[i]] = frequency[visited[i]] + 1;
		}
	}
	printf("---------------------------------------------\n");
	printf("Kevin Bacon has 0 Kevin Bacon Number.\n");
	for(i=0; i<max+1; i++){
		if(i!=0){
			printf("%d actors/actress: %d Kevin Bacon Number.\n",frequency[i],i);
		}
		else{
			printf("%d actors/actress: Infinite Kevin Bacon Number.\n",frequency[i]-1);
		}
	}
	printf("---------------------------------------------\n");
	return frequency;
}

int findMaxDistance(int n,int* visited){
	int i;
	int max;
	int start = 0;
	for(i=0; i<n; i++){
		if(moviectrl[i] == 0 && start == 0){
			visited[i] = visited[i]/2;
			max = visited[i];
			start++;
		}
		if(moviectrl[i] == 0 && start !=0){
			visited[i] = visited[i]/2;
			if(max< visited[i]){
			max = visited[i];
			}
		}
	}
	return max;
}

void shortestDistance(GRAPH* _graph,char from[100], int n,int* visited, int* parent,char destination_actor[100]){
	int i;
	GRAPH* current = _graph;
	int path[10000];
	int pathIndex=0;
	int filectrl = 0;
	char buffer[200];
	i = 0;
	while(i<n && strcmp(storage[i],destination_actor) != 0){
		i++;
	}
	if(i == n){
		printf("The name %s cannot be found in movie data!\n",destination_actor);
	}
	else if(strcmp(destination_actor,"Bacon, Kevin") == 0){
		printf("Kevin Bacon's Kevin Bacon Number is 0.");
	}
	else{
		int distance = i;
		path[pathIndex] = i;
		pathIndex++;
		while(parent[i] != -1){
			path[pathIndex] = parent[i];
			pathIndex++;
			i = parent[i];
		}
		printf("%s's Kevin Bacon number is %d:\n\n",destination_actor,visited[distance]);
		for(i=0; i<pathIndex-2; i=i+2){
			printf("%s - %s -> %s\n",storage[path[i]],storage[path[i+2]],storage[path[i+1]]);
		}
		if(i==0){
				printf("Not in the same sub-network.\n");
		}
	}
}
