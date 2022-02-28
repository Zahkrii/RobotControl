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

private slots:
    void on_standButton_clicked();

    void on_SettingsButton_clicked();

    void on_connectButton_clicked();

    void setButtonsEnabled();

    void on_upButton_clicked();

    void on_downButton_clicked();

    void on_upButton_pressed();

    void on_upButton_released();

    void on_rightButton_pressed();

    void on_rightButton_released();

    void on_downButton_pressed();

    void on_downButton_released();

    void on_leftButton_pressed();

    void on_leftButton_released();

    void on_action1Button_clicked();

    void on_action2Button_clicked();

    void on_action3Button_clicked();

    void on_rightButton_clicked();

    void on_leftButton_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
