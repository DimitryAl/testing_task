
int triangulate(const float *scrVertex, const float *scrColor, int scrCount, int maxWidth, 
                int maxHeight, int maxDstSize, float *dstVertex, float *dstColor, int *scrTreatedCount);


int main() {

    const int count = 10;   // кол-во треугольников
    const int coords = 9;   // кол-во координат
    const int RGBA = 4; // кол-во цветовых компонент
    const int maxWidth = 10;    // максимальныя ширина треугольника
    const int maxHeight = 10;   // максимальная высота треуголтника
    const int maxDstSize = 10;  // макс кол-во треуголтников в выходном массиве

    // создание входного массива координат
    float **scrVertex;
    scrVertex = new float* [coords];
    for (int i = 0; i < count; i++) {
        scrVertex[i] = new float [count];
    }
    // создание массива цветов
    float **scrColor;
    scrColor = new float* [RGBA];
    for (int i = 0; i < count; i++) {
        scrColor[i] = new float [count];
    }
    // создание выходного массива
     

    // удаляем массивы
    for (int i = 0; i < coords; i++) {
        delete [] scrVertex[i];
    }
    delete scrVertex;
    for (int i = 0; i < RGBA; i++)    {
        delete [] scrColor[i];
    }
    delete scrColor;

    return 0;
}


int triangulate(const float *scrVertex, const float *scrColor, int scrCount, int maxWidth, 
                int maxHeight, int maxDstSize, float *dstVertex, float *dstColor, int *scrTreatedCount) {
    // scrVertex входной массив треугольников 
    // 


}