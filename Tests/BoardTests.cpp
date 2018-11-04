#include "..\TestFramework\CppUnitTest.h"
#include "..\Source\RobotSimulator.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace RoboSim;

TEST_CLASS(BoardTests)
{
public:

	TEST_METHOD(BoardTestZero) {
		Board b = Board(0, 0);
		Assert::AreEqual(0, b.MAX_HEIGHT);
		Assert::AreEqual(0, b.MAX_WIDTH);
	}

	TEST_METHOD(BoardTest1x1) {
		Board b = Board(1, 1);
		Assert::AreEqual(1, b.MAX_HEIGHT);
		Assert::AreEqual(1, b.MAX_WIDTH);
	}

	TEST_METHOD(BoardTestDefault) {
		Board b = Board(5,5);
		Assert::AreEqual(5, b.MAX_HEIGHT);
		Assert::AreEqual(5, b.MAX_WIDTH);
	}
};
