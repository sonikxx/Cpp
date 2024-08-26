#ifndef PARSER_H
#define PARSER_H

#include <cstdio>
#include <set>
#include <string>

#include "data.h"

namespace s21 {

/**
 * @class Parser
 * @brief A class for parsing 3D model data from files.
 */
class Parser {
 private:
  Data &data_; /**< Reference to the Data object to store parsed data. */

  /**
   * @brief Parse a line containing vertex data.
   * @param line A string containing the line to be parsed.
   */
  void ParserVertexes(std::string line);

  /**
   * @brief Parse a line containing face data.
   * @param line A string containing the line to be parsed.
   */
  void ParserFaces(std::string line,
                   std::set<std::pair<int64_t, int64_t>> &edges);

  /**
   * @brief Check the validity of the parsed data.
   * @throw std::runtime_error if the parsed data is invalid.
   */
  void Check();

 public:
  /**
   * @brief Constructor for the Parser class.
   * @param data A reference to the Data object where parsed data will be
   * stored.
   */
  Parser(Data &data) : data_(data) {}

  /**
   * @brief Read and parse a file.
   * @param filename The name of the file to be read and parsed.
   * @throw std::runtime_error if the file cannot be opened or contains invalid
   * data.
   */
  void ReadFile(const std::string &filename);
};

}  // namespace s21

#endif  // PARSER_H
