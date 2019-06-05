#ifndef MENU_H
#define MENU_H

#include <QWidget>
#include "ImuProcesserWidget.h"
#include "ImuDaqDialog.h"

namespace Ui {
class Menu;
}

class Menu : public QWidget
{
    Q_OBJECT

public:
    explicit Menu(QWidget *parent = nullptr);
    ~Menu();
    void closeEvent(QCloseEvent *event);

private slots:
    void deleteWindows(QString id);
    void on_ImuDAQ_clicked();
    void on_Processer_clicked();

private:
    ImuProcesserWidget* w;
    ImuDaqDialog* d;
    Ui::Menu *ui;
};

#endif // MENU_H
