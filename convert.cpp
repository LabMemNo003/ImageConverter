#include <iostream>
#include <cstdio>
#include <boost/filesystem.hpp>
#include <opencv2/opencv.hpp>

#include "convert.hpp"

namespace fs = boost::filesystem;

void cvtColorTwoPlaneYUV2BGR(const Options &options)
{
    int frameSize = options.height * options.width / 2 * 3;
    cv::Mat yuvImage(options.height / 2 * 3, options.width, CV_8UC1);
    cv::Mat rgbImage;

    for (std::vector<fs::path>::const_iterator ite = options.inFiles.begin();
         ite != options.inFiles.end(); ite++)
    {
        if (options.verbose)
            std::cout << "Processing " << *ite << '\n';

        int fileSize = fs::file_size(*ite);
        int frameCnt = fileSize / frameSize;

        int frameStart = options.frameStart;
        if (frameStart <= 0)
            frameStart += frameCnt;

        int frameEnd = options.frameEnd;
        if (frameEnd <= 0)
            frameEnd += frameCnt;

        if (frameStart > frameEnd)
        {
            std::cout << "No frame is converted in " << *ite << '\n';
            continue;
        }

        fs::path targetDir(ite->string() + "_Cvt");
        if (options.outDir.length() > 0)
            targetDir = fs::path(options.outDir) / targetDir.leaf();
        fs::create_directories(targetDir);

        FILE *pFile = std::fopen(ite->c_str(), "rb");
        std::fseek(pFile, frameSize * (frameStart - 1), SEEK_SET);
        for (int i = frameStart; i <= frameEnd; i++)
        {
            if (options.verbose)
            {
                if (i != frameStart)
                    std::cout << "..";
                std::cout << i << std::flush;
                if (i == frameEnd)
                    std::cout << '\n';
            }
            fread(yuvImage.data, frameSize, 1, pFile);
            cv::cvtColor(yuvImage, rgbImage, options.code);
            char num2str[10];
            std::sprintf(num2str,"%06d",i);
            fs::path targetFile(options.outPrefix + std::string(num2str) + options.outSuffix);
            cv::imwrite((targetDir / targetFile).string(), rgbImage);
        }

        std::fclose(pFile);
    }
}