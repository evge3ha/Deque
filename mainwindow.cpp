#include <iterator>
#include <algorithm>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "algo.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ApplyModel();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::ApplyModel() {
    auto preserve_iter = deque_model_.iterator;

    ui->list_widget->clear();
    for (size_t i = 0; i < deque_model_.items.size(); ++i) {
        ui->list_widget->addItem(
            QString("%1: %2")
                .arg(i)
                .arg(QString::fromStdString(deque_model_.items[i])));
    }

    ui->list_widget->addItem("end");

    deque_model_.iterator = preserve_iter;

    ui->txt_size->setText(QString::number(deque_model_.items.size()));

    ApplyIterator();
}

void MainWindow::ApplyIterator() {
    auto offset = std::distance(deque_model_.items.begin(),
                                deque_model_.iterator);

    ui->list_widget->blockSignals(true);
    ui->list_widget->setCurrentRow(static_cast<int>(offset));
    ui->list_widget->blockSignals(false);

    const bool at_end   = (deque_model_.iterator == deque_model_.items.end());
    const bool at_begin = (deque_model_.iterator == deque_model_.items.begin());

    ui->pb_edit->setDisabled(at_end);
    ui->pb_erase->setDisabled(at_end);
    ui->pb_dec_iterator->setDisabled(at_begin);
    ui->pb_inc_iterator->setDisabled(at_end);

    ui->pb_pop_front->setDisabled(deque_model_.items.empty());
    ui->pb_pop_back->setDisabled(deque_model_.items.empty());

    if (at_end) {
        ui->txt_elem_content->clear();
    } else {
        ui->txt_elem_content->setText(
            QString::fromStdString(*deque_model_.iterator));
    }
}

//-----------------------------Методы управления-------------------------------
void MainWindow::on_pb_edit_clicked() {
    if (deque_model_.iterator == deque_model_.items.end()) {
        return;
    }
    *deque_model_.iterator = ui->txt_elem_content->text().toStdString();
    ApplyModel();
}

void MainWindow::on_pb_find_clicked() {
    const std::string target = ui->txt_elem_content->text().toStdString();

    deque_model_.iterator = std::find(
        deque_model_.items.begin(),
        deque_model_.items.end(),
        target);

    ApplyIterator();
}

void MainWindow::on_pb_count_clicked() {
    QString str_count = ui->le_count->text();
    int size = static_cast<int>(std::count(deque_model_.items.begin(),
                                           deque_model_.items.end(),
                                           str_count.toStdString()));
    ui->lbl_count->setText(QString::number(size));
}

void MainWindow::on_pb_resize_clicked() {
    bool ok = false;
    int requested  = ui->txt_size->text().toInt(&ok);
    if (!ok)  {
        return;
    }

    constexpr int min_size = 0;
    constexpr int max_size = 1000;
    const int clamped = std::clamp(requested, min_size, max_size);

    deque_model_.items.resize(static_cast<size_t>(clamped));
    deque_model_.iterator = deque_model_.items.begin();

    ApplyModel();
}

//--------------------------------Методы дек------------------------------------
void MainWindow::on_pb_pop_front_clicked() {
    deque_model_.items.pop_front();
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
}

void MainWindow::on_pb_push_front_clicked() {
    deque_model_.items.push_front(ui->txt_elem_content->text().toStdString());
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
}

void MainWindow::on_pb_pop_back_clicked() {
    deque_model_.items.pop_back();
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
}

void MainWindow::on_pb_push_back_clicked() {
    deque_model_.items.push_back(ui->txt_elem_content->text().toStdString());
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
}

void MainWindow::on_pb_erase_clicked() {
    if (deque_model_.iterator == deque_model_.items.end()) {
        return;
    }
    deque_model_.items.erase(deque_model_.iterator);
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
}

void MainWindow::on_pb_insert_clicked() {
    auto str = ui->txt_elem_content->text().toStdString();
    deque_model_.items.insert(deque_model_.iterator, str);
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
}

void MainWindow::on_pb_clear_clicked() {
    deque_model_.items.clear();
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
}

//--------------------------------Алгоритмы------------------------------------
void MainWindow::on_pb_min_element_clicked() {
    deque_model_.iterator = std::min_element(
        deque_model_.items.begin(),
        deque_model_.items.end());

    ApplyIterator();
}

void MainWindow::on_pb_max_element_clicked() {
    deque_model_.iterator = std::max_element(
        deque_model_.items.begin(),
        deque_model_.items.end());

    ApplyIterator();
}

void MainWindow::on_pb_merge_sort_clicked() {
    deque_model_.items = MergeSort(deque_model_.items, std::less<std::string>{});
    deque_model_.iterator = deque_model_.items.begin();

    ApplyModel();
}

void MainWindow::on_pb_merge_sort_case_insensitive_clicked() {
    deque_model_.items = MergeSort(
        deque_model_.items,
        [](const std::string& left, const std::string& right) {
            return QString::compare(QString::fromStdString(left),
                                    QString::fromStdString(right),
                                    Qt::CaseInsensitive) < 0;
        });

    deque_model_.iterator = deque_model_.items.begin();

    ApplyModel();
}

void MainWindow::on_pb_unique_clicked() {
    if (!std::is_sorted(deque_model_.items.begin(), deque_model_.items.end())) {
        return;
    }

    auto new_end = std::unique(deque_model_.items.begin(),
                               deque_model_.items.end());
    deque_model_.items.erase(new_end, deque_model_.items.end());

    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
}

void MainWindow::on_pb_reverse_clicked() {
    std::reverse(deque_model_.items.begin(), deque_model_.items.end());
    ApplyModel();
}

void MainWindow::on_pb_shuffle_clicked() {
    std::shuffle(deque_model_.items.begin(),
                 deque_model_.items.end(),
                 deque_model_.random_gen);
    ApplyModel();
}

void MainWindow::on_pb_lower_bound_clicked() {
    if (!std::is_sorted(deque_model_.items.begin(), deque_model_.items.end())) {
        return;
    }

    const std::string target = ui->txt_elem_content->text().toStdString();
    deque_model_.iterator = std::lower_bound(deque_model_.items.begin(), deque_model_.items.end(), target);

    ApplyIterator();
}

void MainWindow::on_pb_upper_bound_clicked() {
    if (!std::is_sorted(deque_model_.items.begin(), deque_model_.items.end())) {
        return;
    }

    const std::string target = ui->txt_elem_content->text().toStdString();
    deque_model_.iterator = std::upper_bound(deque_model_.items.begin(), deque_model_.items.end(), target);

    ApplyIterator();
}

//--------------------------------Итераторы--------------------------------
void MainWindow::on_pb_dec_iterator_clicked() {
    if (deque_model_.iterator != deque_model_.items.begin()) {
        --deque_model_.iterator;
    }
    ApplyIterator();
}

void MainWindow::on_pb_inc_iterator_clicked() {
    if (deque_model_.iterator != deque_model_.items.end()) {
        ++deque_model_.iterator;
    }
    ApplyIterator();
}

void MainWindow::on_pb_begin_clicked() {
    deque_model_.iterator = deque_model_.items.begin();
    ApplyIterator();
}

void MainWindow::on_pb_end_clicked() {
    deque_model_.iterator = deque_model_.items.end();
    ApplyIterator();
}

//--------------------------------Заготовки--------------------------------
void MainWindow::on_pb_tea_clicked() {
    deque_model_.items = Model::tea;
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
}

void MainWindow::on_pb_cakes_clicked() {
    deque_model_.items = Model::cakes;
    deque_model_.iterator = deque_model_.items.begin();
    ApplyModel();
}

//--------------------------------Вспомогательные методы--------------------------------
void MainWindow::on_list_widget_currentRowChanged(int current_row) {
    if (current_row < 0) {
        return;
    }
    if (current_row == static_cast<int>(deque_model_.items.size())) {
        deque_model_.iterator = deque_model_.items.end();
    } else {
        deque_model_.iterator = deque_model_.items.begin() + current_row;
    }
    ApplyIterator();
}

void MainWindow::SetRandomGen(const std::mt19937& random_gen) {
    deque_model_.random_gen = random_gen;
}


