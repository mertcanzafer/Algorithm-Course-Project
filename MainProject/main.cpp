#include "Graph.h"

graph::Graph g;
std::vector<graph::Vertex>VertexList;
std::vector<std::string>CityLists;
std::vector<graph::Entity>Adjacents;

static const char* AdjacentFileLoc = "text_Files/adjacent_cities.txt";
static const char* DistanceFileLoc = "text_Files/CityDistances.txt";

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

void Menu()
{
	std::cout << "1)Enter city(or select):\n";
	std::cout << "2)Print selected(or entered) city:\n";
	std::cout << "3)List k closest  cities (to selected city):\n";
	std::cout << "4)Find shortest path to\n";
	std::cout << "5)Exit: \n";
	std::cout << "Enter your choice: " << std::endl;
}

int main()
{
	// Build the graph !!
	ReadFile(AdjacentFileLoc);
	g = graph::Graph(VertexList);
	g.ConstructDistanceTable(DistanceFileLoc);
	g.SetWeights();

	int choice = 0,plateId = 0,ctr = 0, k = 0;
	std::string CurCity,DestCity;

	while (choice != 5)
	{
		Menu();
		std::cin >> choice;

		switch (choice)
		{
		case 1:
			std::cout << "Choose 1 to enter a city name\n";
			std::cout << "Choose 2 to enter a plate id\n";
			std::cout << "Choose (1 / 2): ";
			std::cin >> ctr;
			if (ctr == 1)
			{
				std::cout << "Enter a city name: ";
				std::cin >> CurCity;
				std::cout<<"\n";
			}
			else if(ctr == 2) {
				std::cout << "Enter a plate Number: ";
				std::cin >> plateId;
				CurCity = VertexList[plateId - 1].CityName;
				std::cout << "\n";
			}
			break;
		case 2:
			std::cout << "You've selected city = " << CurCity << std::endl;
			std::cout << "\n";
			break;
		case 3:
			std::cout << "Enter the k value" << std::endl;
			std::cin >> k;
			g.findKClosestCities(CurCity, k);
			std::cout << "\n";
			break;
		case 4:
			std::cout << "Enter the Dest City name to find the shortest path: ";
			std::cin >> DestCity;
			g.FindShortestPath(CurCity, DestCity);
			std::cout << "\n";
			break;
		}
	}

	return 0;
}