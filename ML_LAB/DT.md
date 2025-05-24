
### 📘 **Training Dataset (10 Points)**

| student\_id | attendance | lab\_hours\_per\_week | project\_submission | lab\_discipline\_score | previous\_semester\_performance | study\_performance\_category |
| ----------- | ---------- | --------------------- | ------------------- | ---------------------- | ------------------------------- | ---------------------------- |
| S01         | 92         | High                  | On-Time             | Excellent              | High                            | Strong                       |
| S02         | 76         | Medium                | Late                | Average                | Medium                          | Average                      |
| S03         | 88         | High                  | On-Time             | Good                   | High                            | Strong                       |
| S04         | 65         | Low                   | Not Submitted       | Poor                   | Low                             | Weak                         |
| S05         | 70         | Medium                | Late                | Average                | Medium                          | Average                      |
| S06         | 95         | High                  | On-Time             | Excellent              | High                            | Strong                       |
| S07         | 60         | Low                   | Not Submitted       | Poor                   | Low                             | Weak                         |
| S08         | 85         | Medium                | On-Time             | Good                   | Medium                          | Average                      |
| S09         | 90         | High                  | Late                | Good                   | High                            | Strong                       |
| S10         | 72         | Medium                | On-Time             | Average                | Medium                          | Average                      |

---

### 📗 **Test Dataset (5 Points)**

| student\_id | attendance | lab\_hours\_per\_week | project\_submission | lab\_discipline\_score | previous\_semester\_performance | study\_performance\_category |
| ----------- | ---------- | --------------------- | ------------------- | ---------------------- | ------------------------------- | ---------------------------- |
| T01         | 80         | Medium                | On-Time             | Good                   | Medium                          | Average                      |
| T02         | 67         | Low                   | Late                | Poor                   | Low                             | Weak                         |
| T03         | 93         | High                  | On-Time             | Excellent              | High                            | Strong                       |
| T04         | 78         | Medium                | Late                | Average                | Medium                          | Average                      |
| T05         | 89         | High                  | On-Time             | Good                   | High                            | Strong                       |

---

To build a **decision tree from scratch** in Python using the dataset you provided, we’ll follow these steps:

---

### ✅ **Steps to Build the Decision Tree:**

1. **Preprocess the data**: Convert categorical and ordinal values to numeric codes.
2. **Define utility functions**:

   * Entropy
   * Information Gain
3. **Build the tree recursively**:

   * Select the best attribute (highest information gain)
   * Create subtrees
4. **Predict new samples using the tree**

---

### ✅ **Step 1: Preprocess the Data**

Let’s first convert the ordinal and nominal attributes into numeric form. We'll encode the values in order if they are ordinal, and arbitrary if nominal.

```python
import pandas as pd
import numpy as np
from collections import Counter
import math

# Ordinal/Nominal Encodings
ordinal_encodings = {
    'lab_hours_per_week': {'Low': 0, 'Medium': 1, 'High': 2},
    'lab_discipline_score': {'Poor': 0, 'Average': 1, 'Good': 2, 'Excellent': 3},
    'previous_semester_performance': {'Low': 0, 'Medium': 1, 'High': 2},
    'study_performance_category': {'Weak': 0, 'Average': 1, 'Strong': 2},
    'project_submission': {'Not Submitted': 0, 'Late': 1, 'On-Time': 2},
}

# Training Data
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

# Convert to DataFrame
columns = ["student_id", "attendance", "lab_hours_per_week", "project_submission", 
           "lab_discipline_score", "previous_semester_performance", "study_performance_category"]
df = pd.DataFrame(data, columns=columns)

# Apply encoding
for col, mapping in ordinal_encodings.items():
    df[col] = df[col].map(mapping)

# Drop student_id (identifier)
df = df.drop(columns=["student_id"])
```

---

### ✅ **Step 2: Entropy and Information Gain**

```python
def entropy(y):
    counts = Counter(y)
    probabilities = [v / len(y) for v in counts.values()]
    return -sum(p * math.log2(p) for p in probabilities)

def info_gain(data, split_attr, target_attr):
    total_entropy = entropy(data[target_attr])
    values = data[split_attr].unique()
    weighted_entropy = 0

    for val in values:
        subset = data[data[split_attr] == val]
        weight = len(subset) / len(data)
        weighted_entropy += weight * entropy(subset[target_attr])
        
    return total_entropy - weighted_entropy
```

---

### ✅ **Step 3: Build the Decision Tree**

```python
def build_tree(data, features, target_attr):
    if len(set(data[target_attr])) == 1:
        return data[target_attr].iloc[0]

    if not features:
        return data[target_attr].mode()[0]

    gains = {feature: info_gain(data, feature, target_attr) for feature in features}
    best_feature = max(gains, key=gains.get)
    tree = {best_feature: {}}

    for val in sorted(data[best_feature].unique()):
        subset = data[data[best_feature] == val]
        subtree = build_tree(subset, [f for f in features if f != best_feature], target_attr)
        tree[best_feature][val] = subtree

    return tree
```

---

### ✅ **Step 4: Prediction Function**

```python
def predict(tree, sample):
    if not isinstance(tree, dict):
        return tree
    
    feature = next(iter(tree))
    feature_val = sample[feature]
    subtree = tree[feature].get(feature_val, None)
    
    if subtree is None:
        return None  # handle unknown value
    return predict(subtree, sample)
```

---

### ✅ **Build the Tree and Predict on Test Data**

```python
features = list(df.columns[:-1])
target = "study_performance_category"
tree = build_tree(df, features, target)

print("Decision Tree:\n", tree)
```

---

### ✅ **Evaluate on Test Data**

Now you can create the test set, encode it, and run predictions similarly.
