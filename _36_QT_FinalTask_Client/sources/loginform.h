#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <QWidget>
#include <memory>

namespace Ui {
class LoginForm;
}

class LoginForm : public QWidget
{
    Q_OBJECT

public:
    explicit LoginForm(QWidget *parent = nullptr);
    ~LoginForm();

signals:
    void registerRequested();
    void accepted(int userId, QString userName);
    void rejected();

private slots:
    void on_register_button_clicked();
    void on_buttonBox1_accepted();
    void on_buttonBox1_rejected();

private:
    Ui::LoginForm *ui;
};

#endif // LOGINFORM_H
