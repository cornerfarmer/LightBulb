# Build

## Parts of LightBulb

### LightBulb

* The LightBulb core
* Includes everything necessary for learning
* Includes serialization
* Dependencies: eigen, cereal (build automatically)

### LightBulbApp

* A GUI for LightBulb
* Can be used to monitor and manage the learning process
* Dependencies: LightBulb, wxFreechart, wxWidgets (You have to install wxWidgets by yourself, see [how](/docs/wxwidgets.md))

### LightBulbExample

* An example application which uses LightBulb and LightBulbApp
* Includes multiple example learning problems
* Dependencies: LightBulb, LightBulbApp

### UnitTests

* Just a bunch of unit tests for LightBulb
* Dependencies: LightBulb

## CMake

Basic usage: 

```bash
mkdir build
cd build
cmake ..
```

Available options:

* BUILD_SHARED_LIBS: Detemines if the libs should be build statically or shared (ON or OFF, default: OFF)
* EnableLightBulbApp: ON, if LightBulbApp should be build (ON or OFF, default: ON)
* EnableLightBulbExample: ON, if LightBulbExample should be build (ON or OFF, default: ON)
* EnableUnitTests: ON, if UnitTests should be build (ON or OFF, default: OFF)
* wxWidgets_ROOT_DIR: Sets the root directory of your wxWidgets installation (default: auto search)

Example usage

```bash
cmake .. -DEnableLightBulbApp=OFF -DEnableLightBulbExample=OFF
```

This would just build the LightBulb core.


## Build it:

```bash
make
sudo make install
```

Now LightBulb and LightBulbApp are installed to your default library directories.

LightBulbExample is ready to use:

```bash
example/LightBulbExample/LightBulbExample
```
