#!/usr/bin/env python3
import csv
import argparse

def load_dataset(filepath="data.csv"):
    try:
        with open(filepath, "r") as f:
            reader = csv.reader(f)
            next(reader)
            dataset = []
            for row in reader:
                dataset.append((float(row[0]), float(row[1])))
    except Exception as e:
        print(f"Error loading dataset '{filepath}': {e}")
        return None
    return dataset

def load_model(filepath="model.csv"):
    theta_0 = 0.0
    theta_1 = 0.0
    try:
        with open(filepath, "r") as f:
            reader = csv.reader(f)
            for row in reader:
                theta_0 = float(row[0])
                theta_1 = float(row[1])
    except Exception as e:
        print(f"Model file '{filepath}' not found, fallback to defaults: {e}")
    return theta_0, theta_1

def predict(X, theta_0, theta_1):
    return theta_0 + theta_1 * X

def check_precision(theta_0, theta_1, dataset):
    prices = [price for _, price in dataset]
    mean_price = sum(prices) / len(prices)

    mae = 0.0
    mse = 0.0
    ss_tot = 0.0

    for mileage, price in dataset:
        prediction = predict(mileage, theta_0, theta_1)
        error = prediction - price
        mae += abs(error)
        mse += error ** 2
        ss_tot += (price - mean_price) ** 2

    mae /= len(dataset)
    mse /= len(dataset)
    rmse = mse ** 0.5
    r2 = 1.0 - (mse * len(dataset) / ss_tot) if ss_tot != 0 else 0.0

    print(f"MAE (Mean Absolute Error): {mae:.4f}")
    print(f"RMSE (Root Mean Squared Error): {rmse:.4f}")
    print(f"R² Score: {r2:.4f} ({r2 * 100:.2f}%)")

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Evaluate precision metrics for linear regression model.")
    parser.add_argument("-d", "--dataset", type=str, default="data.csv",
                        help="Percorso del file CSV contenente il dataset (default: data.csv)")
    parser.add_argument("-m", "--model", type=str, default="model.csv",
                        help="Percorso del file dei pesi del modello (default: model.csv)")
    args = parser.parse_args()

    theta_0, theta_1 = load_model(args.model)
    dataset = load_dataset(args.dataset)
    if dataset is None:
        exit(1)
    
    check_precision(theta_0, theta_1, dataset)