#! /usr/bin/env bash

$EXTRACTRC `find . -name \*.ui -o -name \*.rc -o -name \*.kcfg` >> rc.cpp
$XGETTEXT `find . -name \*.cpp -o -name \*.qml` -o $podir/systemsettings.pot
rm -f rc.cpp
