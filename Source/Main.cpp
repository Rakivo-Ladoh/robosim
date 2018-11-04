#include <iostream>   
#include <fstream> 
#include <cassert>
#include <filesystem>
#include "RobotSimulator.h"
#include "Main.h"

namespace fs = std::experimental::filesystem;
using namespace std;

const string INPUT_DIRECTORY_PATH = "Input/";

/*
Main file to start the testing the Robot Simulation.
Input files are read from a directory and each line is processed as a command.
*/
int main()
{
	cout << "Welcome to Robot Simulation!" << endl << endl;

	ExecuteFilesInDirectory(INPUT_DIRECTORY_PATH);
	PauseForUserInput();

	return 0;
}

void ExecuteFilesInDirectory(const string& directoryPath)
{
	auto directory = fs::directory_iterator(directoryPath);

	for (const auto & file : directory) {
		const string &filePath = file.path().string();
		ExecuteCommandsFromFile(filePath);
	}
}

void ExecuteCommandsFromFile(const string &fileName)
{
	cout << "Testing start: " << fileName << endl << endl;
	ifstream file(fileName);
	assert(file);

	auto sim = RoboSim::RobotSimulator();

	if (file.is_open()) {
		std::string line;
		while (getline(file, line)) {
			sim.ProcessCommand(line.c_str());
		}
		file.close();
	}
	else {
		cerr << "Error with " << fileName << endl;
	}

	cout << endl << "Testing done: " << fileName << endl << endl;
}

void PauseForUserInput()
{
	do
	{
		cout << endl << "Simulation done." << endl;
		cout << "Press a key to exit..." << endl;
	} 
	while (cin.get() != '\n');
}
