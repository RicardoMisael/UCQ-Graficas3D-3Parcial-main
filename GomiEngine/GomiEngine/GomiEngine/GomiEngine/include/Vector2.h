#pragma once
#include "MathEngine.h"

class Vector2 {
public:
    // Valores de las coordenadas x y y
    float x;
    float y;

    /**
     * @brief Constructor por defecto
     * Inicializa las coordenadas del vector a 0.
     */
    Vector2() : x(0), y(0) {}

    /**
     * @brief Constructor parametrizado.
     * Inicializa las coordenadas del vector con los valores dados.
     */
    Vector2(float xVal, float yVal) : x(xVal), y(yVal) {}

    // Sobrecarga del operador para la suma de 2 vectores.
    Vector2 operator+(const Vector2& other) const {
        return Vector2(x + other.x, y + other.y);
    }

    // Sobrecarga del operador +=
    Vector2& operator+=(const Vector2& other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    // Sobrecarga del operador para la resta de 2 vectores.
    Vector2 operator-(const Vector2& other) const {
        return Vector2(x - other.x, y - other.y);
    }

    // Sobrecarga del operador para la multiplicación por un escalar.
    Vector2 operator*(float scalar) const {
        return Vector2(x * scalar, y * scalar);
    }

    // Sobrecarga del operador / para la división por un escalar.
    Vector2 operator/(float scalar) const {
        if (scalar != 0) {
            return Vector2(x / scalar, y / scalar);
        }
        return Vector2(0, 0); // Manejo de división por cero
    }

    // Sobrecarga del operador /= para la división por un escalar.
    Vector2& operator/=(float scalar) {
        if (scalar != 0) {
            x /= scalar;
            y /= scalar;
        }
        else {
            // Manejo de división por cero
            x = 0;
            y = 0;
        }
        return *this;
    }

    /**
     * @brief Calcula la magnitud del vector.
     * La magnitud se calcula como la raíz cuadrada de la suma de los cuadrados de sus componentes.
     */
    float magnitude() const {
        return MathEngine::sqrt(x * x + y * y);
    }

    /**
     * @brief Método para normalizar el vector.
     * Devuelve un vector en la misma dirección pero con magnitud 1.
     * Si el vector tiene magnitud 0, devuelve un vector con componentes (0, 0).
     */
    Vector2 normalize() const {
        float mag = magnitude();
        if (mag == 0) {
            return Vector2(0, 0);
        }
        return *this / mag; // Devuelve un vector normalizado.
    }

    /**
     * @brief Normaliza el vector en el lugar (modifica el objeto actual).
     * Si el vector tiene magnitud 0, no hace nada.
     */
    void normalizeInPlace() {
        float mag = magnitude();
        if (mag != 0) {
            x /= mag;
            y /= mag;
        }
    }

    // Método para devolver un puntero a los datos no constantes.
    float* data() {
        return &x;
    }

    // Método para devolver un puntero a los datos constantes.
    const float* data() const {
        return &x;
    }
};
