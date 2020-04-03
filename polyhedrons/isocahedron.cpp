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
  