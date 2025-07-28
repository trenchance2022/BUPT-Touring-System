#ifndef DIARYCREATE_H
#define DIARYCREATE_H

#include <QWidget>
#include "cJSON.h"
#include <vector>
#include <QFile>
#include <QTextStream>
#include <QString>
#include "huffman.h"
#include "kmp.h"
#include "diarymanagement.h"

struct Diary;

namespace Ui {
class DiaryCreate;
}

class DiaryCreate : public QWidget
{
    Q_OBJECT

public:
    explicit DiaryCreate(QWidget *parent = nullptr, std::string account = "");
    std::string m_account;
    ~DiaryCreate();

private slots:
    void on_cancel_clicked();

    void on_confirm_clicked();

signals:
    void quit_function();

private:
    Ui::DiaryCreate *ui;

private:
    std::vector<Diary> parseDiariesContents(cJSON *diaries);
    void saveDiary(const Diary& diary);

};

#endif // DIARYCREATE_H
