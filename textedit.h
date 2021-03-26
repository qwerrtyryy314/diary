
#ifndef TEXTEDIT_H
#define TEXTEDIT_H

#include <QWidget>
#include <QMap>
#include <QPointer>
#include <QPrinter>
#include "odt/allconfig.h"


#if QT_VERSION >= 0x040500
#include <QTextDocumentWriter>
#endif

class DocEditor : public QTextEdit {
    Q_OBJECT
public:
    DocEditor(QTextEdit *parent = 0);

signals:
    void Newdatain();  /// remote image is load !!! update
public slots:
    void doc_netready(QNetworkReply* rep);

private:
    int im_cursor;
    QNetworkAccessManager *manager;
    QNetworkDiskCache *m_diskCache;

protected:
    bool canInsertFromMimeData(const QMimeData * source) const;//FIXME: image insert
    void insertFromMimeData(const QMimeData * source);
    void get_part(const QString stringurl);
};

QT_FORWARD_DECLARE_CLASS(QAction)
QT_FORWARD_DECLARE_CLASS(QComboBox)
QT_FORWARD_DECLARE_CLASS(QFontComboBox)
QT_FORWARD_DECLARE_CLASS(QTextEdit)
QT_FORWARD_DECLARE_CLASS(QTextCharFormat)
QT_FORWARD_DECLARE_CLASS(QMenu)
QT_FORWARD_DECLARE_CLASS(QSplitter)

class TextEdit : public QWidget
{
    Q_OBJECT

public:
    TextEdit(QWidget *parent = 0);//?
//    static TextEdit* self( QWidget* = 0 );
//moved to private
//    void setupFileActions();
//    void setupEditActions();
//    void setupTextActions();
//    bool load(const QString &f);
//    bool maybeSave();
//    void setCurrentFileName(const QString &fileName);

protected:
    virtual void closeEvent(QCloseEvent *e);
     static QPointer<TextEdit> _self;

public slots:
    bool dbOpenRecord(const QByteArray data);
private slots:
    void CursorMargins(qreal left, qreal right);
    void fileNew();
    void fileOpen();
    bool fileSave();
    bool saveToDB();
    bool fileSaveAs();
    void filePrint();
    void filePrintPreview();
    void filePrintPdf();
    void textBold();
    void textUnderline();
    void textItalic();
    void textFamily(const QString &f);
    void textSize(const QString &p);
    void textStyle(int styleIndex);
    void textColor();
    void textAlign(QAction *a);
    void currentCharFormatChanged(const QTextCharFormat &format);
    void cursorPositionChanged();

    void clipboardDataChanged();
    void about();
    void printPreview(QPrinter *);

private:
    //_
    void setupFileActions();
    void setupEditActions();
    void setupTextActions();
    bool load(const QString &f);
    bool maybeSave();
    void setCurrentFileName(const QString &fileName);
    //^
    void mergeFormatOnWordOrSelection(const QTextCharFormat &format);
    void fontChanged(const QFont &f);
    void colorChanged(const QColor &c);
    void alignmentChanged(Qt::Alignment a);

    QAction *actionSave,
        *actionSaveToDB,
        *actionTextBold,
        *actionTextUnderline,
        *actionTextItalic,
        *actionTextColor,
        *actionAlignLeft,
        *actionAlignCenter,
        *actionAlignRight,
        *actionAlignJustify,
        *actionUndo,
        *actionRedo,
        *actionCut,
        *actionCopy,
        *actionPaste;

    QStatusBar *statusbar;
    QSettings setter;
    QComboBox *comboStyle;
    QFontComboBox *comboFont;
    QComboBox *comboSize;

    QToolBar *tb;
    QString fileName;
    DocEditor *textEdit;
    QGridLayout *gridLayout;
    DocMargin *Umargin;

    QMenuBar *menuBar;
    QVBoxLayout *mainLayout;
    QSplitter *toolBarSplitter1;
    QSplitter *toolBarSplitter2;
signals:
    void saveToDBsignal(QByteArray str);
};

#endif
