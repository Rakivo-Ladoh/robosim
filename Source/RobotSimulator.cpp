#include "RobotSimulator.h"

using namespace std;

/*
The main Robot Simulator. 
Set ups a board (5x5) and a unplaced robot.
Handles all commands:
PLACE X,Y,<FACE> 
MOVE
LEFT
RIGHT
REPORT

Command interpretation is generous as long as the begining is correct.
*/

namespace RoboSim {
	RobotSimulator::RobotSimulator() :
		board(5, 5),
		robot()
	{
	}

	RobotSimulator::~RobotSimulator()
	{
	}

	bool RobotSimulator::ProcessCommand(const std::string & command)
	{
		//TODO: Tokenise command?
		//TODO: Better command handling with all commands in a vector to iterate through. 
		if (command.length() < 4) return false;

		// Generous with commands and allow extra chars as long as the begining is correct.
		if (command.substr(0, 4).compare("MOVE") == 0) {

			return MoveRobot();;
		}
		else if (command.substr(0, 4).compare("LEFT") == 0) {
			return RotateRobot(false);
		}

		if (command.length() < 5) return false;

		if (command.substr(0, 5).compare("PLACE") == 0) {

			return ProcessPlace(command);
		}
		else if (command.substr(0, 5).compare("RIGHT") == 0) {
			return RotateRobot(true);
		}

		if (command.length() < 6) return false;

		if (command.substr(0, 6).compare("REPORT") == 0) {

			PrintRobotReport();
			return true;
		}

		return false;
	}

	bool RobotSimulator::ProcessPlace(const std::string &command)
	{
		//X,Y
		if (command.length() < 8) return false;

		int x = stoi(command.substr(6, 7));
		int y = stoi(command.substr(8, 9));
		//TODO:: Handle negative or double digits boards? Or any other char.

		if (x >= board.MAX_WIDTH || x < 0) {
			return false;
		}

		if (y >= board.MAX_HEIGHT || y < 0) {
			return false;
		}

		// Face
		//TODO: Improve similar to better handling commands (list/tokenise).
		FACE face = FACE::INVALID;
		if (command.length() == 14) {
			if (command.substr(10, 14).compare("EAST") == 0) {
				face = FACE::EAST;
			}
			else if (command.substr(10, 14).compare("WEST") == 0) {
				face = FACE::WEST;
			}
			else {
				return false;
			}
		}
		else if (command.length() == 15) {
			if (command.substr(10, 15).compare("NORTH") == 0) {
				face = FACE::NORTH;
			}
			else if (command.substr(10, 15).compare("SOUTH") == 0) {
				face = FACE::SOUTH;
			}
			else {
				return false;
			}
		}
		 
		if (face == FACE::INVALID) {
			return false;
		}

		return PlaceRobot(x, y, face);
	}

	std::string RobotSimulator::GetRobotReport()
	{
		return robot.GetReport();
	}

	void RobotSimulator::PrintRobotReport()
	{
		cout << GetRobotReport() << endl;
	}

	bool RobotSimulator::PlaceRobot(int x, int y, FACE face)
	{
		robot.X = x;
		robot.Y = y;
		robot.Face = face;
		robot.IsPlaced = true;
		return true;
	}

	bool RobotSimulator::MoveRobot()
	{
		if (robot.IsPlaced == false) return false;

		if (robot.Face == FACE::EAST) {
			++robot.X;
		}
		else if (robot.Face == FACE::NORTH) {
			++robot.Y;
		}
		else if (robot.Face == FACE::SOUTH) {
			--robot.Y;
		}
		else if (robot.Face == FACE::WEST) {
			--robot.X;
		}

		// Clamping
		if (robot.Y < 0) robot.Y = 0;
		if (robot.X < 0) robot.X = 0;
		if (robot.Y >= board.MAX_HEIGHT) robot.Y = board.MAX_HEIGHT - 1;
		if (robot.X >= board.MAX_WIDTH) robot.X = board.MAX_WIDTH - 1;
		//TODO: return false on clamp?

		//TODO: ValidCoords/ClampCoords method to be re-usable?

		return true;
	}

	bool RobotSimulator::RotateRobot(bool rotateRight)
	{
		if (robot.IsPlaced == false) return false;

		if (rotateRight) {
			RotateRight();
		}
		else {
			RotateLeft();
		}
		return true;
	}

	void RobotSimulator::RotateRight()
	{
		if (robot.Face == FACE::EAST) {
			robot.Face = FACE::SOUTH;
		}
		else if (robot.Face == FACE::NORTH) {
			robot.Face = FACE::EAST;
		}
		else if (robot.Face == FACE::SOUTH) {
			robot.Face = FACE::WEST;
		}
		else if (robot.Face == FACE::WEST) {
			robot.Face = FACE::NORTH;
		}
	}

	void RobotSimulator::RotateLeft()
	{
		//TODO: Less code duplication? Map faces clockwise and counter it.
		if (robot.Face == FACE::EAST) {
			robot.Face = FACE::NORTH;
		}
		else if (robot.Face == FACE::NORTH) {
			robot.Face = FACE::WEST;
		}
		else if (robot.Face == FACE::SOUTH) {
			robot.Face = FACE::EAST;
		}
		else if (robot.Face == FACE::WEST) {
			robot.Face = FACE::SOUTH;
		}
	}
}
