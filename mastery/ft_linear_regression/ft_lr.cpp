#include "ft_lr.h"

float min_mil(t_data *dataset, long size) {
    float min = dataset[0].mileage;
    for (long i = 1; i < size; i++){
        if (dataset[i].mileage < min)
            min = dataset[i].mileage;
    }
    return min;
}

float max_mil(t_data *dataset, long size) {
    float max = dataset[0].mileage;
    for (long i = 1; i < size; i++){
        if (dataset[i].mileage > max)
            max = dataset[i].mileage;
    }
    return max;
}

FT_LR::FT_LR() {
    this->theta0 = 0.0f;
    this->theta1 = 0.0f;
    this->learning_rate = 0.01f;
    this->iterations = 1000;
}

FT_LR::~FT_LR() {
}

void FT_LR::train(t_data *dataset, long size, int epochs, float learning_rate) {
    float sum_error = 0;
    float sum_error_w = 0;
    float prediction = 0;
    float min_milage = min_mil(dataset, size);
    float max_milage = max_mil(dataset, size);
    float range_milage = max_milage - min_milage;

    if (range_milage == 0)
        range_milage = 1;

    t_data *normalized_dataset = new t_data[size];
    for (long i = 0; i < size; i++){
        normalized_dataset[i].mileage = (dataset[i].mileage - min_milage) / range_milage;
        normalized_dataset[i].price = dataset[i].price;
    }

    for (long i = 0; i < size; i++){
        sum_error = 0;
        sum_error_w = 0;

        for (int j = 0; j < epochs; j++){
            prediction = this->theta0 + this->theta1 * dataset[i].mileage;
            sum_error += prediction - dataset[i].price;
            sum_error_w += (prediction - dataset[i].price) * dataset[i].mileage;
        }
        this->theta0 -= learning_rate * (sum_error / size);
        this->theta1 -= learning_rate * (sum_error_w / size);
    }

    this->theta0 = this->theta0 - this->theta1 * (min_milage / range_milage);
    this->theta1 = this->theta1 / range_milage;
    delete[] normalized_dataset;
}

float FT_LR::fit(float mil) {
    return this->theta0 + this->theta1 * mil;
}

float* FT_LR::get_thetas() {
    float *thetas = new float[2];
    thetas[0] = this->theta0;
    thetas[1] = this->theta1;
    return thetas;
}
