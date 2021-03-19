#include "coub.h"

Coub::Coub()
{
    vert = coubVertex();
}

std::vector<GLfloat> Coub::side()
{
    std::vector<GLfloat> vec ={};
    for (GLfloat x = -1.0f ; x <= 1.01f-step ;x += step )
    {
        for (GLfloat y = -1.0f ; y <=1.01f-step ;y += step )
        {
            vec.push_back(x     );vec.push_back(y     );vec.push_back(1.0f);
            vec.push_back(x+step);vec.push_back(y     );vec.push_back(1.0f);
            vec.push_back(x     );vec.push_back(y+step);vec.push_back(1.0f);
            vec.push_back(x     );vec.push_back(y+step);vec.push_back(1.0f);
            vec.push_back(x+step);vec.push_back(y     );vec.push_back(1.0f);
            vec.push_back(x+step);vec.push_back(y+step);vec.push_back(1.0f);
        }
    }
    return vec;
}
std::vector<GLfloat> Coub::slideSide(types type)
{
    auto vec = side();
    int slide = 0;
    if (type==Z)
    {
        slide = 0;
    }
    else if(type ==Y)
    {
        slide = 2;
    }
    else if(type == X)
    {
        slide = 1;
    }
    for(size_t i = 0 ;i< vec.size()/3 ; i++)
    {
        std::vector<GLfloat> v = {vec[i*3],vec[i*3+1],vec[i*3+2]};
        std::rotate(v.rbegin(), v.rbegin() + slide, v.rend());
        for (int k = 0 ; k< 3 ; k ++)
        {
            vec[i*3+k] = v[k];
        }

    }
    return vec;
}
std::vector<GLfloat> Coub::coubVertex()
{
    norm.clear();
    std::vector<GLfloat>result = {};
    std::vector<GLfloat> v ={};
    std::vector<GLfloat> n ={};

    v = slideSide(X);
    result.insert(result.end() , v.begin() , v.end());
    normals(X , v.size()/3 , false);

    v = slideSide(Y);
    result.insert(result.end() , v.begin() , v.end());
    normals(Y , v.size()/3 , false);

    v = slideSide(Z);
    result.insert(result.end() , v.begin() , v.end());
    normals(Z , v.size()/3 , false);

    std::vector<GLfloat> reverse ={};

    v = slideSide(X);
    reverse.insert(reverse.end() , v.begin() , v.end());
    normals(X , v.size()/3 , true);

    v = slideSide(Y);
    reverse.insert(reverse.end() , v.begin() , v.end());
    normals(Y , v.size()/3 , true);

    v = slideSide(Z);
    reverse.insert(reverse.end() , v.begin() , v.end());
    normals(Z , v.size()/3 , true);

    for (auto it = reverse.begin(); it!= reverse.end();++it)
    {
        *it *=-1;
    }
    result.insert(result.end() , reverse.begin() , reverse.end());
    return result;
}

void Coub::normals(types type ,int size , bool inv)
{
    std::vector<GLfloat> n ={0,0,0};
    switch (type){
        case X:
            n[0] = -1;
            break;
        case Y:
            n[1]= -1;
            break;
        case Z:
            n[2]= -1;
            break;
    };

    if (inv)
    {
        for (int i = 0 ; i < static_cast<int>(n.size()) ; ++i)
        {
            n[i] *= -1;
        }
    }

    for (int i=0; i < size; ++i)
    {
        for (int k =0 ; k < static_cast<int>(n.size()) ; ++k)
        {
            norm.push_back(n[k]);
        }
    }
}

std::vector<GLfloat> Coub::getVertex()
{
    return vert;
}
std::vector<GLfloat> Coub::getNormals()
{
    return norm;
}

size_t Coub::vertexCount()
{
    return vert.size();
}

void Coub::setStep(GLfloat stp)
{
    step  = stp;
    vert = coubVertex();
}







