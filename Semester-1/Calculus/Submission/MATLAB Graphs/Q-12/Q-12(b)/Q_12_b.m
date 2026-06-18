x=0:0.1:7;
y=log(x);
plot(x,y)
grid on
hold on

x=2:0.1:7;
y=log(x-2);
plot(x,y)

y=log(x-2)-1;
plot(x,y)

title("Question-12 (b)")