#include "adminmenu.h"
#include "ui_adminmenu.h"
#include "client.h"

#include <QStringListModel>

AdminMenu::AdminMenu(QString username, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdminMenu)
{
    ui->setupUi(this);
    current_user = username;
    showUsers();
}

AdminMenu::~AdminMenu()
{
    delete ui;
}


void AdminMenu::showUsers()
{
    QString chat;
    auto model = new QStringListModel(this);
    QStringList list;
    auto tmp=client("y");
    std::string tmp1="";
    for(int i=0;i<(int)tmp.length();i++)
    {
        if (tmp[i]!=' ')
        {
            tmp1+=tmp[i];
            continue;
        }
        list << QString::fromStdString(tmp1);
        tmp1="";
    }
    model->setStringList(list);
    ui->UserList->setModel(model);
    ui->UserList->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void AdminMenu::on_buttonBox_accepted()
{
    this->close();
}

void AdminMenu::on_UserList_clicked(const QModelIndex &index)
{
    QString chat;
    QAbstractItemModel* model = ui->UserList->model() ;
    QString username = model->index(index.row(), 0).data( Qt::DisplayRole ).toString();
    auto tmp=client("y");
    std::string tmp1="";
    for(int i=0;i<(int)tmp.length();i++)
    {
        if (tmp[i]!=' ')
        {
            tmp1+=tmp[i];
            continue;
        }
        if (tmp1 ==  username.toStdString())
        {
            current = QString::fromStdString(tmp1);
            break;
        }
        tmp1="";
    }
    std::string ban_status = client("i" + username.toStdString());
    if(ban_status[0] != '1')
    {
        ui->ban_btn->setText(tr("Unblock user"));
    }
    else
    {
        ui->ban_btn->setText(tr("Block user"));
    }
    if (username.toStdString() == current_user.toStdString())
    {
        ui->ban_btn->setDisabled(true);
    }
    else
    {
        ui->ban_btn->setDisabled(false);
    }
}


void AdminMenu::on_ban_btn_clicked()
{
    std::string ban_status = client("i" + current.toStdString());
    if(ban_status[0]=='1')
    {
        client("o" + current.toStdString() + " " + "2");
        ui->ban_btn->setText(tr("Unblock user"));
    }
    else
    {
        client("o" + current.toStdString() + " " + "1");
        ui->ban_btn->setText(tr("Block user"));
    }
}


