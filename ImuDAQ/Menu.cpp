#include "Menu.h"
#include "ui_Menu.h"

Menu::Menu(QWidget *parent,QApplication *exe) :
    QWidget(parent),
    ui(new Ui::Menu)
{
    this->exe = exe;
    //setAttribute(Qt::WA_DeleteOnClose, true);
    ui->setupUi(this);
}

Menu::~Menu()
{
//    if(d!=nullptr){
//        delete d;
//        d=nullptr;
//    }
//    if(w!=nullptr){
//        delete w;
//        w=nullptr;
//    }
    delete ui;
}

void Menu::on_ImuDAQ_clicked()
{
//    if(d==nullptr){
//        d = new ImuDaqDialog(nullptr,exe);
//        connect(d,&ImuDaqDialog::deleteme,this,&Menu::deleteWindows);
//        //d->setWindowFlag(Qt::WindowMinMaxButtonsHint,false);
//        d->show();
//    }
//    else {
    if(d.isVisible()){
        d.hide();
    }
    else{
        d.show();
    }
}

void Menu::on_Processer_clicked()
{
//    if(w==nullptr){
//        w = new ImuProcesserWidget;
//        connect(w,&ImuProcesserWidget::deleteme,this,&Menu::deleteWindows);
//        w->show();
//    }
//    else {
//        if(w->isVisible()){
//            w->hide();
//        }
//        else{
//            w->show();
//        }
//    }
    if(w.isVisible()){
        w.hide();
    }
    else{
        w.show();
    }
}

void Menu::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event)
//    if(d!=nullptr){
//        delete d;
//        d=nullptr;
//    }
//    if(w!=nullptr){
//        delete w;
//        w=nullptr;
//    }
}

void Menu::deleteWindows(QString id)
{
//    if(id=="ImuProcesserWidget"){
//        delete w;
//        w = nullptr;
//    }
//    if(id=="ImuDaqDialog"){
//        delete d;
//        d = nullptr;
//    }
}
