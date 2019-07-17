#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdio.h>
int main(){
    IplImage *src, *templ[4], *ftmp[4]; //ftmp is what to display on

    char *filename = const_cast<char *>("2.jpg");
    char *name[4] = {const_cast<char *>("1.jpg"), const_cast<char *>("5.jpeg"), const_cast<char *>("10.jpeg"),
                     const_cast<char *>("55.jpeg")};

    src = cvLoadImage(filename, 1);

    for (size_t i = 0 ; i < 4; ++i)
        templ[i] = cvLoadImage(name[i], 1);

    for (size_t i = 0; i<4; ++i) {
        ftmp[i] = cvCreateImage(cvSize(src->width - templ[i]->width + 1, src->height - templ[i]->height + 1), 32, 1);
    }

    for (size_t i = 0; i<4; ++i) {
        cvMatchTemplate(src, templ[i], ftmp[i], 5);
        cvNormalize(ftmp[i], ftmp[i], 1, 0, CV_MINMAX);
    }

    cvNamedWindow("Template");
    cvShowImage("Template", templ[0]);
    cvNamedWindow("Image");
    cvShowImage("Image", src);

    cvNamedWindow("CCOEFF_NORMED1");
    cvShowImage("CCOEFF_NORMED1", ftmp[0]);

    cvNamedWindow("CCOEFF_NORMED2");
    cvShowImage("CCOEFF_NORMED2", ftmp[1]);

    cvNamedWindow("CCOEFF_NORMED3");
    cvShowImage("CCOEFF_NORMED3", ftmp[2]);

    cvNamedWindow("CCOEFF_NORMED4");
    cvShowImage("CCOEFF_NORMED4", ftmp[3]);

    cvWaitKey(0);
    return 0;
}