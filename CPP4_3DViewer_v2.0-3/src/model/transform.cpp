#include "transform.h"
#include <cmath>
#include <iostream>

using namespace s21;

QMatrix4x4 Transform::Getter() {
    return matrix_;
}

void Transform::Move(QVector3D m_translation) {
    matrix_.setToIdentity();
    matrix_.translate(m_translation.x(), m_translation.y(), -2.0 + m_translation.z());
}

void Transform::Scale(float scale) {
    matrix_.scale(scale);
}

void Transform::Rotate(QVector3D m_rotation) {
    matrix_.rotate(m_rotation.x(), 0.0, 1.0, 0.0f);
    matrix_.rotate(m_rotation.y(), 1.0, 0.0, 0.0f);
    matrix_.rotate(m_rotation.z(), 0.0, 0.0, 1.0f);
}
