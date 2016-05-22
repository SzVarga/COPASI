// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * CBrowseModelVersionDialog.h
 *
 *  Created on: 21 Feb 2016
 *      Author: Peyman Zarrineh
 */

#ifndef CBrowseModelVersionDialog_H
#define CBrowseModelVersionDialog_H

#include <QDialog>
#include "versioning/CModelVersion.h"
#include "DataModelGUI.h"

#ifdef COPASI_Provenance
#include <QUndoStack>
#endif

namespace Ui
{
class CBrowseModelVersionDialog;
}

class CBrowseModelVersionDialog : public QDialog
{

  Q_OBJECT

public:

  /**
   * Default constructor
   * Fetch Version Hierarchy Model data and show it in a table
   */
  explicit CBrowseModelVersionDialog(QWidget *parent = 0, CModelVersion * ModelVersion = NULL, DataModelGUI * ModelGUI = NULL,   QString LastSavedParentOfCurrentModel = QString("")
#ifdef COPASI_Provenance
                                     , QUndoStack  *     UndoStack = NULL, QString PathProvenance = QString(""),  QString ProvenanceParentOfCurrentModel = QString("")
#endif
                                    );

  /**
   * Destructor
   */
  ~CBrowseModelVersionDialog();

  /**
   * Returns the last saved Parent of Current Model
   * In delete case if the last saved Parrent of Current Model changes
   * It is subtitued with its parrent
   */
  QString getLastSavedParentOfCurrentModel();

#ifdef COPASI_Provenance
  /**
   * Returns the Provenance Parent of Current Model
   */
  QString getProvenanceParentOfCurrentModel();
#endif

private:

  Ui::CBrowseModelVersionDialog *ui;

  /**
   * A pointer to Version Hierarchy Model data
   */
  CModelVersion * mpModelVersion;

  /**
   * A pointer to Data Model GUI
   * It is used to load a .cps file
   */
  DataModelGUI * mpDataModelGUI;

  /**
   * The last created/resotored version at the last saving occasion
   */
  QString mLastSavedParentOfCurrentModel;

#ifdef COPASI_Provenance
  QUndoStack  *     mpUndoStack;
  QString           mPathProvenance;
  QString mProvenanceParentOfCurrentModel;
#endif

private slots:

  /**
  * When Restore button clicked, restore the selected version
  */
  void on_RestoreButton_clicked();

  /**
  * When Delete button clicked, delete the selected version
  */
  void on_DeleteButton_clicked();

  /**
  * When a row selected, make Restore and Delete buttons available
  */
  void on_tableView_clicked();

  /**
  * If a comment double clicked, make that comment editable
  */
  void on_tableView_doubleClicked(const QModelIndex &index);
};

#endif // CBrowseModelVersionDialog_H