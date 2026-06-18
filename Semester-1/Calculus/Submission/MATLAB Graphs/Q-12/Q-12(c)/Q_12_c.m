x=-4:0.1:4;
y=sqrt(power(x,2));
plot(x,y)
grid on
hold on

y=sqrt(power((x-1),2));
plot(x,y)

x=0:0.1:2;
y=sqrt(1-power((x-1),2));
plot(x,y)

y=2+sqrt(1-power((x-1),2));
plot(x,y)

title("Question-12 (c)")