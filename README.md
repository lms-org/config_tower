#config_opencv

config-repo for trying out opencv. Execute opencv.sh to install opencv on ubuntu

### Installation

Using openCV3.0.0 is recommended! You also need [opencv_contrib](https://github.com/Itseez/opencv_contrib)
* [OpenCV 3.0.0 on Ubuntu 14.04](http://rodrigoberriel.com/2014/10/installing-opencv-3-0-0-on-ubuntu-14-04/)
* [OpenCV on Ubuntu 10.04](http://docs.opencv.org/doc/tutorials/introduction/linux_install/linux_install.html)
* [OpenCV on Ubuntu < 14.10](https://help.ubuntu.com/community/OpenCV)


Restart after installation!
If you are adding opencv to an existing project delete the build-folder and rebuild from scratch.

To install opencv_contrib:
* cmake -DOPENCV_EXTRA_MODULES_PATH=<opencv_contrib>/modules -D CMAKE_BUILD_TYPE=RELEASE -D CMAKE_INSTALL_PREFIX=/usr/local -D WITH_TBB=ON -D BUILD_NEW_PYTHON_SUPPORT=ON -D WITH_V4L=ON -D WITH_QT=ON -D WITH_OPENGL=ON ..
* make -j $(nproc)
* sudo make install
* 
###What's already done:
 * convert Image from [imaging](github.com/lms-org/imaging) into opencv image (Done)
 * face detection: http://docs.opencv.org/master/d7/d8b/tutorial_py_face_detection.html#gsc.tab=0 (Done)
 * ... (to lazy, if you really want to know it check out the modules/framework_conf.xml)
