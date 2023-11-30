//try inputing anything, or paste anything

#include <ncurses.h>
#include <chrono>
#include <thread>
#include <vector>

int main()
{
    // Initialize ncurses
    initscr();
    cbreak();
    noecho();
    nodelay(stdscr, true);
    timeout(100);  // Refresh every 100 milliseconds

    // Set up the initial time
    auto start_time = std::chrono::steady_clock::now();

    // Buffer to store typed characters
    std::vector<char> typed_chars;

    bool running = true;
    while (running)
    {
        // Calculate the elapsed time
        auto current_time = std::chrono::steady_clock::now();
        auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(current_time - start_time).count() / 1000.0;

        // Clear the screen
        clear();

        // Print the elapsed time
        mvprintw(0, 0, "Elapsed Time: %.2f seconds", elapsed_time);

        // Print the typed characters
        mvprintw(1, 0, "Typed Characters: ");
        for (size_t i = 0; i < typed_chars.size(); ++i)
        {
            addch(typed_chars[i]);
        }

        // Check for user input
        int key = getch();
        if (key != ERR)
        {
            if (key == 'q')
                running = false;
            else
            {
                // Store the typed character in the buffer
                typed_chars.push_back(static_cast<char>(key));
            }
        }

        // Refresh the screen
        refresh();

        // Sleep for a short while to control the update rate
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    // Clean up ncurses
    endwin();

    return 0;
}