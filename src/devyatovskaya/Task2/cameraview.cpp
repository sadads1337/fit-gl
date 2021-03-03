#include "cameraview.hpp"


QMatrix4x4 cameraView::getViewMatrix()
{
    QMatrix4x4 view;
    view.lookAt(position_, center_, up_);

    return view;
}
