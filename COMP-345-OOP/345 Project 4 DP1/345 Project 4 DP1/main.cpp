//
//  main.cpp
//  345 Project 4 DP1
//
//  Created by Guancheng Lai on 2/9/18.
//  Copyright © 2018 Guancheng Lai. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Shape.hpp"
#include "Picture.hpp"
#include "Point.hpp"
#include "Line.hpp"
#include "Rectangle.hpp"
#include "RightTriangle.hpp"
#include "Star.hpp"
#include "Diamond.hpp"
#include "Polygon.hpp"
#include "Circle.hpp"

using std::cout;
using std::cin;
using std::endl;
using std::string;


void storeTheShapes(std::ifstream& ,std::vector<Shape*>&);
void readInPoint(std::ifstream& ,std::vector<Shape*>&);
void readInLine(std::ifstream& ,std::vector<Shape*>&);
void readInRectangle(std::ifstream& ,std::vector<Shape*>&);
void readInRightTriangle(std::ifstream& ,std::vector<Shape*>&);
void readInStar(std::ifstream& ,std::vector<Shape*>&);
void readInDiamond(std::ifstream& ,std::vector<Shape*>&);
void readInPolygon(std::ifstream& ,std::vector<Shape*>&);
void readInCircle(std::ifstream& ,std::vector<Shape*>& );
void writeToBMP(Picture& ,std::string);

int main(int argc, const char * argv[])
{
    Picture& picture1 = Picture::getInstance();

    //Read input file
    std::string fileName;
    cout << "Input File name?" << endl;
    cin >> fileName;
    //std::ifstream fin(fileName + ".txt");
    std::ifstream fin(fileName + ".stb");
    
    /*
    *   Dear Doctor.steil, Xcode cannot open .stb file by using fstream, So I have to use .txt as extension
    */
    
    if(!fin)
    {
        cout << "Fail to open file" << endl;
        exit(0);
    }
    
    std::vector<Shape*> shapes;
    storeTheShapes(fin, shapes);
    
    //Loop thought the list and draw all the shapes
    for(int i = 0; i < shapes.size(); i++)
    {
        shapes[i]->draw();
    }

    writeToBMP(picture1, fileName);
}

void storeTheShapes(std::ifstream& fin, std::vector<Shape*>& shapes)
{
    std::string readShapes;
    fin >> readShapes;
    while(fin)
    {
        if(readShapes == "Point")
        {
            readInPoint(fin, shapes);
        }
        else if(readShapes == "Line")
        {
            readInLine(fin, shapes);
        }
        else if(readShapes == "Rectangle")
        {
            readInRectangle(fin, shapes);
        }
        else if(readShapes == "RightTriangle")
        {
            readInRightTriangle(fin, shapes);
        }
        else if(readShapes == "Star")
        {
            readInStar(fin, shapes);
        }
        else if(readShapes == "Diamond")
        {
            readInDiamond(fin, shapes);
        }
        else if(readShapes == "Polygon")
        {
            readInPolygon(fin, shapes);
        }
        else if(readShapes == "Circle")
        {
            readInCircle(fin, shapes);
        }
        
        fin.ignore();
        fin >> readShapes;
    }
    
}



void readInPoint(std::ifstream& fin, std::vector<Shape*>& shapes)
{
    int red, green, blue;
    fin >> red >> green >> blue;
    RGBTriple RGB_Point(red, green, blue);
    
    int xCoord, yCoord;
    fin >> xCoord >> yCoord;
    coord COORD_Point;
    COORD_Point.x = xCoord;
    COORD_Point.y = yCoord;
    
    Shape* point1 = new Point(COORD_Point, RGB_Point);
    shapes.push_back(point1);
}

void readInLine(std::ifstream& fin, std::vector<Shape*>& shapes)
{
    int red, green, blue;
    fin >> red >> green >> blue;
    RGBTriple RGB_Line(red, green, blue);
    
    int xCoord, yCoord;
    fin >> xCoord >> yCoord;
    coord STARTCOORD_Line;
    STARTCOORD_Line.x = xCoord;
    STARTCOORD_Line.y = yCoord;
    
    fin >> xCoord >> yCoord;
    coord ENDCOORD_Line;
    ENDCOORD_Line.x = xCoord;
    ENDCOORD_Line.y = yCoord;
    
    Shape* line1 = new Line(STARTCOORD_Line,ENDCOORD_Line,RGB_Line);
    shapes.push_back(line1);
}

void readInRectangle(std::ifstream& fin, std::vector<Shape*>& shapes)
{
    int red, green, blue;
    fin >> red >> green >> blue;
    RGBTriple RGB_Rectangle(red, green, blue);
    
    int xCoord, yCoord;
    fin >> xCoord >> yCoord;
    coord STARTCOORD_Rectangle;
    STARTCOORD_Rectangle.x = xCoord;
    STARTCOORD_Rectangle.y = yCoord;
    
    int length, height;
    fin >> length >> height;
    
    Shape* rectangle1 = new Rectangle(STARTCOORD_Rectangle, length, height, RGB_Rectangle);
    shapes.push_back(rectangle1);
}

void readInRightTriangle(std::ifstream& fin, std::vector<Shape*>& shapes)
{
    int red, green, blue;
    fin >> red >> green >> blue;
    RGBTriple RGB_RightTriangle(red, green, blue);
    
    int xCoord, yCoord;
    fin >> xCoord >> yCoord;
    coord STARTCOORD_RightTriangle;
    STARTCOORD_RightTriangle.x = xCoord;
    STARTCOORD_RightTriangle.y = yCoord;
    
    int length, height;
    fin >> length >> height;
    
    Shape* rightTriangle1 = new RightTriangle(STARTCOORD_RightTriangle, length, height, RGB_RightTriangle);
    shapes.push_back(rightTriangle1);
}

void readInStar(std::ifstream& fin, std::vector<Shape*>& shapes)
{
    int red, green, blue;
    fin >> red >> green >> blue;
    RGBTriple RGB_Star(red, green, blue);
    
    int xCoord, yCoord;
    fin >> xCoord >> yCoord;
    coord STARTCOORD_Star;
    STARTCOORD_Star.x = xCoord;
    STARTCOORD_Star.y = yCoord;
    
    double length;
    fin >> length;
    
    Shape* star1 = new Star(STARTCOORD_Star, length, RGB_Star);
    shapes.push_back(star1);
}

void readInDiamond(std::ifstream& fin, std::vector<Shape*>& shapes)
{
    int red, green, blue;
    fin >> red >> green >> blue;
    RGBTriple RGB_Diamond(red, green, blue);
    
    int xCoord, yCoord;
    fin >> xCoord >> yCoord;
    coord STARTCOORD_Diamond;
    STARTCOORD_Diamond.x = xCoord;
    STARTCOORD_Diamond.y = yCoord;
    
    double width, height;
    fin >> width >> height;
    
    Shape* diamond1 = new Diamond(STARTCOORD_Diamond, width, height, RGB_Diamond);
    shapes.push_back(diamond1);
}

void readInPolygon(std::ifstream& fin, std::vector<Shape*>& shapes)
{
    int red, green, blue;
    fin >> red >> green >> blue;
    RGBTriple RGB_Polygon(red, green, blue);
    
    int startCoordinate_X, startCoordinate_Y, endCoordinate_X, endCoordinate_Y;
    fin >> startCoordinate_X >> startCoordinate_Y;
    fin >> endCoordinate_X >> endCoordinate_Y;
    coord STARTCOORD_Polygon, ENDCOORD_Polygon, ORIGINALCOORD_Polygon;
    ORIGINALCOORD_Polygon.x = startCoordinate_X;
    ORIGINALCOORD_Polygon.y = startCoordinate_Y;
    
    Shape* polygon1 = NULL;
    while(fin)
    {
        if(polygon1 == NULL)
        {
            STARTCOORD_Polygon.x = startCoordinate_X;
            STARTCOORD_Polygon.y = startCoordinate_Y;
        }
        ENDCOORD_Polygon.x = endCoordinate_X;
        ENDCOORD_Polygon.y = endCoordinate_Y;
        
        polygon1 = new Polygon(STARTCOORD_Polygon, ENDCOORD_Polygon, RGB_Polygon);
        shapes.push_back(polygon1);
        
        fin >> endCoordinate_X >> endCoordinate_Y;
        STARTCOORD_Polygon.x = ENDCOORD_Polygon.x;
        STARTCOORD_Polygon.y = ENDCOORD_Polygon.y;
    }
    
    //Connect the first dot and the last dot
    polygon1 = new Polygon(ORIGINALCOORD_Polygon, ENDCOORD_Polygon, RGB_Polygon);
    shapes.push_back(polygon1);
}

void readInCircle(std::ifstream& fin, std::vector<Shape*>& shapes)
{
    int red, green, blue;
    fin >> red >> green >> blue;
    RGBTriple RGB_Circle(red, green, blue);
    
    int xCoord, yCoord;
    fin >> xCoord >> yCoord;
    coord STARTCOORD_Circle;
    STARTCOORD_Circle.x = xCoord;
    STARTCOORD_Circle.y = yCoord;
    
    double radius;
    fin >> radius;
    
    Shape* circle1 = new Circle(STARTCOORD_Circle, radius, RGB_Circle);
    shapes.push_back(circle1);
}

void writeToBMP(Picture& picture1, std::string fileName)
{
    fileName += ".bmp";
    const char* fNameInChar = fileName.c_str();
    picture1.WriteToFile(fNameInChar);
}

