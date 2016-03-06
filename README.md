# Arduino
Arduino sketches &amp; stuff ( old &amp; new )

### Can't access the serial port in the official IDE ?
-> ```sudo usermod -aG dialout <username> && sudo usermod -aG tty <username>``` ;p

### Wana know if some serial port is already used by some stuff ?
-> ```lsof | grep tty.usbmodemfd1411```

### Wana get more infos on some serial port ?
-> ```ls -l /dev/tty.usbmodemfd1411```

### Wana list the loaded kernel extensions ( .kext ) ?
-> ```kextstat```

### Wana check if FTDI kext is installed /loaded ?
-> ```ls -ld `/System/Library/Extensions/FTDIUSBSerialDriver.kext` ``` and ```kextstat | grep FTDI```

### Wana check if the OS has detected the USB device ?
-> go to System Profiler > Hardware > USB > the_device
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
-> record PID & VID & convert them to decimal ( convert base 16 into base 10 for each of the two numbers )  
-> ```dc -e "16i the_PID p the_VID p"```  
-> ex: dc -e "16i 0001 p 2341 p" for the above device, which renders: PID: 1 & VID: 9025  

### Wana look for some product in a driver ?
-> ```cd /System/Library/Extensions/FTDIUSBSerialDriver.kext/Contents/```& then search the Info.plist for PID/VID  
-> each device is grouped in a section within a <dict> with "CFBundleIdentifier" == "com.FTDI.driver.FTDIUSBSerialDriver"  
-> if we find the device, we can try to unload/load the driver, else, we way be up to add a new device config  

### Wana add a new device config the a .kext Info.plist ?
-> ``````

### Wana check if .kext already loaded or unload/load one ?
-> ```kextstat |grep FTDI``` to check if loaded ( if it returns anything, unloading it / rebooting are our choices )  
-> ```kextunload /System/Library/Extensions/FTDIUSBSerialDriver.kext``` to unload ( can fail, so look for "success")  
-> ```kextload /System/Library/Extensions/FTDIUSBSerialDriver.kext``` to load it ( as root or sudo )  
-> ```kextstat |grep FTDI``` again, to check if it has loaded
