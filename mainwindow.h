#pragma once

#include <QMainWindow>

#include "model.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void SetRandomGen(const std::mt19937& random_gen);

private slots:
    // Методы управления
    void on_pb_edit_clicked();
    void on_pb_find_clicked();
    void on_pb_count_clicked();
    void on_pb_resize_clicked();

    // Методы дека
    void on_pb_pop_front_clicked();
    void on_pb_push_front_clicked();
    void on_pb_pop_back_clicked();
    void on_pb_push_back_clicked();
    void on_pb_erase_clicked();
    void on_pb_insert_clicked();
    void on_pb_clear_clicked();

    // Алгоритмы
    void on_pb_min_element_clicked();
    void on_pb_max_element_clicked();
    void on_pb_merge_sort_clicked();
    void on_pb_merge_sort_case_insensitive_clicked();
    void on_pb_unique_clicked();
    void on_pb_reverse_clicked();
    void on_pb_shuffle_clicked();
    void on_pb_lower_bound_clicked();
    void on_pb_upper_bound_clicked();

    // Итераторы
    void on_pb_dec_iterator_clicked();
    void on_pb_inc_iterator_clicked();
    void on_pb_begin_clicked();
    void on_pb_end_clicked();

    // Заготовки
    void on_pb_tea_clicked();
    void on_pb_cakes_clicked();

    // Вспомогательные
    void on_list_widget_currentRowChanged(int current_row);


private:
    void ApplyModel();
    void ApplyIterator();

private:
    Model deque_model_;
    Ui::MainWindow *ui;
};