#ifndef CPP4_3DVIEWER_V2_0_SRC_CONTROLLER_GLVIEW_H
#define CPP4_3DVIEWER_V2_0_SRC_CONTROLLER_GLVIEW_H

#define GL_SILENCE_DEPRECATION  // Ignore OpenGL deprecation warnings

#include <QMatrix4x4>
#include <QMouseEvent>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLVertexArrayObject>
#include <QVector>
#include <QtOpenGLWidgets/QOpenGLWidget>
#include <iostream>

#include "../controller/controller_singleton.h"
#include "../observer/observer.h"
#include "settings.h"

/// @brief The glView class is responsible for rendering the 3D model.
class glView : public QOpenGLWidget,
               public QOpenGLFunctions,
               public s21::Observer {
  Q_OBJECT

 public:
  /**
   * @brief Get a singleton instance of the glView class.
   * @param c Pointer to the controller instance.
   * @param parent QWidget parent.
   * @return Pointer to the glView instance.
   */
  static glView *getInstance(s21::Controller *c, QWidget *parent);

  /// @brief Destructor
  ~glView();

  /**
   * @brief Function to handle scrollbar events.
   * @param Value of the scrollbar.
   * @param QString representing the type of scrollbar.
   */
  void scrollBar(int, QString);

  /**
   * @brief Virtual function to set options based on the provided settings.
   * @param options The Settings object containing configuration options.
   */
  virtual void setOptions(s21::Settings options) override {
    colorBack = options.back_color;
    colorDot = options.vertex_color;
    colorLine = options.line_color;
    proection = options.projection_orth;
    lineSize = options.line_width;
    dotSize = options.vertex_size;
    dotType = options.vertex_type;
    lineType = options.line_type;
    options.SaveSettings();
    update();
  };

  /**
   * @brief Function to translate and display the 3D model.
   * @param vertex Vector containing vertex coordinates.
   * @param object Vector containing object segments.
   */
  void translate(std::vector<float> vertex, std::vector<int64_t> object);

 private slots:

 protected:
  /// @brief Function to initialize OpenGL context.
  void initializeGL() override;

  /// @brief Function to handle resizing of the OpenGL widget.
  void resizeGL(int, int) override;

  /// @brief Function to handle painting (drawing) on the OpenGL widget.
  void paintGL() override;

  /// @brief Function to handle mouse press events.
  void mousePressEvent(QMouseEvent *) override;

  /// @brief Function to handle mouse move events.
  void mouseMoveEvent(QMouseEvent *) override;

  /// @brief Function to handle wheel (scroll) events.
  void wheelEvent(QWheelEvent *event) override;

  /// @brief Function to initialize drawing settings.
  void initDraw();

 private:
  /// @brief Helper function to reset internal variables.
  void zeroing();

  /// @brief Constructor
  glView(s21::Controller *c, QWidget *parent = nullptr);

  static glView *instance; /**< Pointer to the singleton instance of glView */
  s21::Controller *controller; /**< Pointer to the controller instance */
  QMatrix4x4 projection_m;     /**< QMatrix4x4 for projection */
  QOpenGLShaderProgram
      m_program; /**< QOpenGLShaderProgram for OpenGL shaders */
  QOpenGLVertexArrayObject
      m_vao;                   /**< QOpenGLVertexArrayObject for vertex array */
  QOpenGLBuffer m_arrayBuffer; /**< QOpenGLBuffer for vertex data */
  QOpenGLBuffer m_indexBuffer; /**< QOpenGLBuffer for index data */
  QVector2D m_mousePosition;   /**< QVector2D for mouse position */
  QVector3D m_rotation;        /**< QVector3D for rotation angles */
  QVector3D m_translation;     /**< QVector3D for translation */
  QVector<float> pointsGL = {0}; /**< QVector<float> for vertex coordinates */
  QVector<unsigned int> modelGL = {
      0};                /**< QVector<unsigned int> for object segments */
  float scale = 1;       /**< Scaling factor */
  bool proection = 0;    /**< Flag for orthographic projection */
  int openFileFl = 0;    /**< Flag to indicate if a file is open */
  int lineType = 0;      /**< Line type */
  int dotType = 0;       /**< Dot type */
  float lineSize = 1;    /**< Line size */
  float dotSize = 1;     /**< Dot size */
  QColor colorDot = {};  /**< QColor for dot color */
  QColor colorLine = {}; /**< QColor for line color */
  QColor colorBack = {}; /**< QColor for background color */
};

#endif  // CPP4_3DVIEWER_V2_0_SRC_CONTROLLER_GLVIEW_H
