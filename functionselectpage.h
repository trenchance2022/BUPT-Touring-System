#ifndef FUNCTIONSELECTPAGE_H
#define FUNCTIONSELECTPAGE_H

#include <QWidget>
#include <iostream>

namespace Ui {
class FunctionSelectPage;
}

class FunctionSelectPage : public QWidget
{
    Q_OBJECT

public:
    explicit FunctionSelectPage(QWidget *parent = nullptr, std::string account = "");
    ~FunctionSelectPage();
private:
    std::string m_account;

private slots:
    void on_btn_function_confirm_clicked();

    void on_btn_function_quit_clicked();

signals:
    void quit_function();

private:
    Ui::FunctionSelectPage *ui;
};

#endif // FUNCTIONSELECTPAGE_H
