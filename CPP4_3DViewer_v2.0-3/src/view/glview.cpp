#include "glview.h"
#include <iostream>

glView::glView(s21::Controller *c, QWidget *parent)
    : QOpenGLWidget(parent),
      m_arrayBuffer(QOpenGLBuffer::VertexBuffer),
      m_indexBuffer(QOpenGLBuffer::IndexBuffer),
      controller(c) {}

glView *glView::instance = nullptr;

glView *glView::getInstance(s21::Controller *c, QWidget *parent) {
    if (instance == nullptr) {
        instance = new glView(c, parent);
    }
    return instance;
}

glView::~glView(){};

const char *vertexShaderSource =
    "#version 410 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "uniform mat4 qt_ModelViewProjectionMatrix;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = qt_ModelViewProjectionMatrix * vec4(aPos.x, aPos.y, "
    "aPos.z, 1.0);\n"
    "}\0";

const char *fragmentShaderSource =
    "#version 410 core\n"
    "in vec4 Color;\n"
    "out vec4 FragColor;\n"
    "uniform vec4 qt_lineColor;\n"
    "uniform int qt_lineType;\n"
    "uniform int qt_dotType;\n"
    "void main()\n"
    "{\n"
    "float u_dashSize = 1;\n"
    "float u_gapSize = 20;\n"
    "float val = mod(gl_FragCoord.x, (u_dashSize + u_gapSize)) / (u_dashSize + "
    "u_gapSize);\n"
    "if (qt_lineType == 1 && Color.w != 0) {\n"
    "if (val > 0.7) {\n"
    "FragColor = Color;\n"
    "} else {\n"
    "discard;\n"
    "}\n"
    "} else {\n"

    "FragColor = Color;\n"
    "}\n"
    "}\0";

const char *geometryShaderSource =
    "#version 410 core\n"
    "layout (lines) in;\n"
    "layout (triangle_strip, max_vertices = 24) out;\n"
    "uniform float qt_lineWidth;\n"
    "uniform float qt_dotWidth;\n"
    "uniform vec4 qt_dotColor;\n"
    "uniform vec4 qt_lineColor;\n"
    "uniform int qt_lineType;\n"
    "uniform int qt_dotType;\n"
    "out vec4 Color;\n"
    "void main()\n"
    "{\n"
    "if (qt_dotType == 1) {\n"
    "Color = qt_dotColor;\n"
    "Color.w = 0;\n"
    "gl_Position = gl_in[0].gl_Position + vec4(-qt_dotWidth, -qt_dotWidth, "
    "0.0, 0.0);\n"
    "EmitVertex();\n"
    "gl_Position = gl_in[0].gl_Position + vec4(qt_dotWidth, -qt_dotWidth, 0.0, "
    "0.0);\n"
    "EmitVertex();\n"
    "gl_Position = gl_in[0].gl_Position + vec4(-qt_dotWidth, qt_dotWidth, 0.0, "
    "0.0);\n"
    "EmitVertex();\n"
    "gl_Position = gl_in[0].gl_Position + vec4(qt_dotWidth, qt_dotWidth, 0.0, "
    "0.0);\n"
    "EmitVertex();\n"
    "}"
    "if (qt_dotType == 0) {\n"
    "Color = qt_dotColor;\n"
    "Color.w = 0;\n"
    "for (int i = 0; i <= 8; ++i) {\n"
    "float angle = float(i) * 0.19634954084936207 * 4;\n"
    "vec2 offset = vec2(cos(angle) * qt_dotWidth, sin(angle) * qt_dotWidth);\n"
    "gl_Position = gl_in[0].gl_Position + vec4(offset, 0.0, 0.0);\n"
    "EmitVertex();\n"
    "gl_Position = gl_in[0].gl_Position - vec4(offset, 0.0, 0.0);\n"
    "EmitVertex();\n"
    "}\n"
    "}\n"
    "EndPrimitive();\n"
    "if (qt_lineType != 2) {\n"
    "Color = qt_lineColor;\n"
    "vec2 dir_vec = normalize(gl_in[1].gl_Position.xy - "
    "gl_in[0].gl_Position.xy);\n"
    "vec2 normal = vec2(-dir_vec.y, dir_vec.x) * qt_lineWidth;\n"
    "gl_Position = gl_in[0].gl_Position + vec4(normal, 0.0, 0.0);\n"
    "EmitVertex();\n"
    "gl_Position = gl_in[0].gl_Position - vec4(normal, 0.0, 0.0);\n"
    "EmitVertex();\n"
    "gl_Position = gl_in[1].gl_Position + vec4(normal, 0.0, 0.0);\n"
    "EmitVertex();\n"
    "gl_Position = gl_in[1].gl_Position - vec4(normal, 0.0, 0.0);\n"
    "EmitVertex();\n"
    "EndPrimitive();\n"
    "}\n"
    "}\0";

void glView::scrollBar(int valueButton, QString check) {
    if (check == "radioButtonRotationY") {
        m_rotation.setX(m_rotation.x() + valueButton * 4.0);
    } else if (check == "radioButtonRotationX") {
        m_rotation.setY(m_rotation.y() + valueButton * 4.0);
    } else if (check == "radioButtonRotationZ") {
        m_rotation.setZ(m_rotation.z() + valueButton * 4.0);
    } else if (check == "radioButtonMoveX") {
        m_translation.setX(m_translation.x() + valueButton / 50.0);
    } else if (check == "radioButtonMoveY") {
        m_translation.setY(m_translation.y() - valueButton / 50.0);
    } else if (check == "radioButtonMoveZ") {
        m_translation.setZ(m_translation.z() + valueButton / 50.0);
    } else if ((check == "radioButtonZoomeModel") &&
               (scale + valueButton / 50.0) > 0) {
        scale = scale + valueButton / 50.0;
    }
    update();
}

void glView::translate(std::vector<float> p, std::vector<int64_t> k) {
    std::vector<unsigned int> m(k.begin(), k.end());
    pointsGL = QVector<float>(p.begin(), p.end());
    modelGL = QVector<unsigned int>(m.begin(), m.end());
    openFileFl = 1;
    zeroing();
    m_arrayBuffer.bind(); // размещение памяти
    m_arrayBuffer.allocate(
        pointsGL.constData(),
        pointsGL.size() *
            sizeof(float)); // выделение памяти и газрузка укзанных данных
    m_arrayBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_indexBuffer.bind(); // размещение памяти
    m_indexBuffer.allocate(
        modelGL.constData(),
        modelGL.size() *
            sizeof(unsigned int)); // выделение памяти и газрузка укзанных данных
    m_indexBuffer.setUsagePattern(QOpenGLBuffer::StaticDraw);
    m_indexBuffer.release();
    m_arrayBuffer.release();
    update();
}

void glView::initializeGL() {
    initializeOpenGLFunctions();
    glClearColor(colorBack.redF(), colorBack.greenF(), colorBack.blueF(),
                 colorBack.alphaF());
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE); // включает отсечение задней грани
    initDraw();
}

void glView::resizeGL(int w, int h) { glViewport(0, 0, w, h); }

void glView::paintGL() {
    glClearColor(colorBack.redF(), colorBack.greenF(), colorBack.blueF(),
                 colorBack.alphaF()); // not working
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if (openFileFl) {
        projection_m.setToIdentity(); // единичная матрица
        if (proection) {
            projection_m.ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f);
        } else {
            projection_m.perspective(45, 1, 0.1f,
                                     10.0f); // последние два параметра - передняя и
                                             // дальняя плоскости отсечения
        }
        m_program.bind();
        controller->Transform(m_rotation, m_translation, scale);

        m_program.setUniformValue("qt_ModelViewProjectionMatrix",
                                  projection_m * controller->Getter());
        m_program.setUniformValue("qt_lineWidth", lineSize / 10);
        m_program.setUniformValue("qt_dotWidth", dotSize);
        m_program.setUniformValue("qt_lineColor", colorLine);
        m_program.setUniformValue("qt_dotColor", colorDot);
        m_program.setUniformValue("qt_dotType", dotType);
        m_program.setUniformValue("qt_lineType", lineType);
        m_arrayBuffer.bind();
        m_vao.bind();
        m_indexBuffer.bind();
        glDrawElements(GL_LINES, modelGL.size(), GL_UNSIGNED_INT, nullptr);
        m_indexBuffer.release();
        m_vao.release();
        m_arrayBuffer.release();
        m_program.release();
    }
}

void glView::mousePressEvent(QMouseEvent *event) {
    if ((event->buttons() == Qt::LeftButton) ||
        (event->buttons() == Qt::RightButton))
        m_mousePosition = QVector2D(event->position());
    event->accept();
}

void glView::mouseMoveEvent(QMouseEvent *event) {
    if (event->buttons() == Qt::LeftButton) {
        QVector2D delta = QVector2D(event->position()) - m_mousePosition;
        m_mousePosition = QVector2D(event->position());
        m_rotation.setX(m_rotation.x() + delta.x());
        m_rotation.setY(m_rotation.y() + delta.y());
    } else if (event->buttons() == Qt::RightButton) {
        QVector2D delta = QVector2D(event->position()) - m_mousePosition;
        m_mousePosition = QVector2D(event->position());
        m_translation.setX(m_translation.x() + (delta.x() / 100));
        m_translation.setY(m_translation.y() - (delta.y() / 100));
    }
    update();
}

void glView::wheelEvent(QWheelEvent *event) {
    QPoint circle = event->pixelDelta();
    if ((event->buttons() & Qt::LeftButton)) {
        m_rotation.setZ(m_rotation.z() + (float)circle.y() / 20);
    } else if ((event->buttons() & Qt::RightButton)) {
        m_translation.setZ(m_translation.z() + (float)circle.y() / 200);
    } else if ((scale + ((float)circle.y() / 100)) > 0) {
        scale = scale + ((float)circle.y() / 100);
    }
    update();
}

void glView::initDraw() {
    m_program.create();
    m_program.bind();
    if (!m_program.addShaderFromSourceCode(QOpenGLShader::Vertex,
                                           vertexShaderSource))
        close();
    if (!m_program.addShaderFromSourceCode(QOpenGLShader::Geometry,
                                           geometryShaderSource))
        close();
    if (!m_program.addShaderFromSourceCode(QOpenGLShader::Fragment,
                                           fragmentShaderSource))
        close();
    if (!m_program.link())
        close();
    m_vao.create();
    m_vao.bind();
    m_arrayBuffer.create();
    m_arrayBuffer.bind(); // размещение памяти
    m_arrayBuffer.allocate(
        pointsGL.constData(),
        pointsGL.size() *
            sizeof(float)); // выделение памяти и газрузка укзанных данных

    m_indexBuffer.create();
    m_indexBuffer.bind(); // размещение памяти
    m_indexBuffer.allocate(
        modelGL.constData(),
        modelGL.size() *
            sizeof(unsigned int)); // выделение памяти и газрузка укзанных данных

    m_program.enableAttributeArray("aPos");
    m_program.setAttributeBuffer("aPos", GL_FLOAT, 0, 3);

    m_program.release();
    m_indexBuffer.release();
    m_vao.release();
    m_arrayBuffer.release();
}

void glView::zeroing() {
    m_rotation.setX(0);
    m_rotation.setY(0);
    m_rotation.setZ(0);
    m_translation.setX(0);
    m_translation.setY(0);
    m_translation.setZ(0);
    scale = 1;
}
