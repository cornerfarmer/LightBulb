# How to install wxWidgets

## Get version 3.1 (e.q from github)

```bash
git clone https://github.com/wxWidgets/wxWidgets.git wxwidgets
cd wxwidgets  
git reset --hard v3.1.0
```

## Configure:

```bash
mkdir build-gtk
cd build-gtk
```

### Static:

```bash
../configure --disable-shared --enable-unicode
```

### Or shared:

```bash
../configure --enable-shared --enable-unicode
```

## Build it!

```bash
make
make install
```

Thats it! Now you are ready for building LightBulb.