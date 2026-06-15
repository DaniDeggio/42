
#ifndef FT_LR_H
# define FT_LR_H

#include <pybind11/pybind11.h>

namespace py = pybind11;

typedef struct s_data {
    float mileage;
    float price;
} t_data;

class FT_LR {
    private:
        float theta0;
        float theta1;
        float learning_rate;
        int iterations;
        
    public:
        FT_LR();
        ~FT_LR();
        void train(t_data *dataset, long size, int epochs, float learning_rate);
        float fit(float mil);
        float* get_thetas();
};

#endif