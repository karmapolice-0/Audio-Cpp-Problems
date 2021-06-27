function Coefficients = leastSquares(x, y, n)
    X = [];
    for j = 1: length(x)
        row = []
        for i = n : -1 : 0
            row = [row x(j).^i];
        end
        X = [X; row];
    end
    % СЛАУ XX'b = X'y', b = Coefficients
    Coefficients = (linsolve((X' * X), (X' * y')))';
end