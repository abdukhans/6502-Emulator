#include "pch.h"
#include <iostream>


TEST(GTEST, TEST_GTEST) {
  EXPECT_EQ(2, 3);
  EXPECT_TRUE(true);
}

using namespace std;

int main(int argc, char **argv) {


	testing::InitGoogleTest(&argc,argv);



	const  int res =  RUN_ALL_TESTS();
	
	int x;
	cout << "Type a number: "; // Type a number and press enter
	cin >> x; // Get user input from the keyboard
	cout << "Your number is: " << x;

	return res;





}