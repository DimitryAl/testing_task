// Test.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <math.h>

void output(int x) {
    std::cout << x << "\t";
}

void func(int* scrVertex, int* res) {
    std::cout << "Start\n";
    for (int i = 0; i < 5; i++) {
        output(scrVertex[i]);
        res[i] = scrVertex[i] * scrVertex[i];
    }
    std::cout << std::endl;
}

void foo(float arr[], float maxWidth, float maxHeight) {

    float dir[3] = { 0, 0, 0 };     //напрвляющий вектор
    //float new_x, new_y, new_z;
    float triangle1[9];
    float triangle2[9];

    for (int i = 0; i < 9; i++) {
        triangle1[i] = arr[i];
        triangle2[i] = arr[i];
    }
    float t;


    // проверка не превосходит ли треугольник по ширине(проекция на x )
    if (abs(arr[0] - arr[3]) > maxWidth) {
        dir[0] = arr[3] - arr[0];
        dir[1] = arr[4] - arr[1];
        dir[2] = arr[5] - arr[2];

        triangle1[0] = arr[0] + maxWidth;
        t = (triangle1[0] - arr[0]) / (arr[3] - arr[0]);
        triangle1[1] = dir[1] * t + arr[1];
        triangle1[2] = dir[2] * t + arr[2];

        foo(triangle1, maxWidth, maxHeight);

    }
    else if (abs(arr[0] - arr[6]) > maxWidth) {
        dir[0] = arr[6] - arr[0];
        dir[1] = arr[7] - arr[1];
        dir[2] = arr[8] - arr[2];

        triangle1[0] = arr[0] + maxWidth;
        

        t = (triangle1[0] - arr[0]) / (arr[6] - arr[0]);
        triangle1[1] = dir[1] * t + arr[1];
        triangle1[2] = dir[2] * t + arr[2];
        
        triangle2[6] = triangle1[0];
        triangle2[7] = triangle1[1];
        triangle2[8] = triangle1[2];

        foo(triangle1, maxWidth, maxHeight);
        foo(triangle2, maxWidth, maxHeight);
    }
    else if (abs(arr[3] - arr[6]) > maxWidth) {
        dir[0] = arr[6] - arr[3];
        dir[1] = arr[7] - arr[4];
        dir[2] = arr[8] - arr[5];

        triangle1[0] = arr[3] + maxWidth;
        t = (triangle1[0] - arr[3]) / (arr[6] - arr[3]);
        triangle1[1] = dir[1] * t + arr[4];
        triangle1[2] = dir[2] * t + arr[5];

        foo(triangle1, maxWidth, maxHeight);
    }
    else {
        std::cout << "triangle is ok:\t";
        for (int i = 0; i < 9; i++) {
            output(arr[i]);
        }
        std::cout << std::endl;

    }
}


int main()
{   
    /*int coords = 10;
    int count = 5;
    int n = 1;

    int** scrVertex;
    scrVertex = new int* [coords];
    for (int i = 0; i < coords; i++) {
        scrVertex[i] = new int [count];
    }
    int** res;
    res = new int* [coords];
    for (int i = 0; i < coords; i++) {
        res[i] = new int[count];
    }
    for (int i = 0; i < coords; i++) {
        for (int j = 0; j < count; j++) {
            scrVertex[i][j] = n;
            n++;
        }
    }
    for (int i = 0; i < coords; i++) {
        func(scrVertex[i], res[i]);
    }
    std::cout << res[2][4];*/

    const int N = 9; 
    float maxWidth = 10;
    float maxHeight = 10;

    float vertex[N] = {50, 40, 10, 60, 50, 0, 70, 65, 30};
    for (int i = 0; i < N; i++) {
        output(vertex[i]);
    }
    std::cout << std::endl;

    foo(vertex, maxWidth, maxHeight);

    return 0;
}

