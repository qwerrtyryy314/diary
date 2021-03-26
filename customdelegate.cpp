#include "customdelegate.h"

QWidget * lineEditDelegate::createEditor ( QWidget * parent, const QStyleOptionViewItem & option, const QModelIndex & index) const
{
    QWidget * editor = QStyledItemDelegate::createEditor(parent, option, index);
    QLineEdit * lineEdit = qobject_cast<QLineEdit *>(editor);
    switch(maskType)
    {    //INTEGER=1 DATE=2 TIME=3 TEXT=4
        case 1://INTEGER
            if (lineEdit) lineEdit->setInputMask("9999999999");
            break;
        case 2://DATE
            if (lineEdit)
            {
                QRegExpValidator *v = new QRegExpValidator(lineEdit);
                QRegExp rx("(((0[1-9]|[12][0-9]|3[01])([-./])(0[13578]|10|12)([-./])(\\d{4}))|(([0][1-9]|[12][0-9]|30)([-./])(0[469]|11)"
                           "([-./])(\\d{4}))|((0[1-9]|1[0-9]|2[0-8])([-./])(02)([-./])(\\d{4}))|((29)(\\.|-|\\/)(02)([-./])([02468][048]"
                           "00))|((29)([-./])(02)([-./])([13579][26]00))|((29)([-./])(02)([-./])([0-9][0-9][0][48]))|((29)([-./])(02)([-"
                           "./])([0-9][0-9][2468][048]))|((29)([-./])(02)([-./])([0-9][0-9][13579][26])))");
                           //strict dd/mm/yyyy format w/ leap years
                v->setRegExp(rx);
                lineEdit->setValidator(v);
                //lineEdit->setInputMask("99.99.9999");
            }
            break;
        case 3://TIME
            if (lineEdit)
            {
                QRegExpValidator *v = new QRegExpValidator(lineEdit);
                QRegExp rx("^(([0-9])|([0-1][0-9])|([2][0-3])):(([0-9])|([0-5][0-9]))$");
                           //reg. expr. 4 checking 24 time
                v->setRegExp(rx);
                lineEdit->setValidator(v);
                lineEdit->setInputMask("00:00");
            }
            break;
        case 4://TEXT
            //if (lineEdit) lineEdit->setInputMask("0000-00-00");
            break;
        default:
            qDebug()<<"Unknown field type";
            break;
    }
    return editor;
}

comboBoxDelegate::comboBoxDelegate(const QStringList &slist,const QList<uint> &intlist,const uint foreignColIndex)//
{
    foreach(QString str, slist)
    {
        Items.push_back(str);
    }
    foreach(uint dataIndex, intlist)
    {
        Indexes.push_back(dataIndex);
    }
    fr=foreignColIndex;
}

comboBoxDelegate::comboBoxDelegate(const QStringList &slist)//
{
    foreach(QString str, slist)
    {
        Items.push_back(str);
    }
}

QWidget *comboBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &/* option */, const QModelIndex &/* index */) const
{
  QComboBox* editor = new QComboBox(parent);
  for(int i = 0; i < Items.size(); ++i)
    {
    editor->addItem(Items[i]);
    }
  return editor;
}

void comboBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    if(fr==0)
    {
        qDebug()<<"bad fk index";
        return;
    }
    QComboBox *comboBox = qobject_cast<QComboBox*>(editor);
    model->setData(index,comboBox->itemText(comboBox->currentIndex()),Qt::EditRole);
    if(!Indexes.empty())
        model->setData(model->index(index.row(),fr),Indexes.at(comboBox->currentIndex()),Qt::EditRole);
    //FIMXE: index out of range
}

QWidget * TimeEditDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &, const QModelIndex &) const
{
    QTimeEdit *timeEdit = new QTimeEdit(parent);
    timeEdit->setDisplayFormat("hh:mm:ss.zzz");
    return(timeEdit);
}

void TimeEditDelegate::setEditorData(QWidget *editor,const QModelIndex &index) const
{
    QTimeEdit *timeEdit = static_cast<QTimeEdit*>(editor);
    if(timeEdit)
    timeEdit->setTime(index.model()->data(index, Qt::EditRole).toTime());
}

void TimeEditDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                    const QModelIndex &index) const
{
    QTimeEdit *timeEdit = qobject_cast<QTimeEdit*>(editor);
    timeEdit->interpretText();
    model->setData(index, timeEdit->time() , Qt::EditRole);
}

void TimeEditDelegate::updateEditorGeometry(QWidget *editor,
                                            const QStyleOptionViewItem &option, const QModelIndex &/* index */) const
{
    editor->setGeometry(option.rect);
}

QWidget * DateTimeEditDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &, const QModelIndex &) const
{
    QDateTimeEdit *dateTimeEdit = new QDateTimeEdit(parent);
    dateTimeEdit->setCalendarPopup(true);
    return(dateTimeEdit);
}

void DateTimeEditDelegate::setEditorData(QWidget *editor,const QModelIndex &index) const
{
    QDateTimeEdit *dateTimeEdit = static_cast<QDateTimeEdit*>(editor);
    if(dateTimeEdit)
    {
        dateTimeEdit->setDisplayFormat("yyyy.MM.dd hh:mm:ss.zzz");
        dateTimeEdit->setDateTime(index.model()->data(index, Qt::EditRole).toDateTime());
    }
}

void DateTimeEditDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                    const QModelIndex &index) const
{
    QDateTimeEdit *dateTimeEdit = qobject_cast<QDateTimeEdit*>(editor);
    dateTimeEdit->interpretText();
    model->setData(index, dateTimeEdit->dateTime() , Qt::EditRole);
}

void DateTimeEditDelegate::updateEditorGeometry(QWidget *editor,
                                            const QStyleOptionViewItem &option, const QModelIndex &/* index */) const
{
    editor->setGeometry(option.rect);
}
