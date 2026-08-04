import csv
import argparse

def load_model(filepath="model.csv"):
    theta_0 = 0.0
    theta_1 = 0.0
    try:
        with open(filepath, "r") as f:
            reader = csv.reader(f)
            for row in reader:
                theta_0 = float(row[0])
                theta_1 = float(row[1])
    except:
        print(f"Model file '{filepath}' not found, fallback to defaults")
    return theta_0, theta_1

def predict(X, theta_0, theta_1):
    return theta_0 + theta_1 * X

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Predict car price using trained linear regression model.")
    parser.add_argument("-m", "--model", type=str, default="model.csv",
                        help="Percorso del file dei pesi del modello (default: model.csv)")
    args = parser.parse_args()

    theta_0, theta_1 = load_model(args.model)
    try:
        mileage = float(input("Enter a mileage: "))
        print(f"Predicted price: {predict(mileage, theta_0, theta_1)}")
    except ValueError:
        print("Invalid input. Please enter a number.")