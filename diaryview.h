#ifndef DIARYVIEW_H
#define DIARYVIEW_H

#include <QWidget>
#include "diarymanagement.h"
#include <QString>

struct Diary;

namespace Ui {
class DiaryView;
}

class DiaryView : public QWidget
{
    Q_OBJECT

public:
    explicit DiaryView(QWidget *parent = nullptr, std::vector<Diary> diaries = {}, int id = -1);
    ~DiaryView();

signals:
    void quit_function();

private slots:
    void on_confirmBnt_clicked();

private:
    Ui::DiaryView *ui;
    std::vector<Diary> m_diaries;
    int m_id;
};

#endif // DIARYVIEW_H
