#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "V4L2Camera.h"
#include "opencv2/imgproc/imgproc.hpp"

V4L2Camera* cam;
using namespace cv;
using namespace std;
//void SavePic();
//void SavePic(Mat a){
//  static int i = 0;
//  char fname[20];
//  sprintf(fname,"camera_pic/im%03d.ppm",i++ % 1000);
//  imwrite(fname,a);

//}
//cam = new V4L2Camera();
//  cam->connect("/dev/video0");
//  cam->init(640,480,1);

int ind_c;
uchar * block;    
Mat lastpic;
char fname[23];
int main()
{
  cam = new V4L2Camera();
  namedWindow("hellokitty",1);
  cam->connect("/dev/video0");
  cam->init(V4L2Camera::SIZE_640_480,2);
  static int i=0;
 for(;;)
{
 
  ind_c = cam->grabBlocking();
  block = (uchar*)cam->getDataBuffer(ind_c)->data;
  lastpic =*new Mat(480,640,CV_8UC3,block); 
  sprintf(fname, "test_pic/out%03d.ppm",++i);
  imshow("hellokitty",lastpic);
  waitKey(100);
  imwrite(fname,lastpic);
  printf("pic! %d\n",i);
  if (i>99) i=0;
}
//IplImage* img = 0; 
//int height,width,step,channels;
//uchar *data;
//int i,j,k;
//if(argc<2){
//  printf("Usage: main <image-file-name>\n\7");
//  exit(0);
//}
//
//// load an image  
//img=cvLoadImage(argv[1]);
//if(!img){
//  printf("Could not load image file: %s\n",argv[1]);
//  exit(0);
//}
//
//// get the image data
//height    = img->height;
//width     = img->width;
//step      = img->widthStep;
//channels  = img->nChannels;
//data      = (uchar *)img->imageData;
//printf("Processing a %dx%d image with %d channels\n",height,width,channels); 
//
//// create a window
// cvNamedWindow("mainWin", CV_WINDOW_AUTOSIZE); 
// cvMoveWindow("mainWin", 100, 100);
//
//// invert the image
//  for(i=0;i<height;i++) for(j=0;j<width;j++) for(k=0;k<channels;k++)
//   data[i*step+j*channels+k]=255-data[i*step+j*channels+k];
//
//// show the image
//  cvShowImage("mainWin", img );
//
//// wait for a key
//  cvWaitKey(0);
//
//// release the image
//  cvReleaseImage(&img );
}
