#pragma once
namespace EngineUtilities {
   /**
   * Clase TStaticPtr para manejo de un puntero est�tico.
   *
   * La clase TStaticPtr gestiona un �nico objeto est�tico y proporciona m�todos
   * para acceder al objeto, verificar si el puntero es nulo y realizar operaciones
   * b�sicas de manejo de memoria.
   */
    template<typename T>
    class TStaticPtr
    {
    public:
        // Inicializa el puntero est�tico al objeto.
        TStaticPtr() = default;

        // Constructor que toma un puntero crudo.
        explicit TStaticPtr(T* rawPtr)
        {
            if (instance != nullptr)
            {
                delete instance;
            }
            instance = rawPtr;
        }

        //  Destructor.
        ~TStaticPtr()
        {
            if (instance != nullptr)
            {
                delete instance;
                instance = nullptr;
            }
        }

        // Obtener el puntero crudo.
        static T* get()
        {
            return instance;
        }

        // Verificar si el puntero es nulo.
        static bool isNull()
        {
            return instance == nullptr;
        }

        // Reiniciar el puntero est�tico con un nuevo objeto.
        static void reset(T* rawPtr = nullptr)
        {
            if (instance != nullptr)
            {
                delete instance;
            }
            instance = rawPtr;
        }

    private:
        // Puntero est�tico al objeto gestionado.
        static T* instance; 
    };

}