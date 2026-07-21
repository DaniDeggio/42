import csv

def load_dataset():
    with open("data.csv", "r") as f:
        reader = csv.reader(f)
        next(reader)
        dataset = []
        for row in reader:
            dataset.append((float(row[0]), float(row[1])))
    return dataset

def load_model():
    theta_0 = 0.0
    theta_1 = 0.0
    try:
        with open("model.csv", "r") as f:
            reader = csv.reader(f)
            for row in reader:
                theta_0 = float(row[0])
                theta_1 = float(row[1])
    except:
        pass
    return theta_0, theta_1

def predict(X, theta_0, theta_1):
    return theta_0 + theta_1 * X

def check_precision(theta_0, theta_1, dataset):

    # MAE
    mean_error = 0.0    
    for mileage, price in dataset:
        mean_error += predict(mileage, theta_0, theta_1) - price
    mean_error /= len(dataset)
    print(f"MAE error: {mean_error}")

    # RMSE
    rmse_error = 0.0
    for mileage, price in dataset:
        rmse_error += (predict(mileage, theta_0, theta_1) - price) ** 2
    rmse_error = rmse_error / len(dataset)
    rmse_error = rmse_error ** 0.5
    print(f"RMSE error: {rmse_error}")

if __name__ == "__main__":
    theta_0, theta_1 = load_model()
    dataset = load_dataset()

    check_precision(theta_0, theta_1, dataset)