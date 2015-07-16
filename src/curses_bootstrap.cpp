#include <curses.h>
#include <vector>

namespace curses_bootstrap
{
        struct windows {
        std::vector<int> position;
        std::vector<int> size;
        }

        int main() {
                initscr();
                noecho();
                cbreak();
        }
}
