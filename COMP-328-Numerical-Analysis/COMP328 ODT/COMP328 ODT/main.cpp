
/* naturalSpline.cpp
 This program reads in a set of (x,y) coordinates from a input text file.
 It then finds the natural cubic spline that passes through each of those
 points and prompts the user for an x-value at which it will calculate
 the interpolated y-value.
 
 REQUIRED:  This program relies on the spline.h header file to provide
 the needed logic to implement a natural cubic spline.
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "spline.h"
using namespace std;

void displayPoints( int numPoints, vector<double> x, vector<double> y)
{
    cout << endl;
    cout << "(x,y) points read from input file:" << endl;
    for (int row=0; row<numPoints; row++) {
        cout << row << ":  (" << x[row] << ", " << y[row] << ")" << endl;
    }
    cout << endl;
}

int main(int argc, char *argv[])
{
    string filename;
    if (argc > 1) {        // In case the user specified the filename
        string tmp (argv[1]);    // on the command line
        filename = tmp;
    }
    else {                      // If not, ask for the name now.
        cout << "Filename? ";
        cin  >> filename;
    }
    ifstream fin (filename.c_str());    // Attempt to open the text file
    if (fin.is_open()) {
        int numPoints;
        fin >> numPoints;
        if (numPoints < 2) {
            cout << "Must have at least 3 points." << endl;
            return 0;
        }
        vector<double> x(numPoints);    // Create x & y vectors
        vector<double> y(numPoints);    // of sufficient size
        for (int row=0; row < numPoints; row++) {
            fin >> x[row] >> y[row];
        }
        tk::spline s;            // Create the natural cubic spline
        s.set_points(x,y);
        
        char response;
        do {
            displayPoints(numPoints, x, y);
            double z;
            cout << "Interpolate the spline value at which x-value? ";
            cin  >> z;
            
            cout << "Spline at " << z << " is " << s(z) << std::endl;
            cout << std::endl;
            
            cout << "Finished [y|n]? ";
            cin  >> response;
        } while (response != 'y' && response != 'Y');
    }
}
