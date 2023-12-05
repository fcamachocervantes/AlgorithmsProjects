#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <climits>
#include <algorithm>
#include <cfloat>
using namespace std;

int timber(vector<int> segmentValues, int i, int j, vector<vector<vector<int>>>& DPTable) {
    //checking DP Table first
    if (DPTable[i][j][0] != -1) {
        return DPTable[i][j][0];
    }

    //base case 1
    if (i == j) {
        DPTable[i][j][0] = segmentValues[i];
        return segmentValues[i];
    }

    //base case 2
    if (j == (i + 1)) {
        if (segmentValues[i] >= segmentValues[j]) {
            DPTable[i][j][0] = segmentValues[i];
            DPTable[i][j][1] = -2;
            DPTable[i][j][2] = -3;
            return segmentValues[i];
        }
        else {
            DPTable[i][j][0] = segmentValues[j];
            DPTable[i][j][1] = -3;
            DPTable[i][j][2] = -2;
            return segmentValues[j];
        }
    }

    int length = 0;
    int minLeft1;
    int minLeft2;
    int minRight1;
    int minRight2;
    int maxLeft;
    int maxRight;

    //calculating left side for max function
    maxLeft = segmentValues[i];
    //calculating min of left side min function
    minLeft1 = timber(segmentValues, i + 2, j, DPTable);
    minLeft2 = timber(segmentValues, i + 1, j - 1, DPTable);

    //calculating min from first choosing left side
    if (minLeft1 <= minLeft2) {
        maxLeft += minLeft1;
    }
    else {
        maxLeft += minLeft2;
    }

    //calculating right for max function
    maxRight = segmentValues[j];
    //calculating min of right side min function
    minRight1 = timber(segmentValues, i + 1, j - 1, DPTable);
    minRight2 = timber(segmentValues, i, j - 2, DPTable);

    //calculating min from first choosing right side
    if (minRight1 <= minRight2) {
        maxRight += minRight1;
    }
    else {
        maxRight += minRight2;
    }

    //calculating max from either choosing left or right piece
    if (maxLeft >= maxRight) {
        DPTable[i][j][1] = -2;
        length += maxLeft;
        if (minLeft1 <= minLeft2) {
            DPTable[i][j][2] = -2;
        }
        else {
            DPTable[i][j][2] = -3;
        }
    }
    else {
        DPTable[i][j][1] = -3;
        length += maxRight;
        if (minRight1 <= minRight2) {
            DPTable[i][j][2] = -2;
        }
        else {
            DPTable[i][j][2] = -3;
        }
    }

    DPTable[i][j][0] = length;
    return length;
}

int main()
{
    //storage for tree segments and their values
    int treeSegments;
    int segmentValue;
    vector<int> segmentValues;

    //getting user input
    cin >> treeSegments;

    vector<int> traceBack{ -1, -1, -1 };
    vector<vector<vector<int>>> DPTable(treeSegments, vector<vector<int>>(treeSegments, traceBack));

    for (int i = 0; i < treeSegments; i++) {
        cin >> segmentValue;
        segmentValues.push_back(segmentValue);
    }

    for (int i = 0; i < DPTable.size(); i++)
    {
        for (int j = 0; j < DPTable.size(); j++)
        {
            if (j >= i) {
                timber(segmentValues, i, j, DPTable);
            }
        }
    }

    //making recursive call and printing outputs
    int maxValue = DPTable[0][DPTable.size() - 1][0];
    cout << maxValue << endl;

    /*for (int i = 0; i < DPTable.size(); i++) {
        for (int j = 0; j < DPTable.size(); j++) {
            for (int k = 0; k < 3; k++) {
                if (j >= i)
                {
                    int tempK = DPTable[i][j][k];
                    if (tempK > 0) {
                        cout << tempK << ",";
                    }
                    else {
                        if (tempK == -2) {
                            cout << "L" << ",";
                        }
                        else if (tempK == -3) {
                            cout << "R" << ",";
                        }
                        else {
                            cout << "B" << ",";
                        }
                    }
                }
                else
                {
                    cout << "X" << ",";
                }
            }
            cout << "|";
        }
        cout << endl;
    }*/

    int i = 0;
    int j = DPTable.size() - 1;
    while (DPTable[i][j][1] != -1) {
        if (DPTable[i][j][1] == -2) {
            cout << i + 1 << " ";
            i++;
        }
        else {
            cout << j + 1 << " ";
            j--;
        }
    }
    cout << i + 1;
}
