#ifndef DIARYMANAGEMENT_H
#define DIARYMANAGEMENT_H

#include <QWidget>
#include <QStringListModel>
#include <cJSON.h>
#include <unordered_map>
#include <vector>
#include <QFile>
#include <QTextStream>
#include <QString>
#include "huffman.h"
#include "kmp.h"
#include "diarycreate.h"
#include "diaryview.h"

struct Diary {
    int ID;
    std::string title;
    std::string destination;
    std::string author;
    double rating;
    int popularity;
    std::string content;
};

namespace Ui {
class diaryManagement;
}

class diaryManagement : public QWidget
{
    Q_OBJECT

public:
    explicit diaryManagement(QWidget *parent = nullptr, std::string account = "");
    ~diaryManagement();

private slots:
    void on_btnSearch_clicked();

    void on_creatBnt_clicked();

    void on_backBnt_clicked();

    void on_diaryView_doubleClicked(const QModelIndex &index);

signals:
    void quit_function();

private:
    QStringListModel *m_model;
    cJSON *json;
    std::vector<Diary> diaries;
    std::string m_account;
    int itemID[10000];

private:
    void searchByDest();
    void searchByTitle();
    void searchByContent();
    std::vector<Diary> parseDiariesContents(cJSON* diaries);
    void browseByRating(std::vector<Diary>& matchedDiary);
    void browseByNone(std::vector<Diary>& matchedDiary);
    void browseByPopularity(std::vector<Diary> matchedDiary);
    void browseByInterest(std::vector<Diary> matchedDiary);
    void quickRatingSort(std::vector<Diary>& arr, int low, int high);
    void findRatingTopK(std::vector<Diary>& arr, int low, int high, int k);
    int partitionRating(std::vector<Diary>& arr, int low, int high);
    void quickPopularitySort(vector<Diary>& arr, int low, int high);
    void findPopularityTopK(vector<Diary>& arr, int low, int high, int k);
    int partitionPopularity(vector<Diary>& arr, int low, int high);
    vector<Diary> findMatchedDiaries(const vector<Diary>& unsortedDiaries, const vector<string>& keywordsInDestination);
    Diary cJSONToDiary(const cJSON* diaryItem);
    size_t complexHashFunction(const string& str);
    void Back();


private:
    Ui::diaryManagement *ui;
};

#endif // DIARYMANAGEMENT_H
