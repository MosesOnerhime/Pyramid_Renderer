#include "pyramid.h"
#include "Renderer3D.h"
#include <iostream>
#include <vector>
#include <SDL.h>
#include <cmath>

// Creates an array of points for a pyramid
std::vector<Point3D> points{
    Point3D{0, 0, 1},    // Apex
    Point3D{-1, -1, -1}, // Base vertex 1
    Point3D{1, -1, -1},  // Base vertex 2
    Point3D{1, 1, -1},   // Base vertex 3
    Point3D{-1, 1, -1}   // Base vertex 4
};

// Creates an array of edges for a pyramid (This holds indices referencing the points array)
std::vector<Edge> edges{
    Edge{0, 1}, // Edge from apex to base vertex 1
    Edge{0, 2}, // Edge from apex to base vertex 2
    Edge{0, 3}, // Edge from apex to base vertex 3
    Edge{0, 4}, // Edge from apex to base vertex 4
    Edge{1, 2}, // Edge connecting base vertex 1 to base vertex 2
    Edge{2, 3}, // Edge connecting base vertex 2 to base vertex 3
    Edge{3, 4}, // Edge connecting base vertex 3 to base vertex 4
    Edge{4, 1}  // Edge connecting base vertex 4 to base vertex 1
};

// Function to rotate a point around the Z axis
void rotatePointZ(Point3D& point, double angle) {
    double x = point.x;
    double y = point.y;
    point.x = x * cos(angle) - y * sin(angle);
    point.y = x * sin(angle) + y * cos(angle);
}

// Function to rotate the entire pyramid around the Z axis
void rotatePyramidZ(std::vector<Point3D>& points, double angle) {
    for (Point3D& point : points) {
        rotatePointZ(point, angle);
    }
}

//default C++ function
int main(int argc, char* argv[])
{
    //creating a window and a renderer
    SDL_Window* window;
    SDL_Renderer* renderer;

    //creates a centered window with 960 width and 540 height
    window = SDL_CreateWindow("Pyramid Renderer by Moses Onerhime", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 960, 540, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    bool running = true;
    double angle = 90.0; // Initial angle of rotation

    //Creating an instance of the the Renderer3D class
    Renderer3D render3D(window, renderer, points, edges);

    while (running)
    {
        //if the quit button is pressed, the loop breaks
        if (SDL_QuitRequested()) { running = false; break; }

        // Rotate the pyramid around the Z axis
        rotatePyramidZ(points, angle);

        //Calls the function created in the Renderer3D class (render 3D is an instance of the class defined above)
        render3D.render();

        // Increment the angle for continuous rotation
        angle += 0.01; // Adjust rotation speed as needed
    }

    /*
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cout << "SDL initialization failed. SDL Error: " << SDL_GetError();
    }
    else
    {
        std::cout << "SDL initialization succeeded!";
    }

    std::cin.get();
    return 0;
    */


    return 0;
}