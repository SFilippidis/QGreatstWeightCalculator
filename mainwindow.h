// Header file for the main window.

// Copyright (C) 2011-2017 Stavros Filippidis
// Contact: stavros@filippidis.name

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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QFile>
#include <QDateTime>

void displayInformationMessage(QString infoText, QString title);

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    Ui::MainWindow *m_ui;
    bool m_doesDataFileExist;
    void populate_history();
    void create_history();
private slots:
    void on_pushButtonExit_clicked();
    void about();
    void on_pushButtonSave_clicked();
    void on_pushButtonCalculate_clicked();
    void on_pushButtonResetData_clicked();
};

#endif // MAINWINDOW_H
