#include <iostream>
#include <cstdio>
#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>
#include <boost/regex.hpp>
#include <opencv2/opencv.hpp>

#include "convert.hpp"
#include "debug.hpp"
#include "options.hpp"

namespace po = boost::program_options;
namespace fs = boost::filesystem;


int main(int argc, char **argv)
{
    Options options;

    // clang-format off
    po::options_description desc(
        "OpenCV based image converter"
    );
    desc.add_options()
        ("code,c", po::value<std::string>(&options.convert)->default_value("YUV2BGR_NV12"),
         "The code option in OpenCV's cvtColor(), currently support following options:\n"
         "  YUV2BGR_NV21, YUV2RGB_NV21,\n"
         "  YUV2BGR_NV12, YUV2RGB_NV12,\n"
         "  YUV2BGRA_NV21, YUV2RGBA_NV21,\n"
         "  YUV2BGRA_NV12, YUV2RGBA_NV12")
        ("frame-start,s", po::value<int>(&options.frameStart)->default_value(1))
        ("frame-end,e", po::value<int>(&options.frameEnd)->default_value(0),
         "The options -e and -s are valid when the input file is a video")
        ("help,h",
         "Produce help message")
        ("in-file,i", po::value<std::string>(&options.inFile),
         "Input file")
        ("in-dir,I", po::value<std::string>(&options.inDir)->default_value("./"),
         "Input directory")
        ("in-filter,f",po::value<std::string>(&options.inFilter)->default_value(".*(yuv|YUV)"),
         "Filter the files in input directory")
        ("out-file,o", po::value<std::string>(&options.outFile),
         "Output file")
        ("out-dir,O", po::value<std::string>(&options.outDir),
         "Output directory")
        ("out-prefix,p", po::value<std::string>(&options.outPrefix),
         "Output filename's prefix")
        ("out-suffix,s", po::value<std::string>(&options.outType)->default_value("BMP"),
         "Output file's type, currently support following options:\n"
         "  BMP, PNG")
        ("height,x", po::value<int>(&options.height)->default_value(720),
         "Image height")
        ("width,y", po::value<int>(&options.width)->default_value(1280),
         "Image width")
    ;
    // clang-format on

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help"))
    {
        std::cout << desc;
        return 0;
    }

    if (options.convert == "YUV2BGR_NV21")
        options.code = cv::COLOR_YUV2BGR_NV21;
    else if (options.convert == "YUV2RGB_NV21")
        options.code = cv::COLOR_YUV2RGB_NV21;
    else if (options.convert == "YUV2BGR_NV12")
        options.code = cv::COLOR_YUV2BGR_NV12;
    else if (options.convert == "YUV2RGB_NV12")
        options.code = cv::COLOR_YUV2RGB_NV12;
    else if (options.convert == "YUV2BGRA_NV21")
        options.code = cv::COLOR_YUV2BGRA_NV21;
    else if (options.convert == "YUV2RGBA_NV21")
        options.code = cv::COLOR_YUV2RGBA_NV21;
    else if (options.convert == "YUV2BGRA_NV12")
        options.code = cv::COLOR_YUV2BGRA_NV12;
    else if (options.convert == "YUV2RGBA_NV12")
        options.code = cv::COLOR_YUV2RGBA_NV12;
    else
    {
        std::cout << options.convert << " is not supported!!!\n";
        return 0;
    }

    if (options.inFile.length() > 0 &&
        fs::exists(options.inFile) &&
        fs::is_regular_file(options.inFile))
    {
        options.inFiles.push_back(fs::path(options.inFile));
    }
    else if (options.inDir.length() > 0 &&
             fs::exists(options.inDir) &&
             fs::is_directory(options.inDir))
    {
        boost::regex *filter = NULL;
        if (options.inFilter.length() > 0)
            filter = new boost::regex(options.inFilter);

        for (fs::directory_entry &x : fs::directory_iterator(options.inDir))
            if (fs::is_regular_file(x.path()))
            {
                if (!filter ||
                    boost::regex_match(x.path().filename().string(), *filter))
                    options.inFiles.push_back(x.path());
            }
    }

    if (options.inFiles.size() == 0)
    {
        std::cout << "No input file!!!\n";
        return 0;
    }

    if (options.outFile.length() > 0 &&
            !fs::is_directory(fs::path(options.outFile).remove_filename()) ||
        options.outDir.length() > 0 &&
            !fs::is_directory(fs::path(options.outDir)))
    {
        std::cout << "The path of output file is not existed!!!\n";
        return 0;
    }

    if (options.outType == "BMP")
        options.outSuffix = ".bmp";
    else if (options.outType == "PNG")
        options.outSuffix = ".png";
    else
        std::cout << options.outType << " is not supported!!!!\n";

#ifdef DEBUG
    debug_showOptions(options);
#endif

    switch (options.code)
    {
    case cv::COLOR_YUV2BGR_NV21:
    case cv::COLOR_YUV2RGB_NV21:
    case cv::COLOR_YUV2BGR_NV12:
    case cv::COLOR_YUV2RGB_NV12:
    case cv::COLOR_YUV2BGRA_NV21:
    case cv::COLOR_YUV2RGBA_NV21:
    case cv::COLOR_YUV2BGRA_NV12:
    case cv::COLOR_YUV2RGBA_NV12:
        cvtColorTwoPlaneYUV2BGR(options);
        break;
    default:
        std::cout << "Unknown/unsupported color conversion code\n";
        return 0;
    }
}
