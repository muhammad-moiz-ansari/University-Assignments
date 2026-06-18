x=0:0.1:20;
y=sqrt(x);
plot(x,y)
grid on
hold on

x=-20:0.1:0;
y=sqrt(-x);
plot(x,y)

y=-sqrt(-x);
plot(x,y)

x=-20:0.1:-2;
y=-sqrt(-x-2);
plot(x,y)

y=-2*sqrt(-x-2);
plot(x,y)