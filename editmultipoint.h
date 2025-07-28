#ifndef EDITMULTIPOINT_H
#define EDITMULTIPOINT_H

#include <QDialog>
#include <QString>
#include <vector>

namespace Ui {
class EditMultiPoint;
}

class EditMultiPoint : public QDialog
{
    Q_OBJECT

public:
    explicit EditMultiPoint(QWidget *parent = nullptr, std::vector<QString> points = {""});
    ~EditMultiPoint();

private:
    Ui::EditMultiPoint *ui;

public:
    int way[10];
private slots:
    void on_confirm_clicked();
};

#endif // EDITMULTIPOINT_H
