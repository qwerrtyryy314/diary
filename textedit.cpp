/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the demonstration applications of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/
//ODT: http://fop-miniscribus.googlecode.com/svn/trunk/

#include <QSplitter>
#include <QLabel>
#include <QPrinter>
#include <QPrintDialog>
#include <QPrintPreviewDialog>
#include "textedit.h"
#include "odt/allconfig.h"
#include <QDebug>
#include <QBuffer>

DocEditor::DocEditor(QTextEdit *parent) :
    QTextEdit(parent), im_cursor(1) {

    //// get image or other contenents if paste on text field...
    QString sysCacheDir(__TMPCACHE__);
    QDir dir;
    if (!dir.exists(sysCacheDir)) {
        dir.mkpath(sysCacheDir);
    }
    manager = new QNetworkAccessManager(this);
    m_diskCache = new QNetworkDiskCache(this);
    m_diskCache->setCacheDirectory(sysCacheDir);
    manager->setCache(m_diskCache);
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(doc_netready(QNetworkReply*)));
    //////// get_part(QString("http://www.liberatv.ch/sites/default/files/styles/piccolissima_87/public/topimage/unwomen.jpg"));

}

void DocEditor::get_part(const QString stringurl) {
    QNetworkRequest request;
    request.setUrl(QUrl(stringurl));
    request.setRawHeader("User-Agent", "MyNokkia 1.0");
    QNetworkReply *inetitem = manager->get(request);
}

void DocEditor::doc_netready(QNetworkReply* rep) {

    const qint64 xsizebuff = rep->readBufferSize();
    QVariant lmod = rep->header(QNetworkRequest::LastModifiedHeader);
    if (rep->error() != QNetworkReply::NoError) {
        /////// qDebug() << "### incomming error!" << __TMPCACHE__;
    } else {
        if (rep->isFinished()) {
            QImage im;
            im.loadFromData(rep->readAll());
            if (!im.isNull()) {
                document()->addResource(QTextDocument::ImageResource, rep->url(), QVariant(im));
                ///// /// qDebug() << "### image ok  " << rep->url().toString();
                update();
                emit Newdatain();
            }

        }

    }

}

//bool DocEditor::canInsertFromMimeData(const QMimeData * source) {
//    return QTextEdit::canInsertFromMimeData(source);
//}
//class TextEdit : public QTextEdit
//{
//public:
//    bool canInsertFromMimeData(const QMimeData* source) const
//    {
//        return source->hasImage() || source->hasUrls() ||
//            QTextEdit::canInsertFromMimeData(source);
//    }

//    void insertFromMimeData(const QMimeData* source)
//    {
//        if (source->hasImage())
//        {
//            static int i = 1;
//            QUrl url(QString("dropped_image_%1").arg(i++));
//            dropImage(url, qvariant_cast<QImage>(source->imageData()));
//        }
//        else if (source->hasUrls())
//        {
//            foreach (QUrl url, source->urls())
//            {
//                QFileInfo info(url.toLocalFile());
//                if (QImageReader::supportedImageFormats().contains(info.suffix().toLower().toLatin1()))
//                    dropImage(url, QImage(info.filePath()));
//                else
//                    dropTextFile(url);
//            }
//        }
//        else
//        {
//            QTextEdit::insertFromMimeData(source);
//        }
//    }

//private:
//    void dropImage(const QUrl& url, const QImage& image)
//    {
//        if (!image.isNull())
//        {
//            document()->addResource(QTextDocument::ImageResource, url, image);
//            textCursor().insertImage(url.toString());
//        }
//    }

//    void dropTextFile(const QUrl& url)
//    {
//        QFile file(url.toLocalFile());
//        if (file.open(QIODevice::ReadOnly | QIODevice::Text))
//            textCursor().insertText(file.readAll());
//    }
//};
//
bool DocEditor::canInsertFromMimeData(const QMimeData* source) const
{
    return source->hasImage() || source->hasUrls() ||
            QTextEdit::canInsertFromMimeData(source);
}

void DocEditor::insertFromMimeData(const QMimeData * source) {
    if (source->hasImage()) {
        im_cursor++;
        const QString newimagein = QString("pic_%1.png").arg(im_cursor);
        QImage images = qvariant_cast<QImage>(source->imageData());
        if (!images.isNull()) {
            QTextImageFormat fragment;
            fragment.setName(newimagein);
            fragment.setWidth(images.width());
            fragment.setHeight(images.height());
            document()->addResource(QTextDocument::ImageResource, QUrl(newimagein), QVariant(images));
            textCursor().insertImage(fragment);
            return;
        }
    }

    if (source->formats().contains("text/html")) {
        QString draghtml = source->html();
        QRegExp expression("src=[\"\'](.*)[\"\']", Qt::CaseInsensitive);
        expression.setMinimal(true);
        int iPosition = 0;
        while ((iPosition = expression.indexIn(draghtml, iPosition)) != -1) {
            QString imageurl = expression.cap(1);
            if (!imageurl.isEmpty()) {
                get_part(imageurl); /// load in cache if can
            }
            iPosition += expression.matchedLength();
        }
        QTextDocumentFragment fragment = QTextDocumentFragment::fromHtml(draghtml);
        textCursor().insertFragment(fragment);
        return;
    }
    return QTextEdit::insertFromMimeData(source);
}

static inline QString FileFilterHaving() {
    QString filter;
    filter = "";
    ///////filter += QString( "FOP file" ) + " (*.fop *.fop.gz *.fo *.fo.gz *.xml);;";
    /////filter+= QString( "MiniScribus binary stream file" ) + " (*.page);;";
    //////filter+= QString( "OpenOffice 1.1 file format" ) + " (*.sxw *.stw);;";
    filter += QString("OpenOffice 2.4 file format OASIS ") + " (*.odt *.ott);;";
    filter += QString("XHTML file format") + " (*.htm *.html);;";
    //////filter += ")";
    return filter;
}


//// default :/images/ODTicon.png
#ifdef Q_WS_MAC
const QString rsrcPath = ":/images/mac";
#else
const QString rsrcPath = ":/images/win";
#endif

#include <QCloseEvent>

TextEdit::TextEdit(QWidget *parent)
    : QWidget(parent)
{
    mainLayout = new QVBoxLayout(this);
    toolBarSplitter1 = new QSplitter();
    toolBarSplitter2 = new QSplitter();

    menuBar = new QMenuBar(this);//
    mainLayout->setMenuBar(menuBar);
    mainLayout->addWidget(toolBarSplitter1);
    mainLayout->addWidget(toolBarSplitter2);

    setupFileActions();
    setupEditActions();
    setupTextActions();

    menuBar->addSeparator();

    //    {
    //        QMenu *helpMenu = new QMenu(tr("Help"), this);
    //        menuBar()->addMenu(helpMenu);
    //        ///// helpMenu->addAction(tr("About"), this, SLOT(about()));
    //        helpMenu->addAction(tr("About &Qt"), qApp, SLOT(aboutQt()));
    //    }

    textEdit = new DocEditor(0);//textEdit = new QTextEdit(this);//TODO: this istead of 0?

    //    Umargin = new DocMargin(panel);
    //    Umargin->setFixedHeight(33);
    //    gridLayout->addWidget(Umargin, 0, 0, 1, 1);
    //    gridLayout->addWidget(textEdit, 1, 0, 1, 1);
    //    setCentralWidget(panel);
    mainLayout->addWidget(textEdit);
    QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
    sizePolicy1.setHorizontalStretch(2);
    sizePolicy1.setVerticalStretch(0);
    sizePolicy1.setHeightForWidth(textEdit->sizePolicy().hasHeightForWidth());
    textEdit->setSizePolicy(sizePolicy1);
    textEdit->setFocus();//?
    
    ///7 connect(Umargin, SIGNAL(CursorMove(qreal, qreal)), this, SLOT(CursorMargins(qreal, qreal)));
    
    connect(textEdit, SIGNAL(currentCharFormatChanged(const QTextCharFormat &)),
            this, SLOT(currentCharFormatChanged(const QTextCharFormat &)));
    connect(textEdit, SIGNAL(cursorPositionChanged()),
            this, SLOT(cursorPositionChanged()));
    setWindowIcon(QIcon(":/images/ODTicon.png"));//FIXME:?
    
    setCurrentFileName(QString());

    fontChanged(textEdit->font());
    colorChanged(textEdit->textColor());
    alignmentChanged(textEdit->alignment());

    connect(textEdit->document(), SIGNAL(modificationChanged(bool)),
            actionSave, SLOT(setEnabled(bool)));
    connect(textEdit->document(), SIGNAL(modificationChanged(bool)),
            actionSaveToDB, SLOT(setEnabled(bool)));
    connect(textEdit->document(), SIGNAL(modificationChanged(bool)),
            this, SLOT(setWindowModified(bool)));
    connect(textEdit->document(), SIGNAL(undoAvailable(bool)),
            actionUndo, SLOT(setEnabled(bool)));
    connect(textEdit->document(), SIGNAL(redoAvailable(bool)),
            actionRedo, SLOT(setEnabled(bool)));

    setWindowModified(textEdit->document()->isModified());
    actionSave->setEnabled(textEdit->document()->isModified());
    actionSaveToDB->setEnabled(textEdit->document()->isModified());
    actionUndo->setEnabled(textEdit->document()->isUndoAvailable());
    actionRedo->setEnabled(textEdit->document()->isRedoAvailable());

    connect(actionUndo, SIGNAL(triggered()), textEdit, SLOT(undo()));
    connect(actionRedo, SIGNAL(triggered()), textEdit, SLOT(redo()));

    actionCut->setEnabled(false);
    actionCopy->setEnabled(false);

    connect(actionCut, SIGNAL(triggered()), textEdit, SLOT(cut()));
    connect(actionCopy, SIGNAL(triggered()), textEdit, SLOT(copy()));
    connect(actionPaste, SIGNAL(triggered()), textEdit, SLOT(paste()));

    connect(textEdit, SIGNAL(copyAvailable(bool)), actionCut, SLOT(setEnabled(bool)));
    connect(textEdit, SIGNAL(copyAvailable(bool)), actionCopy, SLOT(setEnabled(bool)));

    connect(QApplication::clipboard(), SIGNAL(dataChanged()), this, SLOT(clipboardDataChanged()));


    //    statusbar = new QStatusBar(this);
    //    statusbar->setObjectName(QString::fromUtf8("statusbar"));
    //    setStatusBar(statusbar);
    //TODO: statusbar?

    //// 4.41 = 263169

    ///////qDebug() << "### QT_VERSION  " << QT_VERSION;



    QString initialFile;
    const QStringList args = QCoreApplication::arguments();
    if (args.count() == 2)
        initialFile = args.at(1);

    if (!load(initialFile))
        fileNew();
}

void TextEdit::closeEvent(QCloseEvent *e) {
    if (maybeSave())
        e->accept();
    else
        e->ignore();
}

void TextEdit::CursorMargins(qreal left, qreal right) {
    ///////// qDebug() << "### on_Umargin_Cursor_Move " << left << "," << right;
    qreal dist = right - left;
    QTextFrame *Tframe = textEdit->document()->rootFrame();
    QTextFrameFormat rootformats = Tframe->frameFormat();
    rootformats.setBorder(0);
    rootformats.setLeftMargin(left - 1);
    rootformats.setRightMargin(Umargin->width() - right + 1);
    Tframe->setFrameFormat(rootformats);
}


void TextEdit::setupFileActions()
{
    QToolBar *tb = new QToolBar(this);
    tb->setWindowTitle(tr("File Actions"));
    tb->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
    toolBarSplitter1->addWidget(tb);tb->adjustSize();
    QMenu *menu = new QMenu(tr("&File"), this);
    menuBar->addMenu(menu);


    QAction *a;

    QIcon newIcon = QIcon::fromTheme("document-new", QIcon(rsrcPath + "/filenew.png"));
    a = new QAction( newIcon, tr("&New"), this);
    a->setPriority(QAction::LowPriority);
    a->setShortcut(QKeySequence::New);
    connect(a, SIGNAL(triggered()), this, SLOT(fileNew()));
    tb->addAction(a);
    menu->addAction(a);

    a = new QAction(QIcon::fromTheme("document-open", QIcon(rsrcPath + "/fileopen.png")),
                    tr("&Open..."), this);
    a->setShortcut(QKeySequence::Open);
    connect(a, SIGNAL(triggered()), this, SLOT(fileOpen()));
    tb->addAction(a);
    menu->addAction(a);

    menu->addSeparator();

    //dbsave
    actionSaveToDB = a = new QAction(QIcon::fromTheme("document-saveToDB", QIcon(rsrcPath + "/filesave.png")),
                                 tr("&DBSave"), this);
    //a->setShortcut(QKeySequence::Save);
    connect(a, SIGNAL(triggered()), this, SLOT(saveToDB()));
    a->setEnabled(false);
    tb->addAction(a);
    menu->addAction(a);
    //

    actionSave = a = new QAction(QIcon::fromTheme("document-save", QIcon(rsrcPath + "/filesave.png")),
                                 tr("&Save"), this);
    a->setShortcut(QKeySequence::Save);
    connect(a, SIGNAL(triggered()), this, SLOT(fileSave()));
    a->setEnabled(false);
    tb->addAction(a);
    menu->addAction(a);

    a = new QAction(tr("Save &As..."), this);
    a->setPriority(QAction::LowPriority);
    connect(a, SIGNAL(triggered()), this, SLOT(fileSaveAs()));
    menu->addAction(a);
    menu->addSeparator();

#ifndef QT_NO_PRINTER
    a = new QAction(QIcon::fromTheme("document-print", QIcon(rsrcPath + "/fileprint.png")),
                    tr("&Print..."), this);
    a->setPriority(QAction::LowPriority);
    a->setShortcut(QKeySequence::Print);
    connect(a, SIGNAL(triggered()), this, SLOT(filePrint()));
    tb->addAction(a);
    menu->addAction(a);

    a = new QAction(QIcon::fromTheme("fileprint", QIcon(rsrcPath + "/fileprint.png")),
                    tr("Print Preview..."), this);
    connect(a, SIGNAL(triggered()), this, SLOT(filePrintPreview()));
    menu->addAction(a);

    a = new QAction(QIcon::fromTheme("exportpdf", QIcon(rsrcPath + "/exportpdf.png")),
                    tr("&Export PDF..."), this);
    a->setPriority(QAction::LowPriority);
    a->setShortcut(Qt::CTRL + Qt::Key_D);
    connect(a, SIGNAL(triggered()), this, SLOT(filePrintPdf()));
    tb->addAction(a);
    menu->addAction(a);

    menu->addSeparator();
#endif

    a = new QAction(tr("&Quit"), this);
    a->setShortcut(Qt::CTRL + Qt::Key_Q);
    connect(a, SIGNAL(triggered()), this, SLOT(close()));
    menu->addAction(a);
}

void TextEdit::setupEditActions()
{
    QToolBar *tb = new QToolBar(this);
    tb->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
    toolBarSplitter1->addWidget(tb);tb->adjustSize();
    QMenu *menu = new QMenu(tr("&Edit"), this);
    menuBar->addMenu(menu);

    QAction *a;
    a = actionUndo = new QAction(QIcon::fromTheme("edit-undo", QIcon(rsrcPath + "/editundo.png")),
                                 tr("&Undo"), this);
    a->setShortcut(QKeySequence::Undo);
    tb->addAction(a);
    menu->addAction(a);
    a = actionRedo = new QAction(QIcon::fromTheme("edit-redo", QIcon(rsrcPath + "/editredo.png")),
                                 tr("&Redo"), this);
    a->setPriority(QAction::LowPriority);
    a->setShortcut(QKeySequence::Redo);
    tb->addAction(a);
    menu->addAction(a);
    menu->addSeparator();
    a = actionCut = new QAction(QIcon::fromTheme("edit-cut", QIcon(rsrcPath + "/editcut.png")),
                                tr("Cu&t"), this);
    a->setPriority(QAction::LowPriority);
    a->setShortcut(QKeySequence::Cut);
    tb->addAction(a);
    menu->addAction(a);
    a = actionCopy = new QAction(QIcon::fromTheme("edit-copy", QIcon(rsrcPath + "/editcopy.png")),
                                 tr("&Copy"), this);
    a->setPriority(QAction::LowPriority);
    a->setShortcut(QKeySequence::Copy);
    tb->addAction(a);
    menu->addAction(a);
    a = actionPaste = new QAction(QIcon::fromTheme("edit-paste", QIcon(rsrcPath + "/editpaste.png")),
                                  tr("&Paste"), this);
    a->setPriority(QAction::LowPriority);
    a->setShortcut(QKeySequence::Paste);
    tb->addAction(a);
    menu->addAction(a);
#ifndef QT_NO_CLIPBOARD
    if (const QMimeData *md = QApplication::clipboard()->mimeData())
        actionPaste->setEnabled(md->hasText());
#endif
}

void TextEdit::setupTextActions()
{
    QToolBar *tb = new QToolBar(this);
    tb->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
    tb->setWindowTitle(tr("Format Actions"));
    toolBarSplitter2->addWidget(tb);tb->adjustSize();

    QMenu *menu = new QMenu(tr("F&ormat"), this);
    menuBar->addMenu(menu);

    actionTextBold = new QAction(QIcon::fromTheme("format-text-bold", QIcon(rsrcPath + "/textbold.png")),
                                 tr("&Bold"), this);
    actionTextBold->setShortcut(Qt::CTRL + Qt::Key_B);
    actionTextBold->setPriority(QAction::LowPriority);
    QFont bold;
    bold.setBold(true);
    actionTextBold->setFont(bold);
    connect(actionTextBold, SIGNAL(triggered()), this, SLOT(textBold()));
    tb->addAction(actionTextBold);
    menu->addAction(actionTextBold);
    actionTextBold->setCheckable(true);

    actionTextItalic = new QAction(QIcon::fromTheme("format-text-italic", QIcon(rsrcPath + "/textitalic.png")),
                                   tr("&Italic"), this);
    actionTextItalic->setPriority(QAction::LowPriority);
    actionTextItalic->setShortcut(Qt::CTRL + Qt::Key_I);
    QFont italic;
    italic.setItalic(true);
    actionTextItalic->setFont(italic);
    connect(actionTextItalic, SIGNAL(triggered()), this, SLOT(textItalic()));
    tb->addAction(actionTextItalic);
    menu->addAction(actionTextItalic);
    actionTextItalic->setCheckable(true);

    actionTextUnderline = new QAction(QIcon::fromTheme("format-text-underline", QIcon(rsrcPath + "/textunder.png")),
                                      tr("&Underline"), this);
    actionTextUnderline->setShortcut(Qt::CTRL + Qt::Key_U);
    actionTextUnderline->setPriority(QAction::LowPriority);
    QFont underline;
    underline.setUnderline(true);
    actionTextUnderline->setFont(underline);
    connect(actionTextUnderline, SIGNAL(triggered()), this, SLOT(textUnderline()));
    tb->addAction(actionTextUnderline);
    menu->addAction(actionTextUnderline);
    actionTextUnderline->setCheckable(true);

    menu->addSeparator();

    QActionGroup *grp = new QActionGroup(this);
    connect(grp, SIGNAL(triggered(QAction*)), this, SLOT(textAlign(QAction*)));

    // Make sure the alignLeft  is always left of the alignRight
    if (QApplication::isLeftToRight()) {
        actionAlignLeft = new QAction(QIcon::fromTheme("format-justify-left", QIcon(rsrcPath + "/textleft.png")),
                                      tr("&Left"), grp);
        actionAlignCenter = new QAction(QIcon::fromTheme("format-justify-center", QIcon(rsrcPath + "/textcenter.png")), tr("C&enter"), grp);
        actionAlignRight = new QAction(QIcon::fromTheme("format-justify-right", QIcon(rsrcPath + "/textright.png")), tr("&Right"), grp);
    } else {
        actionAlignRight = new QAction(QIcon::fromTheme("format-justify-right", QIcon(rsrcPath + "/textright.png")), tr("&Right"), grp);
        actionAlignCenter = new QAction(QIcon::fromTheme("format-justify-center", QIcon(rsrcPath + "/textcenter.png")), tr("C&enter"), grp);
        actionAlignLeft = new QAction(QIcon::fromTheme("format-justify-left", QIcon(rsrcPath + "/textleft.png")), tr("&Left"), grp);
    }
    actionAlignJustify = new QAction(QIcon::fromTheme("format-justify-fill", QIcon(rsrcPath + "/textjustify.png")), tr("&Justify"), grp);

    actionAlignLeft->setShortcut(Qt::CTRL + Qt::Key_L);
    actionAlignLeft->setCheckable(true);
    actionAlignLeft->setPriority(QAction::LowPriority);
    actionAlignCenter->setShortcut(Qt::CTRL + Qt::Key_E);
    actionAlignCenter->setCheckable(true);
    actionAlignCenter->setPriority(QAction::LowPriority);
    actionAlignRight->setShortcut(Qt::CTRL + Qt::Key_R);
    actionAlignRight->setCheckable(true);
    actionAlignRight->setPriority(QAction::LowPriority);
    actionAlignJustify->setShortcut(Qt::CTRL + Qt::Key_J);
    actionAlignJustify->setCheckable(true);
    actionAlignJustify->setPriority(QAction::LowPriority);

    tb->addActions(grp->actions());
    menu->addActions(grp->actions());

    menu->addSeparator();

    QPixmap pix(16, 16);
    pix.fill(Qt::black);
    actionTextColor = new QAction(pix, tr("&Color..."), this);
    connect(actionTextColor, SIGNAL(triggered()), this, SLOT(textColor()));
    tb->addAction(actionTextColor);
    menu->addAction(actionTextColor);


    tb = new QToolBar(this);
    tb->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
    toolBarSplitter2->addWidget(tb);tb->adjustSize();
    tb->setAllowedAreas(Qt::TopToolBarArea | Qt::BottomToolBarArea);
    tb->setWindowTitle(tr("Format Actions"));

    QLabel *fontLabel = new QLabel(tb);
    fontLabel->setText(tr("Font:"));
    tb->addWidget(fontLabel);
    comboFont = new QFontComboBox(tb);
    comboFont->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
    tb->addWidget(comboFont);
    connect(comboFont, SIGNAL(activated(QString)),
            this, SLOT(textFamily(QString)));

    comboSize = new QComboBox(tb);
    comboSize->setObjectName("comboSize");
    tb->addWidget(comboSize);
    comboSize->setEditable(true);

    QFontDatabase db;
    foreach(int size, db.standardSizes())
        comboSize->addItem(QString::number(size));

    connect(comboSize, SIGNAL(activated(QString)),
            this, SLOT(textSize(QString)));
    comboSize->setCurrentIndex(comboSize->findText(QString::number(QApplication::font()
                                                                   .pointSize())));

    QLabel *listLabel = new QLabel(tb);
    listLabel->setText(tr("List:"));
    tb->addWidget(listLabel);
    comboStyle = new QComboBox(tb);
    comboStyle->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
    tb->addWidget(comboStyle);
    comboStyle->addItem("Standard");
    comboStyle->addItem("Bullet List (Disc)");
    comboStyle->addItem("Bullet List (Circle)");
    comboStyle->addItem("Bullet List (Square)");
    comboStyle->addItem("Ordered List (Decimal)");
    comboStyle->addItem("Ordered List (Alpha lower)");
    comboStyle->addItem("Ordered List (Alpha upper)");
    comboStyle->addItem("Ordered List (Roman lower)");
    comboStyle->addItem("Ordered List (Roman upper)");
    connect(comboStyle, SIGNAL(activated(int)),
            this, SLOT(textStyle(int)));
}

bool TextEdit::load(const QString &f) {
    QFileInfo fi(f);
    const QString ext = fi.completeSuffix().toLower();
    if (!fi.exists()) {
        return false;
    }

    if (ext == "odt" || ext == "ott") {
        /// ooo doc load
        OOO::Converter *doc_odt = new OOO::Converter();
        QTextDocument *doc = doc_odt->convert(f);
        textEdit->setDocument(doc);
        setCurrentFileName(f);
        showMaximized();
        return true;
    } else {

        QFile file(f);
        if (!file.open(QFile::ReadOnly))
            return false;

        QByteArray data = file.readAll();
        QTextCodec *codec = Qt::codecForHtml(data);
        QString str = codec->toUnicode(data);
        if (Qt::mightBeRichText(str)) {
            textEdit->setHtml(str);
        } else {
            str = QString::fromLocal8Bit(data);
            textEdit->setPlainText(str);
        }

        setCurrentFileName(f);
        showMaximized();
        return true;
    }
}

bool TextEdit::dbOpenRecord(const QByteArray data)//TODO: &data
{
    //QByteArray data = /**/
//    QTextCodec *codec = Qt::codecForHtml(data);
//    QString str = codec->toUnicode(data);
//    if (Qt::mightBeRichText(str)) {
//        textEdit->setHtml(str);
//    } else {
//        str = QString::fromLocal8Bit(data);
//        textEdit->setPlainText(str);
//    }

//    setCurrentFileName("database");
//    textEdit->document()->setModified(true);//FIXME:
//    return true;
    QBuffer buffer;
    buffer.setData(data);
    qDebug()<<"open buffer size:"<<data.size();

    OOO::Converter *doc_odt = new OOO::Converter();
    QTextDocument *doc = doc_odt->convertBytes(data);
    textEdit->setDocument(doc);
    setCurrentFileName("db");
    showMaximized();
    qDebug()<<"open buffer size:"<<data.size();
    return true;
}

bool TextEdit::maybeSave() {
    if (!textEdit->document()->isModified())
        return true;
    if (fileName.startsWith(QLatin1String(":/")))
        return true;
    QMessageBox::StandardButton ret;
    ret = QMessageBox::warning(this, tr("Application"),
                               tr("The document has been modified.\n"
                                  "Do you want to save your changes?"),
                               QMessageBox::Save | QMessageBox::Discard
                               | QMessageBox::Cancel);
    if (ret == QMessageBox::Save)
        return fileSave();
    else if (ret == QMessageBox::Cancel)
        return false;
    return true;
}

void TextEdit::setCurrentFileName(const QString &fileName) {
    this->fileName = fileName;
    textEdit->document()->setModified(false);

    QString shownName;
    if (fileName.isEmpty())
        shownName = "untitled.txt";
    else
        shownName = QFileInfo(fileName).fileName();
    setWindowTitle(_CVERSION_ + QString("%1 - OASIS Open Document").arg(shownName));
    setWindowModified(false);
}

void TextEdit::fileNew() {
    if (maybeSave()) {
        textEdit->clear();
        setCurrentFileName(QString());
    }
}

void TextEdit::fileOpen() {
    QString fn = QFileDialog::getOpenFileName(this, tr("Open File..."),
                                              QString(setter.value("LastDir").toString()), FileFilterHaving());
    if (!fn.isEmpty()) {
        QFileInfo fi(fn);
        setter.setValue("LastDir", fi.absolutePath() + "/");
        load(fn);

    }
}

bool TextEdit::fileSave()//libreoffice read saved files fine
{
    if (fileName.isEmpty())
        return fileSaveAs();

    bool canodt = false;
#if QT_VERSION >= 0x040500
    canodt = true;
#endif
    const QString ext = QFileInfo(fileName).completeSuffix().toLower();
    if (ext == "odt" && canodt) {
#if QT_VERSION >= 0x040500 
        QTextDocumentWriter writer(fileName);
                qDebug()<<"filesave size:"<<writer.device()->size();
        return writer.write(textEdit->document());
#endif
        return false;
    } else {
        QFile file(fileName);
        if (!file.open(QFile::WriteOnly))
            return false;
        QTextStream ts(&file);
        ts.setCodec(QTextCodec::codecForName("UTF-8"));
        ts << textEdit->document()->toHtml("UTF-8");
        textEdit->document()->setModified(false);
    }
    return true;
}


bool TextEdit::saveToDB()//TODO:define buffer in browser, send &
{
    QBuffer buffer;
    QTextDocumentWriter writer(&buffer,"odt");
    //FIXME:see KZipStream::KZipStream(const QByteArray &data) for proper buffer handling
    qDebug()<< "document writtten:" << writer.write(textEdit->document());
    qDebug()<<"save buffer size:"<<buffer.data().size();//must be  3298493
    //FIXME: layots/styles not saved, file save works fine
    //or styles/layouts not displayed on record open
    //see filesave:

    emit saveToDBsignal(buffer.data());//bad?

    textEdit->document()->setModified(false);
    return true;
}

bool TextEdit::fileSaveAs() {

    QString support;
#if QT_VERSION >= 0x040500
    support = tr("ODF files (*.odt);;HTML-Files (*.htm *.html);;All Files (*)");
#else
    support = tr("HTML-Files (*.htm *.html);;All Files (*)");
#endif
    QString fn = QFileDialog::getSaveFileName(this, tr("Save as..."),
                                              QString(), support);
    if (fn.isEmpty())
        return false;
    setCurrentFileName(fn);
    return fileSave();
}

void TextEdit::filePrint() {
#ifndef QT_NO_PRINTER
    QPrinter printer(QPrinter::HighResolution);
    QPrintDialog *dlg = new QPrintDialog(&printer, this);
    if (textEdit->textCursor().hasSelection())
        dlg->addEnabledOption(QAbstractPrintDialog::PrintSelection);
    dlg->setWindowTitle(tr("Print Document"));
    if (dlg->exec() == QDialog::Accepted) {
        textEdit->print(&printer);
    }
    delete dlg;
#endif
}

void TextEdit::filePrintPreview() {
#ifndef QT_NO_PRINTER
    QPrinter printer(QPrinter::HighResolution);
    QPrintPreviewDialog preview(&printer, this);
    preview.setWindowFlags(Qt::Window);
    connect(&preview, SIGNAL(paintRequested(QPrinter *)), SLOT(printPreview(QPrinter *)));
    preview.exec();
#endif
}

void TextEdit::printPreview(QPrinter *printer) {
#ifndef QT_NO_PRINTER
    textEdit->print(printer);
#endif
}

void TextEdit::filePrintPdf() {
#ifndef QT_NO_PRINTER
    //! [0]
    QString fileName = QFileDialog::getSaveFileName(this, "Export PDF",
                                                    QString(), "*.pdf");
    if (!fileName.isEmpty()) {
        if (QFileInfo(fileName).suffix().isEmpty())
            fileName.append(".pdf");
        QPrinter printer(QPrinter::HighResolution);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setOutputFileName(fileName);
        textEdit->document()->print(&printer);
    }
    //! [0]
#endif
}

void TextEdit::textBold() {
    QTextCharFormat fmt;
    fmt.setFontWeight(actionTextBold->isChecked() ? QFont::Bold : QFont::Normal);
    mergeFormatOnWordOrSelection(fmt);
}

void TextEdit::textUnderline() {
    QTextCharFormat fmt;
    fmt.setFontUnderline(actionTextUnderline->isChecked());
    mergeFormatOnWordOrSelection(fmt);
}

void TextEdit::textItalic() {
    QTextCharFormat fmt;
    fmt.setFontItalic(actionTextItalic->isChecked());
    mergeFormatOnWordOrSelection(fmt);
}

void TextEdit::textFamily(const QString &f) {
    QTextCharFormat fmt;
    fmt.setFontFamily(f);
    mergeFormatOnWordOrSelection(fmt);
}

void TextEdit::textSize(const QString &p) {
    QTextCharFormat fmt;
    fmt.setFontPointSize(p.toFloat());
    mergeFormatOnWordOrSelection(fmt);
}

void TextEdit::textStyle(int styleIndex) {
    QTextCursor cursor = textEdit->textCursor();

    if (styleIndex != 0) {
        QTextListFormat::Style style = QTextListFormat::ListDisc;

        switch (styleIndex) {
        default:
        case 1:
            style = QTextListFormat::ListDisc;
            break;
        case 2:
            style = QTextListFormat::ListCircle;
            break;
        case 3:
            style = QTextListFormat::ListSquare;
            break;
        case 4:
            style = QTextListFormat::ListDecimal;
            break;
        case 5:
            style = QTextListFormat::ListLowerAlpha;
            break;
        case 6:
            style = QTextListFormat::ListUpperAlpha;
            break;
        }

        cursor.beginEditBlock();

        QTextBlockFormat blockFmt = cursor.blockFormat();

        QTextListFormat listFmt;

        if (cursor.currentList()) {
            listFmt = cursor.currentList()->format();
        } else {
            listFmt.setIndent(blockFmt.indent() + 1);
            blockFmt.setIndent(0);
            cursor.setBlockFormat(blockFmt);
        }

        listFmt.setStyle(style);

        cursor.createList(listFmt);

        cursor.endEditBlock();
    } else {
        // ####
        QTextBlockFormat bfmt;
        bfmt.setObjectIndex(-1);
        cursor.mergeBlockFormat(bfmt);
    }
}

void TextEdit::textColor() {
    QColor col = QColorDialog::getColor(textEdit->textColor(), this);
    if (!col.isValid())
        return;
    QTextCharFormat fmt;
    fmt.setForeground(col);
    mergeFormatOnWordOrSelection(fmt);
    colorChanged(col);
}

void TextEdit::textAlign(QAction *a) {
    if (a == actionAlignLeft)
        textEdit->setAlignment(Qt::AlignLeft);
    else if (a == actionAlignCenter)
        textEdit->setAlignment(Qt::AlignHCenter);
    else if (a == actionAlignRight)
        textEdit->setAlignment(Qt::AlignRight);
    else if (a == actionAlignJustify)
        textEdit->setAlignment(Qt::AlignJustify);
}

void TextEdit::currentCharFormatChanged(const QTextCharFormat &format) {
    fontChanged(format.font());
    colorChanged(format.foreground().color());
}

void TextEdit::cursorPositionChanged() {
    alignmentChanged(textEdit->alignment());
}

void TextEdit::clipboardDataChanged() {
    actionPaste->setEnabled(!QApplication::clipboard()->text().isEmpty());
}

void TextEdit::about() {
    QMessageBox::about(this, tr("About"), tr("This example demonstrates Qt's "
                                             "rich text editing facilities in action, providing an example "
                                             "document for you to experiment with."));
}

void TextEdit::mergeFormatOnWordOrSelection(const QTextCharFormat &format) {
    QTextCursor cursor = textEdit->textCursor();
    if (!cursor.hasSelection())
        cursor.select(QTextCursor::WordUnderCursor);
    cursor.mergeCharFormat(format);
    textEdit->mergeCurrentCharFormat(format);
}

void TextEdit::fontChanged(const QFont &f) {
    comboFont->setCurrentIndex(comboFont->findText(QFontInfo(f).family()));
    comboSize->setCurrentIndex(comboSize->findText(QString::number(f.pointSize())));
    actionTextBold->setChecked(f.bold());
    actionTextItalic->setChecked(f.italic());
    actionTextUnderline->setChecked(f.underline());
}

void TextEdit::colorChanged(const QColor &c) {
    QPixmap pix(16, 16);
    pix.fill(c);
    actionTextColor->setIcon(pix);
}

void TextEdit::alignmentChanged(Qt::Alignment a) {
    if (a & Qt::AlignLeft) {
        actionAlignLeft->setChecked(true);
    } else if (a & Qt::AlignHCenter) {
        actionAlignCenter->setChecked(true);
    } else if (a & Qt::AlignRight) {
        actionAlignRight->setChecked(true);
    } else if (a & Qt::AlignJustify) {
        actionAlignJustify->setChecked(true);
    }
}

