#include <iostream>
#include <vector>
#include <string>
#include <string.h>
#include <algorithm>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <list>
#include <ctime>
using namespace std;

struct cities {
	string cityNum;
	double x;
	double y;
};

//1 FUNCTION PROTOTYPES
list<cities> closestNode(list<cities> &locations);
list<cities> getCoords(string FN_coord, string FN_id);
void distcalcline(list<cities> &path, list<cities> &locations);
double calcDist(cities &point1, cities &point2);
void dispList(list<cities> &L);
//22
void dispList(list<cities> &R) {
	list<cities>::iterator itrtr = R.begin();

	while (itrtr != R.end()) {
		cout << itrtr->cityNum << " ";
		++itrtr;
	}
}
//15
list<cities> closestNode(list<cities> &locations) {
	list<cities> path;
	list<cities>::iterator itrtr;
	double currentdist;
	double minDist = 100000;
	string minCityNum = "0";

	//16
	path.push_back(locations.front());

	//17
	for (itrtr = ++locations.begin(); itrtr != locations.end(); ++itrtr) {
		currentdist = calcDist(path.front(), *itrtr);
		//18
		if (currentdist < minDist) {
			minDist = currentdist;
			minCityNum = itrtr->cityNum;
		}
	}
	//19
	itrtr = locations.begin();
	while (itrtr->cityNum != minCityNum) {
		++itrtr;
	}
	path.push_back(*itrtr);
	locations.erase(itrtr);

	// 20
	path.push_back(cities());
	// 21
	path.back().cityNum = "END";
	path.back().x = locations.front().x;
	path.back().y = locations.front().y;
	locations.pop_front();

	return path;
}
//23
list<cities> getCoords(string FN_coord, string FN_id) {
	// Declare variables and objects
	ifstream coord, inid;
	list<cities> cValues;

	string buffer, x, y;

	coord.open(FN_coord);
	inid.open(FN_id);

	if (coord && inid) {


		//24
		for (int i = 0; i < 49; i++) {
			//25
			inid >> buffer;
			coord >> x;
			coord >> y;


			//26
			cValues.push_back(cities());
			cValues.back().cityNum = to_string(i);
			cValues.back().x = atof(x.c_str());
			cValues.back().y = atof(y.c_str());
		}
	}

	coord.close();
	inid.close();

	return cValues;
}


//27

double calcDist(cities &point1, cities &point2) {
	//28
	double x = point2.x - point1.x;
	x *= x;

	double y = point2.y - point1.y;
	y *= y;

	return sqrt(x + y);
}

//7
void distcalcline(list<cities> &path, list<cities> &locations) {
	//8
	double currentdist;
	double minDist = 10000;
	list<cities>::iterator itP, itL;
	double x1, x2, y1, y2;

	//9
	itL = locations.begin();
	string minCityNum = itL->cityNum;
	itP = path.begin();
	string edgeNode = itP->cityNum;

	//10
	for (itP = path.begin(); itP != --path.end(); ++itP) {
		for (itL = locations.begin(); itL != locations.end(); ++itL) {
			//11
			x1 = itP->x;
			y1 = itP->y;
			++itP;
			x2 = itP->x;
			y2 = itP->y;
			--itP;

			//12
			currentdist = abs((x2 - x1)*(y1 - itL->y) - (x1 - itL->x)*(y2 - y1));
			currentdist /= sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1));


			//13
			if (currentdist < minDist) {
				minDist = currentdist;
				minCityNum = itL->cityNum;
				++itP;
				edgeNode = itP->cityNum;
				--itP;
			}
		}
	}



	//14
	itL = locations.begin();
	while (itL->cityNum != minCityNum) {
		++itL;
	}
	itP = path.begin();
	while (itP->cityNum != edgeNode) {
		++itP;
	}
	path.insert(itP, *itL);
	locations.erase(itL);

}


int main(int argc, const char * argv[]) {
	//2
	list<cities> locations48 = getCoords("att48_xy.txt", "att48_s.txt");
	list<cities>::iterator itrtr;
	//3
	list<cities> path48 = closestNode(locations48);
	//4
	cout << "Solution of 48 Cities" << endl;
	cout << "Path: ";
	dispList(path48);
	cout << endl;
	clock_t begin48 = clock();
	while (!locations48.empty()) {
		distcalcline(path48, locations48);

		// Display path
		cout << "Path: ";
		dispList(path48);
		cout << endl;
	}
	clock_t end48 = clock();

	//5
	double duration48 = double(end48 - begin48) / CLOCKS_PER_SEC;
	printf("Insertion time for 48 cities: %f\n", duration48);

	//6
	double distance = 0;
	cities next;
	for (itrtr = path48.begin(); itrtr != --path48.end(); ++itrtr) {
		++itrtr;
		next = *itrtr;
		--itrtr;

		distance += calcDist(*itrtr, next);
	}
	printf("48 cities path distance: %f\n", distance);

	system("pause");
	return 0;
}