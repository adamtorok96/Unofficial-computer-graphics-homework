#include "utility2d3d.hpp"

void drawTextToCenter(cv::Mat &img, const char *text)
{
    int baseline = 0;
    cv::Size textSize = cv::getTextSize(text, cv::FONT_HERSHEY_PLAIN, 1.0, 1, &baseline);
    baseline += 1;
    cv::Point textOrg((img.cols - textSize.width) / 2, (img.rows + textSize.height) / 2);
    cv::putText(img, text, textOrg, cv::FONT_HERSHEY_PLAIN, 1, cv::Scalar::all(255), 1);
}

GLuint createTextureFromFile(const char *filename)
{
    GLuint texId;
    cv::Mat cvImage = cv::imread(filename);			// note that it reads every picture as 3x8-bit (BGR).

    if (0 == cvImage.rows*cvImage.cols) throw filename;

    std::vector<GLubyte> uImage;
    uImage.reserve(cvImage.rows*cvImage.cols * 3);

    for (int i = cvImage.rows - 1; i >= 0; i--)
    {
        for (int j = 0; j < cvImage.cols; j++)
        {
            cv::Vec3b c = cvImage.at<cv::Vec3b>(i, j);
            uImage.push_back(c[2]);
            uImage.push_back(c[1]);
            uImage.push_back(c[0]);
        }
    }

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glGenTextures(1, &texId);
    glBindTexture(GL_TEXTURE_2D, texId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, cvImage.cols, cvImage.rows, 0, GL_RGB, GL_UNSIGNED_BYTE, uImage.data());

    return texId;
}