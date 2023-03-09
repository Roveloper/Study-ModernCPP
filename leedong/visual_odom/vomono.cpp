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

#include "vo_features.h"

using namespace cv;
using namespace std;

#define MAX_FRAME 4000
#define MIN_NUM_FEAT 2000

// IMP: Change the file directories (4 places) according to where your dataset is saved before running!

struct Point3D
{
  /* data */
  double x=0;
  double y=0;
  double z=0;
};

Point3D getGT(int frame_id)
{
  Point3D GT;
  string line;
  int i = 0;
  ifstream myfile ("/home/park/kitti_ws/src/data_odometry_gray/dataset/sequences/08/08.txt");
  double x=0, y=0, z=0;
  double a=0, b=0, c=0, d=0, e=0, f=0, g=0, h=0, j=0;
  double x_prev, y_prev, z_prev;
  if (myfile.is_open())
  {
    while (( getline (myfile,line) ) && (i<=frame_id))
    {
      std::istringstream in(line);
      in >> a >> b >> c >> x >> d >> e >> f >> y >> g >> h >> j >> z;
      
      GT.x = x;
      GT.y = y;
      GT.z = z;
      i++;
    }
    myfile.close();
  }
  else {
    cout << "Unable to open file";
    return GT;
  }
  return GT;
}

double getAbsoluteScale(int frame_id, int sequence_id, double z_cal)	{
  
  string line;
  int i = 0;
  ifstream myfile ("/home/park/kitti_ws/src/data_odometry_gray/dataset/sequences/08/08.txt");
  double x =0, y=0, z = 0;
  double x_prev, y_prev, z_prev;
  if (myfile.is_open())
  {
    while (( getline (myfile,line) ) && (i<=frame_id))
    {
      z_prev = z;
      x_prev = x;
      y_prev = y;
      std::istringstream in(line);
      // cout << line << '\n';
      for (int j=0; j<12; j++)  {
        in >> z ;
        // cout << z << endl;
        if (j==7)  y=z;
        if (j==3)  x=z;
      }
      
      i++;
    }
    myfile.close();
  }

  else {
    cout << "Unable to open file";
    return 0;
  }

  return sqrt((x-x_prev)*(x-x_prev) + (y-y_prev)*(y-y_prev) + (z-z_prev)*(z-z_prev)) ;

}


int main( int argc, char** argv )	{

  Mat img_1, img_2; // openCV Matrix class image
  Mat R_f, t_f; // rotation vector, translation vector

  ofstream myfile; // write mode
  myfile.open ("results1_1.txt"); // file open -> trajactory 저장

  double scale = 1.00;
  char filename1[200];
  char filename2[200];
  sprintf(filename1, "/home/park/kitti_ws/src/data_odometry_gray/dataset/sequences/08/image_0/%06d.png", 0); // file name , image_0에서 0과1부터 저장하며 시작
  sprintf(filename2, "/home/park/kitti_ws/src/data_odometry_gray/dataset/sequences/08/image_0/%06d.png", 1);

  char text[200];
  char text2[200];
  int fontFace = FONT_HERSHEY_PLAIN; // 1
  double fontScale = 1;
  int thickness = 1;  
  cv::Point textOrg(10, 50); // coordinate좌표 글자 시작 위치 조정
  cv::Point textOrg2(10, 30);

  //read the first two frames from the dataset
  Mat img_1_c = imread(filename1); // 이미지 두개 비교하기 위해 Matrix 형태로 만들기
  Mat img_2_c = imread(filename2);

  if ( !img_1_c.data || !img_2_c.data ) { 
    std::cout<< " --(!) Error reading images " << std::endl; return -1; // 이미지가 안들어 오면 error메시지 출력
  }

  // we work with grayscale images
  cvtColor(img_1_c, img_1, COLOR_BGR2GRAY); // Grayscale로 변환
  cvtColor(img_2_c, img_2, COLOR_BGR2GRAY);

  // feature detection, tracking
  vector<Point2f> points1, points2;        //vectors to store the coordinates of the feature points
  
  // featureDetection(img_1, points1);        //detect features in img_1
  //ORBDetection(img_1, points1);
  vector<uchar> status;
  vector<DMatch> good_matches;
  // featureTracking(img_1,img_2,points1,points2, status); //track those features to img_2
  ORBTracking(img_1,img_2, points1,points2, good_matches); //track those features to img_2

  //TODO: add a fucntion to load these values directly from KITTI's calib files
  // WARNING: different sequences in the KITTI VO dataset have different intrinsic/extrinsic parameters
  double focal = 718.8560;
  cv::Point2d pp(607.1928, 185.2157);
  //recovering the pose and the essential matrix
  Mat E, R, t, mask;
  
  cout << points1.size() << endl;
  cout << points2.size() << endl;


  E = findEssentialMat(points2, points1, focal, pp, RANSAC, 0.999, 1.0, mask); // 두 이미지의 해당 점에서 필수 행렬을 계산
  
  recoverPose(E, points2, points1, R, t, focal, pp, mask); // 두 이미지의 해당 점으로부터 상대 카메라 회전 및 평행 이동을 복구

  // previous image, current image의 feature와 Mat,vector 정의
  Mat prevImage = img_2;
  Mat currImage;
  // vector<Point2f> prevFeatures = points2;
  // vector<Point2f> currFeatures;

  char filename[100];

  // 복사
  R_f = R.clone();
  t_f = t.clone();

  clock_t begin = clock(); // 시작 시간 저장

  namedWindow( "Road facing camera", WINDOW_AUTOSIZE );// Create a window for display.
  namedWindow( "Trajectory", WINDOW_AUTOSIZE );// Create a window for display.

  Mat traj = Mat::zeros(600, 600, CV_8UC3); // 경로 행렬 8bit unsigned char

  
  for(int numFrame=2; numFrame < MAX_FRAME; numFrame++)	{
    vector<Point2f> prevFeatures;
    vector<Point2f> currFeatures;
  	sprintf(filename, "/home/park/kitti_ws/src/data_odometry_gray/dataset/sequences/08/image_0/%06d.png", numFrame);
    //cout << numFrame << endl;
  	Mat currImage_c = imread(filename); // 현재 파일 받아서 현재 이미지에 넣음(color)
  	cvtColor(currImage_c, currImage, COLOR_BGR2GRAY); // gray로 변환
  	vector<uchar> status; // feature를 추적한 값을 담는 공간
    vector<DMatch> good_matches;
  	// featureTracking(prevImage, currImage, prevFeatures, currFeatures, status);
  	ORBTracking(prevImage, currImage, prevFeatures, currFeatures, good_matches);


    cout << currFeatures.size() << endl;
    cout << prevFeatures.size() << endl;

  	E = findEssentialMat(currFeatures, prevFeatures, focal, pp, RANSAC, 0.999, 1.0, mask);
  	recoverPose(E, currFeatures, prevFeatures, R, t, focal, pp, mask);

    Mat prevPts(2,prevFeatures.size(), CV_64F), currPts(2,currFeatures.size(), CV_64F); //2*feature개수 matrix prev, curr 두개 생성


   for(int i=0;i<prevFeatures.size();i++)	{   //this (x,y) combination makes sense as observed from the source code of triangulatePoints on GitHub
  		prevPts.at<double>(0,i) = prevFeatures.at(i).x; // prevPts (0,i) = 이전 이미지의 feature의 x 좌표 -> x,x,x,x,x,x,x,x,x,x
  		prevPts.at<double>(1,i) = prevFeatures.at(i).y;                                                   //y,y,y,y,y,y,y,y,y,y

  		currPts.at<double>(0,i) = currFeatures.at(i).x;
  		currPts.at<double>(1,i) = currFeatures.at(i).y;
    }

  	scale = getAbsoluteScale(numFrame, 0, t.at<double>(2)); // n번째 프레임을 받아서 scale return

    //cout << "Scale is " << scale << endl;

    if ((scale>0.1)&&(t.at<double>(2) > t.at<double>(0)) && (t.at<double>(2) > t.at<double>(1))) {

      t_f = t_f + scale*(R_f*t);
      R_f = R*R_f;

    }
  	
    else {
     //cout << "scale below 0.1, or incorrect translation" << endl;
    }
    
   // lines for printing results
  //  myfile << t_f.at<double>(0) << " " << t_f.at<double>(1) << " " << t_f.at<double>(2) << endl;

  // a redetection is triggered in case the number of feautres being trakced go below a particular threshold
 	  if (prevFeatures.size() < MIN_NUM_FEAT)	{
      //cout << "Number of tracked features reduced to " << prevFeatures.size() << endl;
      //cout << "trigerring redection" << endl;
 		  // featureDetection(prevImage, prevFeatures);
      //ORBDetection(prevImage, prevFeatures);
      // featureTracking(prevImage,currImage,prevFeatures,currFeatures, status);
      ORBTracking(prevImage,currImage, prevFeatures,currFeatures, good_matches);

 	  }

    prevImage = currImage.clone(); // 이미지 갱신
    prevFeatures = currFeatures;

    int x = int(t_f.at<double>(0)) + 400;
    int y = int(t_f.at<double>(2)) + 100;
    Point3D gt = getGT(numFrame);
    int xx = int(gt.x)+ 400;
    int zz = int(gt.z)+ 100;

    circle(traj, Point(x, y) ,1, CV_RGB(255,0,0), 2);
    circle(traj, Point(xx, zz), 1, CV_RGB(0,255,0), 2);

    rectangle( traj, Point(10, 30), Point(550, 50), CV_RGB(0,0,0), CV_FILLED);
    rectangle( traj, Point(10, 50), Point(550, 50), CV_RGB(0,0,0), CV_FILLED);//덮어주는 느낌

    sprintf(text, "Coordinates: x = %02fm y = %02fm z = %02fm", t_f.at<double>(0), t_f.at<double>(1), t_f.at<double>(2));
    sprintf(text2, "Coordinates: x = %02fm y = %02fm z = %02fm", gt.x, gt.y, gt.z);

    putText(traj, text, textOrg, fontFace, fontScale, Scalar::all(255), thickness, 8);
    putText(traj, text2, textOrg2, fontFace, fontScale, Scalar::all(255), thickness, 8); // 갱신이 안되는 문제 발생
    

    imshow( "Road facing camera", currImage_c );
    imshow( "Trajectory", traj );

    waitKey(1);
    

  }

  clock_t end = clock(); // 코드가 끝난 시간 저장
  double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
  cout << "Total time taken: " << elapsed_secs << "s" << endl;

  //cout << R_f << endl;
  //cout << t_f << endl;

  return 0;
}