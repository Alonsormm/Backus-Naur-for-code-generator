#include <iostream>
#include <cstdlib> /* srand, rand */
#include <ctime>
#include <fstream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#define MAXIMO 100
using namespace std;
using namespace cv;

//compilar con g++ -I/usr/local/Cellar/opencv/4.2.0_1/include/opencv4/opencv -I/usr/local/Cellar/opencv/4.2.0_1/include/opencv4 -L/usr/local/Cellar/opencv/4.2.0_1/lib -lopencv_gapi -lopencv_stitching -lopencv_aruco -lopencv_bgsegm -lopencv_bioinspired -lopencv_ccalib -lopencv_dnn_objdetect -lopencv_dnn_superres -lopencv_dpm -lopencv_highgui -lopencv_face -lopencv_freetype -lopencv_fuzzy -lopencv_hfs -lopencv_img_hash -lopencv_line_descriptor -lopencv_quality -lopencv_reg -lopencv_rgbd -lopencv_saliency -lopencv_sfm -lopencv_stereo -lopencv_structured_light -lopencv_phase_unwrapping -lopencv_superres -lopencv_optflow -lopencv_surface_matching -lopencv_tracking -lopencv_datasets -lopencv_text -lopencv_dnn -lopencv_plot -lopencv_videostab -lopencv_videoio -lopencv_xfeatures2d -lopencv_shape -lopencv_ml -lopencv_ximgproc -lopencv_video -lopencv_xobjdetect -lopencv_objdetect -lopencv_calib3d -lopencv_imgcodecs -lopencv_features2d -lopencv_flann -lopencv_xphoto -lopencv_photo -lopencv_imgproc -lopencv_core -std=c++11 ifs.cpp

string generarCadenaIfs(int numeroTab)
{
    string temp = "";
    for (int i = 0; i < numeroTab; i++)
    {
        temp += "\t";
    }
    return temp;
}

string reanalizar(string cadenaFinal);

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
        random = rand() % 2;

        if (random)
        {
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
                    cadenaFinal.replace(i, 1, ")");
                }
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
    cout << cadenaFinal << '\n';

    int randomcool = rand() % 5;

    for (int k = 0; k < randomcool; k++)
        cadenaFinal = reanalizar(cadenaFinal);

    cout << cadenaFinal;

    i += parentesisSaltado;
}

string reanalizar(string cadenaFinal)
{
    int random;
    for (int i = 0; i < cadenaFinal.size(); i++)
    {
        if (cadenaFinal[i] == 'A')
        {
            random = rand() % 2;
            if (random)
            {
                cadenaFinal.replace(i, 1, "(;eS)");
            }
            else
            {
                cadenaFinal.replace(i, 1, ")");
            }
        }
    }
    for (int i = 0; i < cadenaFinal.size(); i++)
    {
        if (cadenaFinal[i] == 'S')
        {
            random = rand() % 2;
            if (random)
            {
                cadenaFinal.replace(i, 1, "(iCtS)");
            }
        }
    }
    return cadenaFinal;
}

void generarTxt(string &cadenaFinal, double i, Mat &image)
{

    unsigned char value1, value2, value3;
    int frame_width = MAXIMO;
    int frame_height = MAXIMO * 7;
    VideoWriter video("outcpp2.mp4", VideoWriter::fourcc('m', 'p', '4', 'v'), 60, Size(frame_height, frame_width));

    int row, col = 0;
    double tabulaciones = 0;
    std::ofstream outfile("ifs.txt", std::ofstream::out);
    namedWindow("A_good_name", WINDOW_AUTOSIZE);

    for (int j = 0; j < cadenaFinal.size(); j++)
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
        rotate(image, image, ROTATE_90_COUNTERCLOCKWISE);
        video.write(image);
        rotate(image, image, ROTATE_90_CLOCKWISE);
    }
    rotate(image, image, ROTATE_90_COUNTERCLOCKWISE);

    imwrite("imagen.jpg", image);
    destroyWindow("A_good_name");
}

int main()
{
    Mat img(MAXIMO * 7, MAXIMO, CV_8UC3, Scalar(255, 255, 255));
    string cadenaFinal = "iCtSA";
    double tam = 5;
    double i = tam - 1;
    generarCadena(cadenaFinal, i);
    generarTxt(cadenaFinal, i, img);
    int tabulaciones = 0;
}