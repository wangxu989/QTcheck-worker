#!/bin/bash
export QT_QPA_EGLFS_DISABLE_INPUT=1
export QT_QPA_EGLFS_FB=/dev/fb0
/opt/spc-arm/plugin/mainwindow -platform eglfs

