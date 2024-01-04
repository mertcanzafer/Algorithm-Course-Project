#include "Graph.h"

graph::Graph g;
std::vector<graph::Vertex>VertexList;
std::vector<std::string>CityLists;
std::vector<graph::Entity>Adjacents;

static const char* AdjacentFileLoc = "text_Files/test.txt";
static const char* DistanceFileLoc = "text_Files/test2.txt";

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
	ReadFile(AdjacentFileLoc);

	g = graph::Graph(VertexList);

	std::cout << "The number of vertex is: " << g.getVsize()<<std::endl;
	std::cout << "The number of edge is: " << g.getEsize() << std::endl;
	std::cout << "-----------------------------" << std::endl;
	g.ConstructDistanceTable(DistanceFileLoc);
	//g.printDistanceTable();

	g.SetWeights();
	g.printGraph();
	std::string city = "Giresun";
	std::string dest = "Ankara";
	g.findKClosestCities(city, 3);
	std::cout << "\n-----------------------------" << std::endl;
	g.FindShortestPath(city, dest);

	return 0;
}