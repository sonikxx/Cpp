#include "controller_singleton.h"

namespace s21 {

void Controller::ProcessData() {
    model_.Init();
}

void Controller::Transform(QVector3D m_rotation, QVector3D m_translation, float scale) {
    model_.Transformation(m_rotation, m_translation, scale);
}

Data &Controller::GetData() {
    return model_.GetData();
}

QMatrix4x4 Controller::Getter() {
    return model_.Getter();
}

size_t Controller::GetVertexCount() const {
    return model_.GetVertexes().size() / 3;
}

size_t Controller::GetFaceCount() {
    return model_.GetData().counter_face_;
}

std::vector<float> Controller::GetVertexes() const {
    return model_.GetVertexes();
}

std::vector<int64_t> Controller::GetFaces() const {
    return model_.GetFaces();
}

std::string Controller::GetFilename() {
    return model_.GetFilename();
}

void Controller::SetFilename(const std::string &filename) {
    model_.SetFilename(filename);
}

} // namespace s21
