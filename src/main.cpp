#include "Application.h"

int main() {
    Application app (0, 0, true);

    while (app.handleEvents()) {
        app.draw();
    }

    return 0;
}
