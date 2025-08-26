#include <fstream>

void debug(const std::string& msg) {
    #if DEBUG
        std::ofstream debugFile("debug.log", std::ios::app);
        debugFile << msg << std::endl;
        debugFile.close();
    #endif
}
