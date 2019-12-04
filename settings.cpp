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

void Settings::setAdvanceMode(){
    ui->advance->blockSignals(true);
    ui->simple->blockSignals(true);
    ui->advance->setChecked(true);
    ui->simple->setChecked(false);
    ui->advance->blockSignals(false);
    ui->simple->blockSignals(false);
}

void Settings::setSimpleMode(){
    ui->advance->blockSignals(true);
    ui->simple->blockSignals(true);
    ui->advance->setChecked(false);
    ui->simple->setChecked(true);
    ui->advance->blockSignals(false);
    ui->simple->blockSignals(false);
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

void Settings::on_advance_toggled(bool checked)
{
    emit switchAdvanceMode(checked);
}

void Settings::on_simple_toggled(bool checked)
{
    emit switchSimpleMode(checked);
}
