#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <climits>
#include <algorithm>
#include <cfloat>
using namespace std;

//function to calculate distance between two points
double calcDistance(vector<double> p1, vector<double> p2)
{
    return sqrt(pow(abs(p1[0] - p2[0]), 2.0) + pow(abs(p1[1] - p2[1]), 2.0));
}

//function for calculating cost of a tour
double calculateCost(vector<vector<double>> tour)
{
    double cost = 0;
    //adding up cost to move through tour in order from the given vector
    for (int i = 0; i < tour.size() - 1; i++)
    {
        cost += calcDistance(tour[i], tour[i + 1]);
    }
    //adding cost to return back to origin from final point
    cost += calcDistance(tour[0], tour[tour.size() - 1]);

    return cost;
}


//function for finding all permuations and calculating cost for valid permuations
void Exhuastive(vector<vector<double>> Points, vector<double> startingPoint)
{
    //double to store the cost of the tour
    double tourCost = DBL_MAX;

    do {
        //if current permutation starts with correct starting point then we calculate the cost of that trip
        if (Points[0][0] == startingPoint[0] && Points[0][1] == startingPoint[1])
        {
            double cost = calculateCost(Points);
            //finding minimum cost trip
            if (cost < tourCost)
            {
                tourCost = cost;
            }
        }
        //if current permutation doesn't start with correct point then we continue and get the next permutation
        else
        {
            continue;
        }
        //next_permuation creates a permuation for a vector in order of least to greatest
    } while (next_permutation(Points.begin(), Points.end()));

    //formatting for output to make it correct
    cout << fixed;
    cout << setprecision(3);
    cout << tourCost;
}

int main() {
    //getting number of points in tsp tour
    int numPoints = 0;
    cin >> numPoints;

    //creating a vector of vector of ints to store points 
    vector<vector<double>> tourPoints;

    //for loop to add points to vector of points
    for (int i = 0; i < numPoints; i++) {
        double x;
        double y;

        cin >> x;
        cin >> y;

        vector<double> point;
        point.push_back(x);
        point.push_back(y);

        tourPoints.push_back(point);
    }

    vector<double> startingPoint;
    startingPoint.push_back(tourPoints[0][0]);
    startingPoint.push_back(tourPoints[0][1]);

    //sorting the points so that next_permutation stl can work correctly
    sort(tourPoints.begin(), tourPoints.end());

    //need to know what starting point is because it's lost from sorting the vector of points
    Exhuastive(tourPoints, startingPoint);
    return 0;
}