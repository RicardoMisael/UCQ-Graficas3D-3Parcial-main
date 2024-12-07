#pragma once
#include "MathEngine.h"
#include "Vector3.h"

class Quaternion {
public:
    // Componentes del cuaternión.
    float w, x, y, z;

    /**
     * @brief Constructor por defecto.
     * Inicializa el cuaternión como un vector nulo (0, 0, 0, 0).
     */
    Quaternion() : w(0), x(0), y(0), z(0) {}

    /**
     * @brief Constructor parametrizado.
     * @param w Componente escalar.
     * @param x Componente vectorial en el eje X.
     * @param y Componente vectorial en el eje Y.
     * @param z Componente vectorial en el eje Z.
     */
    Quaternion(float w, float x, float y, float z) : w(w), x(x), y(y), z(z) {}

    /**
     * @brief Constructor a partir de un ángulo y un eje de rotación.
     * @param angle Ángulo de rotación en radianes.
     * @param axis Eje de rotación representado como un vector 3D.
     */
    Quaternion(float angle, const Vector3& axis) {
        float halfAngle = angle / 2.0f;
        float sinHalfAngle = MathEngine::sin(halfAngle);
        w = MathEngine::cos(halfAngle);
        x = axis.x * sinHalfAngle;
        y = axis.y * sinHalfAngle;
        z = axis.z * sinHalfAngle;
    }

    // Operador de suma.
    Quaternion operator+(const Quaternion& other) const {
        return Quaternion(w + other.w, x + other.x, y + other.y, z + other.z);
    }

    // Operador de resta.
    Quaternion operator-(const Quaternion& other) const {
        return Quaternion(w - other.w, x - other.x, y - other.y, z - other.z);
    }

    // Operador de multiplicación por un escalar.
    Quaternion operator*(float scalar) const {
        return Quaternion(w * scalar, x * scalar, y * scalar, z * scalar);
    }

    // Operador de multiplicación entre cuaterniones.
    Quaternion operator*(const Quaternion& other) const {
        return Quaternion(
            w * other.w - x * other.x - y * other.y - z * other.z,
            w * other.x + x * other.w + y * other.z - z * other.y,
            w * other.y - x * other.z + y * other.w + z * other.x,
            w * other.z + x * other.y - y * other.x + z * other.w
        );
    }

    /**
     * @brief Calcula la magnitud del cuaternión.
     * @return Magnitud del cuaternión.
     */
    float magnitude() const {
        return MathEngine::sqrt(w * w + x * x + y * y + z * z);
    }

    /**
     * @brief Normaliza el cuaternión.
     * @return Cuaternión normalizado con magnitud 1.
     */
    Quaternion normalize() const {
        float mag = magnitude();
        return mag != 0 ? Quaternion(w / mag, x / mag, y / mag, z / mag) : Quaternion(0, 0, 0, 0);
    }

    /**
     * @brief Calcula el conjugado del cuaternión.
     * @return Conjugado del cuaternión.
     */
    Quaternion conjugate() const {
        return Quaternion(w, -x, -y, -z);
    }

    /**
     * @brief Calcula el inverso del cuaternión.
     * @return Cuaternión inverso.
     */
    Quaternion inverse() const {
        float magSquared = w * w + x * x + y * y + z * z;
        return magSquared != 0 ? conjugate() * (1.0f / magSquared) : Quaternion(0, 0, 0, 0);
    }

    /**
     * @brief Rota un vector utilizando el cuaternión.
     * @param v Vector 3D a rotar.
     * @return Vector rotado.
     */
    Vector3 rotate(const Vector3& v) const {
        Quaternion qv(0, v.x, v.y, v.z);
        Quaternion result = (*this) * qv * this->inverse();
        return Vector3(result.x, result.y, result.z);
    }

    /**
     * @brief Obtiene un puntero no constante a los datos del cuaternión.
     * @return Puntero a los componentes del cuaternión.
     */
    float* data() {
        return &w;
    }

    /**
     * @brief Obtiene un puntero constante a los datos del cuaternión.
     * @return Puntero constante a los componentes del cuaternión.
     */
    const float* data() const {
        return &w;
    }
};
