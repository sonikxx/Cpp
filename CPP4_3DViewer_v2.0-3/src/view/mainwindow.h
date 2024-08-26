#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QColorDialog>
#include <QDir>
#include <QFileSystemModel>
#include <QMainWindow>
#include <QStringList>
#include <QWidget>
#include <QtGui>
#include <QtOpenGLWidgets/QOpenGLWidget>

#include "../controller/controller_singleton.h"
#include "gifimage/qgifimage.h"
#include "glview.h"
#include "settings.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

/**
 * @brief The MainWindow class
 * This class represents the main window of the application.
 */
class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  /**
   * @brief MainWindow Constructor
   * @param Controller Pointer to the controller instance.
   * @param parent Pointer to the parent widget.
   */
  MainWindow(s21::Controller *Controller, QWidget *parent = nullptr);

  /// @brief Destructor
  ~MainWindow();

 private slots:
  /**
   * @brief Slot for handling double-click events on the list view.
   * @param index The index of the clicked item.
   */
  void on_listView_doubleClicked(const QModelIndex &index);

  /// @brief Slot for handling button click events.
  void on_pushButton_clicked();

  /// @brief Slot for setting the color.
  void setColor();

  /// @brief Slot for handling projection changes.
  void proectionChanged();

  /// @brief Slot for handling dot type changes.
  void dotTypeChanged();

  /// @brief Slot for handling line type changes.
  void lineTypeChanged();

  /// @brief Slot for handling radio button value changes.
  void radioButtonValue();

  /**
   * @brief Slot for handling scroll bar value changes.
   * @param value The new value of the scroll bar.
   */
  void on_verticalScrollBar_valueChanged(int value);

  /// @brief Slot for handling GIF button click events.
  void on_pushButtonGIF_clicked();

  /// @brief Slot for handling JPG button click events.
  void on_pushButtonJPG_clicked();

  /// @brief Slot for handling BMP button click events.
  void on_pushButtonBMP_clicked();

  /// @brief Slot for handling timer finish events.
  void slotTimerFinish();

 private:
  /// @brief Function for configuring settings.
  void settingConfig();

  Ui::MainWindow *ui;          /**< Pointer to the UI instance */
  s21::Controller *Controller; /**< Pointer to the controller instance */
  glView *win;                 /**< Pointer to the OpenGL view */
  QFileSystemModel *fileList;  /**< Pointer to the file system model */
  QDir dir;                    /**< Directory object */
  QString choiceDirectory;     /**< String for the chosen directory */
  s21::Settings Options;       /**< Settings object */
  int index = 0;               /**< Index value */
  int valueScrolBar = 50;      /**< Value of the scroll bar */
  int valueZoomeLine = 0;      /**< Value for zooming lines */
  int valueZoomeDot = 0;       /**< Value for zooming dots */
  int valueZoomeModel = 50;    /**< Value for zooming model */
  QColor color;                /**< Color object */
  QString checkerName;         /**< String for checker name */
  QImage *images;              /**< Pointer to image array */
  int imagesCounter;           /**< Counter for images */
  QTimer *timer;               /**< Pointer to timer object */
};
#endif  // MAINWINDOW_H
