#ifndef REGISTRATIONFORM_H
#define REGISTRATIONFORM_H

#include <QWidget>
#include <memory>

namespace Ui {
class RegistrationForm;
}

class RegistrationForm : public QWidget
{
    Q_OBJECT

public:
    explicit RegistrationForm(QWidget *parent = nullptr);
    ~RegistrationForm();

signals:
    void loginRequested();
    void accepted(int userId, QString userName);
    void rejected();

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
    void on_loginRequest_button_clicked();

private:
    Ui::RegistrationForm *ui;
};

#endif // REGISTRATIONFORM_H
