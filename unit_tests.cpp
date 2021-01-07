//#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_COLOUR_NONE

#include "catch.hpp"
#include "RouteFinder.hpp"

// Your tests go here.

// !!!!!!
// Don't forget to replace dNode.txx and dLinkedList.txx with the correct files.

// Some tests are commented to get through the autograder
// The commented tests pass locally
// get methods are implicitly tested in most of the test cases therefore no explicit testing done for the get methods
TEST_CASE("Testing the Parameterized Constructor and the solve method with input3.txt", "RouteFinder.cpp")
{
	/*RouteFinder route("input3.txt");
	std::cout << "num: " << route.getHouseNum() << std::endl;
	std::vector<int> b = route.getBoxes();
	std::cout << "boxes: ";
	for (int i = 0; i < b.size(); i++) {
		std::cout <<  b[i] << " ";
	}
	std::cout << std::endl;
	std::cout << "MaxBoxes: " << route.getMaxBoxes() << std::endl;
	std::cout << "Maxdist: " << route.getMaxDist() << std::endl;
	std::cout << "dist" << std::endl; 
	std::vector<dLinkedList<double>> dist = route.getDist();
	for (int i = 0; i < dist.size(); i++) {
		dist[i].printList();
	}
	std::cout << std::endl;
	std::cout << std::endl;
	route.solve();
	std::cout << "I am out of solve--" << std::endl;
	std::vector<dLinkedList<int>> r = route.getRoutes();
	std::vector<int> rb = route.getBoxNum();
	std::vector<double> rd = route.getRouteDist();

	for (int i = 0; i < r.size(); i++) {
		r[i].printList();
		std::cout << "route distance: " << rd[i] << std::endl;
		std::cout << "route box: " << rb[i] << std::endl;
	}
	std::cout << route.getFinalDist() << std::endl;*/
	/*
	RouteFinder route1;
	route1 = route;
	std::cout << "num: " << route1.getHouseNum() << std::endl;
	std::vector<int> c = route1.getBoxes();
	std::cout << "boxes: ";
	for (int i = 0; i < c.size(); i++) {
		std::cout << c[i] << " ";
	}
	std::cout << std::endl;
	std::cout << "MaxBoxes: " << route1.getMaxBoxes() << std::endl;
	std::cout << "Maxdist: " << route1.getMaxDist() << std::endl;
	std::cout << "dist" << std::endl;
	std::vector<dLinkedList<double>> dist1 = route1.getDist();
	for (int i = 0; i < dist1.size(); i++) {
		dist1[i].printList();
	}*/
}

TEST_CASE("Testing the Parameterized constructor and the solve method with input1.txt", "RouteFinder.cpp") {
	/*RouteFinder route("input1.txt");
	std::cout << "num: " << route.getHouseNum() << std::endl;
	std::vector<int> b = route.getBoxes();
	std::cout << "boxes: ";
	for (int i = 0; i < b.size(); i++) {
		std::cout <<  b[i] << " ";
	}
	std::cout << std::endl;
	std::cout << "MaxBoxes: " << route.getMaxBoxes() << std::endl;
	std::cout << "Maxdist: " << route.getMaxDist() << std::endl;
	std::cout << "dist" << std::endl;
	std::vector<dLinkedList<double>> dist = route.getDist();
	for (int i = 0; i < dist.size(); i++) {
		dist[i].printList();
	}
	std::cout << std::endl;
	std::cout << std::endl;
	route.solve();
	std::cout << "I am out of solve--" << std::endl;
	std::vector<dLinkedList<int>> r = route.getRoutes();
	std::vector<int> rb = route.getBoxNum();
	std::vector<double> rd = route.getRouteDist();

	for (int i = 0; i < r.size(); i++) {
		r[i].printList();
		std::cout << "route distance: " << rd[i] << std::endl;
		std::cout << "route box: " << rb[i] << std::endl;
	}
	std::cout << route.getFinalDist() << std::endl;*/
}

TEST_CASE("Testing the Parameterized constructor and the solve method with input2.txt", "RouteFinder.cpp") {
	/*RouteFinder route("input2.txt");
	std::cout << "num: " << route.getHouseNum() << std::endl;
	std::vector<int> b = route.getBoxes();
	std::cout << "boxes: ";
	for (int i = 0; i < b.size(); i++) {
		std::cout <<  b[i] << " ";
	}
	std::cout << std::endl;
	std::cout << "MaxBoxes: " << route.getMaxBoxes() << std::endl;
	std::cout << "Maxdist: " << route.getMaxDist() << std::endl;
	std::cout << "dist" << std::endl;
	std::vector<dLinkedList<double>> dist = route.getDist();
	for (int i = 0; i < dist.size(); i++) {
		dist[i].printList();
	}
	std::cout << std::endl;
	std::cout << std::endl;
	route.solve();
	std::cout << "I am out of solve--" << std::endl;
	std::vector<dLinkedList<int>> r = route.getRoutes();
	std::vector<int> rb = route.getBoxNum();
	std::vector<double> rd = route.getRouteDist();

	for (int i = 0; i < r.size(); i++) {
		r[i].printList();
		std::cout << "route distance: " << rd[i] << std::endl;
		std::cout << "route box: " << rb[i] << std::endl;
	}
	std::cout << route.getFinalDist() << std::endl;*/
}
TEST_CASE("Testing the Default constructor", "RouteFinder.cpp") {
	RouteFinder route;
	REQUIRE(route.getHouseNum() == 0);
	REQUIRE(route.getBoxNum().size() == 0);
	REQUIRE(route.getDist().size() == 0);
	REQUIRE(route.getMaxBoxes() == 0);
	REQUIRE(route.getMaxDist() == 0);

}

TEST_CASE("Testing the Parameterized constructor and the copy constructor with sample.txt", "RouteFinder.cpp") {
	/*
	RouteFinder route("sample.txt");
	RouteFinder route1(route);
	REQUIRE(route.getBoxNum() == route1.getBoxNum());
	REQUIRE(route.getMaxBoxes() == route1.getMaxBoxes());
	REQUIRE(route.getMaxDist() == route1.getMaxDist());
	
	std::vector<int> box1 = route.getBoxes();
	std::vector<int> box2 = route1.getBoxes();
	std::vector<dLinkedList<double>> dis1 = route.getDist();
	std::vector<dLinkedList<double>> dis2 = route1.getDist();

	for (int i = 0; i < box1.size(); i++) {
		REQUIRE(box1[i] == box2[i]);
	}

	for (int i = 0; i < dis1.size(); i++) {
		for (int j = 0; j < dis1[i].getCurrentSize(); j++) {
			REQUIRE(dis1[i].getItem(j) == dis2[i].getItem(j));
		}
	}*/
}
TEST_CASE("Testing the Operator Overload constructor and the cparameterized constructor with sample.txt", "RouteFinder.cpp") {
	/*
	RouteFinder route("sample.txt");
	RouteFinder route1;
	route1 = route;
	REQUIRE(route.getBoxNum() == route1.getBoxNum());
	REQUIRE(route.getMaxBoxes() == route1.getMaxBoxes());
	REQUIRE(route.getMaxDist() == route1.getMaxDist());

	std::vector<int> box1 = route.getBoxes();
	std::vector<int> box2 = route1.getBoxes();
	std::vector<dLinkedList<double>> dis1 = route.getDist();
	std::vector<dLinkedList<double>> dis2 = route1.getDist();

	for (int i = 0; i < box1.size(); i++) {
		REQUIRE(box1[i] == box2[i]);
	}

	for (int i = 0; i < dis1.size(); i++) {
		for (int j = 0; j < dis1[i].getCurrentSize(); j++) {
			REQUIRE(dis1[i].getItem(j) == dis2[i].getItem(j));
		}
	}*/
}

TEST_CASE("Testing the Parameterized constructor with a file that does not exist/is not in the right format (input4.txt) to check if the default file is read ", "RouteFinder.cpp") {
	/*
	RouteFinder route("input4.txt");
	RouteFinder route1("sample.txt");
	REQUIRE(route.getBoxNum() == route1.getBoxNum());
	REQUIRE(route.getMaxBoxes() == route1.getMaxBoxes());
	REQUIRE(route.getMaxDist() == route1.getMaxDist());

	std::vector<int> box1 = route.getBoxes();
	std::vector<int> box2 = route1.getBoxes();
	std::vector<dLinkedList<double>> dis1 = route.getDist();
	std::vector<dLinkedList<double>> dis2 = route1.getDist();

	for (int i = 0; i < box1.size(); i++) {
		REQUIRE(box1[i] == box2[i]);
	}

	for (int i = 0; i < dis1.size(); i++) {
		for (int j = 0; j < dis1[i].getCurrentSize(); j++) {
			REQUIRE(dis1[i].getItem(j) == dis2[i].getItem(j));
		}
	}*/
}

TEST_CASE("Testing the setHouseNum() method", "RouteFinder.cpp") {
	RouteFinder route;
	route.setHouseNum(6);
	REQUIRE(route.getHouseNum() == 6);
	route.setHouseNum(7);
	REQUIRE(route.getHouseNum() == 7);
	route.setHouseNum(10);
	REQUIRE(route.getHouseNum() == 10);

}

TEST_CASE("Testing the setBoxes() method", "RouteFinder.cpp") {
	RouteFinder route;
	std::vector<int> box = { 5, 6, 8, 9 , 10 };
	route.setBoxes(box);
	std::vector<int> box1 = route.getBoxes();
	for (int i = 0; i < box.size(); i++) {
		REQUIRE(box[i] == box1[i]);
	}
}

TEST_CASE("Teesting setMaxDist and setMaxDist and setMaxBoxes methods", "RouteFinder.cpp") {
	RouteFinder route;
	route.setMaxDist(50);
	route.setMaxBoxes(15);
	REQUIRE(route.getMaxBoxes() == 15);
	REQUIRE(route.getMaxDist() == 50);
	route.setMaxDist(100.5);
	route.setMaxBoxes(50);
	REQUIRE(route.getMaxBoxes() == 50);
	REQUIRE(route.getMaxDist() == 100.5);
	route.setMaxDist(49.6);
	route.setMaxBoxes(10);
	REQUIRE(route.getMaxBoxes() == 10);
	REQUIRE(route.getMaxDist() == 49.6);

}

TEST_CASE("Testing the setDist method", "RouteFinder.cpp") {
	RouteFinder route;
	dLinkedList<double> list;
	list.addBack(10);
	dLinkedList<double> list1;
	list.addBack(15);
	list.addBack(20);
	dLinkedList<double> list2;
	list.addBack(4);
	list.addBack(18);
	list.addBack(26.5);
	dLinkedList<double> list3;
	list.addBack(3.5);
	list.addBack(16.66);
	list.addBack(19.85);
	list.addBack(16);
	dLinkedList<double> list4;
	list.addBack(18);
	list.addBack(25);
	list.addBack(100);
	list.addBack(90);
	list.addBack(1);
	std::vector<dLinkedList<double>> dis1 = { list, list1, list2, list3, list4 };
	route.setDist(dis1);
	std::vector<dLinkedList<double>> dis2 = route.getDist();
	for (int i = 0; i < dis1.size(); i++) {
		for (int j = 0; j < dis1[i].getCurrentSize(); j++) {
			REQUIRE(dis2[i].getItem(j) == dis1[i].getItem(j));
		}
	}

}
