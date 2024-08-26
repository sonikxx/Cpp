#ifndef DATA_H
#define DATA_H

#include <string>
#include <tuple>
#include <vector>

namespace s21 {

/**
 * @class Data
 * @brief A class that handles the storage and manipulation of 3D model data.
 */
class Data {
 private:
  std::string filename_;        /**< The filename of the 3D model file. */
  std::vector<float> vertexes_; /**< The list of vertex coordinates. */
  std::vector<int64_t> faces_;  /**< The list of face indices. */

 public:
  size_t counter_face_; /**< The counter for the number of faces. */

  /**
   * @brief Constructor for the Data class.
   */
  Data() : filename_(""), counter_face_(0) {}

  /**
   * @brief Get a non-const reference to the list of vertex coordinates.
   * @return A reference to the vector of vertex coordinates.
   */
  std::vector<float> &GetVertexes() { return vertexes_; }

  /**
   * @brief Get a const reference to the list of vertex coordinates.
   * @return A const reference to the vector of vertex coordinates.
   */
  const std::vector<float> &GetVertexes() const { return vertexes_; }

  /**
   * @brief Get a non-const reference to the list of face indices.
   * @return A reference to the vector of face indices.
   */
  std::vector<int64_t> &GetFaces() { return faces_; }

  /**
   * @brief Get a const reference to the list of face indices.
   * @return A const reference to the vector of face indices.
   */
  const std::vector<int64_t> &GetFaces() const { return faces_; }

  /**
   * @brief Get the filename of the 3D model file.
   * @return The filename as a string.
   */
  std::string GetFilename() const { return filename_; }

  /**
   * @brief Set the filename of the 3D model file.
   * @param filename The new filename.
   */
  void SetFilename(const std::string &filename) { filename_ = filename; }

  /**
   * @brief Get the face counter.
   * @return The number of faces.
   */
  size_t GetCounterFace() const { return counter_face_; }
};
}  // namespace s21

#endif  // DATA_H
