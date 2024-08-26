#ifndef CPP4_3DVIEWER_V2_0_SRC_VIEW_SETTINGS_H_
#define CPP4_3DVIEWER_V2_0_SRC_VIEW_SETTINGS_H_

#include <QColorDialog>
#include <QDir>
#include <QFile>
#include <QFileDialog>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>

namespace s21 {

/**
 * @class Settings
 * @brief A class representing the settings for the 3D viewer.
 */
class Settings {
public:
    /// @brief Default constructor
    Settings();

    /// @brief Function to save the current settings to a file
    void SaveSettings();

    /// @brief Function to load settings from a file
    void GetSettings();

    QColor line_color;        /**< QColor for line color */
    QColor back_color;        /**< QColor for background color */
    QColor vertex_color;      /**< QColor for vertex color */
    bool projection_orth;     /**< Flag for orthogonal projection */
    int vertex_type;          /**< Type of vertex representation */
    int line_type;            /**< Type of line representation */
    float line_width = 0.02;  /**< Width of the lines */
    float vertex_size = 0.01; /**< Size of the vertices */
};

} // namespace s21

#endif // CPP4_3DVIEWER_V2_0_SRC_VIEW_SETTINGS_H_
