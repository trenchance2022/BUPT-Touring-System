#include "functionselectpage.h"
#include "ui_functionselectpage.h"
#include <QMessageBox>
#include "diarymanagement.h"
#include "destinationrecommend.h"

FunctionSelectPage::FunctionSelectPage(QWidget *parent, std::string account) :
    QWidget(parent),
    ui(new Ui::FunctionSelectPage)
{
    ui->setupUi(this);
    m_account = account;
}

FunctionSelectPage::~FunctionSelectPage()
{
    delete ui;
}

void FunctionSelectPage::on_btn_function_confirm_clicked()
{
    //根据选项的索引来进入相应功能
    int choice = ui->comboBox->currentIndex();
    switch(choice){
    case 0:
    {
        destinationRecommend *w = new destinationRecommend(nullptr, m_account);
        this->hide();
        w->show();
        break;
    }
    case 1:
    {
        //日记
        diaryManagement *w = new diaryManagement(nullptr, m_account);
        this->hide();
        w->show();
        connect(w, &diaryManagement::quit_function, this, &FunctionSelectPage::show);
        break;
    }
    }
}

void FunctionSelectPage::on_btn_function_quit_clicked()
{
    this->close();
    emit quit_function();
}

