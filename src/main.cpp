#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>
#include <vector>

// Width and height of the grid
constexpr int WIDTH = 80;
constexpr int HEIGHT = 60;

// Size of each cell in pixels
constexpr int CELL_SIZE = 10;

// Alias for the grid type
using Grid = std::vector<std::vector<bool>>;

// Function to update the state of the grid for the next generation
void updateGrid(Grid& grid)
{
    Grid newGrid = grid;

    for (int x = 0; x < WIDTH; ++x)
    {
        for (int y = 0; y < HEIGHT; ++y)
        {
            // Count the number of live neighbors
            int liveNeighbors = 0;
            for (int i = -1; i <= 1; ++i)
            {
                for (int j = -1; j <= 1; ++j)
                {
                    int neighborX = (x + i + WIDTH) % WIDTH;
                    int neighborY = (y + j + HEIGHT) % HEIGHT;
                    if (grid[neighborX][neighborY] && !(i == 0 && j == 0))
                        liveNeighbors++;
                }
            }

            // Apply the rules of the Game of Life
            if (grid[x][y])
            {
                if (liveNeighbors < 2 || liveNeighbors > 3)
                    newGrid[x][y] = false;
            }
            else
            {
                if (liveNeighbors == 3)
                    newGrid[x][y] = true;
            }
        }
    }

    // Move the new grid back to the original grid
    grid = std::move(newGrid);
}

// Function to randomly initialize the grid with live cells
void initializeGridRandomly(Grid& grid)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 1);

    for (int x = 0; x < WIDTH; ++x)
    {
        for (int y = 0; y < HEIGHT; ++y)
        {
            grid[x][y] = dis(gen);
        }
    }
}

int main()
{
    // Create the SFML window
    sf::RenderWindow window(sf::VideoMode(WIDTH * CELL_SIZE, HEIGHT * CELL_SIZE), "Game of Life");

    // Create the grid
    Grid grid(WIDTH, std::vector<bool>(HEIGHT, false));

    // Initialize the grid with random live cells
    initializeGridRandomly(grid);

    // Main loop
    while (window.isOpen())
    {
        // Handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Update the grid
        updateGrid(grid);

        // Clear the window
        window.clear();

        // Draw the cells
        for (int x = 0; x < WIDTH; ++x)
        {
            for (int y = 0; y < HEIGHT; ++y)
            {
                if (grid[x][y])
                {
                    sf::RectangleShape cell(sf::Vector2f(CELL_SIZE, CELL_SIZE));
                    cell.setPosition(x * CELL_SIZE, y * CELL_SIZE);
                    window.draw(cell);
                }
            }
        }

        // Display the window
        window.display();
    }

    return 0;
}