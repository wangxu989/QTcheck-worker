#!/bin/bash
scp ./build-createtab-imx6dq_qt5_6-Release/Qrcode root@192.168.100.163:/opt/spc-arm/

scp ./build-mainwindow-imx6dq_qt5_6-Release/mainwindow root@192.168.100.163:/opt/spc-arm/plugin/

scp ./build-program2-imx6dq_qt5_6-Release/program2 root@192.168.100.163:/opt/spc-arm/plugin/

scp ./build-start_work-imx6dq_qt5_6-Release/start_work root@192.168.100.163:/opt/spc-arm/plugin/
