import matplotlib.pyplot as plt
import numpy as np

# Actual distances (in centimeters)
actual_distance = np.array([20, 40, 60, 80, 100, 120, 140, 160, 180, 200,
                            220, 240, 260, 280, 300, 320, 340, 360, 380, 400,
                            420, 440, 460, 480, 500, 520, 540, 560, 580, 600,
                            620, 640, 660, 680, 700, 720, 740, 760])

# UWB measured distances (in centimeters)
uwb_distance = np.array([19, 50, 77, 100, 103, 125, 142, 167, 185, 210,
                         225, 249, 274, 297, 307, 339, 348, 380, 385, 414,
                         441, 466, 486, 515, 546, 555, 575, 588, 636, 631,
                         656, 711, 721, 735, 759, 785, 796, 827])

# --- Error Calculations ---
# Absolute Error
uwb_error = np.abs(uwb_distance - actual_distance)

# Squared Error
uwb_squared_error = (uwb_distance - actual_distance) ** 2

# Mean Squared Error (MSE)
uwb_mse = np.mean(uwb_squared_error)

# Root Mean Squared Error (RMSE)
uwb_rmse = np.sqrt(uwb_mse)

# --- Output ---
print("Squared Error for each point:\n", uwb_squared_error)
print("\nMean Squared Error (MSE):", uwb_mse)
print("Root Mean Squared Error (RMSE):", uwb_rmse)

# --- Plotting Squared Error vs Distance ---
plt.figure(figsize=(8, 5))
plt.plot(actual_distance, uwb_squared_error, 'o-', linewidth=2)
plt.xlabel("Actual Distance (cm)")
plt.ylabel("Squared Error (cm²)")
plt.title("Squared Error vs Actual Distance (UWB)")
plt.grid(True)
plt.tight_layout()
plt.show()
