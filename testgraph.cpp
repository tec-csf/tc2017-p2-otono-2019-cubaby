/*
Grao usando las funciones de de la libreria de Snap 

/*
Programa utilizando la libreria snap para crear un grafo
Consiste de las funciones :
Insertar vértices en el grafo
Insertar arista en el grafo
Eliminar vértices del grafo
Eliminar aristas del grafo  
Realizar un recorrido en profundidad (DFS)-- 
Realizar un recorrido en amplitud (BFS)--
Algoritmo PRIM--
Algoritmo Kruskal--
Algoritmo Dijkstra--
Algoritmo Floyd-Warshall--
Material de apoyo: 
	http://snap.stanford.edu/snap/quick.html
	http://geeksforgeeks.com
	https://snap.stanford.edu/snap/doc/snapuser-ref/de/de8/classTNEGraph.html
	https://github.com
*/
#include "stdafx.h"
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <iomanip>
#include "Snap.h"
#define INF 1000000
using namespace std;


const int NODOSN = 15;
int valoresPeso[NODOSN][NODOSN];

void insertarNode(int);
void deleteNode(int);
void InsertarVertice(int, int, int);
void deleteVertice(int, int);
void metodoDFS(bool[], int);
void metodoBFS(int);
void algoFloydW();
void algoDijkstra(int);

PNGraph graph;
vector<pair<int,int> > getChildIds(int);


int main() {
	
	
	graph = TNGraph::New(); //se inicializa la gráfica multidirigido para permitir poner más de un vértice con un peso específico
	
	cout<< "Insertando nodos del grafo"<<endl;
	
	for (int i =1; i<NODOSN; i++) 
		insertarNode(i);

	
	cout<< "Insertando vertices y sus pesos al grafo"<<endl;
		

		InsertarVertice(1,4,8);
		InsertarVertice(1,3,8);
		InsertarVertice(2,5,7);
		InsertarVertice(3,2,7);
		InsertarVertice(3,5,8);
		InsertarVertice(3,10,4);
		InsertarVertice(4,5,1);
		InsertarVertice(4,7,3);
		InsertarVertice(4,8,2);	
		InsertarVertice(5,6,9);
		InsertarVertice(6,13,4);
		InsertarVertice(7,4,6);
		InsertarVertice(8,7,3);
		InsertarVertice(8,9,3);
		InsertarVertice(9,10,2);
		InsertarVertice(9,12,4);
		InsertarVertice(10,3,10);
		InsertarVertice(10,6,6);
		InsertarVertice(11,12,6);
		InsertarVertice(12,9,2);
		InsertarVertice(12,11,8);
		InsertarVertice(12,14,9);
		InsertarVertice(13,14,6);
		InsertarVertice(14,13,2);
		
		//int nodo;
		//deleteNodo(nodo);
		//deleteVertice(nodo);
		
		cout<< "Grafo creado"<<endl;
	
		bool visita[NODOSN];
		fill(visita, visita+NODOSN, false);

		cout << "Algoritmo DFS " << endl;
	//etodoDFS(visita,1);
		
		cout << endl << "Algoritmo BFS " << endl;
		metodoBFS(1);
		
		
		cout << "Algoritmo Floyd-Warshall" << endl;
		algoFloydW();
		
		
		
}//end main 


void insertarNode(int nodo){
	
	graph->AddNode(nodo);
	
}//end funcion insertar ndoo 

void deleteNodo(int nodo){
	
	graph->DelNode(nodo);
	
}//end funcion eliminar ndoo 

void deleteVertice(int inicioID, int finalID){
	
	graph->DelEdge(inicioID, finalID);
	valoresPeso[inicioID][finalID] = 0;
}//end funcion para eliminar vertices 

void InsertarVertice(int inicioID, int finalID, int peso){
	
	graph->AddEdge(inicioID, finalID);
	valoresPeso[inicioID][finalID] = peso;
	
}//funcion para insertar vertices con peso

void metodoDFS(bool visitado[], int inicio){
	
	if (!visitado[inicio]){
		// cout << act << endl;
		visitado[inicio] = true;
		vector<pair<int,int> > hijos = getChildIds(inicio);

		for (int i = 0; i < hijos.size(); i++)
			metodoDFS(visitado,hijos.at(i).first);
	}//end if
}//end metodo de DFS 

void algoFloydW(){
	int tabla[NODOSN][NODOSN];
	for (int j = 1; j < NODOSN; j++){
		for (int i = 1; i < NODOSN; i++){
			tabla[i][j] = valoresPeso[i][j];
			if (tabla[i][j] == 0) tabla[i][j] = INF;
			if (i == j) tabla[i][j] = 0;
		}
	}

	for (int z = 1; z < NODOSN; z++){
		for (int j = 1; j < NODOSN; j++){
			for (int i = 1; i < NODOSN; i++){
				if (tabla[z][j] + tabla[i][z]< tabla[i][j]){
					tabla[i][j] = tabla[z][j] + tabla[i][z];
				}
			}
		}
	}

	for (int j = 1; j < NODOSN; j++){
		for (int i = 1; i < NODOSN; i++){
			if (tabla[i][j] == INF) cout << "||";
			else{
				if (tabla[i][j] == 0) cout << "  ";
				else cout << setfill('0') << setw(2) << tabla[i][j];
			}
			cout << " ";
		}
	}

}//end algorithm Floyd 

void metodoBFS(int inicioID){
	
	queue<pair<int,int> > q;
	
	bool visitado[NODOSN];
	fill(visitado, visitado+NODOSN, false);
	q.push(make_pair(inicioID,0));

	while (!q.empty()){
		
		int act = q.front().first;
		q.pop();
		
		if (!visitado[act]){
			
			cout << act << endl;
			vector<pair<int,int> > childs = getChildIds(act);
			
			for (int i = 0; i < childs.size(); i++){
				q.push(childs.at(i));
			}
		}
		visitado[act] = true;
	}
}//end method of BFS

void sortChilds(vector<pair<int,int> >& childs){
	
	sort(childs.begin(), childs.end()/*,
		[](const pair<int,int> & a, const pair<int,int> & b) -> bool {
	return a.second > b.second;
	}*/);
}

vector<pair<int,int> > getChildIds(int id){
	
	vector<pair<int,int> > childs;
	TNGraph::TNodeI nodeI = graph->GetNI(id);
	
	for (int i = 1; i < NODOSN; i++){
		
		if (nodeI.IsOutNId(i)){
			childs.push_back(make_pair(i,valoresPeso[id][i]));
		}
	}
	
	sortChilds(childs);
	return childs;
}

void printDijkstra(int inicioID){
	
	queue<pair<int,int> > q;
	bool visitados[NODOSN];
	int distancias[NODOSN];
	fill(visitados, visitados+NODOSN, false);
	fill(distancias, distancias+NODOSN,INF);

	q.push(make_pair(inicioID,0));
	distancias[inicioID] = 0;

	while (!q.empty()){
		int act = q.front().first;
		q.pop();
		if (!visitados[inicioID]){
			vector<pair<int,int> > childs = getChildIds(act);
			for (int i = 0; i < childs.size(); i++){
				if (distancias[act] + childs.at(i).second < distancias[childs.at(i).first]){
					distancias[childs.at(i).first] = distancias[act] + childs.at(i).second;
					q.push(childs.at(i));
				}
			}
		}
		visitados[act] = true;
	}

	for (int i = 1; i < NODOSN; i++){
		cout << "(" << i << ") ";
		if (distancias[i] == INF) cout << "INF";
		else cout << distancias[i];
	}
}

void algoprim(int inicioID) {
	
	queue<pair<int,int> > q;
	bool visited[NODOSN];
	int distances[NODOSN];
	queue<pair<int,int> > ps;
	
	fill(visited, visited+NODOSN, false);
	fill(distances, distances+NODOSN,INF);

	q.push(make_pair(inicioID,0));
	distances[inicioID] = 0;

	while (!q.empty()) {
		
		int act = q.front().first;
		q.pop();
		
		if (!visited[act]) {
			
			vector<pair<int,int> > childs = getChildIds(act);
			
			for (int i = 0; i < childs.size(); i++) {
				if (childs.at(i).second < distances[childs.at(i).first]) {
					if(childs.at(i).first != NULL){
						
					distances[childs.at(i).first] = childs.at(i).second;
					q.push(childs.at(i));
					ps.push(make_pair(i,childs.at(i).second));
					
					}
				}
			}
		}
		visited[act] = true;
	}

	cout << "Origin\tParent\tWeight" << endl;
	cout << "   " << 1 << "\t   - \t   inf" << endl;
	int i = 2;	
	while(!ps.empty()) {
		cout << "   " << i << "\t   " << ps.front().second << "\t   " << distances[i] << endl;
		ps.pop();
		i++;
		if(i == NODOSN) break;

	}

}

