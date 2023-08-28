#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <memory>
#include "adminmenu.h"
#include "startscreen.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(int userId, QString userName, QWidget *parent = nullptr);
    ~MainWindow();
    static MainWindow* createClient();
    static int kInstanceCount;

private slots:
    void on_sendmsg_button_clicked();
    void on_actionOpen_another_Client_triggered();
    void on_actionClose_this_Client_triggered();
    void on_privatemsg_button_clicked();
    void updateChats();
    void on_actionAdmin_menu_triggered();

private:
    Ui::MainWindow *ui;
    int m_userId;
    QString m_userName;
    AdminMenu *admin_menu;
    StartScreen *test;
};

#endif // MAINWINDOW_H
