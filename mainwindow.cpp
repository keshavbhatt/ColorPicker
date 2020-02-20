#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QTableWidgetItem>
#include <QMessageBox>
#include <QLabel>
#include <QListWidget>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QFile>
#include <QClipboard>
#include <QDesktopWidget>
#include <QSpinBox>
#include <QMimeData>

#include "gridlayoututil.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle(QCoreApplication::applicationName());

    settings.setObjectName("app_settings");
    setting_path =  QStandardPaths::writableLocation(QStandardPaths::DataLocation);

    if(!QDir(setting_path).exists()){
        QDir d(setting_path);
        d.mkpath(setting_path);
    }

    settingsWidget = new Settings(this,setting_path);
    settingsWidget->setWindowTitle(QCoreApplication::applicationName()+" | Settings");
    settingsWidget->setWindowFlags(Qt::Window);
    connect(settingsWidget,&Settings::empty_saved_table,[=](){
        ui->saved->clearContents();
        ui->saved->model()->removeRows(0, ui->saved->rowCount());
    });
    connect(settingsWidget,&Settings::themeChnaged,[=](QString themeName){
        if(themeName.contains("Dark")){
            settings.setValue("theme",themeName);
            setStyle(":/dark.qss");
        }else if(themeName.contains("Flat")){
            settings.setValue("theme",themeName);
            setStyle(":/light.qss");
        }else if(themeName.contains("System")){
            settings.setValue("theme",themeName);
            qApp->setStyleSheet("");
        }
        foreach (QSpinBox *spinbox, colorDialog->findChildren<QSpinBox*>()) {
                spinbox->setFixedSize(54,spinbox->height());
        }
        this->resize(this->minimumSize());
    });


    connect(settingsWidget,&Settings::switchSimpleMode,[=](bool simpleMode){
        if(simpleMode){
            settings.setValue("mode","simple");
            switchSimpleMode();
            qDebug()<<"switch simple mode";
        }
    });

    connect(settingsWidget,&Settings::switchAdvanceMode,[=](bool advanceMode){
        if(advanceMode){
            settings.setValue("mode","advance");
            switchAdvanceMode();
            qDebug()<<"switch advance mode";
        }
    });

    colorDialog = new ColorDialog(this,QColor("green"));
    colorDialog->layout()->setContentsMargins(7,0,0,0);
    ui->colorWidgetLayout->addWidget(colorDialog);
    ui->saved->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->saved->verticalHeader()->setVisible(true);
    ui->saved->setSelectionMode(QAbstractItemView::NoSelection);



    connect(colorDialog,&ColorDialog::currentColorChanged,[=](const QColor color){
            ui->argb->setText(color.name(QColor::HexArgb));

            ui->cmyk->setText(getCMYK(color));
            ui->code->setText(color.name());
            ui->type->setText("HTML");
            ui->colorIndicator->setStyleSheet("background-color:"+ui->code->text().trimmed());
            ui->textBrowser->clear();
            ui->textBrowser->setText("<body style='text-align:center;color:"+color.name()+" ;'>"
                                     "<h1>What is Lorem Ipsum?</h1>"
                                     "<h2>What is Lorem Ipsum?</h2>"
                                     "<h3>What is Lorem Ipsum?</h3>"
                                     "<h4>What is Lorem Ipsum?</h4>"
                                     "<h5>What is Lorem Ipsum?</h5>"
                                     "<p>"+ui->textBrowser->getParaText()+"</p>"
                                     "</body>");
            QString fontColor =  QColor("white").lighter(color.lightness()).name();
            ui->pattern_generator->setStyleSheet("text-align:left;color:"+fontColor+";padding:4px;border:none;background-color: "
                                                 "qlineargradient(spread:reflect,"
                                                 " x1:0, y1:0.482955, x2:1, y2:0.5,"
                                                 " stop:0 rgba("+QString::number(color.red())
                                                 +", "+QString::number(color.green())+", "
                                                 +QString::number(color.blue())+", 255),"
                                                 " stop:1 rgba("+QString::number(color.red())
                                                 +", "+QString::number(color.green())+", "
                                                 +QString::number(color.blue())+", 0));");
            ui->saved->clearSelection();

    });
    colorDialog->setCurrentColor(QColor("red"));//TODO load color from last session


    connect(ui->bgColor,&QLineEdit::textChanged,[=](const QString text){
        QColor color = QColor(text.trimmed());
        if(color.isValid()){
            ui->textBrowser->setBackground(color);
            settings.setValue("background",color.name());
        }
    });


    foreach (QPushButton*btn, colorDialog->findChildren<QPushButton*>())    {
        if(btn->text().contains("Pick Screen Color")){
            btn->setIconSize(QSize(18,18));
            btn->setIcon(QIcon(":/dark/picker.png"));
        }
        if(btn->text().contains("Add to Custom Colors")){
            btn->setIconSize(QSize(18,18));
            btn->setIcon(QIcon(":/dark/plus.png"));
            btn->setText("Add to Temporary Swatch");
        }
    }

    foreach (QLabel*label, colorDialog->findChildren<QLabel*>())    {
        label->setText(label->text().replace("&",""));
        if(label->text().contains("Custom colors")){
//            label->setAlignment(Qt::AlignCenter);
            label->setTextFormat(Qt::RichText);
            label->setText("<b>Temporary Swatch</b><br>Click \"Add to Temporary Swatch\"<br> to save color permanently. <br>or<br>"
                           "Drag color to save for this session.");
        }
    }

    foreach (QLineEdit*ledit, colorDialog->findChildren<QLineEdit*>())    {
        if(ledit->text()=="#ff0000"){
            ledit->setMaximumWidth(40000);
        }
    }

    load_saved_colors();

    restoreGeometry(settings.value("geometry").toByteArray());
    restoreState(settings.value("windowState").toByteArray());

    //set mode
    if(settings.value("mode","advance").toString()=="advance"){
        switchAdvanceMode();
        settingsWidget->setAdvanceMode();
    }else{
        switchSimpleMode();
        settingsWidget->setSimpleMode();
    }

    pattern_widget = new QWidget(this);
    pattern_widget->setWindowFlags(Qt::Dialog);
    pattern_widget->setWindowTitle(QApplication::applicationName()+" | Color Shade");
    _ui_pattern.setupUi(pattern_widget);
    //intetionally placed before connection
    _ui_pattern.factor_spin->setValue(settings.value("pattern_factor",10).toInt());
    ui->bgColor->setText(settings.value("background","white").toString());

    QFont font = QFont(ui->textBrowser->font());
            font.setPixelSize(settings.value("zoomF",14).toInt());
    ui->textBrowser->setFont(font);

    connect(_ui_pattern.factor_spin, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),[=](int value){
        _patter_factor = value;
        settings.setValue("pattern_factor",value);
        ui->pattern_generator->click();
    });


    //keep this function located at last load theme settings
    settingsWidget->setTheme(settings.value("theme","System").toString());
}


void MainWindow::switchAdvanceMode(){
    settings.setValue("mode","advance");
    this->setWindowTitle(QApplication::applicationName()+" | AdvanceMode");
    ui->advanceWidget->show();
    this->adjustSize();
}
void MainWindow::switchSimpleMode(){
    settings.setValue("mode","simple");
    this->setWindowTitle(QApplication::applicationName()+" | SimpleMode");
    ui->advanceWidget->hide();
    this->hide();
    this->show();
    this->adjustSize();
}

void MainWindow::setStyle(QString fname)
{   QFile styleSheet(fname);
    if (!styleSheet.open(QIODevice::ReadOnly)) {
        qWarning("Unable to open file");
    return; }
    qApp->setStyleSheet(styleSheet.readAll());
    styleSheet.close();
}



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::load_saved_colors(){
    QFile file(setting_path+"/saved.colors");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
      return;

    QTextStream in(&file);
    while (!in.atEnd()) {
      QString line = in.readLine();
      //qDebug()<<line;
      add_to_table(line,false);
    }
    file.close();
}

void MainWindow::add_to_table(const QString colorStr,bool saving){
    QColor color = QColor(colorStr);
    if(color.isValid()){
        int nextRow;
        int row = ui->saved->rowCount();
        if(row==0){
            nextRow = 0;
        }else{
            nextRow = row++;
        }
        if(saving){
            QColor color =colorDialog->currentColor();
            //save color to saved.colors file
            save_color(color);
        }
        //data
        QString html =  color.name();
        QString hsv =   getHSV(color);
        QString hexArgb = color.name(QColor::HexArgb);
        QString rgb = getRGB(color);
        QString cymk = getCMYK(color);

        QStringList columnData;
        columnData<<html<<hexArgb<<hsv<<rgb<<cymk<<"color"<<"delete";

        //qDebug()<<columnData;
        //insertRow
        ui->saved->insertRow(nextRow);
        //add column
        for (int i = 0; i < columnData.count(); i++) {

            if(columnData.at(i)=="color"){
                QPushButton *color = new QPushButton(0);
                color->setStyleSheet("background-color:"+html+";border:0px;");
                connect(color,&QPushButton::clicked,[=](){
                    colorDialog->setCurrentColor(QColor(html));
                    ui->colorIndicator->setStyleSheet("background-color:"+html);
                    ui->type->setText("HTML");
                    ui->code->setText(QColor(html).name());
                });
                ui->saved->setCellWidget(nextRow,i,color);
                this->update();
            }else if(columnData.at(i)=="delete"){
                QPushButton *del = new QPushButton("Delete",0);
                del->setIcon(QIcon(":/dark/delete.png"));
                del->setStyleSheet("border:0px;");
                connect(del,&QPushButton::clicked,[=](){
                    delete_color_from_saved_colors_file(hexArgb);
                    ui->saved->removeRow(ui->saved->rowAt(del->y()));
                    ui->type->setText("-");
                    ui->colorIndicator->setStyleSheet("background-color:transparent;");
                    ui->code->clear();
                });
                ui->saved->setCellWidget(nextRow,i,del);
                //hack to forcibly make the inner table widgets's size
                ui->saved->viewport()->resize(ui->saved->viewport()->width(),ui->saved->viewport()->height()+1);
                ui->saved->viewport()->resize(ui->saved->viewport()->width(),ui->saved->viewport()->height()-1);
            }else{
                ui->saved->setItem(nextRow, i,
                                    new QTableWidgetItem(columnData.at(i)));
            }
        }
    }else{
        invalidColor();
    }
}

void MainWindow::delete_color_from_saved_colors_file(const QString hexArgb){
    QFile file(setting_path+"/saved.colors");
    if(file.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        QString s;
        QTextStream t(&file);
        while(!t.atEnd())
        {
            QString line = t.readLine();
            if(!line.contains(hexArgb))
                s.append(line + "\n");
        }
        file.resize(0);
        t << s;
        file.close();
    }
    ui->type->setText("-");
    ui->colorIndicator->setStyleSheet("background-color:transparent;");
    ui->code->clear();
}

void MainWindow::save_color(const QColor color){
    QFile file(setting_path+"/saved.colors");
    if (!file.open(QIODevice::Append | QIODevice::Text))
      return;
    QTextStream out(&file);
    out << color.name(QColor::HexArgb)<< "\n";
    file.close();
}

void MainWindow::on_save_clicked()
{
    QColor color =colorDialog->currentColor();
    add_to_table(color.name(QColor::HexArgb),true);
    ui->saved->scrollToBottom();
}

QString MainWindow::getHSV(const QColor color){
    int h = color.convertTo(QColor::Hsv).hsvHue();
    int s = color.convertTo(QColor::Hsv).hsvSaturation();
    int v = color.convertTo(QColor::Hsv).value();
    return QString::number(h)+" "+QString::number(s)+" "+QString::number(v);
}

QString MainWindow::getRGB(const QColor color){
    int r = color.convertTo(QColor::Rgb).red();
    int g = color.convertTo(QColor::Rgb).green();
    int b = color.convertTo(QColor::Rgb).blue();
    return QString::number(r)+","+QString::number(g)+","+QString::number(b);
}

QString MainWindow::getCMYK(const QColor color){
    int c = color.convertTo(QColor::Cmyk).cyan();
    int m = color.convertTo(QColor::Cmyk).magenta();
    int y = color.convertTo(QColor::Cmyk).yellow();
    int k = color.convertTo(QColor::Cmyk).black();
    return QString::number(c)+","+QString::number(m)+","+QString::number(y)+","+QString::number(k);
}

void MainWindow::on_saved_cellClicked(int row, int column)
{

    if(ui->saved->item(row,column)==nullptr)
        return;
    QString colorname  = ui->saved->item(row,column)->text();

    QColor color(colorname);

    int x,y,z,k;
    if(colorname.contains(",")){
        QStringList val = colorname.split(",");
        if(val.count()==4){
            x= val.at(0).toInt();
            y= val.at(1).toInt();
            z= val.at(2).toInt();
            k= val.at(3).toInt();
            color = QColor::fromCmyk(x,y,z,k);
            qDebug()<<color.isValid();
        }else{
            x= val.at(0).toInt();
            y= val.at(1).toInt();
            z= val.at(2).toInt();
            color = QColor::fromRgb(x,y,z);
        }

    }else if(colorname.contains(" ")){
        QStringList val = colorname.split(" ");
        x= val.at(0).toInt();
        y= val.at(1).toInt();
        z= val.at(2).toInt();
        color = QColor::fromHsv(x,y,z);
    }
    if(color.isValid()){
        colorDialog->setCurrentColor(color);
        ui->colorIndicator->setStyleSheet("background-color:"+color.name());
        ui->type->setText(ui->saved->horizontalHeaderItem(column)->text());
        if(colorname.contains(" ")){
            ui->code->setText(colorname.replace(" ",","));
        }else{
            ui->code->setText(colorname);
        }
    }else{
        invalidColor();
    }
}

void MainWindow::invalidColor(){
    QMessageBox msgBox;
    msgBox.setText("Selected color code is invalid.");
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.exec();
}


void MainWindow::on_actionSettingsAndAbout_triggered()
{
    settingsWidget->move(QApplication::desktop()->screen()->rect().center()-this->rect().center());
    settingsWidget->showNormal();
}

void MainWindow::on_actionQuit_triggered()
{
    qApp->quit();
}


void MainWindow::on_copy_clicked()
{
    QClipboard *clipboard = QGuiApplication::clipboard();
    ui->code->selectAll();
    QString code = ui->code->text();
    if(code.contains(" ")){
        code = code.replace(" ",",");
    }
    clipboard->setText(code);
}

void MainWindow::on_code_textChanged(const QString &arg1)
{
    ui->copy->setEnabled(!arg1.isEmpty());
}


void MainWindow::closeEvent(QCloseEvent *closeEv){
    settings.setValue("geometry",saveGeometry());
    settings.setValue("windowState", saveState());
    closeEv->accept();
}

void MainWindow::on_actionswitchMode_triggered()
{
    //set mode
    if(settings.value("mode","advance").toString()=="advance"){
        switchSimpleMode();
        settingsWidget->setSimpleMode();
    }else if(settings.value("mode","advance").toString()=="simple"){
        switchAdvanceMode();
        settingsWidget->setAdvanceMode();
    }
}

void MainWindow::on_pattern_generator_clicked()
{
    //clear
    for (int i = 0; i < _ui_pattern.gridLayout->columnCount(); i++)
    {
        GridLayoutUtil::removeColumn(_ui_pattern.gridLayout,i,true);
    }
    QColor color = QColor(ui->code->text().trimmed());
    if(color.isValid())
    {
        pattern_widget->setWindowTitle(QApplication::applicationName()+" | Color Shade "+color.name());
        //draw pattern
        int d_max = 300;
        int d_min = 0;
        int factor_diff = settings.value("pattern_factor",10).toInt();
        int cols  = 10;
        int itemscount  = (d_max - d_min)/factor_diff;
        int factor = 300;
        for (int i = 0; i < itemscount; i++)
        {
            QString colorName,fontColor,factorString;
            if(factor<=100)
            {
                factor = factor - factor_diff;
                int l_factor = 100 -(factor - 100);
                colorName =  color.lighter(l_factor).name()+"*"+QString::number(l_factor-100)+"% Lighter";
                fontColor =  color.darker(l_factor+50).name();
            }else{
                factor =  factor - factor_diff;
                int d_factor;
                if(factor<=400)
                    d_factor = factor/3;
                if(factor<=300)
                    d_factor = factor/3;
                if(factor<=200)
                    d_factor = factor/2;
                if(factor<=100)
                    d_factor = factor;
                colorName =  color.darker(factor).name()+"*"+QString::number(d_factor)+"% Darker";
                fontColor =  QColor("white").lighter(factor).name();
            }
            QPushButton *colorWidget = new QPushButton;
            colorWidget->setFocusPolicy(Qt::NoFocus);
            QString colorNameHash =  QString(colorName).split("*").first();
            factorString = colorName.split("*").last();
            colorWidget->setStyleSheet("QPushButton{border:none;background:"+colorNameHash+";color:"+fontColor+";}");
            colorWidget->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
            connect(colorWidget,&QPushButton::clicked,[colorNameHash,this](){
                colorDialog->setCurrentColor(QColor(colorNameHash.trimmed()));
            });
            colorWidget->setText(colorNameHash+"\n"+factorString);
            int row = _ui_pattern.gridLayout->count()/cols;
            int col = _ui_pattern.gridLayout->count() % cols;
            _ui_pattern.gridLayout->addWidget(colorWidget,row,col);
        }

        if(!pattern_widget->isVisible())
        {
            pattern_widget->show();
        }
    }
    else
    {
        qDebug()<<"INVALID COLOR cannot generate pattern";
    }
}

void MainWindow::on_pickBackground_clicked()
{
    if(cDialog == nullptr){
       cDialog = new QColorDialog(this);
    }
    cDialog->setWindowFlags(Qt::Dialog);
    cDialog->setOptions(QColorDialog::NoButtons | QColorDialog::DontUseNativeDialog);
    //cDialog->show();
    foreach (QPushButton*btn, cDialog->findChildren<QPushButton*>())    {
        if(btn->text().contains("Pick Screen Color")){
            screenPicker = btn;
        }
    }
    connect(cDialog,&QColorDialog::currentColorChanged,[=](const QColor color){
        ui->textBrowser->setBackground(color);
        ui->bgColor->setText(color.name());
    });
    if(screenPicker!= nullptr){
        screenPicker->click();
    }
}

void MainWindow::on_zoomin_clicked()
{
    QFont font = QFont(ui->textBrowser->font());
            font.setPixelSize(ui->textBrowser->fontInfo().pixelSize()+1);
    ui->textBrowser->setFont(font);
    settings.setValue("zoomF",ui->textBrowser->fontInfo().pixelSize());
}

void MainWindow::on_zoomout_clicked()
{
    QFont font = QFont(ui->textBrowser->font());
            font.setPixelSize(ui->textBrowser->fontInfo().pixelSize()-1);
    ui->textBrowser->setFont(font);
    settings.setValue("zoomF",ui->textBrowser->fontInfo().pixelSize());
}
