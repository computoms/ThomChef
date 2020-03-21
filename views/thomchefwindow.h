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

private:
    Ui::ThomChefWindow *ui;
    std::shared_ptr<RecipeStore> m_store;
};

#endif // THOMCHEFWINDOW_H
