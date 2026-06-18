e=2.718281828;
x=-4:0.1:7;
y=power(e,-x);
plot(x,y)
grid on
hold on
y=(1/2)*power(e,-x);
plot(x,y)

y=(1/2)*power(e,-x)-1;
plot(x,y)

title("Question-12 (a)")