# Arduino
Arduino sketches &amp; stuff ( old &amp; new )

### Troubles ? read the followings! ( relevant for other uC as well )

#### Can't access the serial port in the official IDE ?
-> ```sudo usermod -aG dialout <username> && sudo usermod -aG tty <username>``` ;p

#### Know if some serial port is already used by some stuff ?
-> ```lsof | grep tty.usbmodemfd1411```  
=> ```Google      730 stephanegarnier  194u     CHR      11,12        0t0      633 /dev/tty.usbmodemfd1411```

#### Get more infos on some serial port ?
-> ```ls -l /dev/tty.usbmodemfd1411```

#### List the loaded kernel extensions ( .kext ) ?
-> ```kextstat```

#### Check if FTDI kext is installed /loaded ?
-> ```ls -ld `/System/Library/Extensions/FTDIUSBSerialDriver.kext` ``` and ```kextstat | grep FTDI```  
=> ```191    0 0x844b7000 0x8000     0x7000     com.FTDI.driver.FTDIUSBSerialDriver (2.2.18) <119 34 5 4 3 1>```

#### Check if the OS has detected the USB device ?
-> go to System Profiler > Hardware > USB > the_device  
=> ex: Arduino UNO
```
Arduino Uno :

  Identifiant du produit :	0x0001
  Identifiant du fournisseur :	0x2341
  Version :	 0.01
  Numéro de série :	649343332353513092C0
  Vitesse :	Jusqu’à 12 Mb/s
  Fabricant :	Arduino (www.arduino.cc)
  Identifiant de l’emplacement :	0xfd141000 / 8
  Courant disponible (mA) :	100
  Courant requis (mA) :	100
```
=> ex: Espruino Pico
```
STM32 Virtual ComPort :

  Identifiant du produit :	0x5740
  Identifiant du fournisseur :	0x0483  (STMicroelectronics)
  Version :	 2.00
  Numéro de série :	00000000001A
  Vitesse :	Jusqu’à 12 Mb/s
  Fabricant :	STMicroelectronics
  Identifiant de l’emplacement :	0xfa144000 / 9
  Courant disponible (mA) :	500
  Courant requis (mA) :	100
```
-> record PID & VID & convert them to decimal ( convert base 16 into base 10 for each of the two numbers )  
-> ```dc -e "16i the_PID p the_VID p"```  
-> ex: dc -e "16i 0001 p 2341 p" for the above device, which renders: PID: 1 & VID: 9025  

#### Look for some product in a driver ?
-> ```cd /System/Library/Extensions/FTDIUSBSerialDriver.kext/Contents/```& then search the Info.plist for PID/VID  
-> each device is grouped in a section within a <dict> with "CFBundleIdentifier" == "com.FTDI.driver.FTDIUSBSerialDriver"  
-> if we find the device, we can try to unload/load the driver, else, we way be up to add a new device config  

#### Add a new device config to the a .kext Info.plist ?
-> ```cp Info.plist Info.plist.ORIG``` to make a backup of the Info.plist  
-> find the first or last entry in the <dict>  & add a custom entry
-> choose one in the list as a template, or use one of the followings as a model, and then add it to the Info.plist  
=> simplest template:
```
<key>My Awesome Device</key>
		<dict>
			<key>CFBundleIdentifier</key>
			<string>com.FTDI.driver.FTDIUSBSerialDriver</string>
			<key>IOClass</key>
			<string>FTDIUSBSerialDriver</string>
			<key>IOProviderClass</key>
			<string>IOUSBInterface</string>
			<key>bConfigurationValue</key>
			<integer>1</integer>
			<key>bInterfaceNumber</key>
			<integer>0</integer>
			<key>idProduct</key>
			<integer>44084</integer>
			<key>idVendor</key>
			<integer>2134</integer>
		</dict>
```
=> template with two entries ( for devices that provides more than one serial port ), see their "bInterfaceNumber":
```
<key>My Awesome Device 1</key>
		<dict>
			<key>CFBundleIdentifier</key>
			<string>com.FTDI.driver.FTDIUSBSerialDriver</string>
			<key>IOClass</key>
			<string>FTDIUSBSerialDriver</string>
			<key>IOProviderClass</key>
			<string>IOUSBInterface</string>
			<key>bConfigurationValue</key>
			<integer>1</integer>
			<key>bInterfaceNumber</key>
			<integer>0</integer>
			<key>idProduct</key>
			<integer>44084</integer>
			<key>idVendor</key>
			<integer>2134</integer>
		</dict>
<key>My Awesome Device 2</key>
		<dict>
			<key>CFBundleIdentifier</key>
			<string>com.FTDI.driver.FTDIUSBSerialDriver</string>
			<key>IOClass</key>
			<string>FTDIUSBSerialDriver</string>
			<key>IOProviderClass</key>
			<string>IOUSBInterface</string>
			<key>bConfigurationValue</key>
			<integer>1</integer>
			<key>bInterfaceNumber</key>
			<integer>1</integer>
			<key>idProduct</key>
			<integer>44084</integer>
			<key>idVendor</key>
			<integer>2134</integer>
		</dict>
```
=> template with additional config data ( non-exhaustive / to digg before setting/using ;p ):
```
<key>My Awesome Device</key>
		<dict>
			<key>CFBundleIdentifier</key>
			<string>com.FTDI.driver.FTDIUSBSerialDriver</string>
			<key>ConfigData</key>
			<dict>
				<key>BaudRates</key>
				<dict>
					<key>BAUDALL</key>
					<string>9600</string>
					<key>B115200</key>
					<string>115200</string>
				</dict>
				<key>PortName</key>
				<string>MiniPlex</string>
				<key>InBufferSize</key>
				<integer>128</integer>
				<key>LatencyTimer</key>
				<integer>2</integer>
				<key>MIDI</key>
				<false/>
			</dict>
			<key>IOClass</key>
			<string>FTDIUSBSerialDriver</string>
			<key>IOProviderClass</key>
			<string>IOUSBInterface</string>
			<key>bConfigurationValue</key>
			<integer>1</integer>
			<key>bInterfaceNumber</key>
			<integer>0</integer>
			<key>idProduct</key>
			<integer>44084</integer>
			<key>idVendor</key>
			<integer>2134</integer>
		</dict>
```

#### Check if a .kext is already loaded or unload/load one ?
-> ```kextstat |grep FTDI``` to check if loaded ( if it returns anything, unloading it / rebooting are our choices )  
-> ```kextunload /System/Library/Extensions/FTDIUSBSerialDriver.kext``` to unload ( can fail, so look for "success")  
-> ```kextload /System/Library/Extensions/FTDIUSBSerialDriver.kext``` to load it ( as root or sudo )  
-> ```kextstat |grep FTDI``` again, to check if it has loaded
