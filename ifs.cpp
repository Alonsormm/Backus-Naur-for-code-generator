#include <iostream>
#include <cstdlib> /* srand, rand */
#include <ctime>
#include <fstream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#define MAXIMO 200
using namespace std;
using namespace cv;

string generarCadenaIfs(int numeroTab)
{
    string temp = "";
    for (int i = 0; i < numeroTab; i++)
    {
        temp += "\t";
    }
    return temp;
}

void generarCadena(string &cadenaFinal, double &i)
{
    double max = MAXIMO;
    double count = 0;
    srand(time(0));
    int random;
    int parentesisSaltado = 0;
    while (count < max)
    {
        if (cadenaFinal[i] == ')')
        {
            i--;
            continue;
        }
        if (cadenaFinal[i] == 'A')
        {
            random = rand() % 2;
            if (random)
            {
                cadenaFinal.replace(i, 1, "(;eS)");
                parentesisSaltado++;
                i += 4;
            }
            else
            {
                cadenaFinal.replace(i, 1, "");
            }
        }
        if (cadenaFinal[i] == 'S')
        {
            cadenaFinal.replace(i, 1, "(iCtSA)");
            parentesisSaltado++;
            i += 6;
        }
        i--;
        count++;
    }
    i += parentesisSaltado;
}

void generarTxt(string &cadenaFinal, double i, Mat &image)
{

    unsigned char value1, value2, value3;
    int frame_width = MAXIMO;
    int frame_height = MAXIMO * 4;
    VideoWriter video("outcpp.avi", VideoWriter::fourcc('m', 'p', '4', 'v'), 10, Size(frame_width, frame_height));

    int row, col = 0;
    double tabulaciones = 0;
    std::ofstream outfile("ifs.txt", std::ofstream::out);
    namedWindow("A_good_name", WINDOW_AUTOSIZE);

    for (int j = 0; j < i; j++)
    {
        if (cadenaFinal[j] == 'i')
        {
            value1 = 255;
            value2 = 0;
            value3 = 0;
            outfile << generarCadenaIfs(tabulaciones) + "if";
        }
        else if (cadenaFinal[j] == 'C')
            outfile << "(C)";
        else if (cadenaFinal[j] == 't')
        {
            tabulaciones += 1;

            value1 = 0;
            value2 = 255;
            value3 = 0;
            outfile << "{\n";
        }
        else if (cadenaFinal[j] == ';')
        {
            tabulaciones -= 1;
            outfile << "\n" + generarCadenaIfs(tabulaciones) + "}";
        }
        else if (cadenaFinal[j] == 'e')
        {

            value1 = 0;
            value2 = 0;
            value3 = 255;
            outfile << "\n" + generarCadenaIfs(tabulaciones) + "else{\n";
            tabulaciones += 1;
        }
        else if (cadenaFinal[j] == ')')
        {
            tabulaciones -= 1;
            outfile << "\n" + generarCadenaIfs(tabulaciones) + "}";

            value1 = 100;
            value2 = 100;
            value3 = 100;
            if (tabulaciones == 0)
            {
                break;
            }
        }
        for (int i = 0; i < tabulaciones; i++)
        {
            image.at<Vec3b>(col, i)[0] = value1;
            image.at<Vec3b>(col, i)[1] = value2;
            image.at<Vec3b>(col, i)[2] = value3;
        }
        col++;
        video.write(image);
        imshow("A_good_name", image);
    }
    destroyWindow("A_good_name");
}

int main()
{
    Mat img(MAXIMO * 4, MAXIMO, CV_8UC3, Scalar(255, 255, 255));
    string cadenaFinal = "iCtSA";
    double tam = 5;
    double i = tam - 1;
    generarCadena(cadenaFinal, i);
    generarTxt(cadenaFinal, i, img);

    int tabulaciones = 0;
}
