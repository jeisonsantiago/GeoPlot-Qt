# GeoPlot
A simple ploting tool with a worldmap, rulers and title using **QGraphicsView** and **QGraphicsSene** from **Qt**.  
You could even export the viewport as SVG(testing) and PNG.

# Motivation
I was tired of using big bloated vizualizer tools, they are really nice but I just need something 
simple to plot wind trajectories.

# Installation
Just clone and open the project file with **QtCreator**, have fun!

# Usage
The fastest way is just copy these files to your project:

*GeoGraphicsView.h*  
*GeoGraphicsView.cpp*  
*GeoScene.h*  
*GeoScene.cpp*  
*ItemGroup.h*  
*ItemGroup.cpp*  
*countries.kml*  
*states_low.kml*

and make sure that you point to the right directory  
when loading the kmz files.

```cpp
// start geo view
GeoGraphicsView *geoview = new GeoGraphicsView(this);

// load kmz files
geoview->loadKmz(":Resources/countries.kml",true);
geoview->loadKmz(":Resources/states_low.kml",false,3.5,1000000,false);

this->setCentralWidget(geoview);
```
and check the example project to see the details.

# Note
Feel free to use it, this is a relative new project and I am still learning Qt and C++.\
Any questions mail me: jeison.santiago at gmail.com

# Screenshots
GeoView example  
<img src="/home/magat5u/Desktop/QT_NEW_TESTS/GEOPLOT/img/geoview_noborder.png" alt="Drawing" style="width: 80%;"/></br>

GeoView example with the border on, so you could export nice figures ;)
<img src="/home/magat5u/Desktop/QT_NEW_TESTS/GEOPLOT/img/geoview_border.png" alt="Drawing" style="width: 80%;"/></br>

# License
[The MIT License (MIT)](http://www.opensource.org/licenses/mit-license.php)

