#include "Graph.h"

graph::Graph g;
std::vector<graph::Vertex>VertexList;
std::vector<std::string>CityLists;
std::vector<graph::Entity>Adjacents;

static const char* AdjacentFileLoc = "text_Files/test.txt";
static const char* DistanceFileLoc = "text_Files/test2.txt";

void ConstructVertexList()
{
	CityLists = { "Ankara","Adana","Giresun","Bursa" };
	
	// Vertex = "Ankara"
	graph::Entity e1;
	e1.cityName = CityLists[1];
	graph::Entity e2;
	e2.cityName = CityLists[3];
	std::vector<graph::Entity> Ev1{e1, e2};
	VertexList.push_back(graph::Vertex(CityLists[0], Ev1));
	Ev1.clear();
	//  Vertex = "Adana"
	e1.cityName = CityLists[0];
	e2.cityName = CityLists[2];
	Ev1 = { e1,e2 };
	VertexList.push_back(graph::Vertex(CityLists[1], Ev1));
	Ev1.clear();
	// Vertex = "Giresun"
	e1.cityName = CityLists[1];
	e2.cityName = CityLists[3];
	Ev1 = { e1,e2 };
	VertexList.push_back(graph::Vertex(CityLists[2], Ev1));
	Ev1.clear();
	// Vertex = "Bursa"
	e1.cityName = CityLists[0];
	e2.cityName = CityLists[2];
	Ev1 = { e1,e2 };
	VertexList.push_back(graph::Vertex(CityLists[3], Ev1));
	Ev1.clear();
}

void ReadFile(const char* fileLoc)
{
	graph::Entity e;

	std::string line;
	std::fstream file;
	file.open(fileLoc, std::ios::in);

	if (!file) { std::cout << "No such a file exits." << std::endl; return; }

	while (!file.eof())
	{
		std::getline(file, line);
		
		std::string content = "";
		int FirstComma = line.find(',');
		std::string VertexStr = line.substr(0, FirstComma);
	    
		for (size_t i = FirstComma + 1; i < line.length(); i++)
		{
			if (line[i] != ',')
			{
				content += line[i];
			}
			else {
				e.cityName = content;
				Adjacents.push_back(e);
				content = "";
			}
		}
		e.cityName = content;
		Adjacents.push_back(e);
		content = "";

		VertexList.push_back(graph::Vertex(VertexStr, Adjacents));
		Adjacents.clear();
	}

	file.close();
}

int main()
{
	//ConstructVertexList();
	ReadFile(AdjacentFileLoc);

	g = graph::Graph(VertexList);

	std::cout << "The number of vertex is: " << g.getVsize()<<std::endl;
	std::cout << "The number of edge is: " << g.getEsize() << std::endl;
	std::cout << "-----------------------------" << std::endl;
	g.printGraph();

	std::cout << "-----------------------------" << std::endl;
	g.ConstructDistanceTable(DistanceFileLoc);
	g.printDistanceTable();

	return 0;
}