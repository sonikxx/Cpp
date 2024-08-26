#include "normalizer.h"

using namespace s21;

void Normalizer::Centering(std::vector<float> &vertexes) {
    for (int i = 0; i < 3; ++i) {
        min_max_[i] = {vertexes[0 + i], vertexes[0 + i]};
    }
    for (int64_t i = 0; i < vertexes.size(); i += 3) {
        for (int j = 0; j < 3; ++j) {
            if (vertexes[i + j] < min_max_[j].first)
                min_max_[j].first = vertexes[i + j];
            if (vertexes[i + j] > min_max_[j].second)
                min_max_[j].second = vertexes[i + j];
        }
    }
    for (int i = 0; i < 3; ++i) {
        center_[i] = min_max_[i].first + (min_max_[i].second - min_max_[i].first) / 2;
    }
    for (int64_t i = 0; i < vertexes.size(); i += 3) {
        for (int j = 0; j < 3; ++j) {
            vertexes[i + j] -= center_[j];
        }
    }
}

void Normalizer::Normalizing(Data &data) {
    auto &vertexes = data.GetVertexes();
    Centering(vertexes);
    double max_diff = std::max({min_max_[0].second - min_max_[0].first, min_max_[1].second - min_max_[1].first, min_max_[2].second - min_max_[2].first});
    double scale = 0.7 / max_diff;

    for (int64_t i = 0; i < vertexes.size(); i += 3) {
        for (int j = 0; j < 3; ++j) {
            vertexes[i + j] *= scale;
        }
    }
}
