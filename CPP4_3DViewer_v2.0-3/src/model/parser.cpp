#include "parser.h"
#include <fstream>
#include <stdexcept>

using namespace s21;

void Parser::ReadFile(const std::string &filename) {
    std::setlocale(LC_NUMERIC, "C");
    data_.GetVertexes().clear();
    data_.GetFaces().clear();
    std::set<std::pair<int64_t, int64_t>> edges;
    std::ifstream in(filename);
    if (in.is_open()) {
        std::string line;
        while (std::getline(in, line)) {
            if (line[0] == 'v' && line[1] == ' ') {
                this->ParserVertexes(line);
            } else if (line[0] == 'f' && line[1] == ' ') {
                this->ParserFaces(line, edges);
            }
        }
        in.close();
        Check();
        data_.counter_face_ = edges.size();
    } else {
        throw std::runtime_error("This file cannot be opened :(");
    }
}

void Parser::ParserVertexes(std::string line) {
    std::setlocale(LC_NUMERIC, "C");
    int counter_coord = 0;
    for (auto it = line.begin() + 2; it != line.end(); ++it) {
        if (isdigit(*it) || *it == '-') {
            std::size_t size_number = 0;
            try {
                data_.GetVertexes().push_back(std::stod(&(*it), &size_number));
                ++counter_coord;
            } catch (const std::exception &e) {
                throw std::runtime_error("This file contains incorrect vertex coordinates :(");
            }
            it += size_number - 1;
        }
    }
    if (counter_coord != 3) {
        throw std::runtime_error("This file contains incorrect vertex coordinates :(");
    }
}

void insert(std::set<std::pair<int64_t, int64_t>> &edges, int64_t first, int64_t second) {
    if (first < second)
        edges.insert(std::make_pair(first, second));
    else
        edges.insert(std::make_pair(second, first));
}

void Parser::ParserFaces(std::string line, std::set<std::pair<int64_t, int64_t>> &edges) {
    std::setlocale(LC_NUMERIC, "C");
    int prev = 0;
    int64_t first_vert;
    for (auto it = line.begin() + 2; it != line.end(); ++it) {
        if (isdigit(*it) && (it == line.begin() + 2 || prev == 0)) {
            std::size_t size_number = 0;
            try {
                if (it == line.begin() + 2) {
                    first_vert = std::stoll(&(*it), &size_number) - 1;
                    data_.GetFaces().push_back(first_vert);
                } else {
                    int64_t tmp_number = std::stoll(&(*it), &size_number) - 1;
                    insert(edges, tmp_number, data_.GetFaces().back());
                    data_.GetFaces().push_back(tmp_number);
                    data_.GetFaces().push_back(tmp_number);
                }
            } catch (const std::exception &e) {
                throw std::runtime_error("This file contains invalid values for vertices :(");
            }
            it += size_number - 1;
        } else if (*it == '/') {
            prev = 1;
        } else if (*it == ' ') {
            prev = 0;
        }
    }
    insert(edges, first_vert, data_.GetFaces().back());
    data_.GetFaces().push_back(first_vert);
}

void Parser::Check() {
    if (data_.GetVertexes().size() == 0 || data_.GetFaces().size() == 0) {
        throw std::runtime_error("This file is empty :(");
    } else {
        for (int64_t i = 0; i < data_.GetFaces().size(); ++i) {
            if (data_.GetFaces()[i] >= data_.GetVertexes().size() / 3) {
                throw std::runtime_error("This file contains invalid values for vertices :(");
            }
        }
    }
}
