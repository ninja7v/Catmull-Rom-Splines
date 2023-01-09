# ➰ Catmull-Rom Splines

**Catmull-Rom Splines interpolaltion coded in C++ by Luc PREVOST.**

![Jeanette](https://user-images.githubusercontent.com/52052772/211431297-2115765a-b592-4b2d-a070-41f17d56807e.gif)

📃 INSTRUCTIONS
============
## 🚀Execution
Catmull-Rom-Splines uses the folowing Libraries:
- [Chono](https://www.cplusplus.com/reference/chrono/)
- [Glut](https://www.opengl.org/resources/libraries/glut/glut_downloads.php)
- [Iostream](https://www.cplusplus.com/reference/iostream/)
- [List](https://www.cplusplus.com/reference/list/list/)
- [Stdexcept](https://www.cplusplus.com/reference/stdexcept/)
 
To execute it, compile the _Catmull-Rom-Splines.cpp_ file and run it. After launching the program, a white window pops up.

## ⚙️Usage
To start, click wherever you want on the screen to place the first point. Continue placing points and the curve will appear as things progress. To close a curve, click on the starting point. When a curve is closed, a small animation operates. Then, it is possible to create another curve by repeating the same process as before. It is possible to reset the current curve by right-clicking on it. Finally, one can animate the view by clicking on the middle button.

## 🪡Interpolation
The interpolation is done with [Catmull-Rom splines](https://en.wikipedia.org/wiki/Cubic_Hermite_spline#Catmull%E2%80%93Rom_spline). The code enables both [centripetal](https://en.wikipedia.org/wiki/Centripetal_Catmull%E2%80%93Rom_spline) and uniform case. The default method is centripetal, but it can be changed by commenting the centripedal section and uncommenting the uniform section.

Now it is your turn to draw nice shapes !

Thank you for using Catmull-Rom Splines 🙂

> Just interpolate !
