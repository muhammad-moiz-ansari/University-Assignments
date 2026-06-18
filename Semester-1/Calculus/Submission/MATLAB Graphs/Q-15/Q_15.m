dx = 0.23;
x = -7+dx:pi/100:7-dx;
y = tan(x);
plot(x,y)
hold on
grid on
y=cot(x);
plot(x,y)
hold off