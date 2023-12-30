#include "Graph.h"

graph::Graph g;
std::vector<graph::Vertex>VertexList;

void ConstructVertexList()
{
	std::vector<std::string>CityLists{ "Ankara","Adana","Giresun","Bursa" };
	
	// Vertex = "Ankara"
	graph::Entity e1;
	e1.cityName = CityLists[1];
	graph::Entity e2;
	e2.cityName = CityLists[3];
	std::vector<graph::Entity> Ev1{e1, e2};
	VertexList.push_back(graph::Vertex(CityLists[0], Ev1));

	//  Vertex = "Adana"
	e1.cityName = CityLists[0];
	e2.cityName = CityLists[2];
	std::vector<graph::Entity>Ev2{ e1,e2 };
	VertexList.push_back(graph::Vertex(CityLists[1], Ev2));

	// Vertex = "Giresun"
	e1.cityName = CityLists[1];
	e2.cityName = CityLists[3];
	std::vector<graph::Entity>Ev3{ e1,e2 };
	VertexList.push_back(graph::Vertex(CityLists[2], Ev3));

	// Vertex = "Bursa"
	e1.cityName = CityLists[0];
	e2.cityName = CityLists[2];
	std::vector<graph::Entity>Ev4{ e1,e2 };
	VertexList.push_back(graph::Vertex(CityLists[3], Ev4));

}

int main()
{
	ConstructVertexList();

	g = graph::Graph(VertexList);

	std::cout << "The number of vertex is: " << g.getVsize()<<std::endl;
	std::cout << "The number of edge is: " << g.getEsize() << std::endl;
	std::cout << "-----------------------------" << std::endl;
	g.printGraph();

	return 0;
}