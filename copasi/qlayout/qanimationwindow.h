// Copyright (C) 2013 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef QANIMATION_WINDOW_H
#define QANIMATION_WINDOW_H

#include <QMainWindow>
#include <qsharedpointer.h>

#include <UI/CWindowInterface.h>

#include <qlayout/ui_qanimationwindow.h>

class QLayoutScene;
class QCopasiAnimation;
class CCopasiDataModel;
class QCloseEvent;
class QMenu;
class CLayout;
class CQLayoutThread;

class QAnimationWindow : public CWindowInterface, public Ui::QAnimationWindow
{
  Q_OBJECT
public:
  QAnimationWindow(CLayout* layout, CCopasiDataModel* dataModel = NULL);
  QAnimationWindow();
  virtual ~QAnimationWindow();
  void setScene(QLayoutScene* scene, CCopasiDataModel* dataModel);
  void setAnimation(QCopasiAnimation* animation, CCopasiDataModel* dataModel);
  virtual QMenu *getWindowMenu() const;
public slots:
  void slotShowStep(int);
  void slotExportImage();
  void slotEditSettings();
  void slotSwitchAnimation();
  void slotRandomizeLayout();
  void slotAutoLayout();
  void slotStopLayout();
  void slotRedrawScene();
  void slotLayoutCreated(QSharedPointer<CLayout> layout);
private:
  void init();
  void toggleUI(bool isPlaying);
  void reloadLayout(CLayout* layout);
protected:
  virtual void closeEvent(QCloseEvent *closeEvent);

  QLayoutScene* mpScene;
  CCopasiDataModel* mpModel;
  QMenu* mpWindowMenu;
  QCopasiAnimation* mAnimation;
  CQLayoutThread* mpLayoutThread;
};

#endif // QANIMATION_WINDOW_H