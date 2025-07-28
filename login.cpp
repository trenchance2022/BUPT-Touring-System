
#include "login.h"
#include "ui_login.h"
#include "login_page.h"
#include "functionselectpage.h"

#include <QDebug>
#include <QMessageBox>

login::login(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::login)
{
    ui->setupUi(this);
}

login::~login()
{
    delete ui;
}

void login::on_btn_login_clicked()
{
    //从ui界面获取用户输入的账号密码
    string account = ui->username->text().toStdString();
    string password = ui->password->text().toStdString();

    if(isAccountExists(account)){//检测账户是否存在
        if(validatePassword(account, password)){//如果账户存在，检测密码是否匹配
            //登录成功
            QMessageBox::information(this, tr("登录成功"), tr("成功登录"), QMessageBox::Ok);
            this->hide();
            FunctionSelectPage *w = new FunctionSelectPage(nullptr, account);//打开功能选择界面
            w->show();
            connect(w, &FunctionSelectPage::quit_function, this, &login::show);
        } else{//如果密码不匹配，提示错误
            QMessageBox::warning(this,tr("登录失败"),tr("用户名或密码输入错误！"),QMessageBox::Ok);
            ui->username->clear();
            ui->password->clear();
            ui->username->setFocus();
        }
    } else{//如果账户不存在
        createAccount(account, password);//根据输入的账户密码创建一个新账户
        //登录成功
        QMessageBox::information(this, tr("注册成功"), tr("成功注册"), QMessageBox::Ok);
        this->hide();
        FunctionSelectPage *w = new FunctionSelectPage(nullptr, account);//打开功能选择界面
        w->show();
        connect(w, &FunctionSelectPage::quit_function, this, &login::show);
    }
}
