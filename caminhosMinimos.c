// A structure to represent a queue
struct Queue {
    int front, rear, size;
    unsigned capacity;
    int* array;
};


struct Queue* createQueue(unsigned capacity)
{
    struct Queue* queue = (struct Queue*)malloc(
        sizeof(struct Queue));
    queue->capacity = capacity;
    queue->front = queue->size = 0;
  
    // This is important, see the enqueue
    queue->rear = capacity - 1;
    queue->array = (int*)malloc(
        queue->capacity * sizeof(int));
    return queue;
}
  
// Queue is full when size becomes
// equal to the capacity
int isFull(struct Queue* queue)
{
    return (queue->size == queue->capacity);
}
  
// Queue is empty when size is 0
int isEmpty(struct Queue* queue)
{
    return (queue->size == 0);
}
  
// Function to add an item to the queue.
// It changes rear and size
void enqueue(struct Queue* queue, int item)
{
    if (isFull(queue))
        return;
    queue->rear = (queue->rear + 1)
                  % queue->capacity;
    queue->array[queue->rear] = item;
    queue->size = queue->size + 1;
    // printf("%d enqueued to queue\n", item);
}
int dequeue(struct Queue* queue)
{
    if (isEmpty(queue))
        return -1;
    int item = queue->array[queue->front];
    queue->front = (queue->front + 1)
                   % queue->capacity;
    queue->size = queue->size - 1;
    return item;
}

// G->adj[G->raiz][G->V+2]: distancia
// G->adj[G->raiz][G->V+3]: estado
int caminhosMinimos(Graph G){
    for(int i=0; i<G->V; i++){
        G->adj[i][G->V+2] = 0;
        G->adj[i][G->V+3] = 0;
    }

    int biggestDistance = 0;
    struct Queue * fila = createQueue(100);
    G->adj[G->raiz][G->V+2] = 0;//distancia pra raiz igual a zero
    enqueue(fila, G->raiz);
    G->adj[G->raiz][G->V+3] = 1;//estado da raiz = 1

    while(!isEmpty(fila)){//enquanto a fila não está vazia
        int v = dequeue(fila);
        for (int w = 0; w < G->V; ++w){
            if(w==v) continue;
            if (G->adj[v][w] == 1 && !G->adj[w][G->V+1]){//se é vizinho E w tá vivo 
                if(!G->adj[w][G->V+3]){
                    G->adj[w][G->V+2] = G->adj[v][G->V+2] + 1;
                    if(G->adj[w][G->V+2]>biggestDistance)biggestDistance = G->adj[w][G->V+2];
                    enqueue(fila, w);
                    G->adj[w][G->V+3] = 1;
                }
            }
        }
        G->adj[v][G->V+3] = 2;
    }

    return biggestDistance;
}