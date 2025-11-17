import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.tree import DecisionTreeClassifier, export_text
from sklearn.metrics import accuracy_score, confusion_matrix
import joblib

# Load dataset
df = pd.read_csv("combined_420.csv")

# Features and labels
X = df[["Distance", "IR"]]
y = df["Final_Class"]

# Split into training/test
X_train, X_test, y_train, y_test = train_test_split(
    X, y, test_size=0.2, random_state=42, stratify=y)

# Train model
model = DecisionTreeClassifier(max_depth=5)  # tuned depth
model.fit(X_train, y_train)

# Predictions
y_pred = model.predict(X_test)

# Accuracy
acc = accuracy_score(y_test, y_pred)
print(f"\n✅ Model Accuracy: {acc*100:.2f}%")

# Confusion Matrix
print("\n✅ Confusion Matrix:")
print(confusion_matrix(y_test, y_pred))

# Text rules for human reading
rules = export_text(model, feature_names=list(X.columns))
print("\n✅ Decision Tree Rules:\n")
print(rules)

# Save readable rules to text file
with open("tree_rules.txt", "w") as f:
    f.write(rules)

print("\n✅ tree_rules.txt exported successfully!")

# Save model
joblib.dump(model, "railway_model.pkl")
print("\n✅ Model saved as railway_model.pkl")
