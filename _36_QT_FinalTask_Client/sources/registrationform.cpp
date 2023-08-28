#include "registrationform.h"
#include "ui_registrationform.h"
#include "client.h"
#include <QMessageBox>

RegistrationForm::RegistrationForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RegistrationForm)
{
    ui->setupUi(this);
}

RegistrationForm::~RegistrationForm()
{
    delete ui;
}

void RegistrationForm::on_buttonBox_accepted()
{
    if (ui->password_edit->text() != ui->password2_edit->text())
    {
        QMessageBox::critical(this, tr("error"), tr("Passwords not match"));
        return;
    }
    std::string zapros = "r" + ui->login_edit->text().toStdString() + " ";
    zapros = zapros + ui->password_edit->text().toStdString() + " ";
    zapros = zapros + ui->nickname_edit->text().toStdString() + " ";
    zapros = zapros + ui->name_edit->text().toStdString() + " ";
    zapros = zapros + ui->family_edit->text().toStdString() + " ";
    zapros = zapros + ui->email_edit->text().toStdString();
    std::string otvet = client(zapros);
    if (otvet[0] == '1')
    {
        QMessageBox::critical(this, tr("error"), tr("Login already exists"));
        return;
    }
    if (otvet[0] == '2')
    {
        QMessageBox::critical(this, tr("error"), tr("Nickname already exists"));
        return;
    }
    emit accepted(1, ui->login_edit->text());
}

void RegistrationForm::on_buttonBox_rejected()
{
    emit rejected();
}

void RegistrationForm::on_loginRequest_button_clicked()
{
    emit loginRequested();
}

