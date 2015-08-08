// Includes
#include "NetworkTopology\GridStructure.hpp"
#include "NetworkTopology\SOMNetwork.hpp"

void GridStructure::initialize(SOMNetwork &somNetwork)
{
	int width = (int)sqrt((float)somNetwork.getNeurons()->front().size());
	float exactHeight = (float)somNetwork.getNeurons()->front().size() / (int)sqrt((float)somNetwork.getNeurons()->front().size());
	int height = (int)exactHeight;
	if (exactHeight != height)
		height++;

	std::vector<std::vector<StandardNeuron*>> grid(width, std::vector<StandardNeuron*>(height, NULL));
	int neuronIndex = 0;
	for (auto neuron = somNetwork.getNeurons()->front().begin(); neuron != somNetwork.getNeurons()->front().end(); neuron++, neuronIndex++)
	{
		grid[neuronIndex % width][neuronIndex / width] = *neuron;
	}

	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{ 
			if (grid[x][y] != NULL)
			{
				neuronPositionsInStructure[grid[x][y]].resize(2);
				neuronPositionsInStructure[grid[x][y]][0] = x;
				neuronPositionsInStructure[grid[x][y]][1] = y;

				for (int otherX = 0; otherX < width; otherX++)
				{
					for (int otherY = 0; otherY < height; otherY++)
					{ 
						if (grid[otherX][otherY] != NULL)
						{
							double distance = sqrt(pow(x - otherX, 2.0) + pow(y - otherY, 2.0));
							if (distance == 1)
							{
								neighborhoodNeurons[grid[x][y]].push_back(grid[otherX][otherY]);
								neighborhoodNeurons[grid[otherX][otherY]].push_back(grid[x][y]);
							}							
							neighborhoodDistances[grid[x][y]][grid[otherX][otherY]] = distance;
							neighborhoodDistances[grid[otherX][otherY]][grid[x][y]] = distance;
						}
					}
				}
			}
		}
	}
}
