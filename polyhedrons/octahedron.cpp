#include <iostream>
#include <stdio.h>
#include <opencv2/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#define w 1000
#define gr 1.618034

using namespace cv;
using namespace std;

void drawLine( Mat img, Point start, Point end );
void drawPoint(Mat img, Point temp);

vector<vector<float>> vecToMatrix(vector<float> b){
  vector<vector<float>> ret{{b[0]},{b[1]},{b[2]}};
  return ret;
}

vector<vector<float>> matmul(vector<vector<float>> a, vector<vector<float>> b){
  int colsA = a[0].size();
  int rowsA = a.size();
  int colsB = b[0].size();
  int rowsB = b.size();

  vector<vector<float>> ret(rowsA,vector<float> (colsB));

  for(int i=0; i < rowsA; i++){
    for(int j=0; j < colsB; j++){
      int sum = 0;
      for(int k=0; k < colsA; k++){
        sum += a[i][k] * b[k][j];
      }
      ret[i][j] = sum;
    }
  }

  return ret;
}

vector<vector<float>> matmul(vector<vector<float>> a, vector<float> b){
  vector<vector<float>> m = vecToMatrix(b);
  return matmul(a,m);
}

int main(){
  Mat image = Mat::zeros(w, w, CV_8UC3);

  float angle = 0;

  //Octahedron
  vector<vector<float>> points{{-w/4,0,0},{w/4,0,0},{0,-w/4,0},{0,w/4,0},{0,0,-w/4},{0,0,w/4}};

  int delay = 0;
  
  while (delay < 10000){
    //rotation matrices
    vector<vector<float>> rotationZ{{cos(angle),-sin(angle),0},{sin(angle),cos(angle),0},{0,0,1}};
    vector<vector<float>> rotationX{{1,0,0},{0,cos(angle),-sin(angle)},{0,sin(angle),cos(angle)}};
    vector<vector<float>> rotationY{{cos(angle),0,-sin(angle)},{0,1,0},{sin(angle),0,cos(angle)}};

    vector<Point> pts;

    for(int i=0; i < points.size(); i++){
      vector<vector<float>> rotated = matmul(rotationY,points[i]);
      rotated = matmul(rotationX,rotated);
      rotated = matmul(rotationY,rotated);

      float distance = 2;
      float z = 1/(2 - rotated[2][0]);
      cout << z << endl;
      vector<vector<float>> projection{{z,0,0},{0,z,0}};

      vector<vector<float>> projected2d = matmul(projection, rotated);
      drawPoint(image,Point(projected2d[0][0]+w/2,projected2d[1][0]+w/2));
      pts.push_back(Point(projected2d[0][0]+w/2,projected2d[1][0]+w/2));
    }

    //connect edges (octahedron)
    for(int i=0; i < 4; i++){
      drawLine(image,pts[0],pts[i+2]);
      drawLine(image,pts[1],pts[i+2]);
    }
    drawLine(image,pts[2],pts[4]);
    drawLine(image,pts[3],pts[5]);
    drawLine(image,pts[4],pts[3]);
    drawLine(image,pts[5],pts[2]);

    imshow("Animation", image);
    waitKey(1);
    image = Mat::zeros(w, w, CV_8UC3); //resets image
    angle += 0.02; //update angle
    delay++;
  }
}

void drawLine( Mat img, Point start, Point end ){
  line( img,start,end,Scalar(255, 255, 0),2,8);
}

void drawPoint( Mat img, Point temp){
  circle(img,temp,2,Scalar(255,158,179),18,8,0);
}