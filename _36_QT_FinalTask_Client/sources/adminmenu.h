#ifndef ADMINMENU_H
#define ADMINMENU_H

#include <QWidget>
#include <memory>

namespace Ui {
class AdminMenu;
}

class AdminMenu : public QWidget
{
    Q_OBJECT

public:
    explicit AdminMenu(QString username, QWidget *parent = nullptr);
    ~AdminMenu();

private slots:
    void showUsers();
    void on_buttonBox_accepted();
    void on_UserList_clicked(const QModelIndex &index);
    void on_ban_btn_clicked();

private:
    QString current;
    QString current_user;
    Ui::AdminMenu *ui;
};

#endif // ADMINMENU_H
