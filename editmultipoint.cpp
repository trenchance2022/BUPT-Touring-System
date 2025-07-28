#include "editmultipoint.h"
#include "ui_editmultipoint.h"

EditMultiPoint::EditMultiPoint(QWidget *parent, std::vector<QString> points)
    : QDialog(parent)
    , ui(new Ui::EditMultiPoint)
{
    ui->setupUi(this);
    for(QString i : points){
        ui->p1->addItem(i);
        ui->p2->addItem(i);
        ui->p3->addItem(i);
        ui->p4->addItem(i);
        ui->p5->addItem(i);
        ui->p6->addItem(i);
        ui->p7->addItem(i);
        ui->p8->addItem(i);
        ui->p9->addItem(i);
        ui->p10->addItem(i);
    }
}

EditMultiPoint::~EditMultiPoint()
{
    delete ui;
}

void EditMultiPoint::on_confirm_clicked()
{
    way[0] = ui->p1->currentIndex() - 1;
    way[1] = ui->p2->currentIndex() - 1;
    way[2] = ui->p3->currentIndex() - 1;
    way[3] = ui->p4->currentIndex() - 1;
    way[4] = ui->p5->currentIndex() - 1;
    way[5] = ui->p6->currentIndex() - 1;
    way[6] = ui->p7->currentIndex() - 1;
    way[7] = ui->p8->currentIndex() - 1;
    way[8] = ui->p9->currentIndex() - 1;
    way[9] = ui->p10->currentIndex() - 1;
    emit accept();
}

