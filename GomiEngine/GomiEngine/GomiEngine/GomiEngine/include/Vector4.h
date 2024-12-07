#pragma once
#include "MathEngine.h"

class Vector4 {
public:

    // Valores de las coordenadas x, y, z y w.
    float x, y, z, w;

    /**
     * @brief Constructor por defecto
     * Inicializa las coordenadas del vector a 0.
     */
    Vector4() : x(0), y(0), z(0), w(0) {}

    /**
     * @brief Constructor parametrizado.
     * Inicializa las coordenadas del vector con los valores dados.
     */
    Vector4(float xVal, float yVal, float zVal, float wVal) : x(xVal), y(yVal), z(zVal), w(wVal) {}

    // Sobrecarga del operador para la suma de 2 vectores.
    Vector4 operator+(const Vector4& other) const {
        return Vector4(x + other.x, y + other.y, z + other.z, w + other.w);
    }

    // Sobrecarga del operador para la resta de 2 vectores.
    Vector4 operator-(const Vector4& other) const {
        return Vector4(x - other.x, y - other.y, z - other.z, w - other.w);
    }

    // Sobrecarga del operador para la multiplicación de un vector por un escalar.
    Vector4 operator*(float scalar) const {
        return Vector4(x * scalar, y * scalar, z * scalar, w * scalar);
    }

    // Sobrecarga del operador para la división de un vector por un escalar.
    Vector4 operator/(float scalar) const {
        if (scalar != 0) {
            return Vector4(x / scalar, y / scalar, z / scalar, w / scalar);
        }
        return Vector4(0, 0, 0, 0); // Manejo de división por cero
    }

    /**
     * @brief Calcula la magnitud del vector.
     * La magnitud se calcula como la raíz cuadrada de la suma de los cuadrados de sus componentes.
     */
    float magnitude() const {
        return MathEngine::sqrt(x * x + y * y + z * z + w * w);
    }

    /**
     * @brief Método para normalizar el vector.
     * Devuelve un vector en la misma dirección pero con magnitud 1.
     * Si el vector tiene magnitud 0, devuelve un vector con componentes (0, 0, 0, 0).
     */
    Vector4 normalize() const {
        float mag = magnitude();
        if (mag == 0) {
            return Vector4(0, 0, 0, 0);
        }
        return Vector4(x / mag, y / mag, z / mag, w / mag);
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
            z /= mag;
            w /= mag;
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
