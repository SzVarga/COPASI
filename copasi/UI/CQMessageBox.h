// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef CQMESSAGEBOX_H
#define CQMESSAGEBOX_H

#include <QMessageBox>

#include <set>

class QTabWidget;
class QTextEdit;
class QVBoxLayout;
class CDataObject;
class CFunctionDB;
class CDataModel;
class CObjectInterface;
class CDataContainer;

class CQMessageBox: public QMessageBox
{
  Q_OBJECT

public:
  CQMessageBox(Icon icon, const QString &title, const QString &text,
               StandardButtons buttons = NoButton, QWidget *parent = 0,
               Qt::WindowFlags f = Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

  ~CQMessageBox();

  static StandardButton information(QWidget *parent, const QString &title,
                                    const QString &text, StandardButtons buttons = Ok,
                                    StandardButton defaultButton = NoButton);

  static StandardButton question(QWidget *parent, const QString &title,
                                 const QString &text, StandardButtons buttons = Ok,
                                 StandardButton defaultButton = NoButton);

  static StandardButton warning(QWidget *parent, const QString &title,
                                const QString &text, StandardButtons buttons = Ok,
                                StandardButton defaultButton = NoButton);

  static StandardButton critical(QWidget *parent, const QString &title,
                                 const QString &text, StandardButtons buttons = Ok,
                                 StandardButton defaultButton = NoButton);

  static StandardButton confirmDelete(QWidget *parent,
                                      const QString &objectType, const QString &objects,
                                      const CDataContainer * pContainer);

  static QString buildDeleteConfirmationMessage(const QString & objectType,
      const QString & objects,
      CFunctionDB * pFunctionDB,
      std::set< const CObjectInterface * > & DeletedObjects,
      const CDataModel * pDataModel,
      bool& isUsed);

  void setText(const QString & text);

  void setFilteredText(const QString & text);

protected:
  QTabWidget *mpTabWidget;
  QWidget *mpPage1;
  QVBoxLayout *mpVerticalLayoutPage1;
  QTextEdit *mpText1;
  QWidget *mpPage2;
  QVBoxLayout *mpVerticalLayoutPage2;
  QTextEdit *mpText2;
};

#endif // CQMESSAGEBOX_H
