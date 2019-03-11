#ifndef __OPTIONS_HPP__
#define __OPTIONS_HPP__

#include <string>
#include <vector>
#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;

typedef struct Options
{
    std::string convert;
    int height;
    int width;
    int frameStart;
    int frameEnd;
    std::string inFile;
    std::string inDir;
    std::string inFilter;
    std::string outFile;
    std::string outDir;
    std::string outPrefix;
    std::string outType;

    int code;
    std::string outSuffix;
    std::vector<fs::path> inFiles;
} Options;

#endif
