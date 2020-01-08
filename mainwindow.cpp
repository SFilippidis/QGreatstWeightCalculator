// MainWindow's implementation.

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

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextStream>
//#include <QStandardPaths>
#include <QDir>

void displayInformationMessage(QString infoText, QString title, QMessageBox::Icon icon)
{
    QMessageBox msgBox;
#if defined(Q_OS_WIN)
    msgBox.setWindowTitle(title);
    msgBox.setText(infoText);
#else
    msgBox.setText(title);
    msgBox.setInformativeText(infoText);
#endif
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setButtonText(QMessageBox::Ok, QString::fromWCharArray(L"Ok"));
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.setIcon(icon);
    msgBox.exec();
} // void displayInformationMessage(QString infoText, QString title, QMessageBox::Icon icon)

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), m_ui(new Ui::MainWindow), m_doesDataFileExist(false)
{
    m_ui->setupUi(this);
    m_ui->pushButtonSave->setEnabled(false);
    MainWindow::populate_history();
    setUnifiedTitleAndToolBarOnMac(true);
    setWindowTitle(QString::fromWCharArray(L"QGreatstWeightCalculator"));
    connect(m_ui->actionAbout_QGreatstWeightCalculator, SIGNAL(triggered()), this, SLOT(about()));
    connect(m_ui->actionAbout_Qt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
} // MainWindow::MainWindow(QWidget *parent)

void MainWindow::populate_history()
{
    double BMIValue=0.0;
    double heightValue=0.0;
    double weightValue=0.0;
    QString genderValue;
    QString nameValue;
    QString idealWeightValue;
    QDateTime recordDateTimeValue;
    //QFile dataFile(QStandardPaths::writableLocation(QStandardPaths::HomeLocation)+"/QGreatstWeightCalculator.data");
    QFile dataFile(QDir::homePath()+"/QGreatstWeightCalculator.data");
    if(!dataFile.open(QIODevice::ReadOnly))
        return;
    m_doesDataFileExist = true;
    QDataStream in(&dataFile);
    //in.setVersion(QDataStream::Qt_DefaultCompiledVersion);
    QString dataFromFileInHTML;
    dataFromFileInHTML="<center><table border='1'><tr><td><center><b>"+QString::fromWCharArray(L"Date and time")+"</b></center></td><td><center><b>"+QString::fromWCharArray(L"Name")+"</b></center></td><td><center><b>"+QString::fromWCharArray(L"Gender")+"</b></center></td><td><center><b>"+QString::fromWCharArray(L"Height (m)")+"</b></center></td><td><center><b>"+QString::fromWCharArray(L"Weight (kg)")+"</b></center></td><td><center><b>"+QString::fromWCharArray(L"Body mass index")+"</b></center></td><td><center><b>"+QString::fromWCharArray(L"Ideal weight (kg)")+"</b></center></td></tr>";
    while (!in.atEnd())
    {
        in >> recordDateTimeValue >> nameValue >> genderValue >> heightValue >> weightValue >> BMIValue >> idealWeightValue;
        dataFromFileInHTML+="<tr><td><center>"+recordDateTimeValue.toString()+"</center></td><td><center>"+nameValue+"</center></td><td><center>"+genderValue+"</center></td><td><center>"+QString::number(heightValue,'f',2)+"</center></td><td><center>"+QString::number(weightValue,'f',2)+"</center></td><td><center>"+QString::number(BMIValue,'f',2)+"</center></td><td><center>"+idealWeightValue+"</center></td></tr>";
    } // while (!in.atEnd())
    dataFromFileInHTML+="</table></center>";
    MainWindow::m_ui->textBrowser_3->setText(dataFromFileInHTML);
    dataFile.close();
} // void MainWindow::populate_history()

void MainWindow::create_history()
{
    double weight = m_ui->doubleSpinBoxWeight->value();
    double height = m_ui->doubleSpinBoxHeight->value()/100.0;
    int gender = m_ui->comboBoxGender->currentIndex();
    QString genderText = QString::fromWCharArray(L"male");
    if (gender == 1)
        genderText = QString::fromWCharArray(L"female");
    double bmi = weight/(height*height);
    double idealWeightLow = 18.50 * height * height;
    double idealWeightHigh = 24.99999 * height * height;
    //QString filename = QStandardPaths::writableLocation(QStandardPaths::HomeLocation)+"/QGreatstWeightCalculator.data";
    QString filename = QDir::homePath()+"/QGreatstWeightCalculator.data";
    QFile dataFile(filename);
    if(!dataFile.open(QIODevice::Append))
    {
        QString datafileErrorInfoText = QString::fromWCharArray(L"File could not be opened for appending new data. Your data was not saved!");
        QString datafileErrorTitle = QString::fromWCharArray(L"Error with the results' file");
        displayInformationMessage(datafileErrorInfoText, datafileErrorTitle, QMessageBox::Critical);
        return;
    } // if(!dataFile.open(QIODevice::Append))
    QDataStream out(&dataFile);
    //out.setVersion(QDataStream::Qt_DefaultCompiledVersion);
    QString idealWeight = QString::fromWCharArray(L"from ");
    idealWeight += QString::number(idealWeightLow,'f',1);
    idealWeight += QString::fromWCharArray(L" to ");
    idealWeight += QString::number(idealWeightHigh,'f',1);
    out << QDateTime::currentDateTime() << m_ui->name->text() << genderText << height << weight << bmi << idealWeight;
    dataFile.flush();
    if (!m_doesDataFileExist)
    {
        QString writingDataInfoText = QString::fromWCharArray(L"File QGreatstWeightCalculator.data was created and your data is saved.<br><br>File QGreatstWeightCalculator.data exists in your home directory. To delete all saved data, delete the file QGreatstWeightCalculator.data.<BR><BR>This window will not appear again (in the following savings).<br><br>The location of the file is:<BR><BR>");
        writingDataInfoText += filename;
        QString writingDataTitle = QString::fromWCharArray(L"Data file created");
        displayInformationMessage(writingDataInfoText, writingDataTitle, QMessageBox::Information);
    } // if (!m_doesDataFileExist)
} // void MainWindow::create_history()

MainWindow::~MainWindow()
{
    delete m_ui;
} // MainWindow::~MainWindow()

void MainWindow::about()
{
    QString licenceAndInfoText = QString::fromWCharArray(L"QGreatstWeightCalculator. Version 1.0.5+. A program for weight related calculations.<BR><BR>Copyright (C) 2011-2020 Stavros Filippidis<BR>email: <A HREF='mailto:sfilippidis@gmail.com'>sfilippidis@gmail.com</A><BR>www: <A HREF='https://blogs.sch.gr/sfil/'>https://blogs.sch.gr/sfil/</A><BR><BR>QGreatstWeightCalculator is free software: you can redistribute it and/or modify<BR>it under the terms of the GNU General Public License as published by<BR>the Free Software Foundation, either version 3 of the License, or<BR>(at your option) any later version.<BR><BR>QGreatstWeightCalculator is distributed in the hope that it will be useful,<BR>but WITHOUT ANY WARRANTY; without even the implied warranty of<BR>MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the<BR>GNU General Public License for more details.<BR><BR>You should have received a copy of the GNU General Public License<BR>along with QGreatstWeightCalculator.  If not, see <A HREF='http://www.gnu.org/licenses/'>http://www.gnu.org/licenses/</A>.<BR>");
    QString licenceTitle = "About QGreatstWeightCalculator";
    displayInformationMessage(licenceAndInfoText, licenceTitle, QMessageBox::NoIcon);
} // void MainWindow::about()

void MainWindow::on_pushButtonResetData_clicked()
{
    m_ui->name->setText(QString::fromWCharArray(L""));
    m_ui->doubleSpinBoxWeight->setValue(80.0);
    m_ui->doubleSpinBoxHeight->setValue(180.0);
    m_ui->doubleSpinBoxAge->setValue(40.0);
    m_ui->results->setText(QString::fromWCharArray(L"Results will appear here!"));
    m_ui->comboBoxGender->setCurrentIndex(0);
    m_ui->comboBoxActivity->setCurrentIndex(0);
    m_ui->pushButtonSave->setEnabled(false);
} // void MainWindow::on_pushButtonResetData_clicked()

void MainWindow::on_pushButtonCalculate_clicked()
{
    double weight = m_ui->doubleSpinBoxWeight->value();
    double height = m_ui->doubleSpinBoxHeight->value()/100.0;
    double age = m_ui->doubleSpinBoxAge->value();
    int gender = m_ui->comboBoxGender->currentIndex();
    int activity = m_ui->comboBoxActivity->currentIndex();
    double bmi = weight/(height*height);
    double idealWeightLow = 18.50 * height * height;
    double idealWeightHigh = 24.99999 * height * height;
    QString results = QString::fromWCharArray(L"Here are your results (approximately):<br>");
    results += QString::fromWCharArray(L"<ul><li>Your body mass index is <b>");
    results += QString::number(bmi,'d',2);
    results += QString::fromWCharArray(L"</b>, so your standard weight status category is <b>\"");
    if (bmi < 18.5)
        results += QString::fromWCharArray(L"underweight");
    else if ((bmi >= 18.5) && (bmi < 25.0))
        results += QString::fromWCharArray(L"normal");
    else if ((bmi >= 25.0) && (bmi < 30.0))
        results += QString::fromWCharArray(L"overweight");
    else if (bmi >= 30.0)
        results += QString::fromWCharArray(L"obese");
    results += QString::fromWCharArray(L"\"</b>.</li><br>");
    results += QString::fromWCharArray(L"<li>Based on your height, your normal weight range is <b>from ");
    results += QString::number(idealWeightLow,'f',1);
    results += QString::fromWCharArray(L" to ");
    results += QString::number(idealWeightHigh,'f',1);
    results += QString::fromWCharArray(L" kg</b>.</li><br>");
    double kcal = 0.0;
    if (gender == 0)
        kcal += 66.0 + weight * 13.70 + height * 5.00 * 100.0 - age * 6.80; // 0 == male
    else
        kcal += 655.0 + weight * 9.60 + height * 1.80 * 100.0 - age * 4.70; // 1 == female
    switch (activity)
    {
        case 0:
            // no change in kcal!
            break;
        case 1:
            kcal *= 1.20;
            break;
        case 2:
            kcal *= 1.375;
            break;
        case 3:
            kcal *= 1.55;
            break;
        case 4:
            kcal *= 1.725;
            break;
        case 5:
            kcal *= 1.90;
            break;
    } // switch (activity)
    results += QString::fromWCharArray(L"<li> Based on the data you entered, to maintain your current weight you need <b>");
    results += QString::number((kcal),'f',2);
    results += QString::fromWCharArray(L" Calories (kCal)</b> per day.</li>");
    m_ui->results->setText(results);
    m_ui->pushButtonSave->setEnabled(true);
} // void MainWindow::on_pushButtonCalculate_clicked()

void MainWindow::on_pushButtonSave_clicked()
{
    MainWindow::create_history();
    m_ui->pushButtonSave->setEnabled(false);
    MainWindow::on_pushButtonResetData_clicked();
    MainWindow::populate_history();
} // void MainWindow::on_pushButtonSave_clicked()

void MainWindow::on_pushButtonExit_clicked()
{
    QApplication::quit();
} // void MainWindow::on_pushButtonExit_clicked()
