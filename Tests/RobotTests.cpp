#include "..\TestFramework\CppUnitTest.h"
#include "..\Source\RobotSimulator.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace RoboSim;

namespace RobotTest {
	TEST_CLASS(RobotTests)
	{
	public:
		TEST_METHOD(RobotNotPlaced) {
			Robot robot = Robot();
			Assert::AreEqual(false, robot.IsPlaced);
		}

		TEST_METHOD(RobotInvalid) {
			Robot robot = Robot();
			Assert::AreEqual(INVALID_POSITION, robot.X);
			Assert::AreEqual(INVALID_POSITION, robot.Y);
			Assert::AreEqual((int) FACE::INVALID, (int) robot.Face);
		}
	};

}