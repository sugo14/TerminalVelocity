#include <fstream>

const bool DEBUG_MODE = false;

void debug(std::string msg) {
    if (!DEBUG_MODE) { return; }
    std::ofstream debugFile("debug.log", std::ios::app);
    debugFile << msg << std::endl;
    debugFile.close();
}
