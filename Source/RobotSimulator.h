#pragma once

#include <iostream>
#include <string>    
#include <sstream>  

using namespace std;

namespace RoboSim {
	struct Board {

		// The origin (0,0) can be considered to be the SOUTH WEST most corner.
		int MAX_HEIGHT = 0;
		int MAX_WIDTH = 0;

		Board() {};
		Board(int height, int width) {
			MAX_HEIGHT = height;
			MAX_WIDTH = width;
		}
	};

	const int INVALID_POSITION = -1;
	static const std::string NOT_PLACED = "NOT PLACED";

	enum FACE {
		EAST,
		NORTH,
		SOUTH,
		WEST,
		NUM_FACES,
		INVALID // Starting face
	};

	//TODO:: Have const strings of all faces and commands?

	struct Robot {
		bool IsPlaced = false;
		FACE Face = FACE::INVALID;
		int X = INVALID_POSITION;
		int Y = INVALID_POSITION;

		string GetReport() {
			if (IsPlaced) {
				string s = std::to_string(X);
				s.append(",");
				s.append(std::to_string(Y));
				s.append(",");

				string face = "INVALID";
				if (Face == FACE::EAST) {
					face = "EAST";
				}
				else if (Face == FACE::NORTH) {
					face = "NORTH";
				}
				else if (Face == FACE::SOUTH) {
					face = "SOUTH";
				}
				else if (Face == FACE::WEST) {
					face = "WEST";
				}
				s.append(face);

				return s;
			}
			return NOT_PLACED;
		}
	};

	class RobotSimulator
	{
	public:
		RobotSimulator();
		~RobotSimulator();

		bool ProcessCommand(const string & command);
		string GetRobotReport(); // Mainly for unit testing.
		void PrintRobotReport();

	private:
		Board board;
		Robot robot;

		bool ProcessPlace(const string &command);
		bool PlaceRobot(int x, int y, FACE Face);
		bool MoveRobot();
		bool RotateRobot(bool rotateRight);
		void RotateRight();
		void RotateLeft();
	};
}