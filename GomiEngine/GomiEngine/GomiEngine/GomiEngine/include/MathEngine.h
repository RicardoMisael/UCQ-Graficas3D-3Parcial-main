#pragma once

namespace EngineMath {
    // Autor Original: "Roberto Charreton".
    // Constantes matemáticas comunes.
    constexpr float MATH_PI = 3.14159265358979323846f;
    constexpr float MATH_E = 2.71828182845904523536f;

    /**
     * @brief Calcula la raíz cuadrada utilizando el método de aproximación de Newton-Raphson.
     * @param value Número del cual se desea obtener la raíz cuadrada.
     * @return Aproximación de la raíz cuadrada del valor dado. Devuelve 0 si el valor es negativo.
     */
    inline float calculateSquareRoot(float value) {
        if (value < 0) {
            return 0.0f;
        }
        float approx = value;
        float prev = 1.0f;
        constexpr float tolerance = 0.00001f; // Precisión del cálculo.
        while (approx - prev > tolerance) {
            approx = (approx + prev) / 2.0f;
            prev = value / approx;
        }
        return approx;
    }

    /**
     * @brief Calcula el seno de un ángulo dado en radianes.
     * @param angle Ángulo en radianes.
     * @return Seno del ángulo calculado mediante la serie de Taylor.
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
     * @brief Calcula el coseno de un ángulo dado en radianes.
     * @param angle Ángulo en radianes.
     * @return Coseno del ángulo.
     */
    inline float calculateCosine(float angle) {
        return calculateSine(angle + MATH_PI / 2);
    }

    /**
     * @brief Calcula la tangente de un ángulo dado en radianes.
     * @param angle Ángulo en radianes.
     * @return Tangente del ángulo. Devuelve 0 si el coseno es 0 para evitar divisiones por cero.
     */
    inline float calculateTangent(float angle) {
        float sineValue = calculateSine(angle);
        float cosineValue = calculateCosine(angle);
        return cosineValue != 0.0f ? sineValue / cosineValue : 0.0f;
    }
};
