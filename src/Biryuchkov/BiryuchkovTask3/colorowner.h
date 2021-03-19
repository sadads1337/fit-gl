#ifndef COLOROWNER_H
#define COLOROWNER_H
#include "sourcelight.h"
#include <vector>
#include <QColorDialog>

class ColorOwner
{
public:
    ColorOwner();

    void setDialog(QColorDialog* dial);
    void checkColor();
    void setActive(int ac);
    void setSources(std::vector<SourceLight*> srcs);

private:
    std::vector<SourceLight*> vect = {};
    int active = 0;
    QColorDialog* colorDialog = nullptr;
};

#endif // COLOROWNER_H
