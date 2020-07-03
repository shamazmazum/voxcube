#include <iostream>
#include <stdlib.h>
#include <getopt.h>
#include "Application.h"

#define NAME "voxcube"

static struct option longopts[] = {
    { "config",        required_argument, NULL, 'c' },
    { "width",         required_argument, NULL, 'w' },
    { "height",        required_argument, NULL, 'h' },
    { "no-fullscreen",       no_argument, NULL, 'f' },
    { NULL,                            0, NULL,  0  }
};

static void usage () {
    std::cerr << "Usage: " << NAME <<
        " --config|-c configuration "
        " [--no-fullscreen|-f] "
        " [--width|-w width] "
        " [--height|-h height]" << std::endl;
    exit (1);
}

int main (int argc, char *argv[]) {
    std::string cfg;
    std::unique_ptr<Application> app;
    bool fullscreen = true;
    int w = 800, h = 600;
    char c;

    while ((c = getopt_long (argc, argv, "c:w:h:f", longopts, NULL)) != -1) {
        switch (c) {
        case 'c':
            cfg = optarg;
            break;
        case 'w':
            w = std::stoi (optarg);
            break;
        case 'h':
            h = std::stoi (optarg);
            break;
        case 'f':
            fullscreen = false;
            break;
        default:
            usage();
        }
    }

    if (cfg.empty ()) {
        usage ();
    }

    try {
        app = std::make_unique<Application> (cfg, w, h, fullscreen);
    } catch (const std::runtime_error &e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    while (app->handleEvents()) {
        app->draw();
    }

    return 0;
}
