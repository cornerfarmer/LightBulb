if [ -d wxwidgets/build-gtk ]; then
	cd wxwidgets/build-gtk
else
	git clone https://github.com/wxWidgets/wxWidgets.git wxwidgets
	cd wxwidgets  
	git reset --hard v3.1.0
	mkdir build-gtk
	cd build-gtk
	if [ "$SHARED" = "OFF" ]
		../configure --disable-shared --enable-unicode
	else
		../configure --enable-shared --enable-unicode
	fi
	make --silent
fi
sudo make install
cd ../..

exit 0
