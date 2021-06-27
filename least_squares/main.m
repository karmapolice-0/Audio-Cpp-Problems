n = 8;
x = [1, -2, 5, 7, 9];
y = [0, 3, 3, -4, 5];

Coefficients = leastSquares(x, y, n);

x1 = [];
y1 = [];
for i = -10 : 0.1 : 10
    y1 = [y1 polyval(Coefficients, i)];
    x1 = [x1 i];
end

plot(x1, y1)
hold on
plot(x, y, 'bo')
grid on
axis([-11 10 -11 10])