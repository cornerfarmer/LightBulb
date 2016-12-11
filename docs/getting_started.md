# Getting started:

First of all, make sure you have [built](/docs/build.md) LightBulb correctly.

## Using only LightBulb

### Libaries to bind:

* LightBulb

### Include directories (Probably only necessary for windows)

* (LightBulbRoot)/include/
* (LightBulbRoot)/extlibs/eigen/
* (LightBulbRoot)/extlibs/cereal/include/

## Using LightBulbApp (Additional to LightBulb)

### Libaries to bind:

* LightBulbApp
* wxWidgets (core, base, richtext, adv, html, xml, aui)
* freechart

### Include directories (Probably only necessary for windows) 

* (LightBulbRoot)/extlibs/freechart/include/
* (wxWidgetsRoot)/include/
* (wxWidgetsRoot)/include/msvc

See [CMake script of LightBulbExample](example/LightBulbExample/CMakeLists.txt)
