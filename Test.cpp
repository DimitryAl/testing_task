#include <iostream>
#include <math.h>


//void func(int* scrVertex, int* res) {
//    std::cout << "Start\n";
//    for (int i = 0; i < 5; i++) {
//        output(scrVertex[i]);
//        res[i] = scrVertex[i] * scrVertex[i];
//    }
//    std::cout << std::endl;
//}

void foo(float arr[], float maxWidth, float maxHeight, int depth) {

    if (depth == 100) {
        return;
    }
    depth += 1;
    
    float dir[3] = { 0, 0, 0 };     //direction vector
    float triangle1[9];
    float triangle2[9];


    for (int i = 0; i < 9; i++) {
        triangle1[i] = arr[i];
        triangle2[i] = arr[i];
    }
    float t;


    // checking projection on axis X
    if (abs(arr[3] - arr[0]) > maxWidth) {

        dir[0] = arr[3] - arr[0];
        dir[1] = arr[4] - arr[1];
        dir[2] = arr[5] - arr[2];

        if (arr[3] < arr[0]) {
            triangle1[0] = arr[0] - maxWidth;
        }
        else {
            triangle1[0] = arr[0] + maxWidth;
        }
        t = (triangle1[0] - arr[0]) / (arr[3] - arr[0]);
        triangle1[1] = dir[1] * t + arr[1];
        triangle1[2] = dir[2] * t + arr[2];
        triangle2[3] = triangle1[0];
        triangle2[4] = triangle1[1];
        triangle2[5] = triangle1[2];

        foo(triangle1, maxWidth, maxHeight, depth);
        foo(triangle2, maxWidth, maxHeight, depth);
    }
    else if (abs(arr[6] - arr[0]) > maxWidth) {
        dir[0] = arr[6] - arr[0];
        dir[1] = arr[7] - arr[1];
        dir[2] = arr[8] - arr[2];

        if (arr[6] < arr[0]) {
            triangle1[0] = arr[0] - maxWidth;
        }
        else {
            triangle1[0] = arr[0] + maxWidth;
        }

        t = (triangle1[0] - arr[0]) / (arr[6] - arr[0]);
        triangle1[1] = dir[1] * t + arr[1];
        triangle1[2] = dir[2] * t + arr[2];
        triangle2[6] = triangle1[0];
        triangle2[7] = triangle1[1];
        triangle2[8] = triangle1[2];

        foo(triangle1, maxWidth, maxHeight, depth);
        foo(triangle2, maxWidth, maxHeight, depth);
    }
    else if (abs(arr[6] - arr[3]) > maxWidth) {
        dir[0] = arr[6] - arr[3];
        dir[1] = arr[7] - arr[4];
        dir[2] = arr[8] - arr[5];

        if (arr[6] < arr[3]) {
            triangle1[6] = arr[3] - maxWidth;
        }
        else {
            triangle1[6] = arr[3] + maxWidth;
        }

        t = (triangle1[0] - arr[3]) / (arr[6] - arr[3]);
        triangle1[7] = dir[1] * t + arr[4];
        triangle1[8] = dir[2] * t + arr[5];
        triangle2[3] = triangle1[6];
        triangle2[4] = triangle1[7];
        triangle2[5] = triangle1[8];

        foo(triangle1, maxWidth, maxHeight, depth);
        foo(triangle2, maxWidth, maxHeight, depth);
    }
    //projection on  Y
    else if (abs(arr[1] - arr[4]) > maxHeight) {
        dir[0] = arr[3] - arr[0];
        dir[1] = arr[4] - arr[1];
        dir[2] = arr[5] - arr[2];

        if (arr[4] < arr[1]) {
            triangle1[4] = arr[1] - maxWidth;
        }
        else {
            triangle1[4] = arr[1] + maxWidth;
        }

        t = (triangle1[4] - arr[1]) / dir[1];
        triangle1[3] = dir[0] * t + arr[0];
        triangle1[5] = dir[2] * t + arr[2];
        triangle2[0] = triangle1[3];
        triangle2[1] = triangle1[4];
        triangle2[2] = triangle1[5];

        foo(triangle1, maxWidth, maxHeight, depth);
        foo(triangle2, maxWidth, maxHeight, depth);
    }
    else if (abs(arr[4] - arr[7]) > maxHeight) {
        dir[0] = arr[6] - arr[3];
        dir[1] = arr[7] - arr[4];
        dir[2] = arr[8] - arr[5];

        if (arr[4] < arr[7]) {
            triangle1[7] = arr[4] + maxWidth;
        }
        else {
            triangle1[7] = arr[4] - maxWidth;
        }

        t = (triangle1[7] - arr[4]) / dir[1];
        triangle1[6] = dir[0] * t + arr[3];
        triangle1[8] = dir[2] * t + arr[5];
        triangle2[3] = triangle1[6];
        triangle2[4] = triangle1[7];
        triangle2[5] = triangle1[8];

        foo(triangle1, maxWidth, maxHeight, depth);
        foo(triangle2, maxWidth, maxHeight, depth);
    }
    else if (abs(arr[1] - arr[7]) > maxHeight) {
        dir[0] = arr[6] - arr[0];
        dir[1] = arr[7] - arr[1];
        dir[2] = arr[8] - arr[2];

        if (arr[1] < arr[7]) {
            triangle1[7] = arr[1] + maxWidth;
        }
        else {
            triangle1[7] = arr[1] - maxWidth;
        }

        t = (triangle1[7] - arr[1]) / dir[1];
        triangle1[6] = dir[0] * t + arr[0];
        triangle1[8] = dir[2] * t + arr[2];
        triangle2[0] = triangle1[6];
        triangle2[1] = triangle1[7];
        triangle2[2] = triangle1[8];

        foo(triangle1, maxWidth, maxHeight, depth);
        foo(triangle2, maxWidth, maxHeight, depth);
    }
    else {
        /*std::cout << "triangle is ok:\t";
        for (int i = 0; i < 9; i++) {
            output(arr[i]);
        }
        std::cout << std::endl << std::endl;*/
        std::cout << "Polygon";
        std::cout << "(";
        std::cout << "(" << arr[0] << "," << arr[1] << "," << arr[2] << "),";
        std::cout << "(" << arr[3] << "," << arr[4] << "," << arr[5] << "),";
        std::cout << "(" << arr[6] << "," << arr[7] << "," << arr[8] << ")";
        std::cout << ")\n";
    }
}


void foo2(float arr[], float maxWidth, float maxHeight) {

    float dir[3] = { 0, 0, 0 };     //íŕďđâë˙ţůčé âĺęňîđ
    float triangle1[9];
    float triangle2[9];
    float temp[3] = { 0, 0, 0 };

    for (int i = 0; i < 9; i++) {
        triangle1[i] = arr[i];
        triangle2[i] = arr[i];
    }
    float t;


    // ďđîâĺđęŕ íĺ ďđĺâîńőîäčň ëč ňđĺóăîëüíčę ďî řčđčíĺ(ďđîĺęöč˙ íŕ x )

    if (abs(arr[0] - arr[3]) > maxWidth) {
        dir[0] = arr[3] - arr[0];
        dir[1] = arr[4] - arr[1];
        dir[2] = arr[5] - arr[2];


        triangle1[0] = arr[0] + abs(arr[3] - arr[0]) / 2;
        t = (triangle1[0] - arr[0]) / (arr[3] - arr[0]);
        triangle1[1] = dir[1] * t + arr[1];
        triangle1[2] = dir[2] * t + arr[2];
        triangle2[3] = triangle1[0];
        triangle2[4] = triangle1[1];
        triangle2[5] = triangle1[2];

        foo2(triangle1, maxWidth, maxHeight);
        foo2(triangle2, maxWidth, maxHeight);
    }
    else if (abs(arr[0] - arr[6]) > maxWidth) {
        dir[0] = arr[6] - arr[0];
        dir[1] = arr[7] - arr[1];
        dir[2] = arr[8] - arr[2];

        triangle1[0] = arr[0] + abs(arr[6] - arr[0]) / 2;
        t = (triangle1[0] - arr[0]) / (arr[6] - arr[0]);
        triangle1[1] = dir[1] * t + arr[1];
        triangle1[2] = dir[2] * t + arr[2];
        triangle2[6] = triangle1[0];
        triangle2[7] = triangle1[1];
        triangle2[8] = triangle1[2];

        foo2(triangle1, maxWidth, maxHeight);
        foo2(triangle2, maxWidth, maxHeight);
    }
    else if (abs(arr[3] - arr[6]) > maxWidth) {
        dir[0] = arr[6] - arr[3];
        dir[1] = arr[7] - arr[4];
        dir[2] = arr[8] - arr[5];

        triangle1[6] = arr[3] + abs(arr[6] - arr[3]) / 2;
        t = (triangle1[0] - arr[3]) / (arr[6] - arr[3]);
        triangle1[7] = dir[1] * t + arr[4];
        triangle1[8] = dir[2] * t + arr[5];
        triangle2[3] = triangle1[6];
        triangle2[4] = triangle1[7];
        triangle2[5] = triangle1[8];

        foo2(triangle1, maxWidth, maxHeight);
        foo2(triangle2, maxWidth, maxHeight);
    }
    //ďđîâĺđęŕ íŕ Y
    else if (abs(arr[1] - arr[4]) > maxHeight) {
        dir[0] = arr[3] - arr[0];
        dir[1] = arr[4] - arr[1];
        dir[2] = arr[5] - arr[2];

        triangle1[4] = arr[1] + abs(arr[4] - arr[1]) / 2;;
        t = (triangle1[4] - arr[1]) / dir[1];
        triangle1[3] = dir[0] * t + arr[0];
        triangle1[5] = dir[2] * t + arr[2];
        triangle2[0] = triangle1[3];
        triangle2[1] = triangle1[4];
        triangle2[2] = triangle1[5];

        foo2(triangle1, maxWidth, maxHeight);
        foo2(triangle2, maxWidth, maxHeight);
    }
    else if (abs(arr[4] - arr[7]) > maxHeight) {
        dir[0] = arr[6] - arr[3];
        dir[1] = arr[7] - arr[4];
        dir[2] = arr[8] - arr[5];

        triangle1[7] = arr[4] + abs(arr[7] - arr[4]) / 2;;
        t = (triangle1[7] - arr[4]) / dir[1];
        triangle1[6] = dir[0] * t + arr[3];
        triangle1[8] = dir[2] * t + arr[5];
        triangle2[3] = triangle1[6];
        triangle2[4] = triangle1[7];
        triangle2[5] = triangle1[8];

        foo2(triangle1, maxWidth, maxHeight);
        foo2(triangle2, maxWidth, maxHeight);
    }
    else if (abs(arr[1] - arr[7]) > maxHeight) {
        dir[0] = arr[6] - arr[0];
        dir[1] = arr[7] - arr[1];
        dir[2] = arr[8] - arr[2];

        triangle1[7] = arr[1] + abs(arr[7] - arr[4]) / 2;;
        t = (triangle1[7] - arr[1]) / dir[1];
        triangle1[6] = dir[0] * t + arr[0];
        triangle1[8] = dir[2] * t + arr[2];
        triangle2[0] = triangle1[6];
        triangle2[1] = triangle1[7];
        triangle2[2] = triangle1[8];

        foo2(triangle1, maxWidth, maxHeight);
        foo2(triangle2, maxWidth, maxHeight);
    }
    else {
        std::cout << "triangle is ok:\t";
        for (int i = 0; i < 9; i++) {
            std::cout<<arr[i];
        }
        std::cout << std::endl << std::endl;

    }



    /*if (abs(arr[0] - arr[3]) > maxWidth || abs(arr[3] - arr[6]) > maxWidth || abs(arr[0] - arr[6]) > maxWidth) {
        dir[0] = arr[6] - arr[3];
        dir[1] = arr[7] - arr[4];
        dir[2] = arr[8] - arr[5];
        if (arr[3] < arr[6]) {
            temp[0] = arr[3] + (arr[6] - arr[3]) / 2;
            t = (temp[0] - arr[3]) / dir[0];
            temp[1] = dir[1] * t + arr[4];
            temp[2] = dir[2] * t + arr[5];
        }
        else {
            temp[0] = arr[6] + (arr[3] - arr[6]) / 2;
            t = (temp[0] - arr[3]) / dir[0];
            temp[1] = dir[1] * t + arr[4];
            temp[2] = dir[2] * t + arr[5];
        }
        triangle1[6] = temp[0];
        triangle1[7] = temp[1];
        triangle1[8] = temp[2];
        triangle2[4] = temp[0];
        triangle2[5] = temp[1];
        triangle2[6] = temp[2];
        foo2(triangle1, maxWidth, maxHeight);
        foo2(triangle2, maxWidth, maxHeight);
    }
    else if (abs(arr[1] - arr[4]) > maxHeight || abs(arr[4] - arr[7]) > maxHeight || abs(arr[1] - arr[7]) > maxHeight) {
        dir[0] = arr[6] - arr[3];
        dir[1] = arr[7] - arr[4];
        dir[2] = arr[8] - arr[5];
        if (arr[4] < arr[7]) {
            temp[1] = arr[4] + (arr[7] - arr[4]) / 2;
            t = (temp[1] - arr[4]) / dir[1];
            temp[0] = dir[0] * t + arr[3];
            temp[2] = dir[2] * t + arr[5];
        }
        else {
            temp[1] = arr[7] + (arr[4] - arr[7]) / 2;
            t = (temp[1] - arr[4]) / dir[1];
            temp[0] = dir[0] * t + arr[3];
            temp[2] = dir[2] * t + arr[5];
        }
        triangle1[6] = temp[0];
        triangle1[7] = temp[1];
        triangle1[8] = temp[2];
        triangle2[4] = temp[0];
        triangle2[5] = temp[1];
        triangle2[6] = temp[2];
        foo2(triangle1, maxWidth, maxHeight);
        foo2(triangle2, maxWidth, maxHeight);
    }
    else {
        std::cout << "triangle is ok:\t";
        for (int i = 0; i < 9; i++) {
            output(arr[i]);
        }
        std::cout << std::endl << std::endl;
    }*/

}

int main()
{
    const int N = 9;
    float maxWidth = 15;
    float maxHeight = 20;

    //float vertex[N] = { 50, 45, 10, 60, 55, 0, 60, 70, 30 };//ok
    //float vertex[N] = { -10, 0, 0, 10, 0, 0, 0, 0, 10 }; //ok
    //float vertex[N] = {0,45,10, 10,55,15, 15,70,20 }; //ok
    //float vertex[N] = { 50, 40, 10, 60, 50, 0, 75, 65, 30 }; //ok
    //float vertex[N] = { 4, 5, 1, 4, 3, 5, 3, 4, 3 }; //ok
    //float vertex[N] = { 40, 45, 0, 50, 45, -10, 50, 60, 20 }; //ok
    //float vertex[N] = { 25,12.5,5, 30,27.5,0, 30,35,15 };
    
    //float vertex[N] = { -4,-3,-5, -2,4,3, 4,4,4 };
    //float vertex[N] = { 10, 21, 3, -10,-3,12, 32,3,-5 };
    float vertex[N] = { 10, 11, 3, -10,-3,12, 12,3,-5 };
    for (int i = 0; i < N; i++) {
        std::cout<<(vertex[i])<<" ";
    }
    std::cout << std::endl;

    foo(vertex, maxWidth, maxHeight, 0);
    //std::cout << "\nfoo2\n";
    //foo2(vertex, maxWidth, maxHeight);

    return 0;
}