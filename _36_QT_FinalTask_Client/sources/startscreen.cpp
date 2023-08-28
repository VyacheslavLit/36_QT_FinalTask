#include "startscreen.h"
#include "ui_startscreen.h"
#include <QMessageBox>

StartScreen::StartScreen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StartScreen)
{
    ui->setupUi(this);
    connect(ui->login_widget, &LoginForm::registerRequested, this, &StartScreen::setRegistrationForm);
    connect(ui->login_widget, &LoginForm::accepted, this, &StartScreen::onLoggedIn);
    connect(ui->login_widget, &LoginForm::rejected, this, &StartScreen::onRejectRequested);
    connect(ui->register_widget, &RegistrationForm::loginRequested, this, &StartScreen::setLoginForm);
    connect(ui->register_widget, &RegistrationForm::accepted, this, &StartScreen::onLoggedIn);
    connect(ui->register_widget, &RegistrationForm::rejected, this, &StartScreen::onRejectRequested);


    ui->login_widget;
    ui->register_widget;
}

StartScreen::~StartScreen()
{
    delete ui;
}

void StartScreen::setLoginForm()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void StartScreen::setRegistrationForm()
{
    ui->stackedWidget->setCurrentIndex(0);
}

int StartScreen::userId() const
{
    return m_userId;
}

const QString &StartScreen::userName() const
{
    return m_userName;
}

void StartScreen::onLoggedIn(uint userId, QString userName)
{
    m_userId = userId;
    m_userName = userName;
    accept();
}

void StartScreen::onRejectRequested()
{
    reject();
}
