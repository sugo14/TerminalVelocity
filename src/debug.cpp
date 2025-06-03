#include <fstream>

void debug(std::string msg) {
    std::ofstream debugFile("debug.log", std::ios::app);
    debugFile << msg << std::endl;
    debugFile.close();
}
