#ifndef MODEL_H
#define MODEL_H

#include "data.h"
#include "normalizer.h"
#include "parser.h"
#include "transform.h"

namespace s21 {

/**
 * @class Model
 * @brief A facade class that provides a simplified interface for managing and
 * transforming 3D model data.
 */
class Model {
 private:
  Data data_; /**< The data object that holds vertex and face information. */
  Parser parser_; /**< The parser object for reading 3D model files. */
  Normalizer
      normalizer_; /**< The normalizer object for normalizing the model data. */
  Transform transform_; /**< The transform object for applying transformations
                           to the model. */

 public:
  /**
   * @brief Constructor for the Model class.
   * @param filename The filename of the 3D model file.
   */
  Model(const std::string &filename)
      : data_(), parser_(data_), normalizer_(), transform_(data_) {
    data_.SetFilename(filename);
  }

  /**
   * @brief Initialize the model by reading the file and normalizing the data.
   */
  void Init();

  /**
   * @brief Apply transformations to the model.
   * @param m_rotation The rotation vector.
   * @param m_translation The translation vector.
   * @param scale The scale factor.
   */
  void Transformation(QVector3D m_rotation, QVector3D m_translation,
                      float scale);

  /**
   * @brief Get the Data object.
   * @return A reference to the Data object.
   */
  Data &GetData();

  /**
   * @brief Get the transformation matrix.
   * @return The transformation matrix.
   */
  QMatrix4x4 Getter();

  /**
   * @brief Get the vertex coordinates of the model.
   * @return A vector of vertex coordinates.
   */
  std::vector<float> GetVertexes() const { return data_.GetVertexes(); }

  /**
   * @brief Get the face indices of the model.
   * @return A vector of face indices.
   */
  std::vector<int64_t> GetFaces() const { return data_.GetFaces(); }

  /**
   * @brief Get the filename of the 3D model file.
   * @return The filename as a string.
   */
  std::string GetFilename();

  /**
   * @brief Set the filename of the 3D model file.
   * @param filename The new filename.
   */
  void SetFilename(const std::string &filename);
};

}  // namespace s21

#endif  // MODEL_H
