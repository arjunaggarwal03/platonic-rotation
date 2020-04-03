# platonic-rotation
 
## introduction
At the root of 3D rendering is the usage of basic matrix multiplcation to convert three-dimensional points (x,y,z) into two-dimensional coordinates (x,y). Using OpenCV, I developed a visualization of the application of projection and rotation matrices on four platonic solids (cube, octahedron, isocadehron, & dodecahedron).

## the math

### step one: rotation
For each x-y-z coordinate, I converted the coordinate into a 1x3 matrix and then multiplied it by the following matrices. 
<br>
<p align="center">
<img src="https://wikimedia.org/api/rest_v1/media/math/render/svg/a6821937d5031de282a190f75312353c970aa2df">
</p>

The order of the multiplication changes how the figure rotates in the animation. In my code, I first multiplied by the Y rotation matrix, then the X rotation matrix, and finally, the Z rotation matrix.

### step two: orthographic projection
Lastly, I used the following matrix expression to convert the 1x3 x-y-z coordinate matrix into two-dimensional coordinates.

<p align="center">
<img src="https://wikimedia.org/api/rest_v1/media/math/render/svg/7aed406cbf214a05a044ffc28f4e4549e137b928">
</p>

## run my code
In order to excute the code you must have OpenCV set up on your personal computer. Refer to [here](https://docs.opencv.org/master/d5/de5/tutorial_py_setup_in_windows.html) (Windows) or [here](https://medium.com/@jaskaranvirdi/setting-up-opencv-and-c-development-environment-in-xcode-b6027728003) (Mac/Linux) for OpenCV installation instructions. 
