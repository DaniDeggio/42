import csv
import matplotlib.pyplot as plt
import numpy as np

def train(dataset, iterations, learning_rate, fig, line, x_vals):
    mileages = [row[0] for row in dataset]
    min_mileage = min(mileages)
    max_mileage = max(mileages)
    range_mileage = max_mileage - min_mileage
    
    if range_mileage == 0:
        range_mileage = 1.0

    normalized_dataset = []
    for mileage, price in dataset:
        norm_mileage = (mileage - min_mileage) / range_mileage
        normalized_dataset.append((norm_mileage, price))

    theta_0 = 0.0
    theta_1 = 0.0
    m = len(normalized_dataset)
    
    for epoch in range(iterations):
        sum_error = 0.0
        sum_error_w = 0.0

        if epoch % 20 == 0:
            tmp_t1 = theta_1 / range_mileage
            tmp_t0 = theta_0 - theta_1 * (min_mileage / range_mileage)
            line.set_ydata(tmp_t0 + tmp_t1 * x_vals)
            fig.canvas.draw()
            fig.canvas.flush_events()

        for norm_mileage, price in normalized_dataset:
            # Current prediction
            prediction = theta_0 + (theta_1 * norm_mileage)
            
            # Error
            error = prediction - price
            
            # Sum of errors
            sum_error += error
            sum_error_w += error * norm_mileage

        # Update theta_0 and theta_1 simultaneously
        theta_0 -= learning_rate * (1/m) * sum_error
        theta_1 -= learning_rate * (1/m) * sum_error_w

    # Denormalise theta parameters to match the original dataset scale
    theta_1_real = theta_1 / range_mileage
    theta_0_real = theta_0 - theta_1 * (min_mileage / range_mileage)

    return theta_0_real, theta_1_real

def load_dataset():
    try:
        with open("data.csv", "r") as f:
            reader = csv.reader(f)
            next(reader)
            dataset = []
            for row in reader:
                dataset.append((float(row[0]), float(row[1])))
    except:
        print("Dataset not found")
        return None
    return dataset


def save_model(theta_0, theta_1):
    with open("model.csv", "w") as f:
        writer = csv.writer(f)
        writer.writerow([theta_0, theta_1])

if __name__ == "__main__":
    dataset = load_dataset()
    if dataset is None:
        exit(1)
    print("Dataset loaded")

    plt.ion()
    
    mileages = [row[0] for row in dataset]
    prices = [row[1] for row in dataset]
    
    x_vals = np.linspace(min(mileages), max(mileages), 100)
    fig, ax = plt.subplots()
    line, = ax.plot(x_vals, np.zeros_like(x_vals), color='red')

    plt.scatter(mileages, prices)
    
    print("Starting training")
    theta_0, theta_1 = train(dataset, 3000, 0.1, fig, line, x_vals)
    print(f"Training completed, theta_0: {theta_0}, theta_1: {theta_1}")

    plt.ioff()
    plt.show()
    
    save_model(theta_0, theta_1)