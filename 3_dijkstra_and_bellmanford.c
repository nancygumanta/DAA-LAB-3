#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

#define V 6  // Number of vertices
#define INF INT_MAX

// Structure to represent an edge
struct Edge {
    int src, dest, weight;
};

// Function to initialize the distance array
void initializeDistances(int dist[], int src) {
    for (int i = 0; i < V; i++)
        dist[i] = INF;
    dist[src] = 0;
}

// Function to find the vertex with minimum distance
int minDistance(int dist[], int visited[]) {
    int min = INF, min_index;
    for (int v = 0; v < V; v++) {
        if (!visited[v] && dist[v] <= min) {
            min = dist[v];
            min_index = v;
        }
    }
    return min_index;
}

// Dijkstra's Algorithm
void dijkstra(int graph[V][V], int src, int dist[]) {
    int visited[V];
    
    // Initialize distances and visited array
    initializeDistances(dist, src);
    for (int i = 0; i < V; i++)
        visited[i] = 0;
    
    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, visited);
        visited[u] = 1;
        
        for (int v = 0; v < V; v++) {
            if (!visited[v] && graph[u][v] && 
                dist[u] != INF && 
                dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }
}

// Bellman-Ford Algorithm
int bellmanFord(struct Edge edges[], int E, int src, int dist[]) {
    // Initialize distances
    initializeDistances(dist, src);
    
    // Relax all edges V-1 times
    for (int i = 0; i < V - 1; i++) {
        for (int j = 0; j < E; j++) {
            int u = edges[j].src;
            int v = edges[j].dest;
            int weight = edges[j].weight;
            if (dist[u] != INF && dist[u] + weight < dist[v])
                dist[v] = dist[u] + weight;
        }
    }
    
    // Check for negative weight cycles
    for (int i = 0; i < E; i++) {
        int u = edges[i].src;
        int v = edges[i].dest;
        int weight = edges[i].weight;
        if (dist[u] != INF && dist[u] + weight < dist[v])
            return 0;  // Negative cycle exists
    }
    return 1;  // No negative cycle
}

// Function to print distances
void printDistances(int dist[]) {
    printf("Vertex \t Distance from Source\n");
    for (int i = 0; i < V; i++)
        printf("%d \t\t %d\n", i, dist[i]);
}

// Function to convert adjacency matrix to edge list
int matrixToEdgeList(int graph[V][V], struct Edge edges[]) {
    int E = 0;
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (graph[i][j] != 0) {
                edges[E].src = i;
                edges[E].dest = j;
                edges[E].weight = graph[i][j];
                E++;
            }
        }
    }
    return E;
}

int main() {
    // Example graph represented as adjacency matrix
    int graph[V][V] = {
        {0, 4, 0, 0, 0, 0},
        {4, 0, 8, 0, 0, 0},
        {0, 8, 0, 7, 0, 4},
        {0, 0, 7, 0, 9, 14},
        {0, 0, 0, 9, 0, 10},
        {0, 0, 4, 14, 10, 0}
    };
    
    struct Edge edges[V * V];  // Maximum possible edges
    int E = matrixToEdgeList(graph, edges);
    
    int source = 0;
    int dist_dijkstra[V], dist_bellman[V];
    clock_t start, end;
    double cpu_time_used;
    
    // Measure Dijkstra's Algorithm performance
    start = clock();
    dijkstra(graph, source, dist_dijkstra);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    
    printf("\nDijkstra's Algorithm Results:\n");
    printDistances(dist_dijkstra);
    printf("Time taken: %f seconds\n", cpu_time_used);
    
    // Measure Bellman-Ford Algorithm performance
    start = clock();
    int no_negative_cycle = bellmanFord(edges, E, source, dist_bellman);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    
    printf("\nBellman-Ford Algorithm Results:\n");
    if (no_negative_cycle) {
        printDistances(dist_bellman);
        printf("Time taken: %f seconds\n", cpu_time_used);
    } else {
        printf("Graph contains negative weight cycle\n");
    }
    
    return 0;
}
