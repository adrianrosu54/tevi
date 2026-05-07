#include <stdexcept>

#include <opencv2/core/mat.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/videoio.hpp>

#include "args.hpp"
#include "util/data.hpp"

#include "util/fetcher.hpp"

SourceFetcher setSourceFetcher(const Config &config, AppData &data) {
    SourceFetcher fetch;

    switch (config.sourceType) {
    case Source::CAMERA: {
        cv::VideoCapture cap(0);
        if (!cap.isOpened())
            throw std::runtime_error("Could not open camera");

        updateCameraSize(data, cap);

        cv::Mat frame;
        fetch = [cap = std::move(cap), frame = std::move(frame)]() mutable {
            bool ret = cap.read(frame);
            if (!ret)
                throw std::runtime_error("Could not read from camera");
            return frame;
        };
    } break;
    case Source::PHOTO: {
        cv::Mat frame = cv::imread(config.sourcePath, cv::IMREAD_COLOR_BGR);
        cv::Size frameSize = frame.size();
        data.sourceWidth = frameSize.width;
        data.sourceHeight = frameSize.height;

        fetch = [frame = std::move(frame)]() { return frame; };
    } break;
    case Source::VIDEO:
        throw std::invalid_argument("Video sources not supported");
    }

    return fetch;
}
