#include <iostream>
#include <boost/filesystem.hpp>
#include <opencv2/opencv.hpp>

#include "debug.hpp"

void debug_showOptions(const Options &options)
{
    std::cout << "DEBUG: Show options\n";
    std::cout << "    convert:     " << options.convert << '\n';
    std::cout << "    height:      " << options.height << '\n';
    std::cout << "    width:       " << options.width << '\n';
    std::cout << "    frameStart:  " << options.frameStart << '\n';
    std::cout << "    frameEnd:    " << options.frameEnd << '\n';
    std::cout << "    inFile:      " << options.inFile << '\n';
    std::cout << "    inDir:       " << options.inDir << '\n';
    std::cout << "    inFilter:    " << options.inFilter << '\n';
    std::cout << "    outFile:     " << options.outFile << '\n';
    std::cout << "    outDir:      " << options.outDir << '\n';
    std::cout << "    outPrefix:   " << options.outPrefix << '\n';
    std::cout << "    outType:     " << options.outType << '\n';
    std::cout << '\n';
    std::cout << "    code:        " << options.code << '\n';
    std::cout << "    outSuffix:   " << options.outSuffix << '\n';
    std::cout << "    inFiles:\n";
    for (std::vector<fs::path>::const_iterator ite = options.inFiles.begin();
         ite != options.inFiles.end(); ite++)
        std::cout << "        " << *ite << '\n';
}
