#include <stdlib.h>
#include <opencv2/opencv.hpp>
#include <cv.h>

#define SIZE 6

char temp[][21] = {"own.jpeg", "own_90.jpeg", "own_180.jpeg", "own_270.jpeg",
                   "own_m.jpeg", "own_m_90.jpeg", "own_m_180.jpeg"};
char name_res[][11] =   {"r90", "r180",  "r270", "r_m", "r_m_r90", "r_m_r180"};
char name_p_res[][13] = {"p_r90", "p_r180", "p_r270", "p_m","p_m_r90", "p_m_r180"};
char name_corr[][13] =  {"c_r90", "c_r180", "c_r270", "c_m", "c_m_r90", "c_m_r180"};
int main(){
    IplImage *src = cvLoadImage(temp[0], 1);
    IplImage *p_src = cvCreateImage(cvSize(src->width, src->height), IPL_DEPTH_8U, 3);
    IplImage *p_src_x4 = cvCreateImage(cvSize(src->width*2,src->height*2), IPL_DEPTH_8U, 3);
    IplImage *img2[SIZE];
    IplImage *p_img2[SIZE];
    IplImage *corr[SIZE];
    for (int i = 0; i < SIZE; ++i) {
        img2[i] = cvLoadImage(temp[i + 1], 1);
        p_img2[i] = cvCreateImage(cvSize(img2[i]->width, img2[i]->height), IPL_DEPTH_8U, 3);
        corr[i] = cvCreateImage(cvSize((img2[i]->width + 1), (img2[i]->height + 1)), IPL_DEPTH_32F, 1);
    }
    cvLogPolar(src, p_src, cvPoint2D32f(src->width/2.0, src->height/2.0), 70);
    cvSetImageROI(p_src_x4, cvRect(0, 0, p_src->width, p_src->height));
    cvCopy(p_src, p_src_x4);
    cvResetImageROI(p_src_x4);
    cvSetImageROI(p_src_x4, cvRect(p_src->width, 0, p_src->width, p_src->height));
    cvCopy(p_src, p_src_x4);
    cvResetImageROI(p_src_x4);
    cvSetImageROI(p_src_x4, cvRect(0, p_src->height, p_src->width, p_src->height));
    cvCopy(p_src, p_src_x4);
    cvResetImageROI(p_src_x4);
    cvSetImageROI(p_src_x4, cvRect(p_src->width, p_src->height, p_src->width, p_src->height));
    cvCopy(p_src, p_src_x4);
    cvResetImageROI(p_src_x4);
    cvShowImage("src", src);
    cvShowImage("p_src", p_src);
    cvShowImage("p_src_4x", p_src_x4);
    for (int i = 0; i < SIZE; ++i) {
        cvLogPolar(img2[i], p_img2[i], cvPoint2D32f(img2[i]->width / 2.0, img2[i]->height / 2.0), 70);
        cvMatchTemplate(p_src_x4, p_img2[i], corr[i], CV_TM_CCOEFF_NORMED);
        cvShowImage(name_res[i], img2[i]);
        cvShowImage(name_p_res[i], p_img2[i]);
        cvShowImage(name_corr[i], corr[i]);
        cvWaitKey(0);
    }
//    cvWaitKey(0);
    cvDestroyAllWindows();
    for (int i = 0; i < SIZE; ++i) {
        cvReleaseImage(&img2[i]);
        cvReleaseImage(&p_img2[i]);
        cvReleaseImage(&corr[i]);
    }
    cvReleaseImage(&p_src_x4);
    cvReleaseImage(&src);
    cvReleaseImage(&p_src);
}