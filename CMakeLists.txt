project(shadow CXX)
enable_testing()

SET(CMAKE_CXX_FLAGS "-std=c++11 -fpermissive")

cmake_minimum_required(VERSION 2.6)

include(FindOpenGL)
include(FindGLEW)
include(FindGLUT)

find_package(OpenCV REQUIRED)

include_directories({$OPENGL_INCLUDE_DIRS})
include_directories({$GLEW_INCLUDE_DIRS})
include_directories({$GLUT_INCLUDE_DIRS})

add_executable(shadow
shadow.cpp
        ImageSource.h FileImageSource.cpp FileImageSource.h WebcamImageSource.cpp WebcamImageSource.h GameControl.cpp GameControl.h GameElement.h ImageProcessor.cpp ImageProcessor.h Avatar.cpp Avatar.h CrawlerScroll.cpp CrawlerScroll.h shadow.h utility2d3d.cpp Mesh.cpp Mesh.h Logo.cpp Logo.h CameraWindow.cpp CameraWindow.h)

target_link_libraries(shadow ${GLUT_LIBRARIES} ${OPENGL_LIBRARIES} GL ${GLEW_LIBRARIES} GLU ${OpenCV_LIBS} opencv_core opencv_imgcodecs opencv_imgproc opencv_highgui opencv_video)