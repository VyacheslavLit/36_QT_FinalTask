#ifndef STARTSCREEN_H
#define STARTSCREEN_H

#include <QDialog>
#include <memory>

namespace Ui {
class StartScreen;
}

class StartScreen : public QDialog
{
    Q_OBJECT

public:
    explicit StartScreen(QWidget *parent = nullptr);
    ~StartScreen();
    void setLoginForm();
    void setRegistrationForm();
    int user_num = 0;
    int userId() const;
    const QString &userName() const;

public slots:
    void onLoggedIn(uint userId, QString userName);
    void onRejectRequested();

private:
    Ui::StartScreen *ui;
    int m_userId;
    QString m_userName;
};

#endif // STARTSCREEN_H
