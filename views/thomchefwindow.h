#ifndef THOMCHEFWINDOW_H
#define THOMCHEFWINDOW_H

#include <QMainWindow>

#include "core/recipestore.h"

namespace Ui {
class ThomChefWindow;
}

class ThomChefWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ThomChefWindow(QWidget *parent = nullptr);
    ~ThomChefWindow();

    void initialize();

private slots:
    void on_button_addrecipe_clicked();

private:
    Ui::ThomChefWindow *ui;
    std::shared_ptr<FileRecipeStorage> m_storage;
    std::shared_ptr<RecipeStore> m_store;
};

#endif // THOMCHEFWINDOW_H
