// The main function of the application.

// Copyright (C) 2011-2020 Stavros Filippidis
// Contact: sfilippidis@gmail.com

// This file is part of QGreatstWeightCalculator.

// QGreatstWeightCalculator is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// QGreatstWeightCalculator is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with QGreatstWeightCalculator.  If not, see <http://www.gnu.org/licenses/>.

#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{    
    QApplication application(argc, argv);
    application.setApplicationName(QString::fromWCharArray(L"QGreatstWeightCalculator"));
    application.setQuitOnLastWindowClosed(true);
    MainWindow window;
    window.show();
    return application.exec();
} // int main(int argc, char *argv[])
