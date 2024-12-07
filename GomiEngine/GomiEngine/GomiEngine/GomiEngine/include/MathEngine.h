#pragma once

namespace EngineMath {
    // Autor Original: "Roberto Charreton".
    // Constantes matem�ticas comunes.
    constexpr float MATH_PI = 3.14159265358979323846f;
    constexpr float MATH_E = 2.71828182845904523536f;

    /**
     * @brief Calcula la ra�z cuadrada utilizando el m�todo de aproximaci�n de Newton-Raphson.
     * @param value N�mero del cual se desea obtener la ra�z cuadrada.
     * @return Aproximaci�n de la ra�z cuadrada del valor dado. Devuelve 0 si el valor es negativo.
     */
    inline float calculateSquareRoot(float value) {
        if (value < 0) {
            return 0.0f;
        }
        float approx = value;
        float prev = 1.0f;
        constexpr float tolerance = 0.00001f; // Precisi�n del c�lculo.
        while (approx - prev > tolerance) {
            approx = (approx + prev) / 2.0f;
            prev = value / approx;
        }
        return approx;
    }

    /**
     * @brief Calcula el seno de un �ngulo dado en radianes.
     * @param angle �ngulo en radianes.
     * @return Seno del �ngulo calculado mediante la serie de Taylor.
     */
    inline float calculateSine(float angle) {
        float result = 0.0f;
        float term = angle;
        float angleSq = angle * angle;
        int iteration = 1;

        while (term > 1e-6f || term < -1e-6f) {
            result += term;
            term *= -angleSq / ((2 * iteration) * (2 * iteration + 1));
            ++iteration;
        }
        return result;
    }

    /**
     * @brief Calcula el coseno de un �ngulo dado en radianes.
     * @param angle �ngulo en radianes.
     * @return Coseno del �ngulo.
     */
    inline float calculateCosine(float angle) {
        return calculateSine(angle + MATH_PI / 2);
    }

    /**
     * @brief Calcula la tangente de un �ngulo dado en radianes.
     * @param angle �ngulo en radianes.
     * @return Tangente del �ngulo. Devuelve 0 si el coseno es 0 para evitar divisiones por cero.
     */
    inline float calculateTangent(float angle) {
        float sineValue = calculateSine(angle);
        float cosineValue = calculateCosine(angle);
        return cosineValue != 0.0f ? sineValue / cosineValue : 0.0f;
    }
};
