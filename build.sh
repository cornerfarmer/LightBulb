if [ -d "wxwidgets-cache" ]; then
	cd wxwidgets-cache/build-gtk
else
	git clone https://github.com/wxWidgets/wxWidgets.git wxwidgets
	cd wxwidgets  
	git reset --hard v3.1.0
	mkdir build-gtk
	cd build-gtk
	../configure --disable-shared --enable-unicode
	make --silent
fi
sudo make install
cd ../..

exit 0