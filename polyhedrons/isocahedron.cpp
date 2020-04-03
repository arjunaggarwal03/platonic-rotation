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

  //Isocahedron
  vector<vector<float>> points{{0,w*gr/6,w/6},{0,-w*gr/6,-w/6},{0,w*gr/6,-w/6},{0,-w*gr/6,w/6},{w/6,0,w*gr/6},{-w/6,0,-w*gr/6},{-w/6,0,w*gr/6},{w/6,0,-w*gr/6},{w*gr/6,w/6,0},{-w*gr/6,-w/6,0},{-w*gr/6,w/6,0},{w*gr/6,-w/6,0}};

  int delay = 0;
  
  while (delay < 10000){
    //rotation matrices
    vector<vector<float>> rotationZ{{cos(angle),-sin(angle),0},{sin(angle),cos(angle),0},{0,0,1}};
    vector<vector<float>> rotationX{{1,0,0},{0,cos(angle),-sin(angle)},{0,sin(angle),cos(angle)}};
    vector<vector<float>> rotationY{{cos(angle),0,-sin(angle)},{0,1,0},{sin(angle),0,cos(angle)}};

    vector<Point> pts;

    for(int i=0; i < points.size(); i++){
      vector<vector<float>> rotated = matmul(rotationY,points[i]); //rotates along Y axis
      rotated = matmul(rotationX,rotated); //then rotated along X axis
      rotated = matmul(rotationZ,rotated); //last rotated along Z axis

      vector<vector<float>> projection{{1,0,0},{0,1,0}}; //projection matrix to convert 3D points to 2D coordinates

      vector<vector<float>> projected2d = matmul(projection, rotated);
      drawPoint(image,Point(projected2d[0][0]+w/2,projected2d[1][0]+w/2)); //draws point (look at drawPoint() below)
      pts.push_back(Point(projected2d[0][0]+w/2,projected2d[1][0]+w/2)); //pushes point to pts vector
    }

    //connect edges (isocahedron)
    for(int i=0; i < 5; i++){
      drawLine(image,pts[0],pts[(i+1)*2]);
      drawLine(image,pts[1],pts[(i+1)*2+1]);
    }
    for(int j=0; j < 4; j++){
      drawLine(image,pts[2+3*j],pts[7]);
    }
    drawLine(image,pts[2],pts[5]);
    drawLine(image,pts[4],pts[3]);
    drawLine(image,pts[4],pts[11]);
    drawLine(image,pts[3],pts[11]);
    drawLine(image,pts[6],pts[9]);
    drawLine(image,pts[6],pts[3]);
    drawLine(image,pts[3],pts[9]);
    drawLine(image,pts[8],pts[11]);
    drawLine(image,pts[10],pts[9]);
    drawLine(image,pts[10],pts[5]);
    drawLine(image,pts[5],pts[9]);
    drawLine(image,pts[2],pts[8]);
    drawLine(image,pts[2],pts[10]);
    drawLine(image,pts[8],pts[4]);
    drawLine(image,pts[10],pts[6]);
    drawLine(image,pts[6],pts[4]);

    imshow("Animation", image);
    waitKey(1);
    image = Mat::zeros(w, w, CV_8UC3); //resets image
    angle += 0.02; //update angle
    delay++;
  }
}

//used opencv line(...) method
void drawLine( Mat img, Point start, Point end ){
  line( img,start,end,Scalar(255, 255, 0),2,8);
}

//used opencv circle(...) method
void drawPoint( Mat img, Point temp){
  circle(img,temp,2,Scalar(255,158,179),18,8,0);
}