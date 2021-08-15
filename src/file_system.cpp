#include "file_system.hpp"

void file_system::save(std::vector<std::vector<int>> vect, std::string filename)
{
	cv::Mat mat_vect(vect.size(), vect[0].size(), CV_8UC3);
	for (int y = 0; y < mat_vect.rows; y++) {
		for (int x = 0; x < mat_vect.cols; x++) {
			if (basic_maze::wall == vect[y][x]) {
				mat_vect.at<cv::Vec3b>(y, x) = black;
			}
			else if (basic_maze::hole == vect[y][x]) {
				mat_vect.at<cv::Vec3b>(y, x) = white;
			}
			else {
				mat_vect.at<cv::Vec3b>(y, x) = red;
			}
		}
	}
	cv::Mat mat_vect_bigger(vect.size()*factor, vect[0].size()*factor, CV_8UC3);
	
	cv::resize(mat_vect, mat_vect_bigger, cv::Size(), factor, factor, cv::INTER_NEAREST);
	cv::imwrite(filename, mat_vect_bigger);
}