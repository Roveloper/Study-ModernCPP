/*

The MIT License

Copyright (c) 2015 Avi Singh

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

*/

#include "opencv2/video/tracking.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/calib3d/calib3d.hpp"


#include <iostream>
#include <ctype.h>
#include <algorithm> // for copy
#include <iterator> // for ostream_iterator
#include <vector>
#include <ctime>
#include <sstream>
#include <fstream>
#include <string>

using namespace cv;
using namespace std;

void featureTracking(Mat img_1, Mat img_2, vector<Point2f>& points1, vector<Point2f>& points2, vector<uchar>& status)	{ 

//this function automatically gets rid of points for which tracking fails

  vector<float> err;					
  Size winSize=Size(21,21);																								
  TermCriteria termcrit=TermCriteria(TermCriteria::COUNT+TermCriteria::EPS, 30, 0.01);

  calcOpticalFlowPyrLK(img_1, img_2, points1, points2, status, err, winSize, 3, termcrit, 0, 0.001);

  //getting rid of points for which the KLT tracking failed or those who have gone outside the frame
  int indexCorrection = 0;
  for( int i=0; i<status.size(); i++)
     {  Point2f pt = points2.at(i- indexCorrection);
     	if ((status.at(i) == 0)||(pt.x<0)||(pt.y<0))	{
     		  if((pt.x<0)||(pt.y<0))	{
     		  	status.at(i) = 0;
     		  }
     		  points1.erase (points1.begin() + (i - indexCorrection));
     		  points2.erase (points2.begin() + (i - indexCorrection));
     		  indexCorrection++;
     	}

     }

}

void featureDetection(Mat img_1, vector<Point2f>& points1)	{   //uses FAST as of now, modify parameters as necessary
  // FAST
  
  vector<KeyPoint> keypoints_1;
  int fast_threshold = 20;
  bool nonmaxSuppression = true;
  FAST(img_1, keypoints_1, fast_threshold, nonmaxSuppression);
   
  KeyPoint::convert(keypoints_1, points1, vector<int>()); //keypoint 의 벡터를 Point의 벡터로 변환한다. FAST
}


void ORBTracking(Mat img_1, Mat img_2, vector<DMatch>& good_matches){

  vector<float> err;
  Ptr<DescriptorMatcher> matcher = ORB::create();
  vector<DMatch> matches;

  Ptr<Feature2D> feature_1 = ORB::create();
  Ptr<Feature2D> feature_2 = ORB::create();

  vector<KeyPoint> keypoint_1, keypoint_2;

  Mat desc1, desc2;

  feature_1->detectAndCompute(img_1, Mat(), keypoint_1, desc1);
  feature_2->detectAndCompute(img_2, Mat(), keypoint_2, desc2);
  
 // 참조로 desc1,2받아오기
  matcher->match(desc1,desc2,matches);

  sort(matches.begin(), matches.end());
  vector<DMatch> gmatch(matches.begin(), matches.begin() + 50);
  good_matches = gmatch;
  matches[0].queryIdx;
  matches[0].trainIdx;

}

void ORBDetection(Mat img_1, vector<Point2f>& points1){
  //ORB
  int nfeature = 500;
  float scaleFactor = 1.2f;
  int nlevels = 8;
  int edgeThreshold = 31;
  int firstLevel = 0;
  int WTA_K = 2;
  int scoreType = ORB::HARRIS_SCORE;
  int patchSize = 31;
  int fastThreshold = 20;

  Ptr<Feature2D> feature = ORB::create(nfeature, scaleFactor, nlevels, edgeThreshold, firstLevel, WTA_K, scoreType, patchSize, fastThreshold);

  vector<KeyPoint> Keypoint1;

  Mat desc1;
  feature->detectAndCompute(img_1, Mat(), Keypoint1, desc1);

  KeyPoint::convert(Keypoint1, points1, vector<int>());
}