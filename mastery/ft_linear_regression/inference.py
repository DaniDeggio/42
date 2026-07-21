import csv

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
        print("Model not found, fallback to defaults")
    return theta_0, theta_1

def predict(X, theta_0, theta_1):
    return theta_0 + theta_1 * X

if __name__ == "__main__":
    theta_0, theta_1 = load_model()
    try:
        mileage = float(input("Enter a mileage: "))
        print(f"Predicted price: {predict(mileage, theta_0, theta_1)}")
    except ValueError:
        print("Invalid input. Please enter a number.")