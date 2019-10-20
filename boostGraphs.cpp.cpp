

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <tuple>
#include <iterator>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/depth_first_search.hpp>
#include <boost/graph/breadth_first_search.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/prim_minimum_spanning_tree.hpp>
#include <boost/graph/kruskal_min_spanning_tree.hpp>
#include <boost/graph/floyd_warshall_shortest.hpp>
#include <boost/graph/exterior_property.hpp>
#include <chrono>
#include <cstdio>

using namespace boost;
using namespace std::chrono;

typedef property<vertex_distance_t, int> Vdistance;
typedef property<edge_weight_t, int> EdgeWeight;
typedef adjacency_list <vecS, vecS, bidirectionalS, Vdistance, EdgeWeight> Graph;
typedef property_map<Graph, edge_weight_t>::type EdgeWeights;
typedef boost::graph_traits<Graph>::vertex_descriptor vertex_t;
typedef graph_traits < Graph >::edge_descriptor Edge;
typedef boost::exterior_vertex_property<Graph, int> DistanceProperty;
typedef DistanceProperty::matrix_type DistanceMatrix;
typedef DistanceProperty::matrix_map_type DistanceMatrixMap;

class dfsVisitor : public boost::default_dfs_visitor
{
public:
	
	void discover_vertex(vertex_t v, const Graph& g) const
	{
		std::cerr << v << " " ;
		
		return;
	}
};

class bfsVisitor : public boost::default_bfs_visitor
{
public:
	void discover_vertex(vertex_t v, const Graph& g) const
	{
		std::cerr << v << " ";
		return;
	}
};


class BoostGraph
{
public:
	
	std::vector<std::string> name = { "1","2","3","4","5","6","7","8","9","10","11","12","13","14" };
public: 

	Graph init_graph()
	{
		std::vector<int> vertices = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14 };
		Graph g(vertices.size());
		std::vector<int> pesos = { 8,8,8,7,4,7,9,4,6,2,3,1,2,6,3,3,2,4,10,6,8,6,2,9 };
		

		add_edge(1,3,8,g);
		add_edge(1, 4,8,g);
		add_edge(3,5,8,g);
		add_edge(3,2,7,g);
		add_edge(3,10,4,g);
		add_edge(2,5,7,g);
		add_edge(5,6,9,g);
		add_edge(6,13,4,g);
		add_edge(13,14,6,g);
		add_edge(14,13,2,g);
		add_edge(4,7,3,g);
		add_edge(4,5,1,g);
		add_edge(4,8,2,g);
		add_edge(7,4,6,g);
		add_edge(8,7,3, g);
		add_edge(8,9,3, g);
		add_edge(9,10,2, g);
		add_edge(9,12,4, g);
		add_edge(10,3,10, g);
		add_edge(10,6,6, g);
		add_edge(12,11,8, g);
		add_edge(11,12,6, g);
		add_edge(12,9,2, g);
		add_edge(12,14,9, g);
		
		

		return g;
	}

	Graph addVertex(Graph p,int vertex)//Complejidad O(1)
	{
		vertex_t u;
		auto start = high_resolution_clock::now();
		
		u= add_vertex(p);

		auto stop = high_resolution_clock::now();
		auto duration = duration_cast<nanoseconds>(stop - start);
		std::cout << "La duracion es: " << duration.count() << " ns \n";
		name.push_back(	std::to_string(vertex));

		std::cout << "Se puso el vertice "<< vertex << "\n";
		return p;
	}

	Graph addEdge(Graph p, int sale, int entra, int peso) //Complejidad O(1)
	{
		auto start = high_resolution_clock::now();

		add_edge(sale, entra, peso, p);
		auto stop = high_resolution_clock::now();
		auto duration = duration_cast<nanoseconds>(stop - start);
		std::cout << "La duracion es: " << duration.count() << " ns \n";

		std::cout << "Se puso la arista de " << sale << " a " << entra << "\n";
		return p;
	}

	Graph removeEdge(Graph p, int sale, int entra)//Complejidad O(1)
	{
		auto start = high_resolution_clock::now();

		remove_edge(sale, entra, p);
		auto stop = high_resolution_clock::now();
		auto duration = duration_cast<nanoseconds>(stop - start);
		std::cout << "La duracion es: " << duration.count() << " ns \n";

		std::cout << "Se removio la arista de " << sale << " a " << entra << "\n";
		return p;
	}

	Graph removeVertex(Graph p, int u) //complejidad O(m+n)
	{
		auto start = high_resolution_clock::now();

		clear_vertex(u,p);
		remove_vertex(u, p);

		auto stop = high_resolution_clock::now();
		auto duration = duration_cast<nanoseconds>(stop - start);
		std::cout << "La duracion de removeVertex es: " << duration.count() << " ns \n";

		std::cout << "Se ha removido el vertice " << u; 
		return p;
	}

	void DFS(Graph p)//complejidad O(n+m) Técnica: Backtracking

	{
		

		dfsVisitor temp;
		std::cout << "DFS: \n";
		auto start = high_resolution_clock::now();

		depth_first_search(p, visitor(temp));

		auto stop = high_resolution_clock::now();
		auto duration = duration_cast<nanoseconds>(stop - start);
		std::cout << "La duracion de DFS es: " << duration.count() << " ns \n";

		std::cout << " \n";
	}

	void BFS(Graph p, int inicio)//complejidad O(n+m) Técnica: No tiene.
	{
		

		bfsVisitor temp;
		std::cout << "BFS: \n";
		auto start = high_resolution_clock::now();

		breadth_first_search(p,inicio, visitor(temp));

		auto stop = high_resolution_clock::now();
		auto duration = duration_cast<nanoseconds>(stop - start);
		std::cout << "La duracion de BFS es: " << duration.count() << " ns \n";

		std::cout << " \n";
	}

	void Dijkstra(Graph g) //complejidad O(n log n) Técnica: Algoritmos ávidos. 
	{

		std::vector<vertex_t> p(num_vertices(g));
		std::vector<int> d(num_vertices(g));
		
		vertex_t s = vertex(1, g);
		property_map<Graph, vertex_index_t>::type indexmap = get(vertex_index, g);
		property_map<Graph, edge_weight_t>::type weightmap = get(edge_weight, g);
		auto start = high_resolution_clock::now();
		dijkstra_shortest_paths(g, s, &p[0], &d[0], weightmap, indexmap,
			std::less<int>(), closed_plus<int>(),
			(std::numeric_limits<int>::max)(), 0,
			default_dijkstra_visitor());

		auto stop = high_resolution_clock::now();
		auto duration = duration_cast<nanoseconds>(stop - start);
		std::cout << "La duracion de Dijkstra es: " << duration.count() << " ns \n";

		std::cout << "\n Dijkstra:" << std::endl;
		graph_traits <Graph>::vertex_iterator vi, vend;
		for (tie(vi, vend) = vertices(g); vi != vend; ++vi) {
			std::cout << "distancia al vertice " << name[*vi] << " = " << d[*vi] << ", ";
			std::cout << " con padre " << name[p[*vi]] << std::
				endl;
		}
	}

	void primMST(Graph p) //complejidad (m log n) Técnica: Algoritmos ávidos. 
	{
		std::vector<vertex_t> v(num_vertices(p));
		
		property_map<Graph, vertex_index_t>::type indexmap = get(vertex_index, p);
		property_map<Graph, vertex_distance_t>::type distance = get(vertex_distance, p);
		property_map<Graph, edge_weight_t>::type weightmap = get(edge_weight, p);
		auto start = high_resolution_clock::now();

		prim_minimum_spanning_tree(p, *vertices(p).first,&v[0],distance,weightmap,indexmap, default_dijkstra_visitor());
		//prim_minimum_spanning_tree(p, &v[0]);

		auto stop = high_resolution_clock::now();
		auto duration = duration_cast<nanoseconds>(stop - start);
		std::cout << "La duracion de Prim es: " << duration.count() << " ns \n";

		for (std::size_t i = 1; i != v.size(); ++i)
			if (v[i] != i)
				std::cout << "parent[" << i << "] = " << v[i] << std::endl;
			else
				std::cout << "parent[" << i << "] = no hay padre" << std::endl;
	}

	void kruskalMST(Graph p) //complejidad O(n log n) Técnica: Algoritmos ávidos
	{
		property_map < Graph, edge_weight_t >::type weight = get(edge_weight, p);
		std::vector < Edge > spanning_tree;

		auto start = high_resolution_clock::now();
		
		kruskal_minimum_spanning_tree(p, std::back_inserter(spanning_tree));

		auto stop = high_resolution_clock::now();
		auto duration = duration_cast<nanoseconds>(stop - start);
		std::cout << "La duracion de Kruskal es: " << duration.count() << " ns";

		std::cout << "Kruskal MST: \n";
		for (std::vector < Edge >::iterator ei = spanning_tree.begin();
			ei != spanning_tree.end(); ++ei) {
			std::cout << source(*ei, p) << " <--> " << target(*ei, p)
				<< " con peso " << weight[*ei]
				<< std::endl;
		}
	}

	void FloydWarshall(Graph p) //complejidad O(n^3) Técnica: Programación dinámica
	{
		DistanceMatrix distances(num_vertices(p));
		DistanceMatrixMap dm(distances, p);
		property_map < Graph, edge_weight_t >::type weight = get(edge_weight, p);
		auto start = high_resolution_clock::now();

		floyd_warshall_all_pairs_shortest_paths(p, dm,boost::weight_map(weight));

		auto stop = high_resolution_clock::now();
		auto duration = duration_cast<nanoseconds>(stop - start);
		std::cout << "La duracion de FW-AP es: " << duration.count() << " ns";

		std::cout << "\n Floyd-Warshall AP-SP: " << std::endl;
		for (std::size_t i = 1; i < num_vertices(p); ++i) {
			for (std::size_t j = 1; j < num_vertices(p); ++j) {
				std::cout << "del vertice " << i  << " al " << j  << " : ";
				if (distances[i][j] == std::numeric_limits<int>::max())
					std::cout << "X" << std::endl;
				else
					std::cout << distances[i][j] << std::endl;
			}
			std::cout << std::endl;
		}
	}
};

int main()
{
	BoostGraph driver;
	Graph g = driver.init_graph();
	g=driver.addVertex(g, 15);
	g=driver.addEdge(g, 14, 15, 2);
	g=driver.removeEdge(g, 10, 3);
	driver.DFS(g);
	driver.BFS(g,1);
	driver.primMST(g);
	driver.kruskalMST(g);
	driver.Dijkstra(g);
	driver.FloydWarshall(g);
	driver.removeVertex(g, 15);
	std::getchar(); //Ahi para que no se cierre el ejecutable a la primera
	return 0;
}


// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
