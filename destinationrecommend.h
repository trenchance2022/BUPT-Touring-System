#ifndef DESTINATIONRECOMMEND_H
#define DESTINATIONRECOMMEND_H

#include <QWidget>
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
#include "myGraph.h"
#include "mymap.h"
#define MAX_ATTRACTION_NUM 200
namespace Ui {
class destinationRecommend;
}

class destinationRecommend : public QWidget
{
    Q_OBJECT

public:
    explicit destinationRecommend(QWidget *parent = nullptr,std::string account = "");
    ~destinationRecommend();


private slots:
    void on_pushButton_clicked();


    void on_listView_doubleClicked(const QModelIndex &index);

private:
    QStringListModel *m_model;
    int attrIndex[MAX_ATTRACTION_NUM];
private:
    void destination_recommend();

    void search_mode();

    void recommend_mode();

    void printFullSortedAttr(const vector<int>& indices, int start, int pageSize);

    void findPopularityTopK(vector<int>& arr, int low, int high, int k);

    void findRatingTopK(vector<int>& arr, int low, int high, int k);

    int partitionRating(vector<int>& arr, int low, int high);

    int partitionPopularity(vector<int>& arr, int low, int high);

    void quickRatingFullSort(vector<int>& arr, int low, int high);

    void quickPopularityFullSort(vector<int>& arr, int low, int high);

    void sortAndPrintPopTop10(vector<int>& indices);

    void sortAndPrintRateTop10(vector<int>& indices);
private:
    Ui::destinationRecommend *ui;
};

#endif // DESTINATIONRECOMMEND_H
