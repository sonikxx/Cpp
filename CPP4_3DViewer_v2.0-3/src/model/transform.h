#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <QMatrix4x4>
#include <QVector3D>
#include <tuple>
#include <vector>

#include "data.h"

namespace s21 {

/**
 * @class Transform
 * @brief A class for applying transformations (translation, rotation, scaling)
 * to 3D model data.
 */
class Transform {
 public:
  /**
   * @brief Constructor for the Transform class.
   * @param data A reference to the Data object to transform.
   */
  Transform(Data &data) : data_(data) {}

  /**
   * @brief Method to translate the data model.
   * @param m_translation A QVector3D containing translation values.
   */
  void Move(QVector3D m_rotation);

  /**
   * @brief Method to rotate the data model.
   * @param m_rotation A QVector3D containing rotation values (angles in
   * degrees).
   */
  void Rotate(QVector3D m_rotation);

  /**
   * @brief Method to scale the data model.
   * @param scale A float value to scale the model.
   */
  void Scale(float scale);

  /**
   * @brief Method to get the current transformation matrix.
   * @return A QMatrix4x4 representing the transformation matrix.
   */
  QMatrix4x4 Getter();

 private:
  Data &data_; /**< Reference to the Data object to store transformed data. */
  QMatrix4x4 matrix_; /**< Matrix to store the current transformation state. */
};

}  // namespace s21

#endif  // TRANSFORM_H
