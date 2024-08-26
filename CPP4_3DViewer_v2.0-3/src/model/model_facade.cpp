#include "./model_facade.h"

using namespace s21;

void Model::Init() {
    parser_.ReadFile(data_.GetFilename());
    normalizer_.Normalizing(data_);
}

void Model::Transformation(QVector3D m_rotation, QVector3D m_translation, float scale) {
    transform_.Move(m_translation);
    transform_.Scale(scale);
    transform_.Rotate(m_rotation);
}

Data &Model::GetData() {
    return data_;
}

QMatrix4x4 Model::Getter() {
    return transform_.Getter();
}

std::string Model::GetFilename() {
    return data_.GetFilename();
}

void Model::SetFilename(const std::string &filename) {
    data_.SetFilename(filename);
}
