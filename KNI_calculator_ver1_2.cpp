#include <iostream>
#include <Windows.h>
#include <cmath>
#include <vector>
#include <limits>

void abs_harm_levels(std::vector<double>& harm_levels);
double dBtoVolts(double dB);
double kHarm(const std::vector<double>& harm_levels);

int main()
{
    setlocale(LC_ALL, "rus");

    std::cout << "======================================" << std::endl;
    std::cout << "     KNI Calculator 1.2" << std::endl;
    std::cout << "======================================" << std::endl;
    std::cout << std::endl;

    double carrier_frequency{};
    std::cout << "Enter VHF carrier (MHz): ";
    std::cin >> carrier_frequency;

    double modulating_frequency{};
    std::cout << "Enter modulating frequency (Hz): ";
    std::cin >> modulating_frequency;

    int num_harm{};
    std::cout << "Enter number of influencing harmonics (1-20): ";
    std::cin >> num_harm;

    if (num_harm < 1 || num_harm > 20)
    {
        std::cout << "Error: number must be between 1 and 20" << std::endl;
        return 1;
    }

    std::vector<double> harm_frequencies(num_harm);
    std::vector<double> harm_levels(num_harm);

    std::cout << "\n--- Harmonic frequencies ---" << std::endl;
    for (int i = 0; i < num_harm; i++)
    {
        harm_frequencies[i] = modulating_frequency * (i + 1);
        std::cout << (i + 1) << "-я гармоника: " << harm_frequencies[i] << " Hz" << std::endl;
    }

    std::cout << "\n--- Enter harmonic levels (dB) ---" << std::endl;
    for (int i = 0; i < num_harm; i++)
    {
        std::cout << "Level of " << (i + 1) << " harmonic ("
            << static_cast<int>(harm_frequencies[i]) << " Hz), dB: ";
        std::cin >> harm_levels[i];
    }

    std::cout << "\n--- Conversion dB to Volts ---" << std::endl;
    abs_harm_levels(harm_levels);

    std::cout << "\n======================================" << std::endl;
    double result = kHarm(harm_levels);
    std::cout << "RS2500V KNI on carrier frequency " << carrier_frequency
        << " MHz = " << result << " %" << std::endl;
    std::cout << "======================================" << std::endl;

    system("pause");
    return 0;
}

void abs_harm_levels(std::vector<double>& harm_levels)
{
    for (size_t i = 0; i < harm_levels.size(); i++)
    {
        double volts = pow(10.0, (harm_levels[i] / 20.0));
        std::cout << harm_levels[i] << " dB = " << volts << " V" << std::endl;
        harm_levels[i] = volts;
    }
}

double dBtoVolts(double dB)
{
    return pow(10.0, (dB / 20.0));
}

double kHarm(const std::vector<double>& harm_levels)
{
    if (harm_levels.empty() || harm_levels[0] == 0.0)
    {
        return 0.0;
    }

    double square_sum = 0.0;

    for (size_t i = 1; i < harm_levels.size(); i++)
    {
        square_sum += harm_levels[i] * harm_levels[i];
    }

    if (square_sum == 0.0)
    {
        return 0.0;
    }

    return (sqrt(square_sum) / harm_levels[0]) * 100.0;
}