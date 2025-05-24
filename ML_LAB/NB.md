To implement a **Naive Bayes classifier from scratch** for your dataset, we'll follow this plan:

---

### ✅ **Plan**

1. **Preprocess Data**: Encode ordinal and nominal attributes.
2. **Calculate Priors**: Frequency of each target class.
3. **Calculate Likelihoods**:

   * For **categorical features**: Use frequency counts.
   * For **numerical features**: Use Gaussian likelihood (mean & variance).
4. **Prediction**:

   * Use Bayes' theorem:

     $$
     P(C|X) \propto P(C) \prod_{i=1}^{n} P(x_i | C)
     $$

---

### ✅ **Step-by-Step Implementation**

#### 🔹 Step 1: Preprocess the Data (Same as Before)

```python
import pandas as pd
import numpy as np
from collections import defaultdict
import math

# Ordinal/Nominal Encoding
ordinal_encodings = {
    'lab_hours_per_week': {'Low': 0, 'Medium': 1, 'High': 2},
    'lab_discipline_score': {'Poor': 0, 'Average': 1, 'Good': 2, 'Excellent': 3},
    'previous_semester_performance': {'Low': 0, 'Medium': 1, 'High': 2},
    'study_performance_category': {'Weak': 0, 'Average': 1, 'Strong': 2},
    'project_submission': {'Not Submitted': 0, 'Late': 1, 'On-Time': 2},
}

# Dataset
data = [
    ["S01", 92, "High", "On-Time", "Excellent", "High", "Strong"],
    ["S02", 76, "Medium", "Late", "Average", "Medium", "Average"],
    ["S03", 88, "High", "On-Time", "Good", "High", "Strong"],
    ["S04", 65, "Low", "Not Submitted", "Poor", "Low", "Weak"],
    ["S05", 70, "Medium", "Late", "Average", "Medium", "Average"],
    ["S06", 95, "High", "On-Time", "Excellent", "High", "Strong"],
    ["S07", 60, "Low", "Not Submitted", "Poor", "Low", "Weak"],
    ["S08", 85, "Medium", "On-Time", "Good", "Medium", "Average"],
    ["S09", 90, "High", "Late", "Good", "High", "Strong"],
    ["S10", 72, "Medium", "On-Time", "Average", "Medium", "Average"],
]

columns = ["student_id", "attendance", "lab_hours_per_week", "project_submission", 
           "lab_discipline_score", "previous_semester_performance", "study_performance_category"]

df = pd.DataFrame(data, columns=columns)

# Apply Encoding
for col, mapping in ordinal_encodings.items():
    df[col] = df[col].map(mapping)

df = df.drop(columns=["student_id"])
```

---

### ✅ Step 2: Train Naive Bayes Classifier

```python
class NaiveBayesClassifier:
    def fit(self, X, y):
        self.classes = np.unique(y)
        self.priors = {}
        self.means = {}
        self.variances = {}
        self.likelihoods = {}

        for cls in self.classes:
            X_c = X[y == cls]
            self.priors[cls] = len(X_c) / len(X)

            self.means[cls] = X_c.mean(numeric_only=True)
            self.variances[cls] = X_c.var(numeric_only=True)

            self.likelihoods[cls] = {}
            for col in X.columns:
                if X[col].dtype == 'int64' and col != "attendance":
                    self.likelihoods[cls][col] = X_c[col].value_counts(normalize=True).to_dict()

    def gaussian_prob(self, x, mean, var):
        eps = 1e-6  # prevent division by zero
        coef = 1.0 / math.sqrt(2 * math.pi * var + eps)
        exponent = math.exp(-(x - mean)**2 / (2 * var + eps))
        return coef * exponent

    def predict(self, X):
        predictions = []
        for _, x in X.iterrows():
            posteriors = {}
            for cls in self.classes:
                prior = math.log(self.priors[cls])
                total = prior

                for col in X.columns:
                    val = x[col]
                    if col == "attendance":
                        # numerical Gaussian
                        mean = self.means[cls][col]
                        var = self.variances[cls][col]
                        total += math.log(self.gaussian_prob(val, mean, var))
                    else:
                        # categorical
                        likelihoods = self.likelihoods[cls].get(col, {})
                        prob = likelihoods.get(val, 1e-6)
                        total += math.log(prob)

                posteriors[cls] = total

            predictions.append(max(posteriors, key=posteriors.get))
        return predictions
```

---

### ✅ Step 3: Use It

```python
X_train = df.drop(columns=["study_performance_category"])
y_train = df["study_performance_category"]

nb = NaiveBayesClassifier()
nb.fit(X_train, y_train)
```

---

### ✅ Step 4: Test on the Test Dataset

```python
test_data = [
    ["T01", 80, "Medium", "On-Time", "Good", "Medium", "Average"],
    ["T02", 67, "Low", "Late", "Poor", "Low", "Weak"],
    ["T03", 93, "High", "On-Time", "Excellent", "High", "Strong"],
    ["T04", 78, "Medium", "Late", "Average", "Medium", "Average"],
    ["T05", 89, "High", "On-Time", "Good", "High", "Strong"],
]

test_df = pd.DataFrame(test_data, columns=columns)
for col, mapping in ordinal_encodings.items():
    test_df[col] = test_df[col].map(mapping)

X_test = test_df.drop(columns=["student_id", "study_performance_category"])
y_test = test_df["study_performance_category"]

y_pred = nb.predict(X_test)

print("Predicted:", y_pred)
print("Actual:   ", list(y_test))
```

---

### ✅ Output Example

You should see something like:

```
Predicted: [1, 0, 2, 1, 2]  # (Ordinal codes for Average, Weak, Strong)
Actual:    [1, 0, 2, 1, 2]
```
