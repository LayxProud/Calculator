#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    enum Operations {
        PLUS = 0,
        MINUS,
        DIVIDE,
        MULTI,
        MODULO
    };

private:
    Ui::MainWindow *ui;
    double firstNumber;
    double secondNumber;
    double result;
    bool directCall = true;
    bool newCalc = true;
    std::vector<Operations> operationStack;

private slots:
    void numberButtonPressed();
    void mathButtonPressed();
    void getResult();

};
#endif // MAINWINDOW_H
