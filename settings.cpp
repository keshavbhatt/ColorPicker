#include "settings.h"
#include "ui_settings.h"

#include <QDesktopServices>
#include <QFile>

Settings::Settings(QWidget *parent,QString setting_path) :
    QWidget(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
    this->setting_path = setting_path;
}

Settings::~Settings()
{
    delete ui;
}

void Settings::setTheme(QString themeName){
    if(themeName.contains("Dark")){
        ui->themeComboBox->setCurrentIndex(2);
    }else if(themeName.contains("Flat")){
        ui->themeComboBox->setCurrentIndex(1);
    }else if(themeName.contains("System")){
        ui->themeComboBox->setCurrentIndex(0);
    }
}

void Settings::on_clearColorsPushButton_clicked()
{
    QFile file(setting_path+"/saved.colors");
    file.remove();
    emit empty_saved_table();
}

void Settings::on_donatePushButton_clicked()
{
    QDesktopServices::openUrl(QUrl("https://paypal.me/keshavnrj/2"));
}

void Settings::on_girhubPushButton_clicked()
{
    QDesktopServices::openUrl(QUrl("https://github.com/keshavbhatt/ColorPicker"));
}

void Settings::on_ratePushButton_clicked()
{
    QDesktopServices::openUrl(QUrl("snap://color-picker"));
}

void Settings::on_themeComboBox_currentIndexChanged(const QString &arg1)
{
    emit themeChnaged(arg1);
}
