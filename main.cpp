#include <math.h>

int triangulate(const float *scrVertex, const float *scrColor, int scrCount, int maxWidth, 
                int maxHeight, int maxDstSize, float *dstVertex, float *dstColor, int *scrTreatedCount);


int main() {

    int count = 10;   // кол-во треугольников
    int coords = 9;   // кол-во координат
    int RGBA = 4; // кол-во цветовых компонент
    int maxWidth = 10;    // максимальныя ширина треугольника
    int maxHeight = 10;   // максимальная высота треуголтника
    int maxDstSize = 10;  // макс кол-во треуголтников в выходном массиве

    // создание входного массива координат
    const float **scrVertex;
    scrVertex = new const float* [coords];
    for (int i = 0; i < coords; i++) {
        scrVertex[i] = new const float [count];
    }
    // создание массива цветов
    const float **scrColor;
    scrColor = new const float* [count];
    for (int i = 0; i < count; i++) {
        scrColor[i] = new const float [RGBA];
    }
    // создание выходного массива координат
    float **dstVertex;
    dstVertex = new float* [coords];
    for (int i = 0; i < coords; i++) {
        dstVertex[i] = new float [maxDstSize];
    }
    float **dstColor;
    dstColor = new float* [maxDstSize];
    for (int i = 0; i < maxDstSize; i++) {
        dstVertex[i] = new float [RGBA];
    }
    int *scrTreatedCount = 0;
    /********************************************/
    for (int i = 0; i < count; i++) {
        triangulate(scrVertex[i], scrColor[i], count, maxWidth, maxHeight, maxDstSize, dstVertex[i], dstColor[i], scrTreatedCount);
    }
    

    // удаляем массивы
    for (int i = 0; i < coords; i++) {
        delete [] scrVertex[i];
    }
    delete scrVertex;
    for (int i = 0; i < RGBA; i++)    {
        delete [] scrColor[i];
    }
    delete scrColor;
    for (int i = 0; i < coords; i++)    {
        delete [] dstVertex[i];
    }
    delete dstVertex;

    return 0;
}


int triangulate(const float *scrVertex, const float *scrColor, int scrCount, int maxWidth, 
                int maxHeight, int maxDstSize, float *dstVertex, float *dstColor, int *scrTreatedCount) {
    // проверка не превосходит ли треугольник по ширине
    if (abs(scrVertex[0] - scrVertex[3]) > maxWidth) {

    }
    else if ( abs(scrVertex[0] - scrVertex[6]) > maxWidth) {

    } 
    else if (abs(scrVertex[3] - scrVertex[6]) > maxWidth) {

    }
    else {
        for (int i = 0; i < 9; i++) {
            dstVertex[i] = scrVertex[i];
        }
        scrTreatedCount++;
        return 1;
    }
    // проверка не превосходит ли треугольник по высоте
    /*
    if (abs(scrVertex[2] - scrVertex[3]) > maxHeight) {

    } 
    else {
        scrTreatedCount++;
        return 2;
    }
    */
    return 0;
}