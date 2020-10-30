#!/bin/bash
scp ./killall.sh root@192.168.100.$1:/opt/spc-arm/killall.sh

scp ./build-createtab-imx6dq_qt5_6-Release/Qrcode root@192.168.100.$1:/opt/spc-arm/Qrcode


scp ./build-mainwindow-imx6dq_qt5_6-Release/mainwindow root@192.168.100.$1:/opt/spc-arm/plugin/

scp ./build-program2-imx6dq_qt5_6-Release/program2 root@192.168.100.$1:/opt/spc-arm/plugin/

scp ./build-start_work-imx6dq_qt5_6-Release/start_work root@192.168.100.$1:/opt/spc-arm/plugin/

#scp ./build-createtab-imx6dq_qt5_6-Release/data/GeneralConfig.xml root@192.168.100.163:/opt/spc-arm/data/

