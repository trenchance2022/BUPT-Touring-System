
#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>



QT_BEGIN_NAMESPACE
namespace Ui { class login; }
QT_END_NAMESPACE

class login : public QWidget

{
    Q_OBJECT

public:
    login(QWidget *parent = nullptr);
    ~login();

private slots:
    void on_btn_login_clicked();

private:
    Ui::login *ui;
};

#endif // LOGIN_H
