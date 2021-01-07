//
//  RouteFinder.cpp
//  
//

#include "RouteFinder.hpp"
#include <fstream>
#include <string>

// default constructor set everything to default and create an empty problem
RouteFinder::RouteFinder() {
	num = 0;
	maxBoxes = 0;
	maxDist = 0;
	totalDist = 0;
	dist.clear();
	boxes.clear();
	routes.clear();
	routeCost.clear();
	boxNum.clear();
}

// Copy Constructor: given a route finder problem perform a deep copy of the object
RouteFinder::RouteFinder(const RouteFinder& r) {
	num = r.num; // setting the num values
	maxBoxes = r.maxBoxes; // setting the maxBoxes value
	maxDist = r.maxDist; // setting the maxDist value  
	totalDist = r.totalDist; // setting the totalDist value 
	// Copying the dist vector in r
	for (int i = 0; i < r.dist.size(); i++) {
		dLinkedList<double> list(r.dist[i]);
		this->dist.push_back(list);
		list.clear();
	}
	// copying the boxes vector
	for (int i = 0; i < r.boxes.size(); i++) {
		this->boxes.push_back(r.boxes[i]);
	}
	// copying the routes vector 
	for (int i = 0; i < r.routes.size(); i++) {
		dLinkedList<int> list(r.routes[i]);
		this->routes.push_back(list);
		list.clear();
	}
	// copying the routecost vector 
	for (int i = 0; i < r.routeCost.size(); i++) {
		this->routeCost.push_back(r.routeCost[i]);
	}
	// copying the boxNum vector 
	for (int i = 0; i < r.boxNum.size(); i++) {
		this->boxNum.push_back(r.boxNum[i]);
	}
}

// Paramterized constructor: read a file and set the respective fields accordingly
RouteFinder::RouteFinder(const std::string& f) {
	// First open and read the file
	std::ifstream file(f);
	// string object to store everyline in the file 
	std::string stringLine;
	int counter = 0; // setting up the counter 
	int ordnum = 0; // to check if the order of the parameters is correct
	int ordbox = 0; // to check if the order of the parameters is correct
	int ordmbox = 0; // to check if the order of the parameters is correct
	int ordmdist = 0; // to check if the order of the parameters is correct
	int orddist = 0; // to check if the order of the parameters is correct

	if (file.is_open()) { // if the file is open and can be found
		while (getline(file, stringLine)) { // for every line in the file 
			
			int length = stringLine.length(); // get the length of the string in the line 
			int num_boxes;
			//std::cout << "string Subscript out of range 1" << std::endl;
			if (stringLine.substr(0, 3) == "num") { // if the substring is equal to num then:
				ordnum = counter; // let ordnum equal to counter
				num = stoi(stringLine.substr(4, length-1)); // and num should be equal to the rest of the string that is there converted to an int
				//std::cout << "string Subscript out of range 2" << std::endl;
			}
			else if (stringLine.substr(0, 5) == "boxes") { // if the subsrtring is equal to boxes then:
				ordbox = counter; // let ordbox equal to counter
				std::string token = ""; // empty token

				for (int i = 5; i < length; i++) { // run a for loop for the length of the string 
	
					if (!isblank(stringLine[i])) { // if the string is not blank
						token = token + stringLine[i]; // append the token with the the next character in the string 
					}
					else if (isblank(stringLine[i]) && token != "") { // else if we hit a blank then 
						num_boxes = stoi(token); // set numboxes to stoi(token)
						boxes.push_back(num_boxes); // pushback num_boxes to boxes
						token = ""; // set token to a blank string 
					}
				}
				boxes.push_back(stoi(token));
			}
			else if (stringLine.substr(0, 6) == "mboxes") { // if the substring is equal to "mboxes"
				ordmbox = counter; // let ordmbox equalt to counter
				//std::cout << "string Subscript out of range 4" << std::endl;
				maxBoxes = stoi(stringLine.substr(7, length - 1)); // set maxboxes equal to stoi( the rest of the string)
			}
			else if (stringLine.substr(0, 5) == "mdist") { // if the substring is equal to "mdist"
				ordmdist = counter;// let ordmdist equalt to counter
				//std::cout << "string Subscript out of range 5" << std::endl;
				maxDist = stoi(stringLine.substr(6, length - 1)); // set maxDist equal to stoi(the rest of the string)
			}
			else if (stringLine.substr(0, 4) == "dist") { // if the substring is equal to "dist"
				orddist = counter; // set orddist equal to the counter
				if (orddist == 4) { // if the order is correct only then do this 
					while (getline(file, stringLine)) { // run another while loop for the rest of the lines 
						//std::cout << "string Subscript out of range 6" << std::endl;
						dLinkedList<double> list; // instantiating a linkedlist
						std::string token = ""; // setting token 
						length = stringLine.length(); // storing the length of the string 
						double distance = 0; // distance = 0
						//std::cout << counter << std::endl;
						for (int i = 0; i < length; i++) { // for the entire length of the string 
							if (!isblank(stringLine[i])) { // if the string is not blank
								//std::cout << "6-- in if statement " << std::endl;
								token = token + stringLine[i]; // then append token
							}
							else if (isblank(stringLine[i]) && token != "") { // if we hit a blank then =
								distance = stod(token); // distance is set to stod(token)
								list.addBack(distance); // distance added to the list 
								token = "";
							}
						}
						list.addBack(stod(token)); 
						dist.push_back(list); // the list id pushed pack after the entire line is read
						list.clear(); // the list is then cleared 
					}
				}
			}
			counter++;
		}
	}
	else { // if the file is not found then the same implimentation as above but with the default "sample.txt" file and not the input f file
		std::cout << "true" << std::endl;
		std::ifstream stdfile("sample.txt");
		while (getline(stdfile, stringLine)) {

			int length = stringLine.length();
			int num_boxes;
			//std::cout << "string Subscript out of range 1" << std::endl;
			if (stringLine.substr(0, 3) == "num") {
				num = stoi(stringLine.substr(4, length - 1));
				//std::cout << "string Subscript out of range 2" << std::endl;
			}
			else if (stringLine.substr(0, 5) == "boxes") {
				std::string token = "";

				for (int i = 5; i < length; i++) {

					if (!isblank(stringLine[i])) {
						token = token + stringLine[i];
					}
					else if (isblank(stringLine[i]) && token != "") {
						num_boxes = stoi(token);
						boxes.push_back(num_boxes);
						token = "";
					}
				}
				boxes.push_back(stoi(token));
			}
			else if (stringLine.substr(0, 6) == "mboxes") {
				//std::cout << "string Subscript out of range 4" << std::endl;
				maxBoxes = stoi(stringLine.substr(7, length - 1));
			}
			else if (stringLine.substr(0, 5) == "mdist") {
				//std::cout << "string Subscript out of range 5" << std::endl;
				maxDist = stoi(stringLine.substr(6, length - 1));
			}
			else if (stringLine.substr(0, 4) == "dist") {
				while (getline(stdfile, stringLine)) {
					//std::cout << "string Subscript out of range 6" << std::endl;
					dLinkedList<double> list;
					std::string token = "";
					length = stringLine.length();
					double distance = 0;
					//std::cout << counter << std::endl;
					for (int i = 0; i < length; i++) {
						if (!isblank(stringLine[i])) {
							//std::cout << "6-- in if statement " << std::endl;
							token = token + stringLine[i];
						}
						else if (isblank(stringLine[i]) && token != "") {
							distance = stod(token);
							list.addBack(distance);
							token = "";
						}
					}
					list.addBack(stod(token));
					dist.push_back(list);
					list.clear();
				}
			}
		}
	} // if the order of the data fields in the file is wrong then read the sample file again
	if (ordnum != 0 || ordbox != 1 || ordmbox != 2 || ordmdist != 3 || orddist != 4) {
		boxes.clear();
		dist.clear();
		std::cout << "true1" << std::endl;
		std::ifstream stdfile("sample.txt");
		while (getline(stdfile, stringLine)) {

			int length = stringLine.length();
			int num_boxes;
			//std::cout << "string Subscript out of range 1" << std::endl;
			if (stringLine.substr(0, 3) == "num") {
				num = stoi(stringLine.substr(4, length - 1));
				//std::cout << "string Subscript out of range 2" << std::endl;
			}
			else if (stringLine.substr(0, 5) == "boxes") {
				std::string token = "";

				for (int i = 5; i < length; i++) {

					if (!isblank(stringLine[i])) {
						token = token + stringLine[i];
					}
					else if (isblank(stringLine[i]) && token != "") {
						num_boxes = stoi(token);
						boxes.push_back(num_boxes);
						token = "";
					}
				}
				boxes.push_back(stoi(token));
			}
			else if (stringLine.substr(0, 6) == "mboxes") {
				//std::cout << "string Subscript out of range 4" << std::endl;
				maxBoxes = stoi(stringLine.substr(7, length - 1));
			}
			else if (stringLine.substr(0, 5) == "mdist") {
				//std::cout << "string Subscript out of range 5" << std::endl;
				maxDist = stoi(stringLine.substr(6, length - 1));
			}
			else if (stringLine.substr(0, 4) == "dist") {
				while (getline(stdfile, stringLine)) {
					//std::cout << "string Subscript out of range 6" << std::endl;
					dLinkedList<double> list;
					std::string token = "";
					length = stringLine.length();
					double distance = 0;
					//std::cout << counter << std::endl;
					for (int i = 0; i < length; i++) {
						if (!isblank(stringLine[i])) {
							//std::cout << "6-- in if statement " << std::endl;
							token = token + stringLine[i];
						}
						else if (isblank(stringLine[i]) && token != "") {
							distance = stod(token);
							list.addBack(distance);
							token = "";
						}
					}
					list.addBack(stod(token));
					dist.push_back(list);
					list.clear();
				}
			}
		}
	}
	
}

// Operator constructor 
RouteFinder &RouteFinder::operator=(RouteFinder x) {
	
	std::swap(this->num, x.num); // swapping num with x.num
	std::swap(this->maxBoxes, x.maxBoxes); // swapping maxboxes with x.maxboxes
	std::swap(this->maxDist, x.maxDist); // swapping maxDist with x.maxDist
	std::swap(this->totalDist, x.totalDist); // swapping totalDist with x.totalDist
	std::swap(this->dist, x.dist); // swapping dist with x.dist
	std::swap(this->boxes, x.boxes); // swapping boxes with x.boxes
	std::swap(this->routes, x.routes); // swapping routes with x.routes
	std::swap(this->routeCost, x.routeCost); // swapping routeCost with x.routeCost
	std::swap(this->boxNum, x.boxNum); // swapping boxNum with x.boxNum
	
	return *this; // return *this 
}

int RouteFinder::getHouseNum() const {
	return num; // returns the number of houses
}

std::vector<dLinkedList<double>> RouteFinder::getDist() const {
	return dist; // returns the dist vector 
}

std::vector<int> RouteFinder::getBoxes() const {
	return boxes; // returns the vector boxes
}

int RouteFinder::getMaxBoxes() const {
	return maxBoxes; // returns the maximum number of boxes a truck can travel
}

double RouteFinder::getMaxDist() const {
	return maxDist; // returns the Maximum distance a truck can travel
}

void RouteFinder::setHouseNum(int n) {
	this->num = n; // sets the number of houses
}

void RouteFinder::setDist(std::vector< dLinkedList<double> > d) {
	// setting the distance vector 
	for (int i = 0; i < d.size(); i++) {
		dLinkedList<double> list(d[i]);
		this->dist.push_back(list);
		list.clear();
	}
}

void RouteFinder::setBoxes(std::vector<int> b) {
	// setting the boxes vector 
	for (int i = 0; i < b.size(); i++) {
		this->boxes.push_back(b[i]);
	}
}

void RouteFinder::setMaxBoxes(int m) {
	// setting the maximum number of boxes a truck can carry
	this->maxBoxes = m;
}

void RouteFinder::setMaxDist(double d) {
	//setting the maximum amount of distance a single truck can travel
	this->maxDist = d;
}

void RouteFinder::solve() {

	
	totalDist = 0;
	// if the size of the boxes vector is not equal to the number of houses then throw an exception 
	if (boxes.size() != num) {
		// throw exception 
		throw std::logic_error("Problem instance is invalid");
	}
	else { // else
		std::vector<dLinkedList<int>> routelist; // a vector to hold the tentative routelList while finding the optimal routes
		std::vector<double> routed; // a vector to hold the distance that a truck travels in each route
		std::vector<bool> visited(num, false); // a boolean vector to check if a given house is visited or not it is initialised with all houses as not visited
		std::vector<int> box_num; // a vector to hold the number of boxes a truck carries in each possible route 

		int currbox = 0; // the current number of boxes
		int possbox = 0; // possible number of boxes
		double traveleddist = 0; // the amount of distance traveled
		double possdist = 0; // possible distance traveled 
		
		

		for (int i = 1; i < num+1; i++) { // i starts with 1 and goes upto num+1 to cover all the houses (rows)
			double min_dist = maxDist; // min_dist a route can have is the maximum distance a truck can travel 
			std::vector<double> disti_j; // vector to store the distance between house i and j
			std::vector<double> truedisti_j; // vector to store the distance between house i and j such that the house is yet to be visited and if the house is visited all the constraints on the truck are followed
			std::vector<int> truehouse_num; // Vector to store the house number we can travel to given the constraints  
			std::vector<int> house_num; // vector to store all the house numbers 
			if (!visited[i - 1]) { // if the given house is not yet visited 
				int houseindex = 0; // start with houseindex = 0
				bool found = false; // boolean variable to check if a compatible house was found
				traveleddist = dist[i - 1].getItem(0); // getting the distance from the warehouse to the currenthouse we are at 
				currbox = boxes[i - 1]; // getting the box demand for the current house 
				dLinkedList<int> currroute; // a list to hold te house numbers in the route 
				currroute.addBack(0); // add the warehouse
				currroute.addBack(i); // and add the current house we are at 
				visited[i - 1] = true; // set the visited value for the current house to "true"
				//std::cout << "Debugging 1 -- " << std::endl;
				// the two for loops shown get the distances of all the houses from the the current 
				// house that we are at and store it into the disti_j vector

				// the two for loops shown below gets all the house numbers and 
				// stores it into the house_num vector in the same order as that of the distances from these houses are stored 
				// in disti_j

				//std::cout << "Debugging 4 -- " << std::endl;
				for (int k = 1; k < i; k++) {
					house_num.push_back(k);
				}
				int counter = 0;
				//std::cout << "Debugging 5 -- " << std::endl;
				for (int k = i + 1; k < num + 1; k++) {
					//std::cout << "counter :: " << k << std::endl;
					house_num.push_back(k);
				}


				for (int k = 1; k < i; k++) {
					disti_j.push_back(dist[i - 1].getItem(k));
					//std::cout << "I ran" << std::endl;
				}
				//std::cout << "Debugging 3 -- " << std::endl;
				for (int k = i; k < num; k++) {
					//std::cout << "counter 1 :: " << k << std::endl;
					disti_j.push_back(dist[k].getItem(i));
				}


				//std::cout << "Debugging 6 -- " << std::endl;
				//std::cout << "Disti_j size: " << disti_j.size() << std::endl;
				//std::cout << "house_num size: " << house_num.size() << std::endl;
					
				// This for loop is to find all the possible houses that we can go to given the constraints
				// of maxBoxes a truack can carry
				// maxDist a truck can travel
				// and such that we do not visit a house again which was visited in on e of the previous routes
				// and push those distance and the house numbers to turedisti_j and truehouse_num
				for (int k = 0; k < disti_j.size(); k++) {

					possdist = traveleddist + disti_j[k] + dist[house_num[k] - 1].getItem(0); // get the possible distance that we will travel 
					// i.e if we were to visit this house then what would the distance traveled

					possbox = boxes[house_num[k] - 1] + currbox; // the possible number of boxes
					// i.e if we were to visit this house then what is the possible number of boxes we can carry
					//std::cout << "Debugging 8 -- " << std::endl;
					if (possdist <= maxDist && possbox <= maxBoxes && !visited[house_num[k] - 1]) {
						//std::cout << "In the if condition " << std::endl;
						truedisti_j.push_back(disti_j[k]);
						truehouse_num.push_back(house_num[k]);	
					}
				}
				//std::cout << "Debugging 7 -- " << std::endl;
					
				// now out of all the houses we can go to which is one is the closest if such a house is found then
				// we go to it (given it has not been visited check in the previous loop)
				for (int k = 0; k < truedisti_j.size(); k++) {
					std::cout << "house_index : " << houseindex << std::endl;
					if (truedisti_j[k] <= min_dist) {

						min_dist = truedisti_j[k]; // update min_dist in every loop to find the closest house 
						houseindex = k; // we get the index of the house
						found = true; // found is set to true

					}
						
					std::cout << "found: " << found << std::endl;
					std::cout << "house_index: " << houseindex << std::endl;
				}
				//std::cout << "Debugging 2 -- " << std::endl;
					
				std::cout << found << std::endl;
				int next_house;
				//std::cout << "Next_house " << next_house << std::endl;
				if (found) { // if found is true we go to this house and repeat the process to check if there is another house that we can visit
					traveleddist = traveleddist + min_dist; // update the traveled distance
					next_house = truehouse_num[houseindex]; // get the house number 
					std::cout << "Next house: " << next_house << std::endl;
					//std::cout << "Next_house " << next_house << std::endl;
					currbox = currbox + boxes[next_house - 1]; // update teh total number of boxes we are carrying
					visited[next_house - 1] = true;
					currroute.addBack(next_house);
					
				}
				while (found) { // repeat the same process until all such houses are found and added to the list
					houseindex = 0;
					disti_j.clear();
					truedisti_j.clear();
					house_num.clear();
					truehouse_num.clear();
					found = false;


					//std::cout << "Debugging 4 -- " << std::endl;
					for (int k = 1; k < next_house; k++) {
						house_num.push_back(k);
					}
					int counter = 0;
					//std::cout << "Debugging 5 -- " << std::endl;
					for (int k = next_house + 1; k < num + 1; k++) {
						//std::cout << "counter :: " << k << std::endl;
						house_num.push_back(k);
					}

					for (int k = 1; k < next_house; k++) {
						disti_j.push_back(dist[next_house - 1].getItem(k));
						//std::cout << "I ran" << std::endl;
					}
					//std::cout << "Debugging 3 -- " << std::endl;
					for (int k = next_house; k < num; k++) {
						//std::cout << "counter 1 :: " << k << std::endl;
						disti_j.push_back(dist[k].getItem(next_house));
					}

					//std::cout << "Debugging 6 -- " << std::endl;
					//std::cout << "Disti_j size: " << disti_j.size() << std::endl;
					//std::cout << "house_num size: " << house_num.size() << std::endl;
					for (int k = 0; k < disti_j.size(); k++) {

						possdist = traveleddist + disti_j[k] + dist[house_num[k] - 1].getItem(0);
						possbox = boxes[house_num[k] - 1] + currbox;
						//std::cout << "Debugging 8 -- " << std::endl;
						if (possdist <= maxDist && possbox <= maxBoxes && !visited[house_num[k] - 1]) {
							//std::cout << "In the if condition " << std::endl;
							truedisti_j.push_back(disti_j[k]);
							truehouse_num.push_back(house_num[k]);
						}
					}
					min_dist = maxDist;
					//std::cout << "Debugging 7 -- " << std::endl;
					for (int k = 0; k < truedisti_j.size(); k++) {

						if (truedisti_j[k] <= min_dist) {

							min_dist = truedisti_j[k];
							houseindex = k;
							found = true;

						}
							
					}
						//std::cout << "Debugging 2 -- " << std::endl;
						//std::cout << "house_index: " << houseindex << std::endl;
						
						//std::cout << "Next_house " << next_house << std::endl;
					if (found) {
						
						next_house = truehouse_num[houseindex];
						traveleddist = traveleddist + min_dist;
						//std::cout << "size " << truehouse_num.size() << std::endl;
						
						//std::cout << "Next_house 1: " << next_house << std::endl;
						//std::cout << "Failing here ?" << std::endl;
						currbox = currbox + boxes[next_house - 1];
						visited[next_house - 1] = true;
						currroute.addBack(next_house);
						
					}
				}
				// if found is false then we go back to the warehouse and update the fields are update accordingly
				traveleddist += dist[currroute.getItem(currroute.getCurrentSize() - 1) - 1].getItem(0);

				routed.push_back(traveleddist);

				currroute.addBack(0);

				box_num.push_back(currbox);

				routelist.push_back(currroute);



			}
		}
		// Once we have been through all the routes we update our data fields
		for (int i = 0; i < routelist.size(); i++) {

			
			routes.push_back(routelist[i]);
			routeCost.push_back(routed[i]);
			boxNum.push_back(box_num[i]);
			totalDist += routed[i];

			

		}

	}

}

std::vector<dLinkedList<int>> RouteFinder::getRoutes() const {
	return routes; // return the vector routes
}

std::vector<double> RouteFinder::getRouteDist() const {
	return routeCost; // return the vector routeCost
}

std::vector<int> RouteFinder::getBoxNum() const {
	return boxNum; // return the vector BoxNum
}

double RouteFinder::getFinalDist() const {
	return totalDist; // return totalDist 
}