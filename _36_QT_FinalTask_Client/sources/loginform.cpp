#include "loginform.h"
#include "ui_loginform.h"
#include "client.h"
#include <QMessageBox>

LoginForm::LoginForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginForm)
{
    ui->setupUi(this);
}

LoginForm::~LoginForm()
{
    delete ui;
}


void LoginForm::on_register_button_clicked()
{
    emit registerRequested();
}

void LoginForm::on_buttonBox1_accepted()
{
    std::string me_;
    std::string mes_cl ="l"+ui->LoginEdit->text().toStdString()+" "+ui->PasswordEdit->text().toStdString();
    std::string tmp=client(mes_cl);
    for (int i = 0; i < tmp.length(); ++i)
    {
        if (tmp[i] == 0) break;
        me_ += tmp[i];
    }
    if (me_[0]=='0')
    {
        QMessageBox::critical(this, tr("error"), tr("Password is wrong"));
        return;
    }
    if (me_[0]=='b')
    {
        QMessageBox::critical(this, tr("error"), tr("User is banned. Sorry."));
        return;
    }
    if (me_=="")
    {
        QMessageBox::critical(this, tr("error"), tr("Communication with the server failed, please try again."));
        return;
    }
    emit accepted(/*userId*/1, ui->LoginEdit->text());
}

void LoginForm::on_buttonBox1_rejected()
{
    emit rejected();
}
