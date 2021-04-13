#include <iostream>
//#include <math.h>

int triangulate(const float* scrVertex, const float* scrColor, int scrCount, int maxWidth,
    int maxHeight, int maxDstSize, float* dstVertex, float* dstColor, int* scrTreatedCount);

int triangulate2(const float* scrVertex, const float* scrColor, int scrCount, int maxWidth,
    int maxHeight, int maxDstSize, float* dstVertex, float* dstColor, int* scrTreatedCount);

int main()
{
    const int scrCount = 3;     // кол-во треугольников
    const int coords = 9;     // кол-во координат
    int RGBA = 4;       // кол-во цветовых компонент
    int maxWidth = 15;    // максимальныя ширина треугольника
    int maxHeight = 15;   // максимальная высота треуголтника
    int maxDstSize = 20;  // макс кол-во треуголтников в выходном массиве
    int* scrTreatedCount = 0;   //Число подлностью обработанных входных треугольников

    // создание входного массива координат
    const float scrVertex[scrCount][coords] = {
        { -4,-3,-5, -2,4,3, 4,4,4 },
        { 10, 21, 3, -10,-3,12, 32,3,-5 },
        { 10, 11, 3, -10,-3,12, 12,3,-5 }
    };
    // создание массива цветов
    const float** scrColor;
    scrColor = new const float* [scrCount];
    for (int i = 0; i < scrCount; i++) {
        scrColor[i] = new const float[RGBA];
    }
    // создание выходного массива координат
    float** dstVertex;
    dstVertex = new float* [maxDstSize];
    for (int i = 0; i < maxDstSize; i++) {
        dstVertex[i] = new float[coords];
    }
    float** dstColor;
    dstColor = new float* [maxDstSize];
    for (int i = 0; i < maxDstSize; i++) {
        dstVertex[i] = new float[RGBA];
    }

    /********************************************/
    for (int i = 0; i < scrCount; i++) {
        std::cout << i <<std::endl;
        triangulate(scrVertex[i], scrColor[i], scrCount, maxWidth, maxHeight, maxDstSize, dstVertex[i], dstColor[i], scrTreatedCount);
        std::cout << std::endl;
        //triangulate2(scrVertex[i], scrColor[i], scrCount, maxWidth, maxHeight, maxDstSize, dstVertex[i], dstColor[i], scrTreatedCount);
       // std::cout << std::endl;

    }
    
    return 0;
}

int triangulate(const float* scrVertex, const float* scrColor, int scrCount, int maxWidth,
    int maxHeight, int maxDstSize, float* dstVertex, float* dstColor, int* scrTreatedCount) {

    float dir[3] = { 0, 0, 0 };     //direction vector
    float triangle1[9];
    float triangle2[9];

    for (int i = 0; i < 9; i++) {
        triangle1[i] = scrVertex[i];
        triangle2[i] = scrVertex[i];
    }
    float t;

    
    float sides[6];
    //by x
    sides[0] = abs(scrVertex[0] - scrVertex[3]); //ab
    sides[1] = abs(scrVertex[3] - scrVertex[6]); //bc
    sides[2] = abs(scrVertex[0] - scrVertex[6]); //ac
    //by y
    sides[3] = abs(scrVertex[1] - scrVertex[4]);
    sides[4] = abs(scrVertex[4] - scrVertex[7]);
    sides[5] = abs(scrVertex[1] - scrVertex[7]);
    
    int temp = -1;
    int max = -1;
    for (int i = 0; i < 3; i++) {
        if (sides[i] > maxWidth && sides[i] > max) {
            temp = i; max = sides[temp];
        }
    }
    for (int i = 3; i < 6; i++) {
        if (sides[i] > maxHeight && sides[i] > max) {
            temp = i; max = sides[temp];
        }
    }
    
    switch (temp) {
    case -1:
        std::cout << "(";
        std::cout << "(" << scrVertex[0] << "," << scrVertex[1] << "," << scrVertex[2] << "), ";
        std::cout << "(" << scrVertex[3] << "," << scrVertex[4] << "," << scrVertex[5] << "), ";
        std::cout << "(" << scrVertex[6] << "," << scrVertex[7] << "," << scrVertex[8] << ")";
        std::cout << ")\n";
        return 1;
        break;
    case 0:
        dir[0] = scrVertex[3] - scrVertex[0];
        dir[1] = scrVertex[4] - scrVertex[1];
        dir[2] = scrVertex[5] - scrVertex[2];

        /*if (scrVertex[3] < scrVertex[0]) {
            triangle1[0] = scrVertex[0] - maxWidth;
        }
        else {
            triangle1[0] = scrVertex[0] + maxWidth;
        }*/
        triangle1[0] = (scrVertex[3] + scrVertex[0]) / 2;
        t = (triangle1[0] - scrVertex[0]) / (scrVertex[3] - scrVertex[0]);
        triangle1[1] = dir[1] * t + scrVertex[1];
        triangle1[2] = dir[2] * t + scrVertex[2];
        triangle2[3] = triangle1[0];
        triangle2[4] = triangle1[1];
        triangle2[5] = triangle1[2];

        triangulate(triangle1, scrColor, scrCount, maxWidth, maxHeight, maxDstSize, dstVertex, dstColor, scrTreatedCount);
        triangulate(triangle2, scrColor, scrCount, maxWidth, maxHeight, maxDstSize, dstVertex, dstColor, scrTreatedCount);
        break;
    case 1:
        dir[0] = scrVertex[6] - scrVertex[3];
        dir[1] = scrVertex[7] - scrVertex[4];
        dir[2] = scrVertex[8] - scrVertex[5];

        /*if (scrVertex[6] < scrVertex[3]) {
            triangle1[6] = scrVertex[3] - maxWidth;
        }
        else {
            triangle1[6] = scrVertex[3] + maxWidth;
        }*/
        triangle1[6] = (scrVertex[6] + scrVertex[3]) / 2;
        //t = (triangle1[6] - scrVertex[3]) / (scrVertex[6] - scrVertex[3]);
        t = (triangle1[6] - scrVertex[6]) / (scrVertex[6] - scrVertex[3]);
        triangle1[7] = dir[1] * t + scrVertex[4];
        triangle1[8] = dir[2] * t + scrVertex[5];
        triangle2[3] = triangle1[6];
        triangle2[4] = triangle1[7];
        triangle2[5] = triangle1[8];

        triangulate(triangle1, scrColor, scrCount, maxWidth, maxHeight, maxDstSize, dstVertex, dstColor, scrTreatedCount);
        triangulate(triangle2, scrColor, scrCount, maxWidth, maxHeight, maxDstSize, dstVertex, dstColor, scrTreatedCount);
        break;
    case 2:
        dir[0] = scrVertex[6] - scrVertex[0];
        dir[1] = scrVertex[7] - scrVertex[1];
        dir[2] = scrVertex[8] - scrVertex[2];

        /*if (scrVertex[6] < scrVertex[0]) {
            triangle1[0] = scrVertex[0] - maxWidth;
        }
        else {
            triangle1[0] = scrVertex[0] + maxWidth;
        }*/
        triangle1[0] = (scrVertex[6] + scrVertex[0]) / 2;
        t = (triangle1[0] - scrVertex[0]) / (scrVertex[6] - scrVertex[0]);
        triangle1[1] = dir[1] * t + scrVertex[1];
        triangle1[2] = dir[2] * t + scrVertex[2];
        triangle2[6] = triangle1[0];
        triangle2[7] = triangle1[1];
        triangle2[8] = triangle1[2];

        triangulate(triangle1, scrColor, scrCount, maxWidth, maxHeight, maxDstSize, dstVertex, dstColor, scrTreatedCount);
        triangulate(triangle2, scrColor, scrCount, maxWidth, maxHeight, maxDstSize, dstVertex, dstColor, scrTreatedCount);
        break;
    case 3:
        dir[0] = scrVertex[3] - scrVertex[0];
        dir[1] = scrVertex[4] - scrVertex[1];
        dir[2] = scrVertex[5] - scrVertex[2];

        /*if (scrVertex[3] < scrVertex[0]) {
            triangle1[0] = scrVertex[0] - maxWidth;
        }
        else {
            triangle1[0] = scrVertex[0] + maxWidth;
        }*/
        triangle1[4] = (scrVertex[4] + scrVertex[1]) / 2;
        //t = (triangle1[4] - scrVertex[1]) / dir[1];
        t = (triangle1[4] - scrVertex[4]) / dir[1];
        triangle1[3] = dir[0] * t + scrVertex[0];
        triangle1[5] = dir[2] * t + scrVertex[2];
        triangle2[0] = triangle1[3];
        triangle2[1] = triangle1[4];
        triangle2[2] = triangle1[5];

        triangulate(triangle1, scrColor, scrCount, maxWidth, maxHeight, maxDstSize, dstVertex, dstColor, scrTreatedCount);
        triangulate(triangle2, scrColor, scrCount, maxWidth, maxHeight, maxDstSize, dstVertex, dstColor, scrTreatedCount);
        break;
    case 4:
        dir[0] = scrVertex[6] - scrVertex[0];
        dir[1] = scrVertex[7] - scrVertex[1];
        dir[2] = scrVertex[8] - scrVertex[2];

        /*if (scrVertex[6] < scrVertex[0]) {
            triangle1[0] = scrVertex[0] - maxWidth;
        }
        else {
            triangle1[0] = scrVertex[0] + maxWidth;
        }*/
        triangle1[4] = (scrVertex[7] + scrVertex[4]) / 2;
        //t = (triangle1[7] - scrVertex[4]) / dir[1];
        t = (triangle1[4] - scrVertex[4]) / dir[1];
        triangle1[6] = dir[0] * t + scrVertex[3];
        triangle1[8] = dir[2] * t + scrVertex[5];
        triangle2[3] = triangle1[6];
        triangle2[4] = triangle1[7];
        triangle2[5] = triangle1[8];

        triangulate(triangle1, scrColor, scrCount, maxWidth, maxHeight, maxDstSize, dstVertex, dstColor, scrTreatedCount);
        triangulate(triangle2, scrColor, scrCount, maxWidth, maxHeight, maxDstSize, dstVertex, dstColor, scrTreatedCount);
        break;
    case 5:
        dir[0] = scrVertex[6] - scrVertex[0];
        dir[1] = scrVertex[7] - scrVertex[1];
        dir[2] = scrVertex[8] - scrVertex[2];

        /*if (scrVertex[6] < scrVertex[0]) {
            triangle1[0] = scrVertex[0] - maxWidth;
        }
        else {
            triangle1[0] = scrVertex[0] + maxWidth;
        }*/
        triangle1[7] = (scrVertex[7] + scrVertex[1]) / 2;
        //t = (triangle1[7] - scrVertex[1]) / dir[1];
        t = (triangle1[7] - scrVertex[7]) / dir[1];
        triangle1[6] = dir[0] * t + scrVertex[0];
        triangle1[8] = dir[2] * t + scrVertex[2];
        triangle2[0] = triangle1[6];
        triangle2[1] = triangle1[7];
        triangle2[2] = triangle1[8];

        triangulate(triangle1, scrColor, scrCount, maxWidth, maxHeight, maxDstSize, dstVertex, dstColor, scrTreatedCount);
        triangulate(triangle2, scrColor, scrCount, maxWidth, maxHeight, maxDstSize, dstVertex, dstColor, scrTreatedCount);
        break;

    }
    

    /*if (ab > maxWidth) {
        temp = 1;
        if (ac > ab) { temp = 3; }
        if (bc > ab) { temp = 2; }
    }
    if (bc > maxWidth) {
        temp = 2;
        if (ac > bc) { temp = 3; }
    }
    if (ac > maxWidth) { temp = 3; }*/
    
    /*switch (temp) {
    case 1:
        dir[0] = scrVertex[3] - scrVertex[0];
        dir[1] = scrVertex[4] - scrVertex[1];
        dir[2] = scrVertex[5] - scrVertex[2];

        if (scrVertex[3] < scrVertex[0]) {
            triangle1[0] = scrVertex[0] - maxWidth;
        }
        else {
            triangle1[0] = scrVertex[0] + maxWidth;
        }
        t = (triangle1[0] - scrVertex[0]) / (scrVertex[3] - scrVertex[0]);
        triangle1[1] = dir[1] * t + scrVertex[1];
        triangle1[2] = dir[2] * t + scrVertex[2];
        triangle2[3] = triangle1[0];
        triangle2[4] = triangle1[1];
        triangle2[5] = triangle1[2];

        triangulate(triangle1, scrColor, scrCount, maxWidth, maxHeight, maxDstSize, dstVertex, dstColor, scrTreatedCount);
        triangulate(triangle2, scrColor, scrCount, maxWidth, maxHeight, maxDstSize, dstVertex, dstColor, scrTreatedCount);
        break;
    case 2:
        dir[0] = scrVertex[6] - scrVertex[3];
        dir[1] = scrVertex[7] - scrVertex[4];
        dir[2] = scrVertex[8] - scrVertex[5];

        if (scrVertex[6] < scrVertex[3]) {
            triangle1[6] = scrVertex[3] - maxWidth;
        }
        else {
            triangle1[6] = scrVertex[3] + maxWidth;
        }

        t = (triangle1[0] - scrVertex[3]) / (scrVertex[6] - scrVertex[3]);
        triangle1[7] = dir[1] * t + scrVertex[4];
        triangle1[8] = dir[2] * t + scrVertex[5];
        triangle2[3] = triangle1[6];
        triangle2[4] = triangle1[7];
        triangle2[5] = triangle1[8];

        triangulate(triangle1, scrColor, scrCount, maxWidth, maxHeight, maxDstSize, dstVertex, dstColor, scrTreatedCount);
        triangulate(triangle2, scrColor, scrCount, maxWidth, maxHeight, maxDstSize, dstVertex, dstColor, scrTreatedCount);
        break;
    case 3:
        dir[0] = scrVertex[6] - scrVertex[0];
        dir[1] = scrVertex[7] - scrVertex[1];
        dir[2] = scrVertex[8] - scrVertex[2];

        if (scrVertex[6] < scrVertex[0]) {
            triangle1[0] = scrVertex[0] - maxWidth;
        }
        else {
            triangle1[0] = scrVertex[0] + maxWidth;
        }

        t = (triangle1[0] - scrVertex[0]) / (scrVertex[6] - scrVertex[0]);
        triangle1[1] = dir[1] * t + scrVertex[1];
        triangle1[2] = dir[2] * t + scrVertex[2];
        triangle2[6] = triangle1[0];
        triangle2[7] = triangle1[1];
        triangle2[8] = triangle1[2];

        triangulate(triangle1, scrColor, scrCount, maxWidth, maxHeight, maxDstSize, dstVertex, dstColor, scrTreatedCount);
        triangulate(triangle2, scrColor, scrCount, maxWidth, maxHeight, maxDstSize, dstVertex, dstColor, scrTreatedCount);
        break;
    case 0:
        std::cout << "(";
        std::cout << "(" << scrVertex[0] << "," << scrVertex[1] << "," << scrVertex[2] << "), ";
        std::cout << "(" << scrVertex[3] << "," << scrVertex[4] << "," << scrVertex[5] << "), ";
        std::cout << "(" << scrVertex[6] << "," << scrVertex[7] << "," << scrVertex[8] << ")";
        std::cout << ")\n";
        return 1;
        break;
    }*/

    //if (abs(scrVertex[3] - scrVertex[0]) > maxWidth) {

    //    dir[0] = scrVertex[3] - scrVertex[0];
    //    dir[1] = scrVertex[4] - scrVertex[1];
    //    dir[2] = scrVertex[5] - scrVertex[2];

    //    if (scrVertex[3] < scrVertex[0]) {
    //        triangle1[0] = scrVertex[0] - maxWidth;
    //    }
    //    else {
    //        triangle1[0] = scrVertex[0] + maxWidth;
    //    }
    //    t = (triangle1[0] - scrVertex[0]) / (scrVertex[3] - scrVertex[0]);
    //    triangle1[1] = dir[1] * t + scrVertex[1];
    //    triangle1[2] = dir[2] * t + scrVertex[2];
    //    triangle2[3] = triangle1[0];
    //    triangle2[4] = triangle1[1];
    //    triangle2[5] = triangle1[2];

    //    triangulate(triangle1, scrColor, maxWidth, scrCount, maxHeight, maxDstSize, dstVertex, dstColor, scrTreatedCount);
    //    triangulate(triangle2, scrColor, maxWidth, scrCount, maxHeight, maxDstSize, dstVertex, dstColor, scrTreatedCount);
    //}
    //else if (abs(scrVertex[6] - scrVertex[0]) > maxWidth) {
    //    dir[0] = scrVertex[6] - scrVertex[0];
    //    dir[1] = scrVertex[7] - scrVertex[1];
    //    dir[2] = scrVertex[8] - scrVertex[2];

    //    if (scrVertex[6] < scrVertex[0]) {
    //        triangle1[0] = scrVertex[0] - maxWidth;
    //    }
    //    else {
    //        triangle1[0] = scrVertex[0] + maxWidth;
    //    }

    //    t = (triangle1[0] - scrVertex[0]) / (scrVertex[6] - scrVertex[0]);
    //    triangle1[1] = dir[1] * t + scrVertex[1];
    //    triangle1[2] = dir[2] * t + scrVertex[2];
    //    triangle2[6] = triangle1[0];
    //    triangle2[7] = triangle1[1];
    //    triangle2[8] = triangle1[2];

    //    triangulate(triangle1, scrColor, scrCount, maxWidth, maxHeight, maxDstSize, dstVertex, dstColor, scrTreatedCount);
    //    triangulate(triangle2, scrColor, scrCount, maxWidth, maxHeight, maxDstSize, dstVertex, dstColor, scrTreatedCount);
    //}
    //else if (abs(scrVertex[6] - scrVertex[3]) > maxWidth) {
    //    dir[0] = scrVertex[6] - scrVertex[3];
    //    dir[1] = scrVertex[7] - scrVertex[4];
    //    dir[2] = scrVertex[8] - scrVertex[5];

    //    if (scrVertex[6] < scrVertex[3]) {
    //        triangle1[6] = scrVertex[3] - maxWidth;
    //    }
    //    else {
    //        triangle1[6] = scrVertex[3] + maxWidth;
    //    }

    //    t = (triangle1[0] - scrVertex[3]) / (scrVertex[6] - scrVertex[3]);
    //    triangle1[7] = dir[1] * t + scrVertex[4];
    //    triangle1[8] = dir[2] * t + scrVertex[5];
    //    triangle2[3] = triangle1[6];
    //    triangle2[4] = triangle1[7];
    //    triangle2[5] = triangle1[8];

    //    triangulate(triangle1, scrColor, scrCount, maxWidth, maxHeight, maxDstSize, dstVertex, dstColor, scrTreatedCount);
    //    triangulate(triangle2, scrColor, scrCount, maxWidth, maxHeight, maxDstSize, dstVertex, dstColor, scrTreatedCount);
    //}
    ////projection on  Y
    //else if (abs(scrVertex[1] - scrVertex[4]) > maxHeight) {
    //    dir[0] = scrVertex[3] - scrVertex[0];
    //    dir[1] = scrVertex[4] - scrVertex[1];
    //    dir[2] = scrVertex[5] - scrVertex[2];

    //    if (scrVertex[4] < scrVertex[1]) {
    //        triangle1[4] = scrVertex[1] - maxWidth;
    //    }
    //    else {
    //        triangle1[4] = scrVertex[1] + maxWidth;
    //    }

    //    t = (triangle1[4] - scrVertex[1]) / dir[1];
    //    triangle1[3] = dir[0] * t + scrVertex[0];
    //    triangle1[5] = dir[2] * t + scrVertex[2];
    //    triangle2[0] = triangle1[3];
    //    triangle2[1] = triangle1[4];
    //    triangle2[2] = triangle1[5];

    //    triangulate(triangle1, scrColor, scrCount, maxWidth, maxHeight, maxDstSize, dstVertex, dstColor, scrTreatedCount);
    //    triangulate(triangle2, scrColor, scrCount, maxWidth, maxHeight, maxDstSize, dstVertex, dstColor, scrTreatedCount);
    //}
    //else if (abs(scrVertex[4] - scrVertex[7]) > maxHeight) {
    //    dir[0] = scrVertex[6] - scrVertex[3];
    //    dir[1] = scrVertex[7] - scrVertex[4];
    //    dir[2] = scrVertex[8] - scrVertex[5];

    //    if (scrVertex[4] < scrVertex[7]) {
    //        triangle1[7] = scrVertex[4] + maxWidth;
    //    }
    //    else {
    //        triangle1[7] = scrVertex[4] - maxWidth;
    //    }

    //    t = (triangle1[7] - scrVertex[4]) / dir[1];
    //    triangle1[6] = dir[0] * t + scrVertex[3];
    //    triangle1[8] = dir[2] * t + scrVertex[5];
    //    triangle2[3] = triangle1[6];
    //    triangle2[4] = triangle1[7];
    //    triangle2[5] = triangle1[8];

    //    triangulate(triangle1, scrColor, scrCount, maxWidth, maxHeight, maxDstSize, dstVertex, dstColor, scrTreatedCount);
    //    triangulate(triangle2, scrColor, scrCount, maxWidth, maxHeight, maxDstSize, dstVertex, dstColor, scrTreatedCount);
    //}
    //else if (abs(scrVertex[1] - scrVertex[7]) > maxHeight) {
    //    dir[0] = scrVertex[6] - scrVertex[0];
    //    dir[1] = scrVertex[7] - scrVertex[1];
    //    dir[2] = scrVertex[8] - scrVertex[2];

    //    if (scrVertex[1] < scrVertex[7]) {
    //        triangle1[7] = scrVertex[1] + maxWidth;
    //    }
    //    else {
    //        triangle1[7] = scrVertex[1] - maxWidth;
    //    }

    //    t = (triangle1[7] - scrVertex[1]) / dir[1];
    //    triangle1[6] = dir[0] * t + scrVertex[0];
    //    triangle1[8] = dir[2] * t + scrVertex[2];
    //    triangle2[0] = triangle1[6];
    //    triangle2[1] = triangle1[7];
    //    triangle2[2] = triangle1[8];

    //    triangulate(triangle1, scrColor, scrCount, maxWidth, maxHeight, maxDstSize, dstVertex, dstColor, scrTreatedCount);
    //    triangulate(triangle2, scrColor, scrCount, maxWidth, maxHeight, maxDstSize, dstVertex, dstColor, scrTreatedCount);
    //}
    //else {
    //    std::cout << "(";
    //    std::cout << "(" << scrVertex[0] << "," << scrVertex[1] << "," << scrVertex[2] << "), ";
    //    std::cout << "(" << scrVertex[3] << "," << scrVertex[4] << "," << scrVertex[5] << "), ";
    //    std::cout << "(" << scrVertex[6] << "," << scrVertex[7] << "," << scrVertex[8] << ")";
    //    std::cout << ")\n";
    //    return 1;
    //}
    return 0;
}

int triangulate2(const float* scrVertex, const float* scrColor, int scrCount, int maxWidth,
    int maxHeight, int maxDstSize, float* dstVertex, float* dstColor, int* scrTreatedCount) {

    float dir[3] = { 0, 0, 0 };     //direction vector
    float triangle1[9];
    float triangle2[9];

    for (int i = 0; i < 9; i++) {
        triangle1[i] = scrVertex[i];
        triangle2[i] = scrVertex[i];
    }
    float t;

    // checking projection on axis X
    if (abs(scrVertex[3] - scrVertex[0]) > maxWidth) {

        dir[0] = scrVertex[3] - scrVertex[0];
        dir[1] = scrVertex[4] - scrVertex[1];
        dir[2] = scrVertex[5] - scrVertex[2];

        if (scrVertex[3] < scrVertex[0]) {
            triangle1[0] = scrVertex[0] - maxWidth;
        }
        else {
            triangle1[0] = scrVertex[0] + maxWidth;
        }
        t = (triangle1[0] - scrVertex[0]) / (scrVertex[3] - scrVertex[0]);
        triangle1[1] = dir[1] * t + scrVertex[1];
        triangle1[2] = dir[2] * t + scrVertex[2];
        triangle2[3] = triangle1[0];
        triangle2[4] = triangle1[1];
        triangle2[5] = triangle1[2];

        triangulate(triangle1, scrColor, maxWidth, scrCount, maxHeight, maxDstSize, dstVertex, dstColor, scrTreatedCount);
        triangulate(triangle2, scrColor, maxWidth, scrCount, maxHeight, maxDstSize, dstVertex, dstColor, scrTreatedCount);
    }
    else if (abs(scrVertex[6] - scrVertex[0]) > maxWidth) {
        dir[0] = scrVertex[6] - scrVertex[0];
        dir[1] = scrVertex[7] - scrVertex[1];
        dir[2] = scrVertex[8] - scrVertex[2];

        if (scrVertex[6] < scrVertex[0]) {
            triangle1[0] = scrVertex[0] - maxWidth;
        }
        else {
            triangle1[0] = scrVertex[0] + maxWidth;
        }

        t = (triangle1[0] - scrVertex[0]) / (scrVertex[6] - scrVertex[0]);
        triangle1[1] = dir[1] * t + scrVertex[1];
        triangle1[2] = dir[2] * t + scrVertex[2];
        triangle2[6] = triangle1[0];
        triangle2[7] = triangle1[1];
        triangle2[8] = triangle1[2];

        triangulate(triangle1, scrColor, scrCount, maxWidth, maxHeight, maxDstSize, dstVertex, dstColor, scrTreatedCount);
        triangulate(triangle2, scrColor, scrCount, maxWidth, maxHeight, maxDstSize, dstVertex, dstColor, scrTreatedCount);
    }
    else if (abs(scrVertex[6] - scrVertex[3]) > maxWidth) {
        dir[0] = scrVertex[6] - scrVertex[3];
        dir[1] = scrVertex[7] - scrVertex[4];
        dir[2] = scrVertex[8] - scrVertex[5];

        if (scrVertex[6] < scrVertex[3]) {
            triangle1[6] = scrVertex[3] - maxWidth;
        }
        else {
            triangle1[6] = scrVertex[3] + maxWidth;
        }

        t = (triangle1[6] - scrVertex[3]) / (scrVertex[6] - scrVertex[3]); //mistake
        triangle1[7] = dir[1] * t + scrVertex[4];
        triangle1[8] = dir[2] * t + scrVertex[5];
        triangle2[3] = triangle1[6];
        triangle2[4] = triangle1[7];
        triangle2[5] = triangle1[8];

        triangulate(triangle1, scrColor, scrCount, maxWidth, maxHeight, maxDstSize, dstVertex, dstColor, scrTreatedCount);
        triangulate(triangle2, scrColor, scrCount, maxWidth, maxHeight, maxDstSize, dstVertex, dstColor, scrTreatedCount);
    }
    //projection on  Y
    else if (abs(scrVertex[1] - scrVertex[4]) > maxHeight) {
        dir[0] = scrVertex[3] - scrVertex[0];
        dir[1] = scrVertex[4] - scrVertex[1];
        dir[2] = scrVertex[5] - scrVertex[2];

        if (scrVertex[4] < scrVertex[1]) {
            triangle1[4] = scrVertex[1] - maxWidth;
        }
        else {
            triangle1[4] = scrVertex[1] + maxWidth;
        }

        t = (triangle1[4] - scrVertex[1]) / dir[1];
        triangle1[3] = dir[0] * t + scrVertex[0];
        triangle1[5] = dir[2] * t + scrVertex[2];
        triangle2[0] = triangle1[3];
        triangle2[1] = triangle1[4];
        triangle2[2] = triangle1[5];

        triangulate(triangle1, scrColor, scrCount, maxWidth, maxHeight, maxDstSize, dstVertex, dstColor, scrTreatedCount);
        triangulate(triangle2, scrColor, scrCount, maxWidth, maxHeight, maxDstSize, dstVertex, dstColor, scrTreatedCount);
    }
    else if (abs(scrVertex[4] - scrVertex[7]) > maxHeight) {
        dir[0] = scrVertex[6] - scrVertex[3];
        dir[1] = scrVertex[7] - scrVertex[4];
        dir[2] = scrVertex[8] - scrVertex[5];

        if (scrVertex[4] < scrVertex[7]) {
            triangle1[7] = scrVertex[4] + maxWidth;
        }
        else {
            triangle1[7] = scrVertex[4] - maxWidth;
        }

        t = (triangle1[7] - scrVertex[4]) / dir[1];
        triangle1[6] = dir[0] * t + scrVertex[3];
        triangle1[8] = dir[2] * t + scrVertex[5];
        triangle2[3] = triangle1[6];
        triangle2[4] = triangle1[7];
        triangle2[5] = triangle1[8];

        triangulate(triangle1, scrColor, scrCount, maxWidth, maxHeight, maxDstSize, dstVertex, dstColor, scrTreatedCount);
        triangulate(triangle2, scrColor, scrCount, maxWidth, maxHeight, maxDstSize, dstVertex, dstColor, scrTreatedCount);
    }
    else if (abs(scrVertex[1] - scrVertex[7]) > maxHeight) {
        dir[0] = scrVertex[6] - scrVertex[0];
        dir[1] = scrVertex[7] - scrVertex[1];
        dir[2] = scrVertex[8] - scrVertex[2];

        if (scrVertex[1] < scrVertex[7]) {
            triangle1[7] = scrVertex[1] + maxWidth;
        }
        else {
            triangle1[7] = scrVertex[1] - maxWidth;
        }

        t = (triangle1[7] - scrVertex[1]) / dir[1];
        triangle1[6] = dir[0] * t + scrVertex[0];
        triangle1[8] = dir[2] * t + scrVertex[2];
        triangle2[0] = triangle1[6];
        triangle2[1] = triangle1[7];
        triangle2[2] = triangle1[8];

        triangulate(triangle1, scrColor, scrCount, maxWidth, maxHeight, maxDstSize, dstVertex, dstColor, scrTreatedCount);
        triangulate(triangle2, scrColor, scrCount, maxWidth, maxHeight, maxDstSize, dstVertex, dstColor, scrTreatedCount);
    }
    else {
        std::cout << "(";
        std::cout << "(" << scrVertex[0] << "," << scrVertex[1] << "," << scrVertex[2] << "), ";
        std::cout << "(" << scrVertex[3] << "," << scrVertex[4] << "," << scrVertex[5] << "), ";
        std::cout << "(" << scrVertex[6] << "," << scrVertex[7] << "," << scrVertex[8] << ")";
        std::cout << ")\n";
        return 1;
    }
    return 0;
}