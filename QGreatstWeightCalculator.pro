#  Project file for QGreatstWeightCalculator.
#
#  Copyright (C) 2011-2021 Stavros Filippidis
#  Contact: stavros@filippidis.name
#
#  This file is part of QGreatstWeightCalculator.
#
#  QGreatstWeightCalculator is free software: you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation, either version 3 of the License, or
#  (at your option) any later version.
#
#  QGreatstWeightCalculator is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with QGreatstWeightCalculator.  If not, see <http://www.gnu.org/licenses/>.

QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TARGET = QGreatstWeightCalculator
TEMPLATE = app
SOURCES += main.cpp \
    mainwindow.cpp
HEADERS  += \
    mainwindow.h
FORMS    += \
    mainwindow.ui
mac {
    ICON = QGreatstWeightCalculator.icns
}
win32-g++ {
    RC_FILE = QGreatstWeightCalculator.rc
}
