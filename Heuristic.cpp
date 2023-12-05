#include <iostream>
#include <iomanip>
#include <vector>
#include <climits>
#include <cmath>
using namespace std;

//struct to store points
struct point {
    double x;
    double y;
};

//function to calculate distance between two points
double calcDistance(struct point p1, struct point p2)
{
    return sqrt(pow(abs(p1.x - p2.x), 2.0) + pow(abs(p1.y - p2.y), 2.0));
}

//function to find closest point from current location
struct point findMinDistance(struct point currentPoint ,vector<point>& Points)
{
    //minDistance to find closest point
    double minDistance = INT_MAX;
    
    //index of closest point so it can be erased from vector later
    int indexOfMin = 0;

    //point to store closest point coordinates
    struct point closestPoint = { 0,0 };

    //finding nearest neighbor
    for (int i = 0; i < Points.size(); i++)
    {
        if (calcDistance(currentPoint, Points[i]) < minDistance)
        {
            minDistance = calcDistance(currentPoint, Points[i]);
            closestPoint = Points[i];
            indexOfMin = i;
        }
    }

    //erasing nearest neighbor from vector so we don't visit it again
    Points.erase(Points.begin() + indexOfMin);

    //returing what the nearest neighbor was
    return closestPoint;
}

//function for finding nearest neighbor, and calculating cost as well as printing the cost
void NearestNeighbor(vector<point> Points)
{
    //double to store the cost of the tour
    double tourCost = 0;

    //vector for storing tour
    vector<point> TSPTour;

    //adding starting point to tsp tour and removing it from vector
    TSPTour.push_back(Points[0]); 
    struct point currentPoint = Points[0];
    Points.erase(Points.begin() + 0);

    //using our current location finding nearest neighbor saving neighbor to tsp tour, and removing it from vector, and setting current point to nearest neighbor
    while (!Points.empty())
    {
        struct point closestPoint = findMinDistance(currentPoint, Points);
        TSPTour.push_back(closestPoint);
        currentPoint = closestPoint;
    }

    //calculating cost of tour by going back through the vector of points in their order of the tour
    for (int i = 0; i < TSPTour.size() - 1; i++)
    {
        tourCost += calcDistance(TSPTour[i], TSPTour[i + 1]);
    }
    //adding cost of going from final point back to beginning of tour
    tourCost += calcDistance(TSPTour[0], TSPTour[TSPTour.size() - 1]);

    //formatting for output to make it correct
    cout << fixed;
    cout << setprecision(3);
    cout << tourCost;
}

int main() {
    //getting number of points in tsp tour
    int numPoints = 0;
    cin >> numPoints;

    //creating a vector to store points 
    vector<point> tourPoints;

    //for loop to add points to vector of points
    for (int i = 0; i < numPoints; i++) {
        double x;
        double y;

        cin >> x;
        cin >> y;

        struct point p = { x, y };

        tourPoints.push_back(p);
    }

    NearestNeighbor(tourPoints);
    return 0;
}
