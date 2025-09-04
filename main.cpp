#include <iostream>
#include <Windows.h>
#include <cmath>

void abs_harm_levels (double arr[], int arr_size);
void print_array (double arr[], int arr_size);
double  dBtoVolts (double dB);
double kHarm (double arr[], int arr_size);
int num_harm_input ();

int main(int argc, char** argv)
{
    setlocale(LC_ALL, "rus");
    std::cout << "KNI Caclulator 1.1." << std::endl;
    std::cout << std::endl;
    double frequency_high{};
    std::cout << "Enter VHF carrier (MHz): "; std::cin >> frequency_high;

    int frequency_low{1000};
//    std::cout << "Ìîäóëèðóþùàÿ ÷àñòîòà (Ãö): ";
//    std::cin >> frequency_low;


    int num_harm{};
    int harm_frequencies[10]{};
    double harm_levels[10]{};

    num_harm = num_harm_input();

    //if (frequency_low == 350)  num_harm = 8;
    //if (frequency_low == 1000) num_harm = 2;
    //if (frequency_low == 2500) num_harm = 2;

   // std::cout << "×èñëî ãàðìîíèê äëÿ ìîäóëèðóþùåé ÷àñòîòû " << frequency_low << " Ãö: " << num_harm << std::endl;

    for (int i{}; i < num_harm; i++)
    {
            harm_frequencies[i] = frequency_low*(i+1);
          //  if (i == 0) std::cout << "Îñíîâíàÿ ÷àñòîòà (1-ÿ ãàðìîíèêà): " << harm_frequencies[i] << " Ãö;" << std::endl;
          //  else {std::cout << "                  " << (i+1) << "-ÿ ãàðìîíèêà : " << harm_frequencies[i] << " Ãö;" << std::endl; }

    }

    for (int i{}; i < num_harm; i++)
        {
            std::cout << "Level of " << i <<" harmonic (" << harm_frequencies[i] << " Hz), dB: ";
            std::cin >> harm_levels[i];
        }

    //for (int i{}; i < num_harm; i++)
    //    {
    //std::cout << "Óðîâåíü " << i <<"-é ãàðìîíèêè (äÁ) = " << harm_levels[i] << std::endl;
    //    }

abs_harm_levels (harm_levels, num_harm);
std::cout << std::endl;
std::cout << std::endl;
std::cout << "RS2500V KNI on entered carrier frequency = " << kHarm(harm_levels, num_harm) << " %";
//print_array(harm_levels, num_harm);

 std::cout << std::endl;
 //std::cout << "108.46 = " << 108.46 << std::endl;
 //std::cout << "Êâàäðàòíûé êîðåíü èç 108 â êâàäðàòå = " << sqrt(108.46*108.46);


// double a = 0.1;
 //a *= a;
 //double b = 0.01;
 //b *= b;
 //double c = 0.001;
 //c *= c;

 //std::cout << "Íåìíîãî âû÷èñëåíèé äëÿ ïðîâåðêè: " << 100 * sqrt(a + b + c)/sqrt(0.2 * 0.2);

    return 0;
}

void abs_harm_levels (double arr[], int arr_size)
{
    for (int i{}; i < arr_size; i++)
        {
            arr[i] = dBtoVolts(arr[i]);
        }
}

void print_array (double arr[], int arr_size)
{
    std::cout << std::endl;
    for (int i{}; i < arr_size; i++)
        {
           std::cout << arr[i] << std::endl;
        }
}

 double  dBtoVolts (double dB){
  double resultVolts;
  resultVolts = pow(10.0, (dB/20.0));
   std::cout << std::endl;
  std::cout << dB << " dB = " << resultVolts << " V";
  return resultVolts;
}

double kHarm (double arr[], int arr_size)
{
  double kHarmResult{};
  double square_mean_harm{};

  for (int i{1}; i < arr_size; i++)
    {
      square_mean_harm += arr[i]*arr[i];
      //std::cout << "Ñóììà êâàäðàòîâ ãàðìîíèê: " << arr[i]*arr[i] << std::endl;
    }

  if (square_mean_harm == 0.0) kHarmResult = 1.0; //sqrt((arr[0]*arr[0] * 0.1))/sqrt(arr[0]*arr[0]);
  kHarmResult = sqrt(square_mean_harm)/sqrt(arr[0]*arr[0]);

  return (kHarmResult*100);
}

int num_harm_input ()
{
int number_of_harmonics{};

std::cout << "Enter number of influencing harmonics: "; std::cin >> number_of_harmonics;
std::cout << std::endl;

return number_of_harmonics;
}
