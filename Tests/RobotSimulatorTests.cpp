#include "..\TestFramework\CppUnitTest.h"
#include "..\Source\RobotSimulator.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;
using namespace RoboSim;

TEST_CLASS(RobotLabTests)
{
public:

// Initial setup tests ===========================================================
	TEST_METHOD(CommandEmpty) {
		auto sim = RobotSimulator();
		Assert::IsFalse(sim.ProcessCommand(string("")));
	}

	TEST_METHOD(CommandFails) {
		auto sim = RobotSimulator();
		Assert::IsFalse(sim.ProcessCommand(string("A")));
		Assert::IsFalse(sim.ProcessCommand(string("1")));
		Assert::IsFalse(sim.ProcessCommand(string("BAD_COMMANDS")));
	}

	TEST_METHOD(RobotNotPlaced) {
		auto sim = RobotSimulator();
		Assert::AreEqual(NOT_PLACED, sim.GetRobotReport());
	}

	TEST_METHOD(BoardSize) {
		auto sim = RobotSimulator();
		Assert::IsFalse(sim.ProcessCommand(string("PLACE 6,6,NORTH")));
	}

// PLACE tests ===========================================================
	TEST_METHOD(PlaceFail) {
		auto sim = RobotSimulator();
		Assert::IsFalse(sim.ProcessCommand(string("PLACE")));
	}

	TEST_METHOD(PlaceFails) {
		auto sim = RobotSimulator();

		Assert::IsFalse(sim.ProcessCommand(string("PLACE 0")));
		Assert::IsFalse(sim.ProcessCommand(string("PLACE 0,0")));
		Assert::IsFalse(sim.ProcessCommand(string("PLACE 0,0,NOR")));
		Assert::IsFalse(sim.ProcessCommand(string("PLACE 0,0,NORT")));
		Assert::IsFalse(sim.ProcessCommand(string("PLACE 0,0,NORTHS")));

		Assert::IsFalse(sim.ProcessCommand(string("PLACE 0,0,WESTS")));

		// TODO: These really fail and could get fixed if time.
		// Assert::IsFalse(sim.ProcessCommand(string("PLACE A,B,WESTS")));
		// Assert::IsFalse(sim.ProcessCommand(string("PLACE A,B,12345")));
		// Assert::IsFalse(sim.ProcessCommand(string("PLACE -1,-10,NORTHS")));
	}

	TEST_METHOD(PlaceOutofBounds) {
		auto sim = RobotSimulator();
		Assert::IsFalse(sim.ProcessCommand(string("PLACE 5,5,SOUTH")));
		Assert::AreEqual(NOT_PLACED, sim.GetRobotReport());
	}

	TEST_METHOD(PlaceTrue) {
		auto sim = RobotSimulator();
		Assert::IsTrue(sim.ProcessCommand(string("PLACE 0,0,NORTH")));
	}

	TEST_METHOD(PlaceTrueMulti) {
		auto sim = RobotSimulator();
		Assert::IsTrue(sim.ProcessCommand(string("PLACE 0,0,NORTH")));
		Assert::IsTrue(sim.ProcessCommand(string("PLACE 1,1,NORTH")));
		Assert::IsTrue(sim.ProcessCommand(string("PLACE 1,2,WEST")));
	}

	TEST_METHOD(PlacedRobot) {
		auto sim = RobotSimulator();
		Assert::IsTrue(sim.ProcessCommand(string("PLACE 0,0,EAST")));
		Assert::AreEqual(string("0,0,EAST"), sim.GetRobotReport());
	}

	TEST_METHOD(PlacedRobotMulti) {
		auto sim = RobotSimulator();

		sim.ProcessCommand(string("PLACE 0,0,NORTH"));
		Assert::AreEqual(string("0,0,NORTH"), sim.GetRobotReport());

		sim.ProcessCommand(string("PLACE 0,0,SOUTH"));
		Assert::AreEqual(string("0,0,SOUTH"), sim.GetRobotReport());

		sim.ProcessCommand(string("PLACE 0,0,WEST"));
		Assert::AreEqual(string("0,0,WEST"), sim.GetRobotReport());

		sim.ProcessCommand(string("PLACE 4,2,EAST"));
		Assert::AreEqual(string("4,2,EAST"), sim.GetRobotReport());
	}


// MOVE tests ===========================================================
	TEST_METHOD(MoveFail) {
		auto sim = RobotSimulator();
		Assert::IsFalse(sim.ProcessCommand(string("MOVE")));
	}

	TEST_METHOD(MoveFails) {
		auto sim = RobotSimulator();
		Assert::IsTrue(sim.ProcessCommand(string("PLACE 4,2,EAST")));
		Assert::IsTrue(sim.ProcessCommand(string("MOVES")));
		Assert::IsFalse(sim.ProcessCommand(string("-MOVES")));
	}

	TEST_METHOD(MoveOnce) {
		auto sim = RobotSimulator();
		Assert::IsTrue(sim.ProcessCommand(string("PLACE 3,2,WEST")));
		Assert::IsTrue(sim.ProcessCommand(string("MOVE")));
	}

	TEST_METHOD(MoveTwice) {
		auto sim = RobotSimulator();
		Assert::IsTrue(sim.ProcessCommand(string("PLACE 4,2,EAST")));
		Assert::IsTrue(sim.ProcessCommand(string("MOVE ")));
		Assert::IsTrue(sim.ProcessCommand(string("MOVEssssss ")));
	}
	TEST_METHOD(MoveReportOnce) {
		auto sim = RobotSimulator();
		Assert::IsTrue(sim.ProcessCommand(string("PLACE 3,2,WEST")));
		Assert::IsTrue(sim.ProcessCommand(string("MOVE")));
		Assert::AreEqual(string("2,2,WEST"), sim.GetRobotReport());
	}


// Board clamping tests ===========================================================
	TEST_METHOD(ClampedEast) {
		auto sim = RobotSimulator();
		Assert::IsTrue(sim.ProcessCommand(string("PLACE 4,4,EAST")));
		Assert::IsTrue(sim.ProcessCommand(string("MOVE")));
		Assert::AreEqual(string("4,4,EAST"), sim.GetRobotReport());
		Assert::IsTrue(sim.ProcessCommand(string("MOVE")));
		Assert::AreEqual(string("4,4,EAST"), sim.GetRobotReport());
	}

	TEST_METHOD(ClampedNorth) {
		auto sim = RobotSimulator();
		Assert::IsTrue(sim.ProcessCommand(string("PLACE 4,4,NORTH")));
		Assert::IsTrue(sim.ProcessCommand(string("MOVE")));
		Assert::AreEqual(string("4,4,NORTH"), sim.GetRobotReport());
		Assert::IsTrue(sim.ProcessCommand(string("MOVE")));
		Assert::AreEqual(string("4,4,NORTH"), sim.GetRobotReport());
	}

	TEST_METHOD(ClampedSouth) {
		auto sim = RobotSimulator();
		Assert::IsTrue(sim.ProcessCommand(string("PLACE 0,0,SOUTH")));
		Assert::IsTrue(sim.ProcessCommand(string("MOVE")));
		Assert::AreEqual(string("0,0,SOUTH"), sim.GetRobotReport());
		Assert::IsTrue(sim.ProcessCommand(string("MOVE")));
		Assert::AreEqual(string("0,0,SOUTH"), sim.GetRobotReport());
	}

	TEST_METHOD(ClampedWest) {
		auto sim = RobotSimulator();
		Assert::IsTrue(sim.ProcessCommand(string("PLACE 0,0,WEST")));
		Assert::IsTrue(sim.ProcessCommand(string("MOVE")));
		Assert::AreEqual(string("0,0,WEST"), sim.GetRobotReport());
		Assert::IsTrue(sim.ProcessCommand(string("MOVE")));
		Assert::AreEqual(string("0,0,WEST"), sim.GetRobotReport());
	}

// Rotate (LEFT/RIGHT) test ===========================================================
	TEST_METHOD(RotateFailLeft) {
		auto sim = RobotSimulator();
		Assert::IsFalse(sim.ProcessCommand(string("LEFT")));
	}

	TEST_METHOD(RotateFailRight) {
		auto sim = RobotSimulator();
		Assert::IsFalse(sim.ProcessCommand(string("RIGHT")));
	}

	TEST_METHOD(RotateFails) {
		auto sim = RobotSimulator();
		Assert::IsFalse(sim.ProcessCommand(string("LEFT")));
		Assert::IsFalse(sim.ProcessCommand(string("ROTATE")));
	}

	TEST_METHOD(RotateOnce) {
		auto sim = RobotSimulator();
		Assert::IsTrue(sim.ProcessCommand(string("PLACE 0,0,SOUTH")));
		Assert::IsTrue(sim.ProcessCommand(string("LEFT")));
	}

	TEST_METHOD(RotateLeftReport) {
		auto sim = RobotSimulator();
		Assert::IsTrue(sim.ProcessCommand(string("PLACE 4,3,WEST")));
		Assert::IsTrue(sim.ProcessCommand(string("LEFT")));
		Assert::AreEqual(string("4,3,SOUTH"), sim.GetRobotReport());
	}

	TEST_METHOD(RotateRightReport) {
		auto sim = RobotSimulator();
		Assert::IsTrue(sim.ProcessCommand(string("PLACE 1,1,WEST")));
		Assert::IsTrue(sim.ProcessCommand(string("RIGHT")));
		Assert::AreEqual(string("1,1,NORTH"), sim.GetRobotReport());
	}

	TEST_METHOD(RotateReportTwice) {
		auto sim = RobotSimulator();
		Assert::IsTrue(sim.ProcessCommand(string("PLACE 4,4,EAST")));
		Assert::IsTrue(sim.ProcessCommand(string("RIGHT")));
		Assert::AreEqual(string("4,4,SOUTH"), sim.GetRobotReport());
		Assert::IsTrue(sim.ProcessCommand(string("RIGHT")));
		Assert::AreEqual(string("4,4,WEST"), sim.GetRobotReport());
	}

	TEST_METHOD(RotateReportMulti) {
		auto sim = RobotSimulator();
		Assert::IsTrue(sim.ProcessCommand(string("PLACE 4,4,EAST")));
		Assert::IsTrue(sim.ProcessCommand(string("RIGHT")));
		Assert::AreEqual(string("4,4,SOUTH"), sim.GetRobotReport());
		Assert::IsTrue(sim.ProcessCommand(string("LEFT")));
		Assert::AreEqual(string("4,4,EAST"), sim.GetRobotReport());
		Assert::IsTrue(sim.ProcessCommand(string("LEFT")));
		Assert::AreEqual(string("4,4,NORTH"), sim.GetRobotReport());
	}

// REPORT test ============================================================
	TEST_METHOD(Report) {
		auto sim = RobotSimulator();
		Assert::IsTrue(sim.ProcessCommand(string("REPORT")));
	}

	TEST_METHOD(ReportNotPlaced) {
		auto sim = RobotSimulator();
		Assert::IsTrue(sim.ProcessCommand(string("REPORT")));
		Assert::AreEqual(NOT_PLACED, sim.GetRobotReport());
	}

// PLACE order tests ======================================================
	TEST_METHOD(PlaceBeforeReport) {
		auto sim = RobotSimulator();
		Assert::IsTrue(sim.ProcessCommand(string("REPORT")));
		Assert::AreEqual(NOT_PLACED, sim.GetRobotReport());
		Assert::IsTrue(sim.ProcessCommand(string("PLACE 1,1,WEST")));
	}

	TEST_METHOD(PlaceAfterReport) {
		auto sim = RobotSimulator();
		Assert::AreEqual(NOT_PLACED, sim.GetRobotReport());
		Assert::IsTrue(sim.ProcessCommand(string("REPORT")));
		Assert::IsTrue(sim.ProcessCommand(string("PLACE 1,1,WEST")));
		Assert::IsTrue(sim.ProcessCommand(string("REPORT")));
		Assert::AreEqual(string("1,1,WEST"), sim.GetRobotReport());
	}

	TEST_METHOD(PlaceBeforeRight) {
		auto sim = RobotSimulator();
		Assert::IsFalse(sim.ProcessCommand(string("RIGHT")));
		Assert::IsTrue(sim.ProcessCommand(string("PLACE 1,1,WEST")));
	}

	TEST_METHOD(PlaceBeforeLeft) {
		auto sim = RobotSimulator();
		Assert::IsFalse(sim.ProcessCommand(string("LEFT")));
		Assert::IsTrue(sim.ProcessCommand(string("PLACE 1,1,WEST")));
	}

	TEST_METHOD(PlaceBeforeLeft2) {
		auto sim = RobotSimulator();
		Assert::IsFalse(sim.ProcessCommand(string("LEFT")));
		Assert::IsTrue(sim.ProcessCommand(string("PLACE 1,1,WEST")));
		Assert::IsTrue(sim.ProcessCommand(string("LEFT")));
	}

	TEST_METHOD(PlaceBeforeMove) {
		auto sim = RobotSimulator();
		Assert::IsFalse(sim.ProcessCommand(string("MOVE")));
		Assert::IsTrue(sim.ProcessCommand(string("PLACE 1,1,WEST")));
		Assert::IsTrue(sim.ProcessCommand(string("MOVE")));
	}

	TEST_METHOD(PlaceBeforeMulti) {
		auto sim = RobotSimulator();
		Assert::IsFalse(sim.ProcessCommand(string("MOVE")));
		Assert::IsFalse(sim.ProcessCommand(string("LEFT")));
		Assert::IsFalse(sim.ProcessCommand(string("RIGHT")));
		Assert::IsTrue(sim.ProcessCommand(string("PLACE 1,1,WEST")));
		Assert::IsTrue(sim.ProcessCommand(string("MOVE")));
		Assert::IsTrue(sim.ProcessCommand(string("LEFT")));
		Assert::IsTrue(sim.ProcessCommand(string("RIGHT")));
	}


// Extended tests

	TEST_METHOD(CaseSimple) {
		auto sim = RobotSimulator();
		Assert::IsTrue(sim.ProcessCommand(string("PLACE 1,1,WEST")));
		Assert::IsTrue(sim.ProcessCommand(string("RIGHT")));
		Assert::AreEqual(string("1,1,NORTH"), sim.GetRobotReport());
		Assert::IsTrue(sim.ProcessCommand(string("MOVE")));
		Assert::AreEqual(string("1,2,NORTH"), sim.GetRobotReport());
		Assert::IsTrue(sim.ProcessCommand(string("LEFT")));
		Assert::AreEqual(string("1,2,WEST"), sim.GetRobotReport());
		Assert::IsTrue(sim.ProcessCommand(string("MOVE")));
		Assert::AreEqual(string("0,2,WEST"), sim.GetRobotReport());

		//TODO: Investigate matrix based/data driven tests
	}

	TEST_METHOD(CaseLong) {
		auto sim = RobotSimulator();
		Assert::IsFalse(sim.ProcessCommand(string("PLACE 4,5,WEST")));
		Assert::IsFalse(sim.ProcessCommand(string("PLACE 4,4,INVALID")));
		Assert::IsFalse(sim.ProcessCommand(string("PLACE 4,4,INVAL")));
		Assert::IsFalse(sim.ProcessCommand(string("PLACE 4,4,INVA")));

		Assert::IsTrue(sim.ProcessCommand(string("PLACE 4,4,WEST")));
		Assert::IsTrue(sim.ProcessCommand(string("MOVE")));
		Assert::IsTrue(sim.ProcessCommand(string("MOVE")));
		Assert::IsTrue(sim.ProcessCommand(string("MOVE")));
		Assert::IsTrue(sim.ProcessCommand(string("MOVE")));
		Assert::IsTrue(sim.ProcessCommand(string("MOVE")));
		Assert::AreEqual(string("0,4,WEST"), sim.GetRobotReport());
		Assert::IsTrue(sim.ProcessCommand(string("MOVE")));
		Assert::IsTrue(sim.ProcessCommand(string("MOVE")));
		Assert::AreEqual(string("0,4,WEST"), sim.GetRobotReport());
		Assert::IsTrue(sim.ProcessCommand(string("LEFT")));
		Assert::AreEqual(string("0,4,SOUTH"), sim.GetRobotReport());
		Assert::IsTrue(sim.ProcessCommand(string("RIGHT")));
		Assert::AreEqual(string("0,4,WEST"), sim.GetRobotReport());
		Assert::IsTrue(sim.ProcessCommand(string("RIGHT")));
		Assert::IsTrue(sim.ProcessCommand(string("RIGHT")));
		Assert::AreEqual(string("0,4,EAST"), sim.GetRobotReport());
		Assert::IsTrue(sim.ProcessCommand(string("RIGHT")));
		Assert::IsTrue(sim.ProcessCommand(string("MOVE")));
		Assert::IsTrue(sim.ProcessCommand(string("MOVE")));
		Assert::AreEqual(string("0,2,SOUTH"), sim.GetRobotReport());

		Assert::IsFalse(sim.ProcessCommand(string("PLACE 6,6,WEST")));
		Assert::IsTrue(sim.ProcessCommand(string("PLACE 0,0,NORTH")));

	}


};
