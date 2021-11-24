# ➰ Catmull-Rom Splines

**Catmull-Rom Splines interpolaltion coded in C++ by Luc PREVOST.**

![DS_splines](https://user-images.githubusercontent.com/52052772/143148529-8ae15b05-7f18-412c-8920-01b144027902.png)

📃 INSTRUCTIONS
============
## 🚀Execution
Catmull-Rom-Splines uses the folowing Libraries:
- [Chono](https://www.cplusplus.com/reference/chrono/)
- [Glut](https://www.opengl.org/resources/libraries/glut/glut_downloads.php)
- [Iostream](https://www.cplusplus.com/reference/iostream/)
- [List](https://www.cplusplus.com/reference/list/list/)
- [Stdexcept](https://www.cplusplus.com/reference/stdexcept/)
 
To execute it, compile the _Catmull-Rom-Splines.cpp_ file and run it. After launching the program, a black window pops up.

## ⚙️Usage
To start, click wherever you want on the screen to place the first point. After that, the window turns white. Continue placing points and the curve will appear as things progress. To close a curve, click on the starting point. When a curve is closed, a small animation operates. Then, it is possible to create another curve by repeating the same process as before. It is possible to suppress a point on the current curve by right-clicking on it. Finally, one can animate the view by clicking on the middle button.

## 🪡Interpolation
The interpolation is done with [Catmull-Rom splines](https://en.wikipedia.org/wiki/Cubic_Hermite_spline#Catmull%E2%80%93Rom_spline). The code enables both [centripetal](https://en.wikipedia.org/wiki/Centripetal_Catmull%E2%80%93Rom_spline) and uniform case. The default method is centripetal, but it can be changed by commenting the centripedal section and uncommenting the uniform section.

Now it is your turn to draw nice shapes !

Thank you for using Catmull-Rom Splines 🙂

> Just interpolate !
