#ifndef CONTROLLER_SINGLETON_H
#define CONTROLLER_SINGLETON_H

#include "../model/model_facade.h"

namespace s21 {

/**
 * @class Controller
 * @brief A controller class to manage interactions between the view and the
 * model.
 */
class Controller {
 public:
  /**
   * @brief Constructor for the Controller class.
   * @param filename The name of the file to process.
   */
  Controller(const std::string &filename) : model_(filename) {}

  /**
   * @brief Processes data from the file.
   */
  void ProcessData();

  /**
   * @brief Transforms the data model.
   * @param m_rotation A QVector3D containing rotation values (angles in
   * degrees).
   * @param m_translation A QVector3D containing translation values.
   * @param scale A float value to scale the model.
   */
  void Transform(QVector3D m_rotation, QVector3D m_translation, float scale);

  /**
   * @brief Gets the data model.
   * @return A reference to the Data object.
   */
  Data &GetData();

  /**
   * @brief Gets the current transformation matrix.
   * @return A QMatrix4x4 representing the transformation matrix.
   */
  QMatrix4x4 Getter();

  /**
   * @brief Gets the number of vertices.
   * @return The number of vertices.
   */
  size_t GetVertexCount() const;

  /**
   * @brief Gets the number of faces.
   * @return The number of faces.
   */
  size_t GetFaceCount();

  /**
   * @brief Gets the vertices of the model.
   * @return A vector of floats representing the vertices.
   */
  std::vector<float> GetVertexes() const;

  /**
   * @brief Gets the faces of the model.
   * @return A vector of int64_t representing the faces.
   */
  std::vector<int64_t> GetFaces() const;

  /**
   * @brief Gets the filename.
   * @return A string representing the filename.
   */
  std::string GetFilename();

  /**
   * @brief Sets the filename.
   * @param filename The name of the file.
   */
  void SetFilename(const std::string &filename);

 private:
  Model model_; /**< The model object to manage data. */
};

}  // namespace s21

#endif  // CONTROLLER_SINGLETON_H
