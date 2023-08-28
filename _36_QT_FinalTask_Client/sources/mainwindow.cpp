#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "startscreen.h"
#include "client.h"
#include <QDialog>
#include <QVBoxLayout>
#include <QDialogButtonBox>
#include <QListWidget>
#include <QTimer>

int MainWindow::kInstanceCount = 0;

MainWindow::MainWindow(int userId, QString userName, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_userId(userId),
    m_userName(userName)
{
    ui->setupUi(this);
    kInstanceCount++;
    auto timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateChats);
    timer->start(100);
    admin_menu = new AdminMenu(userName);
    if (m_userName != "admin")
    {
        ui->actionAdmin_menu->setDisabled(true);
        ui->actionAdmin_menu->setVisible(false);
    }
    else
    {
        ui->actionAdmin_menu->setDisabled(false);
        ui->actionAdmin_menu->setVisible(true);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
    kInstanceCount--;
    if(kInstanceCount <= 0)
        qApp->exit(0);
}

MainWindow *MainWindow::createClient()
{
    StartScreen s;
    auto result = s.exec();
    if (result == QDialog::Rejected)
    {
        return nullptr;
    }
    auto w = new MainWindow(s.userId(), s.userName());
    w->setAttribute(Qt::WA_DeleteOnClose);
    return w;
}

void MainWindow::on_sendmsg_button_clicked()
{
    client("d" + m_userName.toStdString() + "+" + ui->messageEdit->text().toStdString());
}

void MainWindow::on_actionOpen_another_Client_triggered()
{
    auto w = createClient();
    if(w)
        w->show();
}

void MainWindow::on_actionClose_this_Client_triggered()
{
    this->close();
}

void MainWindow::on_privatemsg_button_clicked()
{
    QDialog dial(this);
      dial.setModal(true);
      auto l = new QVBoxLayout();
      dial.setLayout(l);
      auto userListWgt = new QListWidget(&dial);

      l->addWidget(userListWgt);
      auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &dial);
      l->addWidget(buttonBox);

      connect(buttonBox, &QDialogButtonBox::accepted, &dial, &QDialog::accept);
      connect(buttonBox, &QDialogButtonBox::rejected, &dial, &QDialog::reject);

      auto tmp=client("y");
      std::string tmp1="";
      for(int i=0;i<(int)tmp.length();i++)
      {
        if (tmp[i]!=' ')
        {
            tmp1+=tmp[i];
            continue;
        }
        userListWgt->addItem(QString::fromStdString(tmp1));
        tmp1="";
      }

      userListWgt->setCurrentRow(0);

      auto result = dial.exec();

      if(result == QDialog::Accepted &&
         userListWgt->currentItem())
      {
        client("q" + m_userName.toStdString() + " " + userListWgt->currentItem()->text().toStdString() + " " + ui->messageEdit->text().toStdString());
      }
}

void MainWindow::updateChats()
{
    QString chat;
    chat.clear();
    chat = QString::fromStdString(client("m"));

    if (ui->CommonBrowser->toPlainText() != chat)
        ui->CommonBrowser->setText(chat);

    chat.clear();
    chat = QString::fromStdString(client("j" + m_userName.toStdString()));
    if (ui->PrivateBrowser->toPlainText() != chat)
        ui->PrivateBrowser->setText(chat);
}

void MainWindow::on_actionAdmin_menu_triggered()
{
    admin_menu->show();
}

