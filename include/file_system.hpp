#pragma once

#include <string>
#include <opencv4/opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs/imgcodecs.hpp>

#include "maze_generator.hpp"

class file_system
{
public:
	void save(std::vector<std::vector<int>> vect, std::string filename);

private:
	static constexpr int factor = 20;
	const cv::Vec3b white = cv::Vec3b(255, 255, 255);
	const cv::Vec3b black = cv::Vec3b(0, 0, 0);
	const cv::Vec3b red = cv::Vec3b(0, 0, 255);
};