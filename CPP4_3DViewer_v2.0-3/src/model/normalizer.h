#ifndef NORMALIZER_H
#define NORMALIZER_H

#include <algorithm>
#include <vector>

#include "data.h"

namespace s21 {

/**
 * @class Normalizer
 * @brief A class for normalizing 3D model vertex data.
 */
class Normalizer {
 private:
  std::vector<std::pair<double, double>>
      min_max_; /**< Vector to store the min and max values of the vertex
                   coordinates. */
  std::vector<double> center_; /**< Vector to store the center coordinates of
                                  the vertex data. */

  /**
   * @brief Center the vertex data around the origin.
   * @param vertexes A reference to the vector of vertex coordinates.
   */
  void Centering(std::vector<float> &vertexes);

 public:
  /**
   * @brief Constructor for the Normalizer class.
   */
  Normalizer() : min_max_(3), center_(3) {}

  /**
   * @brief Normalize the vertex data.
   * @param data A reference to the Data object containing vertex data.
   */
  void Normalizing(Data &data);
};

}  // namespace s21

#endif  // NORMALIZER_H
