#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , operationStack{}
{
    ui->setupUi(this);
    connect(ui->zeroButton, &QPushButton::pressed, this, &MainWindow::numberButtonPressed);
    connect(ui->oneButton, &QPushButton::pressed, this, &MainWindow::numberButtonPressed);
    connect(ui->twoButton, &QPushButton::pressed, this, &MainWindow::numberButtonPressed);
    connect(ui->threeButton, &QPushButton::pressed, this, &MainWindow::numberButtonPressed);
    connect(ui->fourButton, &QPushButton::pressed, this, &MainWindow::numberButtonPressed);
    connect(ui->fiveButton, &QPushButton::pressed, this, &MainWindow::numberButtonPressed);
    connect(ui->sixButton, &QPushButton::pressed, this, &MainWindow::numberButtonPressed);
    connect(ui->sevenButton, &QPushButton::pressed, this, &MainWindow::numberButtonPressed);
    connect(ui->eightButton, &QPushButton::pressed, this, &MainWindow::numberButtonPressed);
    connect(ui->nineButton, &QPushButton::pressed, this, &MainWindow::numberButtonPressed);
    connect(ui->dotButton, &QPushButton::pressed, this, &MainWindow::numberButtonPressed);

    connect(ui->plusButton, &QPushButton::pressed, this, &MainWindow::mathButtonPressed);
    connect(ui->minusButton, &QPushButton::pressed, this, &MainWindow::mathButtonPressed);
    connect(ui->divideButton, &QPushButton::pressed, this, &MainWindow::mathButtonPressed);
    connect(ui->multiButton, &QPushButton::pressed, this, &MainWindow::mathButtonPressed);
    connect(ui->moduloButton, &QPushButton::pressed, this, &MainWindow::mathButtonPressed);

    connect(ui->equalsButton, &QPushButton::pressed, this, &MainWindow::getResult);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::numberButtonPressed()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (button->text() == "." && ui->resultOutput->text().contains("."))
            return;
    if (ui->resultOutput->text() == "0" && button->text() != ".")
        ui->resultOutput->setText(button->text());
    else
        ui->resultOutput->setText(ui->resultOutput->text() + button->text());
}

void MainWindow::mathButtonPressed()
{
    bool ok;
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    ui->memoryLabel->setText(ui->resultOutput->text());
    if (newCalc)
        firstNumber = ui->resultOutput->text().toDouble(&ok);

    if (!ok)
        return;

    // continious operations
    if (!operationStack.empty())
    {
        directCall = false;
        getResult();
        directCall = true;
    }

    // single operation
    if (button->text() == "+")
    {
        operationStack.push_back(Operations::PLUS);
        ui->memoryLabel->setText(ui->memoryLabel->text() + " + ");
        ui->resultOutput->clear();
    }
    else if (button->text() == "-")
    {
        operationStack.push_back(Operations::MINUS);
        ui->memoryLabel->setText(ui->memoryLabel->text() + " - ");
        ui->resultOutput->clear();
    }
    else if (button->text() == "X")
    {
        operationStack.push_back(Operations::MULTI);
        ui->memoryLabel->setText(ui->memoryLabel->text() + " * ");
        ui->resultOutput->clear();
    }
    else if (button->text() == "÷")
    {
        operationStack.push_back(Operations::DIVIDE);
        ui->memoryLabel->setText(ui->memoryLabel->text() + " / ");
        ui->resultOutput->clear();
    }
    else if (button->text() == "%")
    {
        operationStack.push_back(Operations::MODULO);
        ui->memoryLabel->setText(ui->memoryLabel->text() + " % ");
        ui->resultOutput->clear();
    }
    qDebug() << operationStack;
}

void MainWindow::getResult()
{
    if (operationStack.empty())
        return;
    bool ok;
    ui->memoryLabel->setText(ui->memoryLabel->text() + ui->resultOutput->text());
    secondNumber = ui->resultOutput->text().toDouble(&ok);
    if (!ok)
        return;

    Operations current = operationStack.back();
    switch (current)
    {
    case Operations::PLUS:
        result = firstNumber + secondNumber;
        break;
    case Operations::MINUS:
        result = firstNumber - secondNumber;
        break;
    case Operations::MULTI:
        result = firstNumber * secondNumber;
        break;
    case Operations::DIVIDE:
        result = firstNumber / secondNumber;
        break;
    case Operations::MODULO:
        result = std::fmod(firstNumber, secondNumber);
        break;
    }

    if (!directCall)
    {
        newCalc = false;
        firstNumber = result;
        ui->memoryLabel->setText(QString::number(firstNumber));
        return;
    }
    ui->memoryLabel->setText(ui->memoryLabel->text() + " = ");
    ui->resultOutput->setText(QString::number(result));
    operationStack.clear();
    newCalc = true;
}

