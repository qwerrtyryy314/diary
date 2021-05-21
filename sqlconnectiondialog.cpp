#include "sqlconnectiondialog.h"

#include <QSqlDatabase>
#include <QDebug>

SqlConnectionDialog::SqlConnectionDialog(QWidget *parent)
    : QDialog(parent)
{
    resize(315, 302);
    vboxLayout = new QVBoxLayout(this);
#ifndef Q_OS_MAC
    vboxLayout->setSpacing(6);
#endif
    vboxLayout->setContentsMargins(8, 8, 8, 8);
    connGroupBox = new QGroupBox(this);
    gridLayout = new QGridLayout(connGroupBox);
#ifndef Q_OS_MAC
    gridLayout->setSpacing(6);
#endif
    gridLayout->setContentsMargins(8, 8, 8, 8);
    comboDriver = new QComboBox(connGroupBox);
    gridLayout->addWidget(comboDriver, 0, 1, 1, 1);
    textLabel4 = new QLabel(connGroupBox);
    gridLayout->addWidget(textLabel4, 2, 0, 1, 1);
    textLabel2 = new QLabel(connGroupBox);
    gridLayout->addWidget(textLabel2, 0, 0, 1, 1);
   editDatabase = new QLineEdit(connGroupBox);
    gridLayout->addWidget(editDatabase, 1, 1, 1, 1);
    portSpinBox = new QSpinBox(connGroupBox);
    portSpinBox->setMinimum(-1);
    portSpinBox->setMaximum(65535);
    portSpinBox->setValue(-1);
    gridLayout->addWidget(portSpinBox, 5, 1, 1, 1);
    textLabel3 = new QLabel(connGroupBox);
    gridLayout->addWidget(textLabel3, 1, 0, 1, 1);
    editPassword = new QLineEdit(connGroupBox);
    editPassword->setEchoMode(QLineEdit::Password);
    gridLayout->addWidget(editPassword, 3, 1, 1, 1);
    editUsername = new QLineEdit(connGroupBox);
    gridLayout->addWidget(editUsername, 2, 1, 1, 1);
    editHostname = new QLineEdit(connGroupBox);
    gridLayout->addWidget(editHostname, 4, 1, 1, 1);
    textLabel5 = new QLabel(connGroupBox);
    gridLayout->addWidget(textLabel5, 4, 0, 1, 1);
    textLabel5_2 = new QLabel(connGroupBox);
    gridLayout->addWidget(textLabel5_2, 5, 0, 1, 1);
    textLabel4_2 = new QLabel(connGroupBox);
    gridLayout->addWidget(textLabel4_2, 3, 0, 1, 1);
    vboxLayout->addWidget(connGroupBox);
    hboxLayout = new QHBoxLayout();
#ifndef Q_OS_MAC
    hboxLayout->setSpacing(6);
#endif
    hboxLayout->setContentsMargins(0, 0, 0, 0);
    spacerItem = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);//TODO: parenet?
    hboxLayout->addItem(spacerItem);
    dbCheckBox = new QCheckBox(this);
    hboxLayout->addWidget(dbCheckBox);
    vboxLayout->addLayout(hboxLayout);
    hboxLayout1 = new QHBoxLayout();//TODO: parent, more below
#ifndef Q_OS_MAC
    hboxLayout1->setSpacing(6);
#endif
    hboxLayout1->setContentsMargins(0, 0, 0, 0);
    spacerItem1 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
    hboxLayout1->addItem(spacerItem1);
    okButton = new QPushButton(this);
    okButton->setDefault(true);
    cancelButton = new QPushButton(this);
    hboxLayout1->addWidget(cancelButton);
    hboxLayout1->addWidget(okButton);
    vboxLayout->addLayout(hboxLayout1);
#ifndef QT_NO_SHORTCUT
    textLabel4->setBuddy(editUsername);
    textLabel2->setBuddy(comboDriver);
    textLabel3->setBuddy(editDatabase);
    textLabel5->setBuddy(editHostname);
    textLabel5_2->setBuddy(portSpinBox);
    textLabel4_2->setBuddy(editPassword);
#endif // QT_NO_SHORTCUT
    QWidget::setTabOrder(comboDriver, editDatabase);
    QWidget::setTabOrder(editDatabase, editUsername);
    QWidget::setTabOrder(editUsername, editPassword);
    QWidget::setTabOrder(editPassword, editHostname);
    QWidget::setTabOrder(editHostname, portSpinBox);
    QWidget::setTabOrder(portSpinBox, dbCheckBox);
    QWidget::setTabOrder(dbCheckBox, okButton);
    QWidget::setTabOrder(okButton, cancelButton);
    setWindowTitle(tr("Connect..."));
    connGroupBox->setTitle(tr("Connection settings"));
    textLabel4->setText(tr("&Username:"));
    textLabel2->setText(tr("D&river"));
    portSpinBox->setSpecialValueText(tr("Default"));
    textLabel3->setText(tr("Database Name:"));
    textLabel5->setText(tr("&Hostname:"));
    textLabel5_2->setText(tr("P&ort:"));
    textLabel4_2->setText(tr("&Password:"));
    dbCheckBox->setText(tr("Us&e local file database"));
    okButton->setText(tr("&OK"));
    cancelButton->setText(tr("&Cancel"));

    if (!QSqlDatabase::drivers().contains("QSQLITE"))
    {
        dbCheckBox->setEnabled(false);
        QMessageBox::warning(this,"Error","Sqlite driver not found");
    }
    comboDriver->addItem("QSQLITE");

    connect(okButton,SIGNAL(clicked()),this,SLOT(okButton_clicked()));
    connect(cancelButton,SIGNAL(clicked()),this,SLOT(cancelButton_clicked()));
    connect(dbCheckBox,SIGNAL(clicked()),this,SLOT(dbCheckBox_clicked()));
//just quick start
    dbCheckBox->setChecked(true);
    dbCheckBox_clicked();
    okButton_clicked();
}

SqlConnectionDialog::~SqlConnectionDialog()
{
}

QString SqlConnectionDialog::driverName() const
{
    return comboDriver->currentText();
}

QString SqlConnectionDialog::databaseName() const
{
    return editDatabase->text();
}

QString SqlConnectionDialog::userName() const
{
    return editUsername->text();
}

QString SqlConnectionDialog::password() const
{
    return editPassword->text();
}

QString SqlConnectionDialog::hostName() const
{
    return editHostname->text();
}

int SqlConnectionDialog::port() const
{
    return portSpinBox->value();
}

bool SqlConnectionDialog::useFileDatabase() const
{
    return dbCheckBox->isChecked();
}

void SqlConnectionDialog::cancelButton_clicked()
{
    reject();
}

 void SqlConnectionDialog::dbCheckBox_clicked()
 {
     connGroupBox->setEnabled(!dbCheckBox->isChecked());
 }

void SqlConnectionDialog::okButton_clicked()
{
    if (comboDriver->currentText().isEmpty()) {
        QMessageBox::information(this, tr("No database driver selected"),
                                 tr("Please select a database driver"));
        comboDriver->setFocus();
    } else {
        accept();
    }
}
