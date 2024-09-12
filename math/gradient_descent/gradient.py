import numpy as np
import matplotlib.pyplot as plt


class BatchGD:
    def __init__(self, learn_rate=0.001, n_iter=10_000, tolerance=1e-6, epoch=100):
        self.learn_rate = learn_rate
        self.n_iter = n_iter
        self.tolerance = tolerance
        self.epoch = epoch
        self.weights = self.bias = None
        self.cost = []
        self._n_iter_arr = np.arange(self.epoch)

    def fit(self, X, y):
        self.cost = []
        m = X.shape[0]  # no. of samples
        n = X.shape[1]  # no. of features or weights

        self.weights = np.random.random(n)
        self.bias = np.random.random()

        for i in range(self.n_iter):
            y_pred = self.predict(X)

            dw = np.dot(y_pred - y, X) / m
            db = np.mean(y_pred - y)

            if i % self.epoch == 0:
                mse = np.mean(np.square(y_pred - y)) / 2
                self.cost.append(mse)

            self.weights += -self.learn_rate * dw
            self.bias += -self.learn_rate * db

    def show_cost_plot(self):
        if self.cost:
            plt.plot(self.cost)
            plt.xlabel("No. of iterations")
            plt.ylabel("Cost")
            plt.show()

    def predict(self, X):
        return np.dot(X, self.weights) + self.bias

    def cost_function(self, X, y):
        y_pred = self.predict(X)
        mse = np.mean(np.square(y_pred - y)) / 2
        return mse


def show_plot(cost, n_iter, epoch):
    plt.plot(np.arange(0, n_iter, epoch), cost)
    plt.show()


rng = np.random.RandomState(seed=42)
# Input data
X = np.array([[1, 2, 3, 4]]).T  # (mxn)
X = rng.randint(-10, 10, size=100).reshape(-1, 1)
print(X.shape)
y = np.dot(X, [8.9]) + 4 + rng.random(size=X.shape[0]) * \
    2.4 + rng.random(size=X.shape[0])*7.8  # (mx1)

model = BatchGD()
model.fit(X, y)
print(model.weights, model.bias)
# model.show_cost_plot()

plt.plot(X.flatten(), y, "o")
plt.show()
