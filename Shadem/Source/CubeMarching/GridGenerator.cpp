#pragma once

#include <fstream>
#include <iostream>
#include <vector>
#include "CubeMarching/GridGenerator.h"
#include "CubeMarching/Types.h"

using namespace MarchingCubeGenerator;

float GridGenerator::get_random_number() {
	float randomNumber = (float)rand() / RAND_MAX;
	randomNumber -= 0.5;
	randomNumber *= 2.0;

	return randomNumber;
}

GridGenerator::GridGenerator(glm::vec3 gridSize) {
    this->gridSize = gridSize;
}

std::vector<std::vector<std::vector<float>>> GridGenerator::generate_random_grid()
{
	std::vector<std::vector<std::vector<float>>> scalarFunction(gridSize.x, std::vector<std::vector<float>>(gridSize.y, std::vector<float>(gridSize.z)));

	for (int i = 0; i < gridSize.x; i++) {
		for (int j = 0; j < gridSize.y; j++) {
			for (int k = 0; k < gridSize.z; k++) {
				scalarFunction[i][j][k] = get_random_number();
			}
		}
	}

	return scalarFunction;
}

std::vector<std::vector<std::vector<float>>> GridGenerator::generate_sphere() {
	std::vector<std::vector<std::vector<float>>> scalarFunction(gridSize.x, std::vector<std::vector<float>>(gridSize.y, std::vector<float>(gridSize.z)));

	float centerX = 0.5f, centerY = 0.5f, centerZ = 0.5f, radius = 0.25f;
	for (int k = 0; k < gridSize.x; k++) {
		for (int j = 0; j < gridSize.y; j++) {
			for (int i = 0; i < gridSize.z; i++) {
				float x = i / gridSize.x, y = j / gridSize.y, z = k / gridSize.z;
				float val = (centerX - x) * (centerX - x) + (centerY - y) * (centerY - y) + (centerZ - z) * (centerZ - z);

				if (val <= radius * radius)
					scalarFunction[i][j][k] = -1.0f; 
				else {
					scalarFunction[i][j][k] = 1.0;
				}
			}
		}
	}

	return scalarFunction;
}

std::vector<std::vector<std::vector<float>>> GridGenerator::generate_nested_spheres() {
	std::vector<std::vector<std::vector<float>>> scalarFunction(gridSize.x, std::vector<std::vector<float>>(gridSize.y, std::vector<float>(gridSize.z)));

	int r1 = 50, cx1 = 64, cy1 = 64, cz1 = 64;
	int r2 = 25, cx2 = 64, cy2 = 64, cz2 = 64;

	for (int i = 0; i < gridSize.x; i++) {
		for (int j = 0; j < gridSize.y; j++) {
			for (int k = 0; k < gridSize.z; k++) {

				int val1 = (cx1-i)*(cx1-i) + (cy1-j)*(cy1-j) + (cz1-k)*(cz1-k);
				int val2 = (cx2-i)*(cx2-i) + (cy2-j)*(cy2-j) + (cz2-k)*(cz2-k);

				if (val1 <= r1*r1 && val2 > r2*r2) {
					scalarFunction[i][j][k] = -1;
				}
				else {
					scalarFunction[i][j][k] = 1;
				}
			}
		}
	}
	return scalarFunction;
}

std::vector<std::vector<std::vector<float>>> GridGenerator::read_grid_from_file(const char* path) {
	std::vector<std::vector<std::vector<float>>> scalarFunction(gridSize.x, std::vector<std::vector<float>>(gridSize.y, std::vector<float>(gridSize.z)));
	
	int i, j, k;
	float value;
	FILE* inputFile = fopen(path, "r");
	while (fscanf(inputFile, "%d %d %d %f", &i, &j, &k, &value) != EOF) {
		scalarFunction[i][j][k] = value;
	}

	return scalarFunction;
}